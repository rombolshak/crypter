#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>

#include "md5.h"
#include "random.h"
#include "Feistel network.h"

using namespace std;

int main(int argc, char **argv) {
    
	/*
	unsigned int out[4];
	MD5 m = MD5("md5");
	m.getNumbers(out);
	
	
	cout << "md5 of 'grape': " << md5("grape")<<endl;
	cout << "md5 numbers are: " << out[0] << ", " << out[1] << ", " << out[2] << ", " << out[3] << ", " << endl;
	
	
	Random *r = new Random();
	r->seed(out[0]);
	cout << "First 10 random numbers with seed " << out[0] << ":\n";
	for (int i=0;i<10;++i)
	    cout << i << ':' << r->next() << endl;
	
	r->seed(0);
	cout << "First 10 random numbers with 0 seed:\n";
	for (int i=0;i<10;++i)
	    cout << i << ':' << r->next() << endl;
	
	
	r->seed();
	cout << "Firs 50 random numbers with default seed:\n";
	for (int i=0;i<50;++i)
	    cout << i << ':' << r->next() << endl;
	
	
	FNetwork* f = new FNetwork();
	f->generateRoundKeys("msg", "qwertyqwerty"); 	// - private now
	f->fillRandArray(0);				// - private now
	cout << f->F("Iamagood", "12345678");		// - private now
	*/
	
    string key;
    
    /* Вернуть после отладки !!!
     
    while (key.length() != 8)
    {
	key = "";
	char* buf = getpass("Type in a key (8 symbols):\n(If you type in more, the first 8 will be assumed as a key.)\n");
	key = buf;
	bzero(buf, strlen(buf)+1);
	
	if (key.length() < 8)
	{
	    cout <<  "The key is less then 8 symbols, try again.\n";
	}
	
	if (key.length() > 8)
	{
	    key = key.substr(0, 8);
	    cout << "The key is OK. Proceeding to encrypt/decrypt operations...\n";
	}
    }
    * */
    
    key = "superkey";
    FNetwork *f = new FNetwork();
    cout << boolalpha << f->decrypt(f->encrypt("", key).first, "superkey").first << '\t' << f->decrypt(f->encrypt("", key).first, "superkey").second << endl;
    //cout << f->crc32("msg1msg!!!!!!!!!!!!!!#2msg3") << endl;
    return 0;
}
