#ifndef parser_h
#define parser_h

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "vertex.h"
#include "polygon.h"
#include "model.h"

using namespace std;

class Parser {
	vector<string> split(string line, char delimiter);
public:
	Model* loadFile(char* filename);
};

#endif