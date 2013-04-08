#include <ostream>
#include <vector>

#include "../../src/Codegen.h"
#include "../../src/Fingerprint.h"

#include "../common/callback.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ostream;
using std::vector;

void outputCallback(ostream& writer, Codegen* codegen) {
  vector<FPCode>& codes = codegen->getCodes();
  uint number_codes = codes.size();

  cerr << "Computed " << number_codes << " codes" << endl;

  for (uint i = 0; i < number_codes; i++) {
    FPCode& code = codes.at(i);
    writer << code.frame_actual << " " << code.band << endl;
  }
}

