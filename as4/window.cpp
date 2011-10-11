#include "window.h"
#include "FreeImage.h"

int width = 400;
int height = 400;

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

void Window::initialize(int argc, char *argv[], int width, int height) {
	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("Render");

   	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	onGlutResize(width, height);
	
  	glutDisplayFunc(onGlutRedraw);
  	glutReshapeFunc(onGlutResize);	// resized window
  	glutIdleFunc(onGlutIdle);
}

void Window::show() {
	glutMainLoop();
}

void Window::saveFile() {
	FreeImage_Initialise();
	
	FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);
	RGBQUAD color;
	int counter = 0;
	
	if (!bitmap)
		exit (1);
		
	//Draws a gradient from blue to green;
	for (int a=0; a<pixels.size(); a++) {
			Pixel current = pixels[a];
			color.rgbRed = (double) current.r * 255.0;
			color.rgbGreen = (double) current.g * 255.0;
			color.rgbBlue = (double) current.b * 255.0;
			FreeImage_SetPixelColor(bitmap, current.x, current.y, &color);
			counter++;
	}
	
	if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
		cout << "Image_successfully_saved!" <<endl;
	
	FreeImage_DeInitialise(); 
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

void gl_setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
	glColor3f(r, g, b);
	glVertex2f(x+0.5, y+0.5);
}

Pixel Window::getPixel(int pos) {
	return pixels[pos];
}

void Window::render() {
	glBegin(GL_POINTS);
		
	for (int a=0; a<pixels.size(); a++) {
		// if (!(pixels[a].r>=0&&pixels[a].r<=1)) {
		// 	cout << "warning: invalid pixel [location] (color) ";
		// 	pixels[a].print();
		// }
		gl_setPixel(pixels[a].x, pixels[a].y, pixels[a].r, pixels[a].g, pixels[a].b);
	}
	
	glEnd();
}

