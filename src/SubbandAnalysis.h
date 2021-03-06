//
//  echoprint-codegen
//  Copyright 2011 The Echo Nest Corporation. All rights reserved.
//


#ifndef SUBBANDANALYSIS_H
#define SUBBANDANALYSIS_H
#include "Common.h"
#include "Params.h"
#include "MatrixUtility.h"
#include "AudioStreamInput.h"

#define C_LEN 128
#define SUBBANDS 8
#define M_ROWS 8
#define M_COLS 16

namespace SubbandFilterBank {
    // 128pt, 1/8th band low-pass prototype subsampled from Table_analysis_window
    static const float C[C_LEN] = {
         0.000000477,  0.000000954,  0.000001431,  0.000002384,  0.000003815,  0.000006199,  0.000009060,  0.000013828,
         0.000019550,  0.000027657,  0.000037670,  0.000049591,  0.000062943,  0.000076771,  0.000090599,  0.000101566,
        -0.000108242, -0.000106812, -0.000095367, -0.000069618, -0.000027180,  0.000034332,  0.000116348,  0.000218868,
         0.000339031,  0.000472546,  0.000611782,  0.000747204,  0.000866413,  0.000954151,  0.000994205,  0.000971317,
        -0.000868797, -0.000674248, -0.000378609,  0.000021458,  0.000522137,  0.001111031,  0.001766682,  0.002457142,
         0.003141880,  0.003771782,  0.004290581,  0.004638195,  0.004752159,  0.004573822,  0.004049301,  0.003134727,
        -0.001800537, -0.000033379,  0.002161503,  0.004756451,  0.007703304,  0.010933399,  0.014358521,  0.017876148,
         0.021372318,  0.024725437,  0.027815342,  0.030526638,  0.032754898,  0.034412861,  0.035435200,  0.035780907,
        -0.035435200, -0.034412861, -0.032754898, -0.030526638, -0.027815342, -0.024725437, -0.021372318, -0.017876148,
        -0.014358521, -0.010933399, -0.007703304, -0.004756451, -0.002161503,  0.000033379,  0.001800537,  0.003134727,
        -0.004049301, -0.004573822, -0.004752159, -0.004638195, -0.004290581, -0.003771782, -0.003141880, -0.002457142,
        -0.001766682, -0.001111031, -0.000522137, -0.000021458,  0.000378609,  0.000674248,  0.000868797,  0.000971317,
        -0.000994205, -0.000954151, -0.000866413, -0.000747204, -0.000611782, -0.000472546, -0.000339031, -0.000218868,
        -0.000116348, -0.000034332,  0.000027180,  0.000069618,  0.000095367,  0.000106812,  0.000108242,  0.000101566,
        -0.000090599, -0.000076771, -0.000062943, -0.000049591, -0.000037670, -0.000027657, -0.000019550, -0.000013828,
        -0.000009060, -0.000006199, -0.000003815, -0.000002384, -0.000001431, -0.000000954, -0.000000477, 0};
}

class SubbandAnalysis {
public:
    inline SubbandAnalysis() {};

    SubbandAnalysis(AudioStreamInput* pAudio) {
      _pSamples = pAudio->getSamples();
      _NumSamples = pAudio->getNumSamples();
    }

    SubbandAnalysis(const float* pSamples, uint numSamples) :
      _pSamples(pSamples), _NumSamples(numSamples) {} 

    virtual ~SubbandAnalysis() {}
    virtual void Compute() = 0;
public:
    inline uint getNumFrames() const {return _NumFrames;}
    inline uint getNumBands() const {return SUBBANDS;}
    const matrix_f& getMatrix() {return _Data;}

protected:
    const float* _pSamples;
    uint _NumSamples;
    uint _NumFrames;
    matrix_f _Data;
};

class FilterBank : public SubbandAnalysis {
public:
    FilterBank(AudioStreamInput* pAudio);
    FilterBank(const float* pSamples, uint numSamples);
    virtual ~FilterBank() {}
    virtual void Compute();

private:
    matrix_f _Mi;
    matrix_f _Mr;

    void Init();
};

#endif
