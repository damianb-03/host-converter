#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

    while(!fs.eof()) {
        string line;
        getline(fs,line);
        stringstream ss;
        ss << line;
        int i = 0;
        string cols[2];
        if(ss.peek() == '#') {
            continue;
        }
        while(ss.peek() != EOF) {
            while(ss.peek() == ' ' || ss.peek() == '\n') {
                ss.get();
            }
            getline(ss,cols[i],'\t');
            if(!cols[i].size()) {
                continue;
            }
            if(i > 3) {
                cout << "Bad hosts file format! Check if you using tabs instead of spaces" << endl;
            }
            // cout << i << ": " << cols[i] << endl;  //dbg
            i++;
        }
        c_record rec(cols[0],cols[1]);
        if(rec.is_correct()) {
            fs_out << rec.record_to_string_AAAA() << endl;
            fs_out << rec.record_to_string_PTR() << endl;
            fs_out << endl;
        }
    }
    fs.close();
    fs_out.close();

    return 0;
}
