#ifndef C_RECORD_H
#define C_RECORD_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/asio/ip/address.hpp>


using std::string;

struct c_record {
    int line_nr;
    string host;
    string addr;
    bool is_ok;

    c_record(int,string,string);

    void addr_string_to_octets();
    bool is_correct();
    bool is_ipSupported(string);
    string record_to_string_AAAA();
    string record_to_string_PTR();
private:
    string addr_oct[8];
};


#endif // C_RECORD_H
