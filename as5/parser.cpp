#include "parser.h"

vector<Patch> Parser::loadFile(char* filename) {
	vector<Patch> patches;
	
	ifstream myfile(filename);
	if (myfile.is_open()) {
		
		string line;
		
		while (myfile.good()) {
			/* getline(myfile, line);
			vector<string> tokens = split(line, '   ');
			if (line[0] == 'v') {
				if (tokens.size() < 4)
					continue;
				Vertex v = Vertex(
					atof(tokens[1].c_str()), 
					atof(tokens[2].c_str()), 
					atof(tokens[3].c_str()));
				verticies.push_back(v);
			}
			else if (line[0] == 'f') {
				Polygon p;
				for(int a=1; a<tokens.size(); a++) {
					int index = atoi(tokens[a].c_str());
					p.addPoint(verticies[index - 1]);
				}
				model->addPolygon(p);
			}
			
			patches.push_back(patch); */
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
