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

#include "vertex.h"
#include "polygon.h"

using namespace std;

void load_file(char* filename);
void draw_verticies();
void draw_polygons();
vector<string> split(string line, char delimiter);

#endif