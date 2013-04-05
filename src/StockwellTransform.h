#ifndef STOCKWELLTRANSFORM_H
#define STOCKWELLTRANSFORM_H
#include "Common.h"
#include "Params.h"
#include "MatrixUtility.h"
#include "SubbandAnalysis.h"

class StockwellTransform : public SubbandAnalysis {
public:
    StockwellTransform(AudioStreamInput* pAudio) : SubbandAnalysis(pAudio) {}
    StockwellTransform(const float* pSamples, uint numSamples) : SubbandAnalysis(pSamples, numSamples) {}
    virtual ~StockwellTransform() {}
    virtual void Compute();
};

#endif
