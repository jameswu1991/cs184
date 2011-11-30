#include "parser.h"

vector<Patch> Parser::loadFile(char* filename) {
	vector<Patch> patches;
	ifstream myfile(filename);
	string line;
	
	vector<Vector3f> patchPoints;
	
	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, line);
			vector<string> points = split(line, ' ');
			
			if (points.size() != 12)
				continue;
			
			for (int a=0; a<4; a++) {
				Vector3f point;
				point(0,0) = atof(points[a*3].c_str());
				point(1,0) = atof(points[a*3+1].c_str());
				point(2,0) = atof(points[a*3+2].c_str());
				patchPoints.push_back(point);
			}
			
			if (patchPoints.size()==16) {
				Patch patch (patchPoints);
				patches.push_back(patch);
				vector<Vector3f> blank;
				patchPoints = blank;
			}
		}
	}

	return patches;
}

vector<string> Parser::split(string line, char delimiter) {
	vector<string> strings;
	string current;
	for (int i=0; i<line.length(); i++) {
		if (line[i] == delimiter) {
			strings.push_back(current);
			current = "";
		}
		else {
			string h;
			h.assign(1, line[i]);
			current.append(h);
		}
	}
	if (current != "")
		strings.push_back(current);
	return strings;
}
