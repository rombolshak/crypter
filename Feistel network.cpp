/**
 * @version 1.0
 * 
 * This file is part of cmc2011RM blockcrypt.
 * 
 * cmc2011RM blockcrypt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cmc2011RM blockcrypt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cmc2011RM blockcrypt.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Feistel network.h"

#include <string>

pair<string, bool> FNetwork::encrypt(const string _msg, const string key, bool enc)
{
    string msg = _msg;


    MD5 md(key);
    uint32_t h[4];
    md.getNumbers(h);
    fillRandArray(h[3]);

    int diff;
    string res = "";
    string crc = "";
    if (enc)
        res = crc32(msg);
    else
    {
        crc = msg.substr(0, 8);
        msg = msg.substr(8);
    }

    generateRoundKeys(msg, key);

    for (int i = 0; i < countBlocks(msg); ++i) {
        if ((diff = msg.substr(i * 16).length() - 16) < 0)
            for (int k = 0; k < -diff; ++k)
                msg += '\0';
        string s = msg.substr(i*16, 16);
        string L = s.substr(0, 8);
        string R = s.substr(8, 8);
        res += doCrypt(L,R,i,enc);
    }

    keys.clear();

    if (!enc)
    {
        string crcDec = crc32(res);

        if (crcDec != crc)
            return pair<string, bool>("", false);
    }
    return pair<string, bool>(res, true);
}

pair<string, bool> FNetwork::decrypt(const std::string msg, const std::string key)
{
    return encrypt(msg, key, false);
}

string FNetwork::doCrypt(const string _left, const string _right, int i, bool enc)
{
    string Li = _left, Ri = _right;
    for (
        int k = enc?0:roundsNo-1;
        enc?(k<roundsNo):(k>-1);
        enc?++k:--k
    )
    {
        string nL = Li, nR = Li;
        nL = F(keys[i * roundsNo + k], nL);
        nL = strxor(nL, Ri);
        Li = (k == (enc?(roundsNo - 1):0))?Li:nL;
        Ri = (k == (enc?(roundsNo - 1):0))?nL:nR;
    }
    return Li + Ri;
}

void FNetwork::fillRandArray(long unsigned int seed)
{
    randomizer.seed(seed);
    for (int i=0;i< 1<<24; ++i)
        R[i] = randomizer.next();
}

void FNetwork::generateRoundKeys(const string msg, const string key)
{
    int n = countBlocks(msg) * roundsNo;
    unsigned int h[4];

    string Kprev = key;
    stringstream st;

    MD5 m = MD5(Kprev);

    m.getNumbers(h);
    randomizer.seed(h[0]);

    for (int i=0;i<n;++i)
    {
        long unsigned int p1 = h[0] ^ randomizer.next(),
                               p2 = h[1] ^ randomizer.next(),
                                    p3 = h[2] ^ randomizer.next(),
                                         p4 = h[3] ^ randomizer.next();
        Kprev = "";
        st << hex << (p1^p4);
        while (st.str().length() < 8)
            st << '$';
        st << (p2^p3);
        while (st.str().length() < 16)
            st << '#';
        st >> Kprev;
        keys.push_back(Kprev);
        st.clear();
    }
}

inline string FNetwork::strxor(const string a, const string b)
{
    string c = "";
    int n = min(a.length(), b.length());
    for (int i=0;i<n;++i)
        c += a[i]^b[i];
    return c;
}

string FNetwork::F(const string key, const string left)
{
    stringstream st;

    unsigned int h[4];
    MD5 m = MD5(key + left);
    m.getNumbers(h);

    st << hex << R[h[3]%(1<<24)];
    while (st.str().length() < 8)
        st << '&';


    m = MD5(strxor(key, left));
    m.getNumbers(h);
    st << hex << R[h[3]%(1<<24)];

    while (st.str().length() < 16)
        st << '*';

    return st.str();
}

string FNetwork::crc32(const string _buf)
{
    uint32_t crc_table[256];
    uint32_t crc;

    string buf = _buf;
    size_t fst = buf.find_first_of('\0');
    buf = buf.substr(0, fst);

    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

        crc_table[i] = crc;
    };

    crc = 0xFFFFFFFFUL;

    int len = buf.length();
    int i = 0;

    while (len--)
        crc = crc_table[(crc ^ buf[i++]) & 0xFF] ^ (crc >> 8);

    crc ^= 0xFFFFFFFFUL;

    stringstream res;
    string _res = "";
    res << hex << crc;
    for (int diff = 8 - res.str().length(); diff > 0; --diff)
    {
        _res += '0';
    }
    _res += res.str();
    return _res;
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
