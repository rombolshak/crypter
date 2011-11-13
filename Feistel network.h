#ifndef FEISTEL_NETWORK_H
#define FEISTEL_NETWORK_H

#include "md5.h"
#include "random.h"

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
    Random randomizer;

public:
    FNetwork(int roundsNo = 3) : roundsNo(roundsNo), randomizer() {}
    
    string encrypt (const string msg, const string key);
	/* Дополнить сообщение (например \0 -ми)до длины кратной 16 символам (128 бит)
	 * Для каждого куска в 64 бита применить roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултата в строку.
	 * Вернуть эту строку
	 * */
    string decrypt (const string msg, const string key);
	/* Для каждого куска по 128 бит применить roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултата в строку (Ключи подаются в обратном порядке).
	 * Вернуть эту строку
	 * */


private:   
    void fillRandArray(unsigned long seed);
	/* Заполнить массив R сл. числами с порождающим
	 * элементом seed
	 * */
    inline int countBlocks(const string msg)
    {
	int len = msg.length();
	return len%16 == 0 ? len/16 : len/16 + 1;
    }
    
    void generateRoundKeys(const string msg, const string key);
 	/* Сгенерировать массив keys из (countBlocks*roundsNo) ключей. 
	* i-й ключ пердназнаечн для операций i/roundsNo -й строкой
	* на i%roundsNo -й итерации сети Фейстеля
	* */
    
    string strxor (const string a, const string b);
    
    string F(const string key, const string left);

};
#endif /* FEISTEL_NETWORK_H */
