#ifndef C_RECORD_H
#define C_RECORD_H

#include <iostream>
#include <string>
#include <sstream>

using std::string;

struct c_record {
    string host;
    string addr;

    c_record(string,string);

    void addr_string_to_octets();
    bool is_correct();
    string record_to_string_AAAA();
    string record_to_string_PTR();
private:
    string addr_oct[8];
};


#endif // C_RECORD_H
