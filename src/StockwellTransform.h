#ifndef STOCKWELLTRANSFORM_H
#define STOCKWELLTRANSFORM_H
#include "Common.h"
#include "Params.h"
#include "MatrixUtility.h"
#include "SubbandAnalysis.h"

class StockwellTransform : public SubbandAnalysis {
public:
    StockwellTransform(AudioStreamInput* pAudio);
    StockwellTransform(const float* pSamples, uint numSamples);
    virtual ~StockwellTransform() {}
    virtual void Compute();
};

#endif
