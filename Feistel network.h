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
	 * @param enc Если true, то режим шифрования, иначе расшифровки
	 * @return Пара: строка - за/дешифрованное сообщение, bool - верна ли расшифровка. Если false, то строка пуста
	 * */
    pair<string, bool> encrypt (const string msg, const string key, bool enc=true);
	
	/** 
	 * Для каждого куска по 128 бит применить roundsNo раз итерацию шифрования с
	 * заданной F, записывая резултата в строку (Ключи подаются в обратном порядке).
	 * @param msg Зашифрованное сообщение
	 * @param key Ключ шифрования
	 * @return Исходное сообщение, если ключ был верен
	 * */
    pair<string, bool> decrypt (const string msg, const string key);
	


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
		return (len%16 == 0 && len > 0) ? len/16 : len/16 + 1;
    }
    
    /** 
	 * Сгенерировать массив keys из (countBlocks*roundsNo) ключей. 
	 * i-й ключ пердназнаечн для операций i/roundsNo -й строкой
	 * на i%roundsNo -й итерации сети Фейстеля
	 * @param msg Сообщение, на основе которого генерируется массив
	 * @param key Ключ, на основе которого генерируются остальные ключи
	 * */
	void generateRoundKeys(const string msg, const string key);
 	
	/**
	 * Секретная функция. Вы никогда не догадаетесь, что она делает
	 */
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
	 * @param enc Происходит зашифровка или расшифровка
	 * @return Зашифрованную строку, соответствующую i-му блоку исходного сообщения
	 */
    string doCrypt(const string Left, const string Right, int i, bool enc = true);

	/**
	 * Подсчет контрольной суммы
	 */
    string crc32(const string buf);

};
#endif /* FEISTEL_NETWORK_H */
