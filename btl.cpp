#include <Windows.h>
#include <math.h>
#include <iostream>
#include <glut.h>

using namespace std;
/////////////////////////////////////////////////////////////////////
#define PI			3.1415926
#define	COLORNUM	14
const float DEG2RAD = 3.14159f / 180.0f;

float	ColorArr[COLORNUM][3] = { { 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0,  0.0, 1.0 },
					{ 1.0, 1.0,  0.0 },{ 1.0, 0.0, 1.0 },{ 0.0, 1.0, 1.0 },
					{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },{ 0.9,  0.9, 0.9 },
					{ 1.0, 0.5,  0.5 },{ 0.5, 1.0, 0.5 },{ 0.5, 0.5, 1.0 },
					{ 0.0, 0.0, 0.0 },{ 0.7, 0.7, 0.7 } };

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;

	int		numFaces;
	Face*		face;
	float		slideX, slideY, slideZ;
	float		rotateX, rotateY, rotateZ;
	float		scaleX, scaleY, scaleZ;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
		slideX = 0, slideY = 0, slideZ = 0;
		rotateX = 0, rotateY = 0, rotateZ = 0;
		scaleX = 1, scaleY = 1, scaleZ = 1;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void SetColor(int colorIdx);
	void DrawWireframe();
	void DrawColor();
	void DrawPoint();

	void CreateTorus(int fSizeA, int fSizeD);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateBKLogo();
};

void Mesh::SetColor(int colorIdx)
{
	for(int f = 0; f < numFaces; f++)
	{
		for(int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::DrawWireframe()
{
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRotatef(rotateX, 1, 0, 0);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateZ, 0, 0, 1);
	glTranslatef(slideX, slideY, slideZ);
	glScalef(scaleX, scaleY, scaleZ);

	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
	glPopMatrix();
}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	float angle = 0;
	float angle_increment = 360.0f / nSegment;

	for(int i = 0; i < nSegment; ++i)
	{
		pt[i].set(fRadius * cos(DEG2RAD * angle), -fHeight, fRadius * sin(DEG2RAD * angle));
		angle += angle_increment;
	}

	angle = 0;

	for(int i = nSegment; i < nSegment * 2; ++i)
	{
		pt[i].set(fRadius * cos(DEG2RAD * angle), fHeight, fRadius * sin(DEG2RAD * angle));
		angle += angle_increment;
	}

	pt[2 * nSegment].set(0, -fHeight, 0);
	pt[2 * nSegment + 1].set(0, fHeight, 0);

	int midPoint = 2 * nSegment;
	int midPoint2 = 2 * nSegment + 1;

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	for(int i = 0; i < nSegment; ++i)
	{
		face[i].nVerts = 6;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[2].vertIndex = i + nSegment;
		face[i].vert[3].vertIndex = i < nSegment - 1 ? i + nSegment + 1 : nSegment;
		face[i].vert[1].vertIndex = i;
		face[i].vert[0].vertIndex = i < nSegment - 1 ? i + 1 : 0;
		face[i].vert[5].vertIndex = 2 * nSegment;
		face[i].vert[4].vertIndex = 2 * nSegment + 1;
	}

	int j = nSegment;
	int k = 2 * nSegment;

	for(int i = 0; i < nSegment; ++i, ++j)
	{
		face[j].nVerts = 3;
		face[j].vert = new VertexID[face[j].nVerts];
		face[j].vert[1].vertIndex = i;
		face[j].vert[0].vertIndex = i < nSegment - 1 ? i + 1 : 0;
		face[j].vert[2].vertIndex = midPoint;
	}

	for(int i = 0; i < nSegment; ++i, ++k)
	{
		face[k].nVerts = 3;
		face[k].vert = new VertexID[face[k].nVerts];
		face[k].vert[0].vertIndex = nSegment + i;
		face[k].vert[1].vertIndex = i < nSegment - 1 ? nSegment + i + 1 : nSegment;
		face[k].vert[2].vertIndex = midPoint2;
	}
}

void Mesh::CreateTorus(int fSizeA, int fSizeD)
{
	int numU = 20, numV = 20;
	float u = 0.0f, v = 0.0f;
	float u_increment = 360.0f / numU, v_increment = 360.0f / numV;

	numVerts = (numU + 1) * numV;
	pt = new Point3[numVerts];

	for(int i = 0; i < numU + 1; ++i)
	{
		for(int j = 0; j < numV; ++j)
		{
			pt[i * numV + j].set((fSizeD + fSizeA * cos(DEG2RAD * v)) * cos(DEG2RAD * u), (fSizeD + fSizeA * cos(DEG2RAD * v)) * sin(DEG2RAD * u), fSizeA * sin(DEG2RAD * v));
			v += v_increment;
		}
		u += u_increment;
	}

	numFaces = (numU + 1) * numV;
	face = new Face[numFaces];

	for(int i = 0; i < numU; ++i)
	{
		for(int j = 0; j < numV; ++j)
		{
			face[i * numV + j].nVerts = 4;
			face[i * numV + j].vert = new VertexID[face[i * numV + j].nVerts];

			face[i * numV + j].vert[0].vertIndex = i * numV + j;
			face[i * numV + j].vert[1].vertIndex = i * numV + ((j + 1) % numV);
			face[i * numV + j].vert[3].vertIndex = i * numV + j + numV;
			face[i * numV + j].vert[2].vertIndex = i * numV + ((j + 1) % numV) + numV;
		}
	}
}
void Mesh::CreateBKLogo()
{
	numVerts = 100;
	pt = new Point3[numVerts];

}


void Mesh::DrawColor()
{
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRotatef(rotateX, 1, 0, 0);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateZ, 0, 0, 1);
	glTranslatef(slideX, slideY, slideZ);
	glScalef(scaleX, scaleY, scaleZ);

	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = f & COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
	glPopMatrix();
}
void Mesh::DrawPoint()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(3);
	glColor3f(0, 0, 0);
	for (int f = 0; f < numVerts; f++)
	{
		glBegin(GL_POINTS);
		glVertex3f(pt[f].x, pt[f].y, pt[f].z);
		glEnd();
	}
}


//////////////////////////////////////////////////////////////////////
int		screenWidth = 1000;
int		screenHeight = 500;

float		angle = 0;

int		nChoice = 0;

Mesh		base;
Mesh		bk;
Mesh		gimbal1;
Mesh		gimbal2;
Mesh		rotor;

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);//x - red
		glVertex3f(6, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);//y - green
		glVertex3f(0, 6, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);//z - blue
		glVertex3f(0, 0, 6);
	glEnd();
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 4, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////////////////////////////////////////////////////
	glViewport(0, 0, screenWidth, screenHeight);

	glPushMatrix();
	drawAxis();

	glRotatef(angle, 0, 1, 0);

	glutSolidCube(1);

	// gimbal1.SetColor(1);
	gimbal1.slideZ = 5;
	gimbal1.DrawColor();
	gimbal2.DrawColor();

	// base.SetColor(0);
	// base.scaleX = 0.05f;
	// base.scaleY = 0.05f;
	// base.scaleZ = 0.05f;
	// base.slideZ = -5;
	// base.DrawColor();

	glFlush();
	glutSwapBuffers();
}
void mySpecialFunc(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		angle = angle + 5;
	else if (key == GLUT_KEY_RIGHT)
		angle = angle - 5;

	glutPostRedisplay();
}
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		nChoice = 1;
		break;
	case '2':
		nChoice = 2;
		break;
	case '3':
		nChoice = 3;
		break;
	}
	glutPostRedisplay();
}
void myInit()
{
	float	fHalfSize = 5;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}


int main(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("BTL_DHMT"); // open the screen window

	myInit();
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);

	base.CreateCylinder(50, 1, 1);
	gimbal1.CreateTorus(1, 3);
	gimbal2.CreateTorus(3, 1);

	glutMainLoop();
	return 0;
}
