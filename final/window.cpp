#include "window.h"

Scene myScene;

void calculateFormFactors(Scene scene) {
	/*
	for patch1 in scene
		for patch2 in scene
			if (patch1 != patch2)
				patch1.formfactors[patch2] = rendering.calculateFormFator(patch1, patch2);
	*/
	cout << "calculating form factors \n";
}

void propagateLight(Scene scene) {
	/*
	do one value-iteration of the scene
	*/
	cout << "propagating light \n";
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// put pinhole at 0, 0, -8
	glTranslatef(0, 0, -8);
	
	propagateLight(myScene);
	/*
	for patch in scene
		draw patch with color
	*/
	
	glutSwapBuffers();
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 32: // space key
			exit(EXIT_SUCCESS);
			break;
	}
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(fov y, aspect ratio, projection plane, far clipping plane)
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

Window::Window(Scene scene) {
	myScene = scene;
	calculateFormFactors(myScene);
}

void Window::show(int argc, char *argv[]) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Radiosity Testing");
	
	//Initializes Rendering
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop();
}

