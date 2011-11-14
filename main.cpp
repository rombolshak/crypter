#include <iostream>
#include <string>

#include "md5.h"
#include "random.h"
#include "Feistel network.h"


#include <termios.h>
#include <unistd.h>

using namespace std;


void echo( bool on = true )
{
    struct termios settings;
    tcgetattr( STDIN_FILENO, &settings );
    settings.c_lflag = on
		    ? (settings.c_lflag |   ECHO )
		    : (settings.c_lflag & ~(ECHO));
    tcsetattr( STDIN_FILENO, TCSANOW, &settings );
}


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
    
    
    FNetwork *f = new FNetwork();	
    f->encrypt("a", "01234567");
    /* Вернуть после отладки !!!
     * 
    char c = 0;
    while (key.length() != 8)
    {
	key = "";
	cout << "Type in a key (8 symbols):\n(If you type in more, the first 8 will be assumed as a key.)\n";
    
	echo(false);
	while (key.length() != 8 && c!='\n')
	{
	    cin >> noskipws >> c;
	    key += c;
	}
	echo(true);
	
	if (key.length() < 8)
	{
	    cout <<  "The key is less then 8 symbols, try again.\n";
	}
	
	if (key.length() > 8)
	{
	    key = key.substr(0, 8);
	}
    }
    //cout << "Your key is the value between ## ##:\n" << "##" << key  << "##" << "\n";
    * */
    return 0;
}
