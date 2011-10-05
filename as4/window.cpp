#include "window.h"

void onGlutRedraw() {
	glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer
	glMatrixMode(GL_MODELVIEW);   // indicate we are specifying camera transformations
	glLoadIdentity();             // make sure transformation is "zero'd"
	
	Window::get()->render();
	
	glFlush();
	glutSwapBuffers();            // swap buffers (we earlier set double buffer)
}

void onGlutResize(int w, int h) {
	Window::get()->setSize(w, h);

	glViewport (0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	// glOrtho(-1, 1, -1, 1, 1, -1);

}

void onGlutIdle() {
	glutPostRedisplay();
}

Window* Window::singleton;
Window* Window::get() {
	if (!singleton) {
		singleton = new Window();
	}
	return singleton;
}

void Window::initialize(int argc, char *argv[]) {
	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("Render");

   	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	onGlutResize(400, 400);
	
  	glutDisplayFunc(onGlutRedraw);
  	glutReshapeFunc(onGlutResize);	// resized window
  	glutIdleFunc(onGlutIdle);
}

void Window::show() {
	glutMainLoop();
}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

void Window::setSize(int w, int h) {
	width = w;
	height = h;
}

void Window::pixel(int x, int y, float r, float g, float b) {
	Pixel p (x, y, r, g, b);
	pixels.push_back(p);
}

void Window::render() {
	glBegin(GL_POINTS);
	for (int a=0; a<pixels.size(); a++) {
		// if (!(pixels[a].r>=0&&pixels[a].r<=1)) {
		// 	cout << "warning: invalid pixel [location] (color) ";
		// 	pixels[a].print();
		// }
		glColor3f(pixels[a].r, pixels[a].g, pixels[a].b);
		glVertex2f(pixels[a].x, pixels[a].y);
	}
	glEnd();
}
