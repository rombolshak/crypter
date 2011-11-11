#include <iostream>
#include "md5.h"

using namespace std;

int main(int argc, char **argv) {
	unsigned int out[4];
	MD5 m = MD5("1");
	m.getNumbers(out);
	cout << "md5 of 'grape': " << md5("grape")<<endl;
	cout << "md5 numbers are: " << out[0] << ", " << out[1] << ", " << out[2] << ", " << out[3] << ", " << endl;
    return 0;
}
