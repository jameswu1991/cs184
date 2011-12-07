#include "window.h"

Scene myScene;

void calculateFormFactors() {
	/*
	for patch1 in scene
		for patch2 in scene
			if (patch1 != patch2)
				patch1.formfactors[patch2] = rendering.calculateFormFator(patch1, patch2);
	*/
	cout << "calculating form factors... " << endl;
	myScene.calcFormFactors();
	cout << "done" << endl;
}

Vector3f mul (Vector3f a, Vector3f b) {
	Vector3f c (a[0]*b[0], a[1]*b[1], a[2]*b[2]);
	return c;
}

void propagateLight() {
	/*
	do one value-iteration of the scene
	*/
	cout << "propagating light df... " << endl;
	vector<Patch> oldPatches = myScene.patches;
	
	for (int i=0; i<oldPatches.size(); i++) {
		Vector3f weightedSum (0,0,0);
		for (int j=0; j<oldPatches.size(); j++) {
			if (i!=j) {
				// sum of all the form factors * Hj
				weightedSum += oldPatches[i].viewFactors[j] * oldPatches[j].irradiance;
			}
		}
		myScene.patches[i].irradiance = oldPatches[i].emission + mul(oldPatches[i].reflectance, weightedSum); 
	}
	cout << "done" << endl;	
}

void addLights() {
	//Add ambient light
	// GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f}; //Color (0.1, 0.1, 0.1)
	GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	/*
	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	//Add directed light
	GLfloat lightColor1[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 1.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	*/
}

int a=273;
int idx = 0;

float rotateX = 0;
float rotateY = 0;

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	addLights();
	
	glRotatef(rotateY, 1.0f, 0.0f, 0.0f);
	glRotatef(rotateX, 0.0f, 1.0f, 0.0f);
	
	vector<Vector3f> coords;
	vector<Vector3f> colors;
/*	
	for (int a=0; a<myScene.patches.size(); a++) {
		Patch patch = myScene.patches[a];
		for (int b=0; b<patch.vertices.size(); b++) {
			Vector3f coord = patch.vertices[b];
			Vector3f color = patch.irradiance;
			
			bool found = false;
			for(int c=0; c<coords.size(); c++) {
				if (coords[c]==coord) {
					colors[c]=colors[c]+color;
					found = true;
				}
			}
			if (!found) {
				coords.push_back(coord);
				colors.push_back(color);
			}
			
		}
	}
*/
	
	
	for (int a=0; a<myScene.patches.size(); a++) {
		
		Patch patch = myScene.patches[a];
		vector<Vector3f> vertices = patch.vertices;
		
		glBegin(GL_QUADS);
		
		// iterate through each vertex in the patch
		for (int b=0; b<vertices.size(); b++) {
			Vector3f coord = vertices[b];
			Vector3f color;
			// going through each list of neighbors for each vertex
			for (int c=0; c<patch.neighbors.size(); c++) {
					// iterating through each neighbor for that vertex
					for (int d=0; d<patch.neighbors[c].size(); d++) {
						color += myScene.patches[d].irradiance; // get the irradiance from neighbor patches;
					}
					// Average the color between neighbor patches
					color /= patch.neighbors[c].size();
					color *= 10; // scale the color back for display
					glColor3f(color[0], color[1], color[2]);
					glVertex3f(coord[0], coord[1], coord[2]);
			}
		}
		glEnd();
	}
	
	glutSwapBuffers();
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 32: // space key
			idx++;
			propagateLight();
			drawScene();
			break;
		
	}
}

void handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			rotateX -= 0.5;
			break;
		case GLUT_KEY_RIGHT:
			rotateX += 0.5;
			break;
		case GLUT_KEY_DOWN:
			rotateY -= 0.5;
			break;
		case GLUT_KEY_UP:
			rotateY += 0.5;
			break;
	}
	drawScene();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// gluPerspective(fov y, aspect ratio, projection plane, far clipping plane)
	gluPerspective(63.44, (double)w / (double)h, 600, 1600.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(278.0, a++, -800.0, 278.0, 273.0, 0.0, 0.0, 1.0, 0.0);
	
	// put camera pinhole at 0, 0, -8
	// glTranslatef(278, 273, -800);
	// glTranslated(-278.0, -a++, 800.0);
	// glTranslated(0, 0, 0);
	
	glTranslated(0, 0, 0);
	// gluLookAt(278.0, a++, -800.0, 278.0, 273.0, 0.0, 0.0, 1.0, 0.0);
}

Window::Window(Scene scene) {
	myScene = scene;
	calculateFormFactors();
}

void Window::show(int argc, char *argv[]) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	
	//Create the window
	glutCreateWindow("Radiosity Testing");
	
	//Initializes Rendering
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	// glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop();
}

