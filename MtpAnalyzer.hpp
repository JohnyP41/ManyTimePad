//
// Created by ac on 22/10/19.
//

#ifndef MTP_MTPANALYZER_HPP
#define MTP_MTPANALYZER_HPP


#include "mtp.hpp"

class MtpAnalyzer {
private:
    Mtp  mtp;
public:

    MtpAnalyzer(std::string filename);

    void brakeTheCode();
    static std::vector<CipherString> getXorVec(const int i, std::vector<CipherString> cipherVec);
};


#endif //MTP_MTPANALYZER_HPP
