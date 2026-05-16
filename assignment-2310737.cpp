#include <Windows.h>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <glut.h>

using namespace std;

#define PI			3.1415926
#define	COLORNUM	23
#define RED			0
#define GREEN		1
#define BLUE		2
#define YELLOW		3
#define MAGENTA		4
#define CYAN		5
#define DARK_GRAY	6
#define GRAY		7
#define LIGHT_GRAY	8
#define LIGHT_RED	9
#define LIGHT_GREEN	10
#define LIGHT_BLUE	11
#define BLACK		12
#define STEEL_BLUE	13
#define DEEP_BLUE	14
#define WHITE		15
#define MID_GRAY	16
#define LIGHTBROWN	17
#define DARKBROWN	18
#define MATTE_RED	19
#define MATTE_GRAY	20
#define MATTE_LIGHTBROWN	21
#define MATTE_DARKBROWN		22

const float DEG2RAD = 3.14159f / 180.0f;
bool 	isFlat = true;

float	ColorArr[COLORNUM][3] = {
					{ 1.0, 0.0, 0.0 }, //RED
					{ 0.0, 1.0, 0.0 }, //GREEN
					{ 0.0,  0.0, 1.0 }, //BLUE
					{ 1.0, 1.0,  0.0 }, //YELLOW
					{ 1.0, 0.0, 1.0 }, //MAGENTA
					{ 0.0, 1.0, 1.0 }, //CYAN
					{ 0.3, 0.3, 0.3 }, //DARK_GRAY
					{ 0.5, 0.5, 0.5 }, //GRAY
					{ 0.9,  0.9, 0.9 }, //LIGHT_GRAY
					{ 1.0, 0.5,  0.5 }, //LIGHT_RED
					{ 0.5, 1.0, 0.5 }, //LIGHT_GREEN
					{ 0.5, 0.5, 1.0 }, //LIGHT_BLUE
					{ 0.0, 0.0, 0.0 }, //BLACK
					{ 20/255.0, 136/255.0, 219/255.0 }, //STEEL_BLUE
					{ 3/255.0, 43/255.0, 145/255.0 }, //DEEP_BLUE
					{ 1.0, 1.0, 1.0 }, //WHITE
					{ 0.5, 0.5, 0.5 }, //MID_GRAY
					{ 221/255.0, 189/255.0, 172/255.0 }, //LIGHTBROWN
					{ 196/255.0, 140/255.0, 111/255.0 }, //DARKBROWN
					{ 1.0f, 0.0f, 0.0f }, //MATTE_RED
					{ 0.8f, 0.8f, 0.8f }, //MATTE_GRAY
					{ 221/255.0f, 189/255.0f, 172/255.0f }, //MATTE_LIGHTBROWN
					{ 196/255.0f, 140/255.0f, 111/255.0f }, //MATTE_DARKBROWN
};

GLfloat mat_ambient_list[COLORNUM][3] = {
					{ 0.20f, 0.00f, 0.00f }, //RED
					{ 0.00f, 0.20f, 0.00f }, //GREEN
					{ 0.00f, 0.00f, 0.20f }, //BLUE
					{ 0.20f, 0.20f, 0.00f }, //YELLOW
					{ 0.20f, 0.00f, 0.20f }, //MAGENTA
					{ 0.00f, 0.20f, 0.20f }, //CYAN
					{ 0.06f, 0.06f, 0.06f }, //DARK_GRAY
					{ 0.10f, 0.10f, 0.10f }, //GRAY
					{ 0.18f, 0.18f, 0.18f }, //LIGHT_GRAY
					{ 0.20f, 0.10f, 0.10f }, //LIGHT_RED
					{ 0.10f, 0.20f, 0.10f }, //LIGHT_GREEN
					{ 0.10f, 0.10f, 0.20f }, //LIGHT_BLUE
					{ 0.00f, 0.00f, 0.00f }, //BLACK
					{ 0.016f,0.107f,0.172f }, //STEEL_BLUE
					{ 0.002f,0.034f,0.114f }, //DEEP_BLUE
					{ 0.20f, 0.20f, 0.20f }, //WHITE
					{ 0.10f, 0.10f, 0.10f }, //MID_GRAY
					{ 0.17f, 0.15f, 0.13f }, //LIGHTBROWN
					{ 0.15f, 0.11f, 0.09f }, //DARKBROWN
					{ 0.05f, 0.00f, 0.00f }, //MATTE_RED
					{ 0.08f, 0.08f, 0.08f }, //MATTE_GRAY
					{ 0.14f, 0.12f, 0.10f }, //MATTE_LIGHTBROWN
					{ 0.12f, 0.09f, 0.07f }, //MATTE_DARKBROWN
};

GLfloat mat_diffuse_list[COLORNUM][3] = {
					{ 1.0, 0.0, 0.0 }, //RED
					{ 0.0, 1.0, 0.0 }, //GREEN
					{ 0.0,  0.0, 1.0 }, //BLUE
					{ 1.0, 1.0,  0.0 }, //YELLOW
					{ 1.0, 0.0, 1.0 }, //MAGENTA
					{ 0.0, 1.0, 1.0 }, //CYAN
					{ 0.3, 0.3, 0.3 }, //DARK_GRAY
					{ 0.5, 0.5, 0.5 }, //GRAY
					{ 0.9,  0.9, 0.9 }, //LIGHT_GRAY
					{ 1.0, 0.5,  0.5 }, //LIGHT_RED
					{ 0.5, 1.0, 0.5 }, //LIGHT_GREEN
					{ 0.5, 0.5, 1.0 }, //LIGHT_BLUE
					{ 0.0, 0.0, 0.0 }, //BLACK
					{ 20/255.0, 136/255.0, 219/255.0 }, //STEEL_BLUE
					{ 3/255.0, 43/255.0, 145/255.0 }, //DEEP_BLUE
					{ 1.0, 1.0, 1.0 }, //WHITE
					{ 0.5, 0.5, 0.5 }, //MID_GRAY
					{ 221/255.0f, 189/255.0f, 172/255.0f }, //LIGHTBROWN
					{ 196/255.0f, 140/255.0f, 111/255.0f }, //DARKBROWN
					{ 1.0f, 0.0f, 0.0f }, //MATTE_RED
					{ 0.40f, 0.40f, 0.40f }, //MATTE_GRAY
					{ 0.70f, 0.60f, 0.54f }, //MATTE_LIGHTBROWN
					{ 0.60f, 0.43f, 0.34f }, //MATTE_DARKBROWN
};

GLfloat mat_specular_list[COLORNUM][3] = {
					{ 0.8f, 0.8f, 0.8f }, //RED
					{ 0.8f, 0.8f, 0.8f }, //GREEN
					{ 0.8f, 0.8f, 0.8f }, //BLUE
					{ 0.8f, 0.8f, 0.8f }, //YELLOW
					{ 0.8f, 0.8f, 0.8f }, //MAGENTA
					{ 0.8f, 0.8f, 0.8f }, //CYAN
					{ 0.6f, 0.6f, 0.6f }, //DARK_GRAY
					{ 0.7f, 0.7f, 0.7f }, //GRAY
					{ 0.9f, 0.9f, 0.9f }, //LIGHT_GRAY
					{ 0.2f, 0.2f, 0.2f }, //LIGHT_RED
					{ 0.8f, 0.8f, 0.8f }, //LIGHT_GREEN
					{ 0.8f, 0.8f, 0.8f }, //LIGHT_BLUE
					{ 0.3f, 0.3f, 0.3f }, //BLACK
					{ 0.8f, 0.8f, 0.8f }, //STEEL_BLUE
					{ 0.8f, 0.8f, 0.8f }, //DEEP_BLUE
					{ 1.0f, 1.0f, 1.0f }, //WHITE
					{ 0.7f, 0.7f, 0.7f }, //MID_GRAY
					{ 0.6f, 0.6f, 0.6f }, //LIGHTBROWN
					{ 0.5f, 0.5f, 0.5f }, //DARKBROWN
					{ 0.05f, 0.05f, 0.05f }, //MATTE_RED
					{ 0.05f, 0.05f, 0.05f }, //MATTE_GRAY
					{ 0.05f, 0.05f, 0.05f }, //MATTE_LIGHTBROWN
					{ 0.05f, 0.05f, 0.05f }, //MATTE_DARKBROWN
};

GLfloat mat_shininess_list[COLORNUM][1] = {
	{50}, //RED
	{50}, //GREEN
	{40}, //BLUE
	{50}, //YELLOW
	{50}, //MAGENTA
	{30}, //CYAN
	{50}, //DARK_GRAY
	{80}, //GRAY
	{15}, //LIGHT_GRAY
	{40}, //LIGHT_RED
	{40}, //LIGHT_GREEN
	{10}, //LIGHT_BLUE
	{40}, //BLACK
	{40}, //STEEL_BLUE
	{80}, //DEEP_BLUE
	{50}, //WHITE
	{25}, //MID_GRAY
	{25}, //LIGHTBROWN
	{10}, //DARKBROWN
	{50}, //MATTE_RED
	{50}, //MATTE_GRAY
	{40}, //MATTE_LIGHTBROWN
	{50} //MATTE_DARKBROWN
};

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
	void normalize()
	{
		float len = sqrt(x*x + y*y + z*z);
		if (len > 1e-6f) { x /= len; y /= len; z /= len; }
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
	Point3 faceNormal;

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
	Point3*		vertNormal;

	int		numFaces;
	int colorIdx;
	Face*		face;
	float		slideX, slideY, slideZ;
	float		rotateX, rotateY, rotateZ;
	float		scaleX, scaleY, scaleZ;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		vertNormal = NULL;
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
		if (vertNormal != NULL)
		{
			delete[] vertNormal;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void CalculateFacesNorm();
	void CalculateVertexNormals();
	void SetColor(int colorIdx);
	void SetMaterial();
	void DrawWireframe();
	void DrawColor();
	void DrawPoint();
	void Draw();

	void CreateTorus(int fSizeA, int fSizeD, int colorIdx);
	void CreateCylinder(int nSegment, float fHeight, float fRadius, int colorIdx);
	void CreateBKLogo(float rhombusLength);
	void CreateFlowerFloor();
};

void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float nx = 0, ny = 0, nz = 0;
		int n = face[f].nVerts;
		for (int i = 0; i < n; i++)
		{
			Point3& cur  = pt[face[f].vert[i].vertIndex];
			Point3& next = pt[face[f].vert[(i + 1) % n].vertIndex];
			nx += (cur.y  - next.y) * (cur.z  + next.z);
			ny += (cur.z  - next.z) * (cur.x  + next.x);
			nz += (cur.x  - next.x) * (cur.y  + next.y);
		}
		face[f].faceNormal = Point3(nx, ny, nz);
		face[f].faceNormal.normalize();
	}
}

void Mesh::CalculateVertexNormals()
{
	if (vertNormal) { delete[] vertNormal; }
	vertNormal = new Point3[numVerts];
	for (int i = 0; i < numVerts; i++)
		vertNormal[i] = Point3(0, 0, 0);
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			if (iv >= 0 && iv < numVerts)
			{
				vertNormal[iv].x += face[f].faceNormal.x;
				vertNormal[iv].y += face[f].faceNormal.y;
				vertNormal[iv].z += face[f].faceNormal.z;
			}
		}
	}
	for (int i = 0; i < numVerts; i++)
		vertNormal[i].normalize();
}

void Mesh::SetColor(int colorIdx)
{
	this->colorIdx = colorIdx;
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

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius, int colorIdx)
{
	this->colorIdx = colorIdx;
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
		int i_next = (i + 1) % nSegment;
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
		face[i].vert[0].vertIndex = i_next;
		face[i].vert[1].vertIndex = i;
		face[i].vert[2].vertIndex = i + nSegment;
		face[i].vert[3].vertIndex = i_next + nSegment;
		for(int v = 0; v < 4; ++v)
			face[i].vert[v].colorIndex = colorIdx;
	}

	int j = nSegment;
	int k = 2 * nSegment;

	for(int i = 0; i < nSegment; ++i, ++j)
	{
		face[j].nVerts = 3;
		face[j].vert = new VertexID[face[j].nVerts];
		face[j].vert[0].vertIndex = i;
		face[j].vert[1].vertIndex = i < nSegment - 1 ? i + 1 : 0;
		face[j].vert[2].vertIndex = midPoint;
		for(int v = 0; v < face[j].nVerts; ++v)
		{
			face[j].vert[v].colorIndex = colorIdx;
		}
	}

	for(int i = 0; i < nSegment; ++i, ++k)
	{
		face[k].nVerts = 3;
		face[k].vert = new VertexID[face[k].nVerts];
		face[k].vert[1].vertIndex = nSegment + i;
		face[k].vert[0].vertIndex = i < nSegment - 1 ? nSegment + i + 1 : nSegment;
		face[k].vert[2].vertIndex = midPoint2;
		for(int v = 0; v < face[k].nVerts; ++v)
		{
			face[k].vert[v].colorIndex = colorIdx;
		}
	}

	CalculateFacesNorm();
	CalculateVertexNormals();
}

void Mesh::CreateTorus(int fSizeA, int fSizeD, int colorIdx)
{
	this->colorIdx = colorIdx;
	int numU = 50, numV = 50;
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
			for(int v = 0; v < face[i * numV + j].nVerts; ++v)
			{
				face[i * numV + j].vert[v].colorIndex = colorIdx;
			}
		}
	}
	CalculateFacesNorm();
	CalculateVertexNormals();
}
void Mesh::CreateBKLogo(float rhombusLength)
{
	numVerts = 16 * 2;
	pt = new Point3[numVerts];

	float hort_leftMost = -2 * rhombusLength * sqrt(3)/2;
	float hort_left = -rhombusLength * sqrt(3)/2;
	float hort_mid = 0;
	float hort_right = rhombusLength * sqrt(3)/2;
	float hort_rightMost = 2 * rhombusLength * sqrt(3)/2;

	float vert_topMost = rhombusLength * 2;
	float vert_top_3 = rhombusLength * 3/2;
	float vert_top_2 = rhombusLength;
	float vert_top = rhombusLength / 2;
	float vert_mid = 0;
	float vert_bot = -rhombusLength / 2;
	float vert_bot_2 = -rhombusLength;
	float vert_botMost = -rhombusLength * 3/2;

	numFaces = 18 * 2 + 12;
	face = new Face[numFaces];
	for(int i = 0; i < 18 * 2; ++i)
	{
		face[i].nVerts = 3;
		face[i].vert = new VertexID[3];
	}

	for(int i = 18 * 2; i < 18 * 2 + 12; ++i)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
	}

	pt[0].set(hort_mid, vert_topMost, 0);
	pt[1].set(hort_left, vert_top_3, 0);
	pt[2].set(hort_mid, vert_top_2, 0);
	pt[3].set(hort_left, vert_top, 0);
	pt[4].set(hort_right, vert_top_3, 0);
	pt[5].set(hort_right, vert_top, 0);
	pt[6].set(hort_mid, vert_mid, 0);
	pt[7].set(hort_leftMost, vert_mid, 0);
	pt[8].set(hort_left, vert_bot, 0);
	pt[9].set(hort_mid, vert_bot_2, 0);
	pt[10].set(hort_right, vert_bot, 0);
	pt[11].set(hort_rightMost, vert_mid, 0);
	pt[12].set(hort_leftMost, vert_bot_2, 0);
	pt[13].set(hort_left, vert_botMost, 0);
	pt[14].set(hort_right, vert_botMost, 0);
	pt[15].set(hort_rightMost, vert_bot_2, 0);

	for(int i = 16; i < 32; ++i)
	{
		pt[i].set(pt[i - 16].x, pt[i - 16].y, .25);
	}

	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;

	face[1].vert[0].vertIndex = 1;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 3;

	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 2;
	face[2].vert[2].vertIndex = 4;

	face[3].vert[0].vertIndex = 2;
	face[3].vert[1].vertIndex = 4;
	face[3].vert[2].vertIndex = 5;

	face[4].vert[0].vertIndex = 3;
	face[4].vert[1].vertIndex = 2;
	face[4].vert[2].vertIndex = 6;

	face[5].vert[0].vertIndex = 2;
	face[5].vert[1].vertIndex = 5;
	face[5].vert[2].vertIndex = 6;

	face[6].vert[0].vertIndex = 3;
	face[6].vert[1].vertIndex = 7;
	face[6].vert[2].vertIndex = 8;

	face[7].vert[0].vertIndex = 3;
	face[7].vert[1].vertIndex = 6;
	face[7].vert[2].vertIndex = 8;

	face[8].vert[0].vertIndex = 6;
	face[8].vert[1].vertIndex = 5;
	face[8].vert[2].vertIndex = 10;

	face[9].vert[0].vertIndex = 5;
	face[9].vert[1].vertIndex = 11;
	face[9].vert[2].vertIndex = 10;

	face[10].vert[0].vertIndex = 7;
	face[10].vert[1].vertIndex = 8;
	face[10].vert[2].vertIndex = 12;

	face[11].vert[0].vertIndex = 6;
	face[11].vert[1].vertIndex = 8;
	face[11].vert[2].vertIndex = 9;

	face[12].vert[0].vertIndex = 6;
	face[12].vert[1].vertIndex = 9;
	face[12].vert[2].vertIndex = 10;

	face[13].vert[0].vertIndex = 10;
	face[13].vert[1].vertIndex = 11;
	face[13].vert[2].vertIndex = 15;

	face[14].vert[0].vertIndex = 12;
	face[14].vert[1].vertIndex = 8;
	face[14].vert[2].vertIndex = 13;

	face[15].vert[0].vertIndex = 8;
	face[15].vert[1].vertIndex = 13;
	face[15].vert[2].vertIndex = 9;

	face[16].vert[0].vertIndex = 9;
	face[16].vert[1].vertIndex = 10;
	face[16].vert[2].vertIndex = 14;

	face[17].vert[0].vertIndex = 10;
	face[17].vert[1].vertIndex = 14;
	face[17].vert[2].vertIndex = 15;

	for(int i = 18; i < 18 * 2; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			face[i].vert[j].vertIndex = face[i - 18].vert[j].vertIndex + 16;
		}
	}

	int edgeVertexes[12] = {1, 0, 4, 5, 11, 15, 14, 9, 13, 12, 7, 3};

	for(int i = 0; i < 12; ++i)
	{
		face[i + 36].vert[0].vertIndex = edgeVertexes[i];
		face[i + 36].vert[1].vertIndex = i < 12 - 1 ? edgeVertexes[i + 1] : edgeVertexes[0];
		face[i + 36].vert[2].vertIndex = i < 12 - 1 ? edgeVertexes[i + 1] + 16 : edgeVertexes[0] + 16;
		face[i + 36].vert[3].vertIndex = edgeVertexes[i] + 16;
	}

	int lightBlue[12] = {2, 3, 6, 10, 16, 17, 37, 38, 41, 42, 45, 46};
	int deepBlue[12] = {0, 1, 9, 13, 14, 15, 36, 39, 40, 43, 44, 47};
	int white[6] = {4, 5, 7, 8, 11, 12};

	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			face[lightBlue[i]].vert[j].colorIndex = STEEL_BLUE;
			face[deepBlue[i]].vert[j].colorIndex = DEEP_BLUE;
			face[white[i]].vert[j].colorIndex = WHITE;

			face[lightBlue[i] + 18].vert[j].colorIndex = STEEL_BLUE;
			face[deepBlue[i] + 18].vert[j].colorIndex = DEEP_BLUE;
			face[white[i] + 18].vert[j].colorIndex = WHITE;

		}
	}

	for(int i = 6; i < 12; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			face[lightBlue[i]].vert[j].colorIndex = STEEL_BLUE;
			face[deepBlue[i]].vert[j].colorIndex = DEEP_BLUE;
		}
	}
	CalculateFacesNorm();
	CalculateVertexNormals();
}

void Mesh::CreateFlowerFloor()
{
	int nSegments = 72;
	int nPetals = 8;
	numVerts = nSegments * 4 + nPetals * 3 + 1;
	pt = new Point3[numVerts];

	float phi_increment = 360.0f / nSegments;
	float radius_list[4] = { 1.5f, 2.0f, 2.5f, 3.0f };

	float bigPetalP = 2.5f;
	float bigPetalSide = 2.5f / 2 / cos(DEG2RAD * 22.5f);
	float smallPetalP = bigPetalSide;
	float smallPetalSide = smallPetalP / 2 / cos(DEG2RAD * 22.5f);

	int petalStart = nSegments * 4;
	for(int r = 0; r < 4; ++r)
	{
		float phi = 0.0f;
		for(int i = 0; i < nSegments; ++i)
		{
			pt[r * nSegments + i].set(radius_list[r] * cos(DEG2RAD * phi), radius_list[r] * sin(DEG2RAD * phi), 0);
			phi += phi_increment;
		}
	}

	for(int i = 0; i < nPetals; ++i)
	{
		float phi = i * 360.0f / nPetals;
		pt[petalStart + i].set(bigPetalP * cos(DEG2RAD * phi), bigPetalP * sin(DEG2RAD * phi), 0.1);
		pt[petalStart + nPetals + i].set(smallPetalP * cos(DEG2RAD * (phi + 22.5f)), smallPetalP * sin(DEG2RAD * (phi + 22.5f)), 0.1);
		pt[petalStart + nPetals * 2 + i].set(smallPetalSide * cos(DEG2RAD * phi), smallPetalSide * sin(DEG2RAD * phi), 0.1);
	}

	pt[numVerts - 1].set(0, 0, 0.1);

	numFaces = nSegments * 2 + nPetals * 3;
	face = new Face[numFaces];

	for(int i = 0; i < nSegments; ++i)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = nSegments + i;
		face[i].vert[2].vertIndex = nSegments + (i + 1) % nSegments;
		face[i].vert[3].vertIndex = (i + 1) % nSegments;
		for(int v = 0; v < 4; ++v)
			face[i].vert[v].colorIndex = MATTE_GRAY;
	}

	for(int i = 0; i < nSegments; ++i)
	{
		int faceIdx = nSegments + i;
		face[faceIdx].nVerts = 4;
		face[faceIdx].vert = new VertexID[4];
		face[faceIdx].vert[0].vertIndex = 2 * nSegments + i;
		face[faceIdx].vert[1].vertIndex = 3 * nSegments + i;
		face[faceIdx].vert[2].vertIndex = 3 * nSegments + (i + 1) % nSegments;
		face[faceIdx].vert[3].vertIndex = 2 * nSegments + (i + 1) % nSegments;
		for(int v = 0; v < 4; ++v)
			face[faceIdx].vert[v].colorIndex = MATTE_GRAY;
	}

	int petalFaceStart = nSegments * 2;
	for(int i = 0; i < nPetals; ++i)
	{
		int faceIdx = petalFaceStart + i;
		face[faceIdx].nVerts = 4;
		face[faceIdx].vert = new VertexID[4];
		face[faceIdx].vert[0].vertIndex = petalStart + i;
		face[faceIdx].vert[1].vertIndex = petalStart + nPetals + i;
		face[faceIdx].vert[2].vertIndex = petalStart + nPetals * 2 + i;
		face[faceIdx].vert[3].vertIndex = i == 0 ? petalStart + nPetals * 2 - 1 : petalStart + nPetals + i - 1;
		for(int v = 0; v < 4; ++v)
			face[faceIdx].vert[v].colorIndex = i % 2 == 0 ? MATTE_LIGHTBROWN : MATTE_DARKBROWN;

		face[faceIdx + nPetals].nVerts = 3;
		face[faceIdx + nPetals].vert = new VertexID[3];
		face[faceIdx + nPetals].vert[0].vertIndex = petalStart + nPetals * 2 + i;
		face[faceIdx + nPetals].vert[1].vertIndex = petalStart + nPetals + i;
		face[faceIdx + nPetals].vert[2].vertIndex = numVerts - 1;
		for(int v = 0; v < 3; ++v)
			face[faceIdx + nPetals].vert[v].colorIndex = BLACK;

		face[faceIdx + nPetals * 2].nVerts = 3;
		face[faceIdx + nPetals * 2].vert = new VertexID[3];
		face[faceIdx + nPetals * 2].vert[0].vertIndex = petalStart + nPetals + i;
		face[faceIdx + nPetals * 2].vert[1].vertIndex = petalStart + nPetals * 2 + ((i + 1) % nPetals);
		face[faceIdx + nPetals * 2].vert[2].vertIndex = numVerts - 1;
		for(int v = 0; v < 3; ++v)
			face[faceIdx + nPetals * 2].vert[v].colorIndex = WHITE;
	}
	CalculateFacesNorm();
	CalculateVertexNormals();
}

void Mesh::SetMaterial()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT, mat_ambient_list[colorIdx]);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_diffuse_list[colorIdx]);
	glMaterialfv(GL_FRONT,GL_SPECULAR, mat_specular_list[colorIdx]);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_list[colorIdx]);
}

void Mesh::Draw()
{
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRotatef(rotateX, 1, 0, 0);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateZ, 0, 0, 1);
	glTranslatef(slideX, slideY, slideZ);
	glScalef(scaleX, scaleY, scaleZ);

	int lastColorIdx = -1;
	for(int f = 0; f < numFaces; f++)
	{
		if (face[f].nVerts == 0 || face[f].vert == NULL) continue;
		int faceColorIdx = face[f].vert[0].colorIndex;
		if (faceColorIdx != lastColorIdx)
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient_list[faceColorIdx]);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse_list[faceColorIdx]);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular_list[faceColorIdx]);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess_list[faceColorIdx]);
			lastColorIdx = faceColorIdx;
		}
		glBegin(GL_POLYGON);
		for(int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			if (isFlat || !vertNormal)
				glNormal3f(face[f].faceNormal.x, face[f].faceNormal.y, face[f].faceNormal.z);
			else
				glNormal3f(vertNormal[iv].x, vertNormal[iv].y, vertNormal[iv].z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
	glPopMatrix();
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

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	GLfloat noSpec[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat noShin[] = {0.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  noSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, noShin);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			if (isFlat || !vertNormal)
				glNormal3f(face[f].faceNormal.x, face[f].faceNormal.y, face[f].faceNormal.z);
			else
				glNormal3f(vertNormal[iv].x, vertNormal[iv].y, vertNormal[iv].z);
			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
	glDisable(GL_COLOR_MATERIAL);
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

int		screenWidth = 1280;
int		screenHeight = 720;

float		angle = 180;

float	camera_angle  = -25.0f;
float	camera_height = 5.0f;
float	camera_dis    = 30.0f;

int		nChoice = 0;
float 	baseAngle = 0;
float 	frameAngle = 0;
float 	gimbal1Angle = 0;
float 	gimbal2Angle = 0;
float 	bkAngle = 0;

Mesh		base;
Mesh		baseConnector;
Mesh		bk;
Mesh		frame;
Mesh		frame_connector_1;
Mesh		frame_connector_2;
Mesh		gimbal1;
Mesh		gimbal1_connector_1;
Mesh		gimbal1_connector_2;
Mesh 		rotor;	
Mesh		gimbal2;
Mesh		gimbal2_connector_1;
Mesh		gimbal2_connector_2;
Mesh		flowerFloor[20 * 20];

void drawAxis()
{
	glDisable(GL_LIGHTING);
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(6, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 6, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 6);
	glEnd();
}

void setLight()
{
	GLfloat	lightDiffuse[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat	lightSpecular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat	lightAmbient[]={0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat light_position[]={6.0f, 6.0f, 6.0f, 0.0f};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light_position2[]={-6.0f, 6.0f, -6.0f, 0.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

	glEnable(GL_LIGHT1);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float camera_X = sin(DEG2RAD * camera_angle) * camera_dis;
	float camera_Z = cos(DEG2RAD * camera_angle) * camera_dis;
	gluLookAt(camera_X, camera_height, camera_Z, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth, screenHeight);

	setLight();

	glPushMatrix();
		glShadeModel(isFlat ? GL_FLAT : GL_SMOOTH);
		glRotatef(baseAngle, 0, 1, 0);
		base.Draw();
		baseConnector.Draw();
		frame.Draw();
		frame_connector_1.Draw();
		frame_connector_2.Draw();

		glPushMatrix();
			glTranslatef(0, gimbal1.slideY, 0);
			glRotatef(gimbal1Angle, 1, 0, 0);
			glTranslatef(0, -gimbal1.slideY, 0);
			gimbal1.Draw();
			gimbal1_connector_1.Draw();
			gimbal1_connector_2.Draw();

			glPushMatrix();
				glTranslatef(0, gimbal2.slideY, 0);
				glRotatef(gimbal2Angle, 0, 1, 0);
				glTranslatef(0, -gimbal2.slideY, 0);
				gimbal2.Draw();
				rotor.Draw();
				glPushMatrix();
					glTranslatef(0, bk.slideY, 0);
					glRotatef(-bkAngle, 1, 0, 0);
					glTranslatef(0, -bk.slideY, 0);
					bool lastIsFlat = isFlat;
					glShadeModel(GL_FLAT);
					isFlat = true;
					bk.Draw();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glShadeModel(GL_FLAT);
	isFlat = true;
	isFlat = lastIsFlat;

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	for(int i = 0; i < 20 * 20; ++i)
	{
		flowerFloor[i].Draw();
	}
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glFlush();
	glutSwapBuffers();
}
void mySpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:  camera_angle += 1.0f;    break;
	case GLUT_KEY_RIGHT: camera_angle -= 1.0f;    break;
	case GLUT_KEY_UP:    camera_height += 0.5f;   break;
	case GLUT_KEY_DOWN:  camera_height -= 0.5f;   break;
	}
	glutPostRedisplay();
}
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		baseAngle    += 5.0f;
		break;
	case '2':
		baseAngle    -= 5.0f;
		break;
	case '3':
		gimbal1Angle += 5.0f;
		break;
	case '4':
		gimbal1Angle -= 5.0f;
		break;
	case '5':
		gimbal2Angle += 5.0f;
		break;
	case '6':
		gimbal2Angle -= 5.0f;
		break;
	case '7':
		bkAngle      += 5.0f;
		break;
	case '8':
		bkAngle      -= 5.0f;
		break;
	case '+':
	case '=':
		camera_dis += 0.5f;
		break;
	case '-':
		camera_dis -= 0.5f;
		if (camera_dis < 0.5f) camera_dis = 0.5f;
		break;
	case 'F':
	case 'f':
		isFlat = true;
		break;
	case 'S':
	case 's':
		isFlat = false;
		break;
	case 'R':
	case 'r':
		baseAngle = frameAngle = gimbal1Angle = bkAngle = gimbal2Angle = 0.0f;
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
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)screenWidth / screenHeight, 0.1f, 1000.0f);
}

int main(int argc, _TCHAR* argv[])
{
	printf("1, 2: Rotate the base\n");
	printf("3, 4: Rotate the gimbal 1\n");
	printf("5, 6: Rotate the gimbal 2\n");
	printf("7, 8: Rotate the rotor\n");
	printf("R, r: Reset the Gyroscope\n");
	printf("F, f: Switch to flat shading\n");
	printf("S, s: Switch to smooth shading\n");
	printf("+	: to increase camera distance\n");
	printf("-	: to decrease camera distance\n");
	printf("up arrow: to increase camera height\n");
	printf("down arrow: to decrease camera height\n");
	printf("<-	: to rotate camera clockwise\n");
	printf("->	: to rotate camera counterclockwise\n");
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment - Tran Nhat Dang - 2310737");

	myInit();
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);

	int cylinderSegments = 25;

	base.CreateCylinder(cylinderSegments, .15, 1.25, MATTE_RED);
	base.slideY = -2.5;
	baseConnector.CreateCylinder(cylinderSegments, 0.65, 0.25, MATTE_RED);
	baseConnector.slideY = -1.5;
	frame.CreateTorus(1, 15, RED);
	frame.slideY = 3.1;
	frame.scaleX = 0.25f;
	frame.scaleY = 0.25f;
	frame.scaleZ = 0.25f;
	frame_connector_1.CreateCylinder(cylinderSegments, .4, .2, RED);
	frame_connector_1.slideX = 3.1;
	frame_connector_1.slideY = 3.1;
	frame_connector_1.rotateZ = 90;
	frame_connector_2.CreateCylinder(cylinderSegments, .4, .2, RED);
	frame_connector_2.slideX = 3.1;
	frame_connector_2.slideY = -3.1;
	frame_connector_2.rotateZ = 90;
	gimbal1.CreateTorus(1, 13, BLUE);
	gimbal1.slideY = 3.1;
	gimbal1.scaleX = 0.2f;
	gimbal1.scaleY = 0.2f;
	gimbal1.scaleZ = 0.2f;
	gimbal1_connector_1.CreateCylinder(cylinderSegments, 0.15, 0.2, BLUE);
	gimbal1_connector_1.slideY = 0.8;
	gimbal1_connector_2.CreateCylinder(cylinderSegments, 0.15, 0.2, BLUE);
	gimbal1_connector_2.slideY = 5.4;
	gimbal2.CreateTorus(1, 10, GREEN);
	gimbal2.slideY = 3.1;
	gimbal2.scaleX = 0.2f;
	gimbal2.scaleY = 0.2f;
	gimbal2.scaleZ = 0.2f;
	rotor.CreateCylinder(cylinderSegments, 1.8, 0.2, GREEN);
	rotor.slideY = 0;
	rotor.slideX = 3.1;
	rotor.rotateZ = 90;
	bk.CreateBKLogo(.8);
	bk.slideY = 3.1;
	bk.slideZ = -0.1f;
	bk.rotateY = 90;
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 20; ++j)
		{
			flowerFloor[i * 20 + j].CreateFlowerFloor();
			flowerFloor[i * 20 + j].rotateX = -90.0f;
			flowerFloor[i * 20 + j].slideX = (i - 10) * 6;
			flowerFloor[i * 20 + j].slideY = (j - 10) * 6;
			flowerFloor[i * 20 + j].slideZ = -2.7f;
		}
	}

	glutMainLoop();
	return 0;
}
