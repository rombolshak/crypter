#include "Feistel network.h"

#include <string>

string FNetwork::encrypt(const string _msg, const string key, bool enc)
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
		res += doCrypt(L,R,i,enc);
	}
	
	return res;
}

string FNetwork::decrypt(const std::string msg, const std::string key)
{
	return encrypt(msg, key, false);
}

string FNetwork::doCrypt(const string _left, const string _right, int i, bool enc)
{
	string Li = _left, Ri = _right;
	for (
		int k = enc?0:roundsNo-1;
		enc?(k<roundsNo):(k>-1);
		enc?++k:--k) {
		string nL = Li, nR = Li;
		nL = F(keys[i * roundsNo +k], nL);
		nL = strxor(nL, Ri);
		Li = (k == roundsNo - 1)?Li:nL; 
		Ri = (k == roundsNo - 1)?nL:nR;
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
	while (st.str().length() < 32)
	    st << '$';
	st << (p2^p3);
	while (st.str().length() < 64)
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
    //string res = "";
    stringstream st;
    
    unsigned int h[4];
    MD5 m = MD5(key + left);
    m.getNumbers(h);
    
    st << hex << R[h[3]%(1<<24)];
    while (st.str().length() < 32)
	    st << '&';
    
    
    m = MD5(strxor(key, left));
    m.getNumbers(h);
    st << hex << R[h[3]%(1<<24)];
    
    while (st.str().length() < 64)
	st << '*';
    
    //st >> res;
    return st.str();
}