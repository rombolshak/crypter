#include <iostream>
#include <string>

#include "md5.h"
#include "random.h"
#include "Feistel network.h"

using namespace std;

int main(int argc, char **argv) {
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
	    cout << i << 'i' << r->next() << endl;
	
	
	r->seed();
	cout << "Firs 50 random numbers with default seed:\n";
	for (int i=0;i<50;++i)
	    cout << i << ':' << r->next() << endl;
	
	/*
	FNetwork* f = new FNetwork();
	f->generateRoundKeys("msg", "qwertyqwerty"); 	// - private now
	f->fillRandArray(0);				// - private now
	cout << f->F("Iamagood", "12345678");		// - private nows
	*/
    return 0;
}
