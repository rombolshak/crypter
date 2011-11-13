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
    
    /* Дополнить сообщение (например \0 -ми)до длины кратной 16 символам (128 бит)
	 * Для каждого куска в 64 бита применить roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултата в строку.
	 * Вернуть эту строку
	 * */
    string encrypt (const string msg, const string key);
	
	/* Для каждого куска по 128 бит применить roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултата в строку (Ключи подаются в обратном порядке).
	 * Вернуть эту строку
	 * */
    string decrypt (const string msg, const string key);
	


private:  
	/* Заполнить массив R сл. числами с порождающим
	 * элементом seed
	 * */
    void fillRandArray(unsigned long seed);
	
    inline int countBlocks(const string msg)
    {
	int len = msg.length();
	return len%16 == 0 ? len/16 : len/16 + 1;
    }
    
    /* Сгенерировать массив keys из (countBlocks*roundsNo) ключей. 
	 * i-й ключ пердназнаечн для операций i/roundsNo -й строкой
	 * на i%roundsNo -й итерации сети Фейстеля
	 * */
	void generateRoundKeys(const string msg, const string key);
 	
    string strxor (const string a, const string b);
    
	/**
	 * @brief Делает основную магию
	 * @param string key Ключ из массива R, предварительно сгенерированный @by generateRoundKeys
	 * @param string left Левая часть блока данных
	 */
    string F (const string key, const string left);
    string doCrypt(string Left, string Right, int i);

};
#endif /* FEISTEL_NETWORK_H */
