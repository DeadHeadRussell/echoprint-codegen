#ifndef CALLBACK_H
#define CALLBACK_H

#include <iostream>

class Codegen;

typedef void (*OutputCallback)(std::ostream&, Codegen*);
void writeOutput(char*, Codegen*, OutputCallback);
void outputCallback(std::ostream&, Codegen*);

#endif

