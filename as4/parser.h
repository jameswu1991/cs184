#ifndef parser_h
#define parser_h

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include "v_math.h"

using namespace std;

void load_verticies(char* filename);
void draw_verticies();
vector<string> split(string line, char delimiter);

#endif