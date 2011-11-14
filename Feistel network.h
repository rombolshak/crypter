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
	/** Количество раундов */
    int roundsNo;
	
	/** Массив раундовых ключей */
    vector<string> keys;
	
	/** Массив случайных чисел */
    unsigned long R[1<<24];
	
	/** Великий корейский рандом */
    Random randomizer;

public:
    FNetwork(int roundsNo = 3) : roundsNo(roundsNo), randomizer() {}
    
    /** 
	 * Дополняет сообщение (например \0 -ми)до длины кратной 16 символам (128 бит)
	 * Для каждого куска в 64 бита применяет roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултат в строку.
	 * @param msg Исходное сообщение
	 * @param key Ключ шифрования
	 * @return Зашифрованное сообщение
	 * */
    string encrypt (const string msg, const string key);
	
	/** 
	 * Для каждого куска по 128 бит применить roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултата в строку (Ключи подаются в обратном порядке).
	 * @param msg Зашифрованное сообщение
	 * @param key Ключ шифрования
	 * @return Исходное сообщение, если ключ был верен
	 * */
    string decrypt (const string msg, const string key);
	


private:  
	/** 
	 * Заполнить массив R сл. числами
	 * @param seed Порождающий элемент
	 */
    void fillRandArray(unsigned long seed);
	
	/**
	 * Считает, на сколько блоков разбивается
	 * @param msg исходное сообщение
	 * @return Количество блоков
	 */
    inline int countBlocks(const string msg)
    {
		int len = msg.length();
		return len%16 == 0 ? len/16 : len/16 + 1;
    }
    
    /** 
	 * Сгенерировать массив keys из (countBlocks*roundsNo) ключей. 
	 * i-й ключ пердназнаечн для операций i/roundsNo -й строкой
	 * на i%roundsNo -й итерации сети Фейстеля
	 * @param msg Сообщение, на основе которого генерируется массив
	 * @param key Ключ, на основе которого генерируются остальные ключи
	 * */
	void generateRoundKeys(const string msg, const string key);
 	
    string strxor (const string a, const string b);
    
	/**
	 * Делает основную магию
	 * @param key Ключ из массива R, предварительно сгенерированный @see generateRoundKeys
	 * @param left Левая часть блока данных
	 * @return Зашифрованный кусок текста, подлежащий складыванию по модулю со вторым куском
	 */
    string F (const string key, const string left);
	
	/**
	 * Производит шифрование одной пары блоков
	 * @param Left Левый блока
	 * @param Right Правый блока
	 * @param i Номер пары блоков
	 * @return Зашифрованную строку, соответствующую i-му блоку исходного сообщения
	 */
    void doCrypt(string Left, string Right, int i);

};
#endif /* FEISTEL_NETWORK_H */
