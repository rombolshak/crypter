#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <fstream>

#include "md5.h"
#include "random.h"
#include "Feistel network.h"

using namespace std;

void usage(string name) {
	cout << "Usage: " << name << " <options>" << endl;
	cout << "Options:" <<endl << endl;
	cout << "One of the two below is **required**" << endl;
	cout << "-e/--encrypt\tEncrypt mode" << endl;
	cout << "-d/--decrypt\tDecrypt mode" << endl << endl;
	cout << "-i/--input\t**required**\t\tInput file name should be the next arg" << endl;
	cout << "-o/--output\t**out.enc by default**\tOutput file name should be the next arg" << endl;
	cout << "-h/--help\t\tShow this help and exit" << endl;
}

void getKey(string& key) {
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
}

int main(int argc, char **argv) {
    string key; string msg;
    
    bool enc; bool flag = false;
    int inpPos = 0, outPos = 0;
    ifstream inFile; ofstream outFile;
    
    for (int i = 1; i < argc; ++i) {
	    string arg = argv[i];
	    if ((arg == "-e") || (arg == "--encrypt")) {enc = true; flag = true;} else
	    if ((arg == "-d") || (arg == "--decrypt")) {enc = false;flag = true;} else
	    if ((arg == "-h") || (arg == "--help")) {usage(argv[0]); return(0);} else
	    if ((arg == "-i") || (arg == "--input")) inpPos = ++i; else
	    if ((arg == "-o") || (arg == "--output")) outPos = ++i;		
    }
    
    if (inpPos == 0) {cout << endl << "Input file not specified" << endl; return(0);}
    if (!flag) {cout << endl << "You must specify what do you want to do. I'm not a telepath ;)" << endl; return(0);}
    
    getKey(key);
		
	/*vector<string> s;
	char buf[1024];
	inFile.open(argv[inpPos]);
	if (!inFile) {
		cerr << "Unable to open file " << argv[inpPos] << endl;
		return(1);
	}
	while (1) {
		inFile.getline(buf, sizeof(buf));
		s.push_back(buf);
		if (inFile.eof()) break;
	}
	inFile.close();
	for (int i = 0; i < s.size(); ++i) {
		msg += s[i];
		if (i != s.size() - 1) msg += "\n";
	}*/
	
	std::ifstream fs(argv[inpPos], std::ios::in | std::ios::binary);
	
	if( !fs )
	{
		cout << "file open error!!!" << endl;
		return 1;
	}
	
	std::vector<char> buffer;
	std::ifstream::pos_type size = 0;
	
	if( fs.seekg(0, std::ios::end) )
	{
		size = fs.tellg();
	}
	
	if( size && fs.seekg(0, std::ios::beg) )
	{
		buffer.resize(size);
		fs.read(&buffer[0], size);
	}
	
	for (int i = 0; i < buffer.size(); ++i)
		msg += buffer[i];
	
    cout << msg << endl;
    FNetwork *f = new FNetwork();
    pair<string,bool> res = f->encrypt(msg, key, enc);
	cout << res.first << endl;
	outFile.open(outPos != 0 ? argv[outPos] : "out.enc");
	if (!outFile) {
		cerr << "Unable to open file " << argv[outPos] << endl;
		return(1);
	}
    outFile << ( res.second ? res.first : "Invalid key");
// 	string res = f->encrypt(msg, "11111111").first;
// 	cout << res << endl << f->encrypt(res, "11111111", false).second << endl;
    outFile.close();
        
    return 0;
}
