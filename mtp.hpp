//
// Created by ac on 21/10/19.
//

#ifndef MTP_MTP_HPP
#define MTP_MTP_HPP

#include <vector>
#include "CipherString.hpp"

//many time pad attack
class Mtp {


private:

    std::vector<CipherString> ciphers;
    CipherString target;
    CipherString key;

public:

    //loading file with ciphers
    Mtp(const std::string& fileName="cipher.txt");

    //prettyprint
    void print();

    CipherString attack(int fst,int snd);

    static void log(const std::string& message);



    void setKey(CipherString newKey);


    std::vector<CipherString> asVector();

    std::string getStr(const std::string &message);
};


#endif //MTP_MTP_HPP
