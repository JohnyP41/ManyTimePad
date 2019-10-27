//
// Created by ac on 22/10/19.
//

#ifndef MTP_MTPANALYZER_HPP
#define MTP_MTPANALYZER_HPP


#include "mtp.hpp"
#include <map>

struct XorAnalysisInfo {
    float probabilitySameCase;
    float probabilityDifferentCase;
    float probabilityBlank;
};

class MtpAnalyzer {
private:
    Mtp  mtp;
public:

    MtpAnalyzer(std::string filename);

    void brakeTheCode();
    static std::vector<CipherString> getXorVec(const int i, std::vector<CipherString> cipherVec);

    std::vector<std::map<int, float>> blankAnalysis();
};


#endif //MTP_MTPANALYZER_HPP
