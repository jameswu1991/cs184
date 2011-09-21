#include "parser.h"

vector<vector<float> > _verticies;

void load_verticies(char* filename) {
	string line;
	ifstream myfile(filename);
	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, line);
			if (line[0] != 'v')
				continue;
			vector<string> tokens = split(line, ' ');
			if (tokens.size() < 4)
				continue;
			vector<float> f = getVector(
				atof(tokens[1].c_str()), 
				atof(tokens[2].c_str()), 
				atof(tokens[3].c_str()));
			_verticies.push_back(f);
		}
	}
}

vector<string> split(string line, char delimiter) {
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

void draw_verticies() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int i=0; i<_verticies.size(); i++) {
		vector<float> v = _verticies[i];
		vector<float> offset = getVector(0,-1,0);
		v = v_add(offset, v_scale(v, 0.5));
		glVertex3f(v[0], v[1], v[2]);
	}
	glEnd();
}