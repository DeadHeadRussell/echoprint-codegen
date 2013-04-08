#include <fstream>
#include <ostream>

#include "../../src/AudioStreamInput.h"
#include "../../src/Codegen.h"
#include "../../src/Fingerprint.h"

#include "callback.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ofstream;
using std::ostream;
using std::streambuf;

class Arguments {
 public:
  static Arguments parseArguments(int argc, char** argv) {
    if (argc > 3 || argc < 2) {
      cerr << "Usage: " << argv[0] << " audio_file [output_file]" << endl;
      exit(-1);
    }

    char* input_filename = argv[1];
    char* output_filename = NULL;
    if (argc == 3) {
      output_filename = argv[2];
    }

    return Arguments(input_filename, output_filename);
  }

  char* input_filename;
  char* output_filename;

 private:
  Arguments(char* input_filename, char* output_filename) :
    input_filename(input_filename), output_filename(output_filename) {}
};

FfmpegStreamInput* createAudioStream(char* input_filename) {
  FfmpegStreamInput* audio_stream(new FfmpegStreamInput());
  audio_stream->ProcessFile(input_filename, 0, 0);
  cerr << "Read in " << audio_stream->getNumSamples() << " samples from " << input_filename << endl;
  return audio_stream;
}

Codegen* createCodegen(FfmpegStreamInput* audio_stream) {
  Codegen* codegen = new Codegen(audio_stream->getSamples(), audio_stream->getNumSamples(), 0);
  return codegen;
}

void deleteAudioStream(FfmpegStreamInput* audio_stream) {
  delete audio_stream;
}

void deleteCodegen(Codegen* codegen) {
  delete codegen;
}

void writeOutput(char* output_filename, Codegen* codegen, OutputCallback callback) {
  streambuf* output_buffer;
  ofstream output_file;

  if (output_filename != NULL) {
    output_file.open(output_filename);
    output_buffer = output_file.rdbuf();
  } else {
    output_buffer = cout.rdbuf();
  }

  ostream writer(output_buffer);
  callback(writer, codegen);
}

int main(int argc, char** argv) {
  Arguments arguments = Arguments::parseArguments(argc, argv);
  FfmpegStreamInput* audio_stream = createAudioStream(arguments.input_filename);
  Codegen* codegen = createCodegen(audio_stream);
  writeOutput(arguments.output_filename, codegen, outputCallback);
  deleteCodegen(codegen);
  deleteAudioStream(audio_stream);
}

