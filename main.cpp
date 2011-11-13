#include <iostream>
#include "md5.h"
#include "random.h"


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
	    cout << r->next() << endl;
	
	r->seed();
	cout << "Firs 10 random numbers with default seed:\n";
	for (int i=0;i<10;++i)
	    cout << r->next() << endl;
	
    return 0;
}
