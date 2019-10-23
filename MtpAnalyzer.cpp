//
// Created by ac on 22/10/19.
//

#include <iostream>
#include <map>
#include "MtpAnalyzer.hpp"

MtpAnalyzer::MtpAnalyzer(std::string filename) : mtp(filename) {

}

void MtpAnalyzer::brakeTheCode() {

    std::map<int,int> cipherMap;




    CipherString attack;
    for(auto c = 0 ;c < mtp.asVector().size() ; ++c ) {
        cipherMap.clear();
        for (auto i = 0; i < mtp.asVector().size(); i++) {
            if (i != c) {
                attack = mtp.attack(c, i);
                int j = 0;
                for (auto element : attack.str()) {
                    if (isalpha(element)) {
                        if (cipherMap.count(j) == 0)
                            cipherMap.insert({j, 1});
                        else
                            cipherMap.at(j)+=1;
                    }
                    else{}
                   // std::cout << j << std::endl;
                    j++;
                }
            }
            std::cout << i << std::endl;
            for (auto const &element : cipherMap){
                if (element.second > 5)
                    std::cout << element.first << " : " << element.second << "\n";
            }
        }
    }


}

std::vector<CipherString> MtpAnalyzer::getXorVec(const int i, std::vector<CipherString> cipherVec){
    std::vector<CipherString> xorVec;
    for (int j =0 ; j<cipherVec.size();j++){
        if(i!=j)
            xorVec.push_back(cipherVec[i].Xor(cipherVec[j]));
    }
    return xorVec;
}