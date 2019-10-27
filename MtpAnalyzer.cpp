//
// Created by ac on 22/10/19.
//

#include <iostream>
#include <map>
#include <sstream>
#include "MtpAnalyzer.hpp"

const auto NEW_CHAR_COUNT = 1;
const int NOT_FOUND_CHAR_COUNT=0;
const float HIGH_PROBABILITY=0.6;
const char BLANK = ' ';
const int MAX_STRING_LENGHT = 200;

MtpAnalyzer::MtpAnalyzer(std::string filename) : mtp(filename) {

}



std::vector<std::map<int,float>> MtpAnalyzer::blankAnalysis(){
    std::map<int,float> cipherMap;
    CipherString attack;
    float stringsNumber = mtp.asVector().size();
    std::vector<std::map<int,float>> cipherMaps;

    //trying to recognize blank chars in plainText
    //remember: if we compare a string with all the others with xor we obtain stringsNumber - 1 comparisons
     for(int cipherStringCounter = 0 ; cipherStringCounter < stringsNumber ; ++cipherStringCounter ) {
        cipherMap.clear();
        for (int compareCounter = 0; compareCounter < stringsNumber; ++compareCounter) {
            if (compareCounter != cipherStringCounter) {
                attack = mtp.attack(cipherStringCounter, compareCounter);
                for (int cipherCharCounter=0;cipherCharCounter < attack.str().length();++cipherCharCounter) {
                    char cipherChar = attack.str()[cipherCharCounter];
                    if (isalpha(cipherChar)) {
                        if (cipherMap.count(cipherCharCounter) == NOT_FOUND_CHAR_COUNT)
                            cipherMap.insert({cipherCharCounter, 1/(stringsNumber-1)});
                        else
                            cipherMap.at(cipherCharCounter) += 1/(stringsNumber-1);
                    }
                }
            }
        }
        cipherMaps.push_back(cipherMap);
    }
    return cipherMaps;
}


// if "+" is xor then:
//c1=m1+k c2=m2+k c1+c2=m1+m2 m1+c1=m1+m1+k=k

void MtpAnalyzer::brakeTheCode() {

    using namespace std;
    CipherString xorred;
    vector<int> blankIndexVec;
    vector<std::map<int, float>> blankMapVec = blankAnalysis();

    int cipherCounter = 0;
    int xorredCharCounter = 0;

    for (auto cipher: mtp.asVector()) {
        string tmp{};
        char guess[MAX_STRING_LENGHT]{};
        for (auto cipherCompare: mtp.asVector()) {

            if (cipher.str() != cipherCompare.str()) {

                xorred = cipherCompare.Xor(cipher);
                tmp.clear();
                xorredCharCounter = 0;

                for (char xorredChar : xorred.str()) {
                    if(blankMapVec[cipherCounter][xorredCharCounter] >= HIGH_PROBABILITY)
                        tmp.push_back(BLANK);
                    else
                        tmp.push_back(xorredChar);

                    xorredCharCounter++;
                }
                for (char chr : tmp) {
                    char cacca = isalnum(chr)?chr:'-';
                    cout << cacca;
                }
                cout << "\n";
                for(int index=0;index<tmp.length();index++){
                    if (!isalnum(guess[index]))
                        guess[index]=tmp[index];

                }

            }

        }
        cout << "guessing... :"<<endl;
        cout << mtp.getStr(guess) << endl<<endl;
        cipherCounter++;
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