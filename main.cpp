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
            cout << "The key is scanned. Proceeding to encrypt/decrypt operations...\n";
        }
    }
}

int main(int argc, char **argv) {
    string key;
    string msg;

    bool enc;
    bool flag = false;
    int inpPos = 0, outPos = 0;
    ifstream inFile;
    ofstream outFile;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if ((arg == "-e") || (arg == "--encrypt")) {
            enc = true;
            flag = true;
        } else
            if ((arg == "-d") || (arg == "--decrypt")) {
                enc = false;
                flag = true;
            } else
                if ((arg == "-h") || (arg == "--help")) {
                    usage(argv[0]);
                    return(0);
                } else
                    if ((arg == "-i") || (arg == "--input")) inpPos = ++i;
                    else
                        if ((arg == "-o") || (arg == "--output")) outPos = ++i;
    }

    if (inpPos == 0) {
        cout << endl << "Input file not specified" << endl;
        return(0);
    }
    if (!flag) {
        cout << endl << "You must specify what do you want to do. I'm not a telepath ;)" << endl;
        return(0);
    }

    getKey(key);

    ifstream fs(argv[inpPos], std::ios::in | std::ios::binary);

    if ( !fs )
    {
        cout << "Unable to open file " << argv[inpPos] << endl;
        return 1;
    }

    vector<char> buffer;
    ifstream::pos_type size = 0;

    if ( fs.seekg(0, std::ios::end) )
    {
        size = fs.tellg();
    }

    if ( size && fs.seekg(0, std::ios::beg) )
    {
        buffer.resize(size);
        fs.read(&buffer[0], size);
    }

    for (int i = 0; i < buffer.size(); ++i)
        msg += buffer[i];

    FNetwork *f = new FNetwork();
    pair<string,bool> res = f->encrypt(msg, key, enc);

    //if (res.second)
    //{
        outFile.open(outPos != 0 ? argv[outPos] : (enc ? "out.enc" : "out.dec") );
        if (!outFile) {
            cerr << "Unable to open file " << argv[outPos] << endl;
            return 1;
        }

        if (enc)
            cout << "Done." << endl;
        //else
        //    cout    << "The key is possibly valid. You may check the output file." << endl;

        outFile << ( res.second ? res.first : "Invalid key");
        outFile.close();
    //}
    //else
    //{
    //    cout << "Invalid key." << endl;
    //}

    return 0;
}