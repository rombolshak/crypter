#include "Feistel network.h"

#include <string>

string FNetwork::encrypt(const string _msg, const string key)
{
	string msg = _msg;
	
	generateRoundKeys(msg, key);
	
	MD5 md(key);
	uint32_t h[4];
	md.getNumbers(h);
	fillRandArray(h[3]);
	
	int diff;
	string res = "";
	for (int i = 0; i < countBlocks(msg); ++i) {
		if ((diff = msg.substr(i * 16).length() - 16) < 0) 
			for (int k = 0; k < -diff; ++k)
				msg += '\0';
		string s = msg.substr(i*16, 16);
		string L = s.substr(0, 8);
		string R = s.substr(8, 8);
		doCrypt(L,R,i);
		res += L; res += R;
	}
}

void FNetwork::doCrypt(string _left, string _right, int i)
{
	string Li = _left, Ri = _right;
	for (int k = 0; k < roundsNo; ++k) {
		string nL = Li, nR = Li;
		nL = F(keys[i * roundsNo +k], nL);
		nL = strxor(nL, Ri);
		Li = (k == roundsNo - 1)?Li:nL; 
		Ri = (k == roundsNo - 1)?nL:nR;
	}
	_left = Li; _right = Ri;
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
	st << hex << (p1^p4) << (p2^p3);
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
    string res = "";
    stringstream st;
    
    unsigned int h[4];
    MD5 m = MD5(key + left);
    m.getNumbers(h);
    st << hex << R[h[3]%(1<<24)];
    
    m = MD5(strxor(key, left));
    m.getNumbers(h);
    st << hex << R[h[3]%(1<<24)];
    st >> res;
    return res;
}