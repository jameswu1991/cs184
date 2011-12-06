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

void propagateLight(Scene scene) {
	/*
	do one value-iteration of the scene
	*/
	cout << "propagating light df... " << endl;
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

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	addLights();
	
	propagateLight(myScene);
	
	for (int a=0; a<myScene.patches.size(); a++) {
		
		float color = 1;
		if (a!=idx%myScene.patches.size()) {
			color = myScene.patches[idx%myScene.patches.size()].viewFactors[a]*20; 
			glColor3f(color, color, color);
		}
		else glColor3f(1, 0, 0); // blue
		 // blue
		
		vector<Vector3f> patch = myScene.patches[a].vertices;
		glBegin(GL_QUADS);
		glVertex3f(patch[0](0), patch[0](1), patch[0](2));
		glVertex3f(patch[1](0), patch[1](1), patch[1](2));
		glVertex3f(patch[2](0), patch[2](1), patch[2](2));
		glVertex3f(patch[3](0), patch[3](1), patch[3](2));
		glVertex3f(patch[0](0), patch[0](1), patch[0](2));
		glEnd();
	}
	
	glutSwapBuffers();
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 32: // space key
			idx++;
			drawScene();
			break;
	}
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
	// glShadeModel(GL_SMOOTH); //Enable smooth shading
	glShadeModel(GL_FLAT);
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop();
}

