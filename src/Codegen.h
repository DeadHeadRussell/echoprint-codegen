//
//  echoprint-codegen
//  Copyright 2011 The Echo Nest Corporation. All rights reserved.
//


#ifndef CODEGEN_H
#define CODEGEN_H

// Entry point for generating codes from PCM data.

#include <string>
#include <vector>

#ifndef ECHOPRINT_VERSION
#define ECHOPRINT_VERSION 412
#endif

#ifdef _MSC_VER
    #ifdef CODEGEN_EXPORTS
        #define CODEGEN_API __declspec(dllexport)
        #pragma message("Exporting codegen.dll")
    #else
        #define CODEGEN_API __declspec(dllimport)
        #pragma message("Importing codegen.dll")
    #endif
#else
    #define CODEGEN_API
#endif

#ifdef TEST
#include "Fingerprint.h"
#endif

class Fingerprint;
class SubbandAnalysis;
struct FPCode;

class CODEGEN_API Codegen {
public:
    Codegen(const float* pcm, unsigned int numSamples, int start_offset);

    std::string getCodeString(){return _CodeString;}
    int getNumCodes(){return _NumCodes;}
    static double getVersion() { return ECHOPRINT_VERSION / 100.0; }
private:
    Fingerprint* computeFingerprint(SubbandAnalysis *pSubbandAnalysis, int start_offset);
    std::string createCodeString(std::vector<FPCode> vCodes);

    std::string compress(const std::string& s);
    std::string _CodeString;
    int _NumCodes;

#ifdef TEST
public:
    matrix_f& getSpectrogram() { return _Spectrogram; }
    std::vector<FPCode>& getCodes() { return _Codes; }

private:
    matrix_f _Spectrogram;
    std::vector<FPCode> _Codes;
#endif

};

#endif
