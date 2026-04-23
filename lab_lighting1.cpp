#include <windows.h>
#include <math.h>
#include <gl\glut.h>
#include <stdio.h>
#include <ctype.h>

const int screenWidth = 650;
const int screenHeight = 650;
int nChoice = 0;

GLfloat mat_ambient_list[10][3] = {
	{0.0, 0.0, 0.0},
	{0.329412, 0.223529, 0.027451},
	{0.2125, 0.1275, 0.027451},
	{0.25, 0.25, 0.25},
	{0.19125, 0.0735, 0.025},
	{0.24725, 0.1995, 0.0745},
	{0.10588, 0.058824, 0.113725},
	{0.19225, 0.19225, 0.19225},
	{0.23125, 0.23125, 0.23125}
};

GLfloat mat_diffuse_list[10][3] = {
	{0.01, 0.01, 0.01},
	{0.780392, 0.568627, 0.113725},
	{0.714, 0.4284, 0.18144},
	{0.4, 0.4, 0.4},
	{0.7038, 0.27048, 0.0828},
	{0.75164, 0.60648, 0.22648},
	{0.427451, 0.470588, 0.541176},
	{0.50754, 0.50754, 0.50754},
	{0.2775, 0.2775, 0.2775}
};

GLfloat mat_specular_list[10][3] = {
	{0.5, 0.5, 0.5},
	{0.992157, 0.941176, 0.807843},
	{0.393548, 0.271906, 0.166721},
	{0.774597, 0.774597, 0.774597},
	{0.256777, 0.256777, 0.256777},
	{0.628281, 0.555802, 0.366065},
	{0.3333, 0.3333, 0.521569},
	{0.508273, 0.508273, 0.508273},
	{0.773911, 0.773911, 0.773911}
};

GLfloat mat_shininess_list[10][1] = {
	{32},
	{27.8974},
	{25.6},
	{76.8},
	{12.8},
	{51.2},
	{9.84615},
	{51.2},
	{89.6}
};

GLfloat	mat_ambient[]={0.2f, 0.2f, 0.2f, 1.0f};
GLfloat	mat_diffuse[]={1.0f, 0.0f, 0.0f, 1.0f};
GLfloat	mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_shininess[] = {50.0f};

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
}
void setLight()
{
	GLfloat	lightAmbient[]={0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat	lightDiffuse[]={0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	lightSpecular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_position[]={2, 1, 2, 0.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
}
void setMaterial()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT, mat_ambient_list[nChoice]);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_diffuse_list[nChoice]);
	glMaterialfv(GL_FRONT,GL_SPECULAR, mat_specular_list[nChoice]);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_list[nChoice]);
}
void setCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2, 1, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void drawAxis()
{
	glDisable(GL_LIGHTING);

	float	xmax = 1.0, ymax = 1.0, zmax = 1.0;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(-xmax, 0, 0);
		glVertex3f(xmax, 0, 0);
		glVertex3f(0, -ymax, 0);
		glVertex3f(0, ymax, 0);
		glVertex3f(0, 0, -zmax);
		glVertex3f(0, 0, zmax);
	 glEnd();


	glColor3f(0.0, 0.0, 0.0);
	void * font = GLUT_BITMAP_TIMES_ROMAN_24;

	glRasterPos3f(1.0, 0, 0);
	glutBitmapCharacter(font, 'X');

	glRasterPos3f(0, 1.0, 0);
	glutBitmapCharacter(font, 'Y');

	glRasterPos3f(0, 0, 1.0);
	glutBitmapCharacter(font, 'Z');
}
void display()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	setCamera();
	drawAxis();
	setLight();

	setMaterial();

	glutSolidTeapot(0.5);

	glFlush();
}

void myKeyboard(unsigned char key, int x, int y)
{
	if(isdigit(key))
	{
		char keyy = key;
		nChoice = strtol(&keyy, NULL, 10) - 1;
		nChoice = fmax(fmin(nChoice, 10), 0);
	}
	glutPostRedisplay();
}


int main(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Lab Lighting"); // open the screen window

	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);

	init();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}
