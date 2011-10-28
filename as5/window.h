#ifndef window_h
#define window_h

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

#define WIDTH 400
#define HEIGHT 400

using namespace std;
using namespace Eigen;

class Window {
public:
	void addQuad(MatrixXf quad);
	void show(int argc, char *argv[]);
};

#endif