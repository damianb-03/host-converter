#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "c_record.hpp"

using namespace std;


int main(int argc, char *argv[]) {

    string filename;
    if(argc == 2) {
        filename = argv[1];
    } else {
        cerr << "No hosts file specified!" << endl;
        return 1;
    }

    fstream fs;
    fs.open(filename.c_str(), std::fstream::in);
    if(!fs.is_open()) {
        cerr << "Fail to open file: " << filename << endl;
        return 1;
    }

    fstream fs_out;
    string filename_out = filename;
    filename_out += ".new";
    fs_out.open(filename_out.c_str(), std::fstream::out);
    if(!fs_out.is_open()) {
        cerr << "Fail to create file: " << filename_out << endl;
        return 0;
    }


    for(int nr = 1; !fs.eof(); ++nr) {
        string line;
        getline(fs,line);
        replace(line.begin(),line.end(),' ','\t'); // replace all spaces to tabs
        std::cout << line << std::endl; // dbg
        stringstream ss;
        ss << line;

        const int cols_num = 2;
        string cols[cols_num];
        if(ss.peek() == '#') {
            continue;
        }
        int i = 0;
        while(ss.peek() != EOF) {
            //while(ss.peek() == ' ' || ss.peek() == '\n') {
            //    ss.get();
           // }
            getline(ss,cols[i],'\t');
            if(!cols[i].size()) {
                continue;
            }
            cout << "Col" << i << " " << cols[i] << endl;  //dbg
            i++;
            if(i >= cols_num) {
                cout << "Bad hosts file format!:\n" << line << endl;
                break;
            }
        }
        if(!cols[0].size() || !cols[1].size()) {
            continue;
        }
        c_record rec(nr,cols[0],cols[1]);
        if(rec.is_ok) {
            fs_out << rec.record_to_string_AAAA() << endl;
            fs_out << rec.record_to_string_PTR() << endl;
        }
    }
    fs.close();
    fs_out.close();

    return 0;
}
