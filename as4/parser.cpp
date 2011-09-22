#include "parser.h"

vector<Vertex> _verticies;
vector<Polygon> _polygons;

void load_file(char* filename) {
	string line;
	ifstream myfile(filename);
	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, line);
			vector<string> tokens = split(line, ' ');
			if (line[0] == 'v') {
				if (tokens.size() < 4)
					continue;
				Vertex v = Vertex(
					atof(tokens[1].c_str()), 
					atof(tokens[2].c_str()), 
					atof(tokens[3].c_str()));
				_verticies.push_back(v);
			} else if (line[0] == 'f') {
				Polygon p;
				for(int a=1; a<tokens.size(); a++) {
					int index = atoi(tokens[a].c_str());
					p.addPoint(_verticies[index - 1]);
				}
				_polygons.push_back(p);
			}
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

Vertex offset = Vertex(0,-1,0);

void draw_verticies() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int i=0; i<_verticies.size(); i++) {
		Vertex v = _verticies[i];
		v = v.scale(0.5).add(offset);
		v.draw();
	}
	glEnd();
}

void draw_polygons() {
	glColor3f(1,1,1);
	for (int i=0; i<_polygons.size(); i++) {
		_polygons[i].translate(offset).scale(0.5).draw();
	}
}