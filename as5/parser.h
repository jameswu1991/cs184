#ifndef parser_h
#define parser_h

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <Eigen/Core>

#include "patch.h"

using namespace std;
using namespace Eigen;

class Parser {
	vector<string> split(string line, char delimiter);
public:
	vector<Patch> loadFile(char* filename);
};

#endif
