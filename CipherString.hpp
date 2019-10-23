//
// Created by ac on 21/10/19.
//

#ifndef MTP_CIPHERSTRING_HPP
#define MTP_CIPHERSTRING_HPP


#include <string>

class CipherString {
private:
    std::string cipher;

    unsigned char hexVal(unsigned char c);
    std::string hex2ascii(std::string cipherText);
    std::string asciiChars(std::string cipherText);
    std::string strXor(std::string a, std::string b);


public:
    CipherString(){};
    CipherString(std::string cipher) {this->cipher = cipher;}
    CipherString decode();
    std::string str();
    CipherString Xor(CipherString plain);
    void set(std::string text){this->cipher = text; };

    CipherString hex();
};


#endif //MTP_CIPHERSTRING_HPP
