#ifndef globals_h
#define gglobals_h

#include "parser.h"
#include "window.h"
// #include "rendering.h"

using namespace std;

class Globals {
private:
	Window _window;
	Parser _parser;
public:
	Window* window;
	Parser* parser;
}
// Rendering rendering;

#endif