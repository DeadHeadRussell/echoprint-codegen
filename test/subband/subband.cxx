#include <ostream>

#include "../../src/Codegen.h"
#include "../../src/MatrixUtility.h"

#include "../common/callback.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ostream;

void outputCallback(ostream& writer, Codegen* codegen) {
  matrix_f spectrogram = codegen->getSpectrogram();
  uint number_bands = spectrogram.size1();
  uint number_frames = spectrogram.size2();

  cerr << "Computed " << number_bands << " bands with " << number_frames << " frames" << endl;

  for (uint i = 0; i < number_frames; i++) {
    for (uint j = 0; j < number_bands; j++) {
      writer << spectrogram(j, i) << " ";
    }
    writer << "\n";
  }
}

