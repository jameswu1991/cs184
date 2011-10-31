#include "window.h"

bool smooth = true;
bool hiddenLine = false;
bool wireframe = false;
float rotateX = 0.0f;
float rotateY = 0.0f;
float translateX = 0.0f;
float translateY = 0.0f;
float zoom = 1.0f;

vector<MatrixXf> quads;
vector<MatrixXf> triangles;
float _angle = -70.0f;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 43: // plus button
			zoom += 0.05;
			break;
		case 45: // minus button
			zoom -= 0.05;
			break;
		case 115: // s
			smooth = !smooth;
			break;
		case 119: // w
			wireframe = !wireframe;
			break;
		case 104: // h
			hiddenLine = !hiddenLine;
			break;
	}
}

void handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				translateX -= 0.2;
			else rotateX -= 1.5;
			break;
		case GLUT_KEY_RIGHT:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				translateX += 0.2;
			else rotateX += 1.5;
			break;
		case GLUT_KEY_DOWN:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				translateY -= 0.2;
			else rotateY -= 1.5;
			break;
		case GLUT_KEY_UP:
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
				translateY += 0.2;
			else rotateY += 1.5;
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
	glColor3f(0.0f, 0.5f, 1.0f); // blue
	
	GLuint index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	if (wireframe) {
		for (int a=0; a<quads.size(); a++) {
			MatrixXf quad = quads[a];
			
			glBegin(GL_LINE_STRIP);
			glVertex3f(quad(0,0), quad(1,0), quad(2,0));
			glVertex3f(quad(0,1), quad(1,1), quad(2,1));
			glVertex3f(quad(0,2), quad(1,2), quad(2,2));
			glVertex3f(quad(0,3), quad(1,3), quad(2,3));
			glVertex3f(quad(0,0), quad(1,0), quad(2,0));
			glEnd();
			if (hiddenLine) {
				// draw giant black quad to block out frames behind it
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonOffset(1.0, 1.0);
				glColor3f(0.0f, 0.0f, 0.0f); // black
				glBegin(GL_QUADS);
				glVertex3f(quad(0,0), quad(1,0), quad(2,0));
				glVertex3f(quad(0,1), quad(1,1), quad(2,1));
				glVertex3f(quad(0,2), quad(1,2), quad(2,2));
				glVertex3f(quad(0,3), quad(1,3), quad(2,3));
				glEnd();
				glColor3f(0.0f, 0.5, 1.0f); // blue
				glDisable(GL_POLYGON_OFFSET_FILL);
			}
		}
	}
	else {
		glBegin(GL_QUADS);
		if (smooth) {
			glShadeModel(GL_SMOOTH); //Enable smooth shading
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
		}
		else {
			glShadeModel(GL_FLAT); //Enable smooth shading
			for (int a=0; a<quads.size(); a++) {
				MatrixXf quad = quads[a];
				Vector3f side1; 
				side1 << quad(0,1)-quad(0,0),
						quad(1,1)-quad(1,0),
						quad(2,1)-quad(2,0);
				Vector3f side2;
				side2 << quad(0,2)-quad(0,1),
						quad(1,2)-quad(1,1),
						quad(2,2)-quad(2,1);
				Vector3f cross = side1.cross(side2);
				
				int side1Index = 0;
				do {
					int side2Index = (side1Index+1)%4;
					int side3Index = (side1Index+2)%4;
					Vector3f side1;
					side1 << quad(0,side2Index)-quad(0,side1Index),
							 quad(1,side2Index)-quad(1,side1Index),
							 quad(2,side2Index)-quad(2,side1Index);
					Vector3f side2;
					side2 << quad(0,side3Index)-quad(0,side2Index),
							 quad(1,side3Index)-quad(1,side2Index),
							 quad(2,side3Index)-quad(2,side2Index);
					cross = side1.cross(side2);
					side1Index++;
				} while (cross.norm() < 0.00001 && side1Index<4);
				
				glNormal3f(cross(0), cross(1), cross(2));
				glVertex3f(quad(0,0), quad(1,0), quad(2,0));
				glVertex3f(quad(0,1), quad(1,1), quad(2,1));
				glVertex3f(quad(0,2), quad(1,2), quad(2,2));
				glVertex3f(quad(0,3), quad(1,3), quad(2,3));
			}
		}
		glEnd();
	}
	
	glEndList();
	
	glCallList(index);
	glDeleteLists(index,1);
}

void addTriangles() {
	glColor3f(0.0f, 0.5f, 1.0f); // blue
	
	GLuint index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	if (wireframe) {
		for (int a=0; a<triangles.size(); a++) {
			MatrixXf triangle = triangles[a];
			
			if (hiddenLine) {
				// draw giant black quad to block out frames behind it
				glColor3f(0.0f, 0.0f, 0.0f); // black
				glBegin(GL_TRIANGLES);
				glVertex3f(triangle(0,0), triangle(1,0), triangle(2,0));
				glVertex3f(triangle(0,1), triangle(1,1), triangle(2,1));
				glVertex3f(triangle(0,2), triangle(1,2), triangle(2,2));
				glEnd();
				glColor3f(0.0f, 0.5, 1.0f); // blue
			}
			
			glBegin(GL_LINE_STRIP);
			glVertex3f(triangle(0,0), triangle(1,0), triangle(2,0));
			glVertex3f(triangle(0,1), triangle(1,1), triangle(2,1));
			glVertex3f(triangle(0,2), triangle(1,2), triangle(2,2));
			glVertex3f(triangle(0,0), triangle(1,0), triangle(2,0));
			glEnd();
		}
	}
	else {
		glBegin(GL_TRIANGLES);
		if (smooth) {
			glShadeModel(GL_SMOOTH); //Enable smooth shading
			for (int a=0; a<triangles.size(); a++) {
				MatrixXf triangle = triangles[a];
				glNormal3f(triangle(0,3), triangle(1,3), triangle(2,3));
				glVertex3f(triangle(0,0), triangle(1,0), triangle(2,0));
				glNormal3f(triangle(0,4), triangle(1,4), triangle(2,4));
				glVertex3f(triangle(0,1), triangle(1,1), triangle(2,1));
				glNormal3f(triangle(0,5), triangle(1,5), triangle(2,5));
				glVertex3f(triangle(0,2), triangle(1,2), triangle(2,2));
			}
		}
		else {
			glShadeModel(GL_FLAT); //Enable smooth shading
			for (int a=0; a<triangles.size(); a++) {
				MatrixXf triangle = triangles[a];
				Vector3f side1; 
				side1 << triangle(0,1)-triangle(0,0),
						triangle(1,1)-triangle(1,0),
						triangle(2,1)-triangle(2,0);
				Vector3f side2;
				side2 << triangle(0,2)-triangle(0,1),
						triangle(1,2)-triangle(1,1),
						triangle(2,2)-triangle(2,1);
				Vector3f cross = side1.cross(side2);
				
				int side1Index = 0;
				do {
					int side2Index = (side1Index+1)%3;
					int side3Index = (side1Index+2)%3;
					Vector3f side1;
					side1 << triangle(0,side2Index)-triangle(0,side1Index),
							 triangle(1,side2Index)-triangle(1,side1Index),
							 triangle(2,side2Index)-triangle(2,side1Index);
					Vector3f side2;
					side2 << triangle(0,side3Index)-triangle(0,side2Index),
							 triangle(1,side3Index)-triangle(1,side2Index),
							 triangle(2,side3Index)-triangle(2,side2Index);
					cross = side2.cross(side1);
					side1Index++;
				} while (cross.norm() < 0.00001 && side1Index<3);
				
				glNormal3f(cross(0), cross(1), cross(2));
				glVertex3f(triangle(0,0), triangle(1,0), triangle(2,0));
				glVertex3f(triangle(0,1), triangle(1,1), triangle(2,1));
				glVertex3f(triangle(0,2), triangle(1,2), triangle(2,2));
			}
		}
		glEnd();
	}
	
	glEndList();
	
	glCallList(index);
	glDeleteLists(index,1);
	
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// put pinhole at 0, 0, -8
	glTranslatef(translateX, translateY, -12.0 / zoom);
	
	addLights();
	
	glRotatef(rotateY, 1.0f, 0.0f, 0.0f);
	glRotatef(rotateX, 0.0f, 1.0f, 0.0f);
	
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

void Window::addTriangle(MatrixXf triangle) {
	triangles.push_back(triangle);
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
	glutSpecialFunc(handleSpecialKeypress);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
}

