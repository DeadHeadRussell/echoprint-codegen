#include "StockwellTransform.h"

#include <fftw3.h>

#include "gft.h"

#include <cstdio>

void StockwellTransform::Compute() {
  static const uint hop = pow(2, SUBBANDS + 1);

  int* partitions = gft_1dPartitions(hop);
  double* window = windows(hop, box);

  _NumFrames = (_NumSamples - hop + 1) / SUBBANDS;
  _Data = matrix_f(SUBBANDS, _NumFrames);

  for (uint i = 0; i < _NumSamples - hop; i += hop) {
    double signal[hop*2];
    memset(signal, 0, hop*2*sizeof(double));
    for (uint j = 0; j < hop; j++) {
      signal[j*2] = _pSamples[i + j];
    }

    gft_1dComplex64(signal, hop, window, partitions, 1);

    for (int subband = 0; subband < SUBBANDS; subband++) {
      int number_values = partitions[subband];

      float factor = (float)number_values / hop;
      for (uint frame = 0; frame < hop / 8; frame++) {
        int index = number_values + (int)(factor * frame * 8);
        float average = 0;
        for (int j = 0; j < 8; j++) {
          float real = signal[(index + j) * 2];
          float imag = signal[(index + j) * 2 + 1];
          average += real * real + imag * imag;
        }
        _Data(subband, frame + i / 8) = average / 8;
      }
    }
  }

  free(window);
  free(partitions);
}

