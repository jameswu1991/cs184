#include "window.h"

vector<MatrixXf> quads;
float _angle = -70.0f;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(fov y, aspect ratio, projection plane, far clipping plane)
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void addLights() {
	//Add ambient light
	GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f}; //Color (0.1, 0.1, 0.1)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	//Add directed light
	GLfloat lightColor1[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}

void addQuads() {
	GLuint index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	
	for (int a=0; a<quads.size(); a++) {
		MatrixXf quad = quads[a];
		glNormal3f(quad(0,4), quad(1,4), quad(2,4));
		glVertex3f(quad(0,0), quad(1,0), quad(2,0));
		glNormal3f(quad(0,5), quad(1,5), quad(2,5));
		glVertex3f(quad(0,1), quad(1,1), quad(2,1));
		glNormal3f(quad(0,6), quad(1,6), quad(2,6));
		glVertex3f(quad(0,2), quad(1,2), quad(2,2));
		glNormal3f(quad(0,7), quad(1,7), quad(2,7));
		glVertex3f(quad(0,3), quad(1,3), quad(2,3));
	}
	
	glEnd();
	glEndList();
	
	glCallList(index);
	glDeleteLists(index,1);
}

void addTriangles() {
	
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// put pinhole at 0, 0, -8
	glTranslatef(0.0f, 0.0f, -8.0f);
	
	addLights();
	
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.5f, 1.0f); // blue
	
	addQuads();
	addTriangles();
	
	glutSwapBuffers();
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void Window::addQuad(MatrixXf quad) {
	quads.push_back(quad);
}

void Window::show(int argc, char *argv[]) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Rendering Window");
	
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
	
	glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
}

