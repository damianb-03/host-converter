#include "c_record.hpp"

c_record::c_record(string h, string adr) :
        host(h),
        addr(adr) {

    if(is_correct()) {
        addr_string_to_octets();
    } else {
        std::cout << "Constructing record fail: [" << adr << "]" << std::endl;
    }
}

void c_record::addr_string_to_octets() {

    std::stringstream adr_s;
    adr_s << addr;
    string oct;
    std::cout << addr << std::endl;
    for(int i = 0; i < 8; ++i) {
        getline(adr_s, oct, ':');
        // std::cout << oct << std::endl; // dbg
        while(oct.size() < 4) {
            oct.insert(0,1,'0');
        }
        addr_oct[i] = oct;
    }
}

bool c_record::is_correct() {

    if(!addr.size() ||
       !host.size()) {
        return 0;
    }
    return 1;
}

string c_record::record_to_string_AAAA() {
   string rec;
   rec += host;
   rec += '\t';
   rec += "IN";
   rec += '\t';
   rec += "AAAA";
   rec += '\t';
   rec += addr;

   std::cout << "record_AAAA:\n" << rec << std::endl;
   return rec;
}

string c_record::record_to_string_PTR() {
   string rec;
   for(int i = 8-1; i >= 0; --i) {
       string oct = addr_oct[i];
       for(int j = oct.size()-1; j >= 0; --j) {
           rec += oct[j];
           rec += '.';
       }
   }
   rec += "ip6.arpa.";
   rec += '\t';
   rec += "IN";
   rec += '\t';
   rec += "AAAA";
   rec += '\t';
   rec += host;

   std::cout << "record_PTR:\n" << rec << std::endl;
   return rec;
}
