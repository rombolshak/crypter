#include "md5.h"

#include <sstream>
#include <vector>
#include <string>

using namespace std;

class FNetwork
{
    int roundsNo;
    vector<string> keys;
    int keyIndex;
    unsigned long R[1<<24];
    
    FNetwork(int roundsNo = 3) : roundsNo(roundsNo) {}
    
    string encrypt (string msg, string key);
	/* Дополнить сообщение (например \0 -ми)до длины кратной 16 символам (128 бит)
	 * Для каждого куска в 64 бита применить roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултата в строку.
	 * Вернуть эту строку
	 * */
    string decrypt (string msg, string key);
	/* Для каждого куска по 128 бит применить roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултата в строку (Ключи подаются в обратном порядке).
	 * Вернуть эту строку
	 * */
    
    void fillRandArray(unsigned long seed);
	/* Заполнить массив R сл. числами с порождающим
	 * элементом seed
	 * */
    inline int countBlocks(string msg)
    {
	int len = msg.length();
	return len%4 == 0 ? len/4 : len/4 + 1;
    }
    
    void generateRoundKeys();
 	/* Сгенерировать массив keys из (countBlocks*roundsNo) ключей. 
	* i-й ключ пердназнаечн для операций i/roundsNo -й строкой
	* на i%roundsNo -й итерации сети Фейстеля
	* */
    
    string strxor (string a, string b)
    {
	string c = "";
	int n = min(a.length(), b.length());
	for (int i=0;i<n;++i)
	    c += a[i]^b[i];
	return c;
    }
    
    inline string F (string key, string block)
    {
	string res = "";
	stringstream st(res);
	
	unsigned int h[4];
	MD5 m1 = MD5(key + block);
	m1.getNumbers(h);
	st << R[h[3]%(1<<24)];
	
	m1 = MD5(strxor(key, block));
	m1.getNumbers(h);
	st << R[h[3]%(1<<24)];
	return res;
    }

};