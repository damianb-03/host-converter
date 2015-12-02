#include "c_record.hpp"

c_record::c_record(int nr, string h, string adr) :
        line_nr(nr),
        host(h),
        addr(adr) {

    if(is_correct()) {
        addr_string_to_octets();
        is_ok = true;
    } else {
        std::cerr << line_nr << ": " << "Constructing record fail: " << host <<  " [" << addr << "]" << std::endl;
        is_ok = false;
    }
}

void c_record::addr_string_to_octets() {
    std::stringstream adr_s;
    adr_s << addr;
    string oct;
    // std::cout << addr << std::endl; // dbg
    const int octets = 8;
    for(int i = 0; i < octets; ++i) {
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
        std::cerr << "Bad format: empty host or address - correct imput file record should have format:\n" << "<host> tab <address>" << std::endl;
        return false;
    }
    boost::system::error_code ec;
    boost::asio::ip::address test_addr = boost::asio::ip::address::from_string(addr, ec );
    if(ec) { ///< boost error - not needed
        //std::cerr << line_nr << ": " << ec.message( ) << std::endl;
        //return false;
    }
    if(!test_addr.is_v6()) {
        std::cerr << line_nr << ": " << addr << " is not valid IPv6 address" << std::endl;

        std::cerr << "Bad format: correct imput file record should have format: " << "<host> tab <address>" << std::endl;
        std::cerr << "Trying to swap host and address . . . ";
        boost::system::error_code ec_h;
        boost::asio::ip::address test_addr_h = boost::asio::ip::address::from_string(host, ec );
        if(test_addr_h.is_v6()) {
            addr.swap(host);
            std::cerr << "OK" << std::endl;
            return is_ipSupported(addr);
        } else {
            std::cerr << "FALSE" << std::endl;
            if(test_addr_h.is_v4()) {
                std::cerr << line_nr << ": " << host << " is correct IPv4 address -> skipping" << std::endl;
                return false;
            }
            return false;
        }
    }
    return is_ipSupported(addr);
}

bool c_record::is_ipSupported(string ip) {
    if(std::count(addr.begin(),addr.end(),':') != 7) {
        std::cerr << "Sry: not supported IPv6 format: " << addr << std::endl;
        return false;
    }
    return true;
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

   //std::cout << line_nr << ": " << "record_AAAA:\n" << rec << std::endl;
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

   //std::cout << line_nr << ": " << "record_PTR:\n" << rec << std::endl;
   return rec;
}
