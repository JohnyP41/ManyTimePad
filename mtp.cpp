//
// Created by ac on 21/10/19.
//


#include <iostream>
#include <fstream>
#include <utility>
#include <iomanip>
#include "mtp.hpp"

#include "CipherString.hpp"


void Mtp::print() {
    int i = 1;
    for (auto&& e:  ciphers){
        std::cout << i;
        log( " <<  " + e.str() );
        ++i;
    }
    log( "Target : " +target.str() );
}

Mtp::Mtp(const std::string& fileName) {
    std::cout << "looking for ciphertext file : " << fileName <<"...";
    //open file
    std::ifstream inFile(fileName);

    //file not found
    if (!inFile) {
        log("Unable to open file");
        exit(1); // terminate with error
    }

    //file found
    std::cout << "file found! setting cipher vector." << "\n";
    std::string str;

    //parsing..std::string
    while (std::getline(inFile,str)){
        if(!str.empty()) {
            if (str.find("target:") != std::string::npos) {
                target.set(str.substr(7));
                target = target.decode();
            } else {
                ciphers.push_back(CipherString(str.substr((str.find(':') + 1))).decode());
            }
        }

    }
    ciphers.push_back(target);
    inFile.close();
}

CipherString Mtp::attack(int fst, int snd) {

    /**
     * if it's a space then
     *
     * the characters at that position in the pairwise XORed plaintexts will be either
     *
     * - letters  (if the character at that position in the other plaintext is a letter)
     * - nulls  (if both of the characters are spaces).
     *
     * If it's a letter,
     *
     *  - random control characters
     *      (if the character at that position in the other plaintext is a letter with the same case),
     *  - numbers or punctuation
     *      (if the other character is a letter with different case)
     *  - flipped
     *      (if the other character is a space).
     **/



    auto xorred = ciphers[fst].Xor(ciphers[snd]);
    return CipherString(getStr(xorred.str()));

}

void Mtp::log(const std::string& message ){
    for (auto letter : message){
        if (!iscntrl(letter)||letter=='\0')
            std::cout << letter << " " ;
        else std::cout << "- ";
    }
    std::cout<< "\n";
}

std::string Mtp::getStr(const std::string& message) {
    std::string  output;
    for (auto letter : message) {
        if (!iscntrl(letter) || letter == '\0')
            output.push_back(letter);
        else
            output.push_back('*');
    }
    return output;
}

void Mtp::setKey(CipherString newKey ){
    this->key = std::move(newKey);
}

std::vector<CipherString> Mtp::asVector(){
    return ciphers;
}

