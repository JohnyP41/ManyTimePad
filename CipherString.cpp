//
// Created by ac on 21/10/19.
//

#include <cstdlib>
#include <ios>
#include <sstream>
#include "CipherString.hpp"

unsigned char CipherString::hexVal(unsigned char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    else if ('a' <= c && c <= 'f')
        return c - 'a' + 10;
    else if ('A' <= c && c <= 'F')
        return c - 'A' + 10;
    else abort();
}


std::string CipherString::hex2ascii(std::string cipherText){
   // toolbox utils;
    std::string out;
    out.clear();
    out.reserve(cipherText.length() / 2);

    for (std::string::const_iterator p = cipherText.begin(); p != cipherText.end(); p++) {
        unsigned char c =  hexVal(*p);
        p++;
        if (p == cipherText.end()) break;
        c = (c << 4) + hexVal(*p);
        out.push_back(c);
    }
    return out;
}

std::string CipherString::asciiChars(std::string cipherText){
    std::ostringstream s;
    for(auto el : cipherText) {
        s <<  std::hex << (0xff&(unsigned int)el);
    }
    return s.str();
}

std::string CipherString::strXor(std::string a, std::string b){
    std::string result;
    size_t length = a.length()<b.length()?a.length():b.length();
    result.reserve(length);
    for(int i=0; i<length;i++){
        result.push_back(a[i]^b[i]);
    }
    return result;
}

CipherString CipherString::decode() {
    return CipherString (hex2ascii(cipher));
}

CipherString CipherString::hex() {
    return CipherString (asciiChars(cipher));
}

std::string CipherString::str() {
    return this->cipher;
}

CipherString CipherString::Xor(CipherString plain) {
    return CipherString(strXor(cipher,plain.cipher));
}

void print(){

}
