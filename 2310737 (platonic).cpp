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
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
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
	void DrawWireframe();
	void DrawColor();
	void DrawPoint();


	void CreateCube(float fSize);
	void CreateTetrahedron(float fSize);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateSphere(int nSlice, int nStack, float radius);
	void CreateTorus(int fSizeA, int fSizeD);
	void CreatePlatonic8(float fSize);
	void CreatePlatonic12(float fSize);
	void CreatePlatonic20(float fSize);
};

void Mesh::CreateTetrahedron(float fSize)
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(fSize, 0, 0);
	pt[2].set(0, fSize, 0);
	pt[3].set(0, 0, fSize);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;


	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;


	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCube(float	fSize)
{
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;


	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
}


void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
	fSizeX /= 2;
	fSizeY /= 2;
	fSizeZ /= 2;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, -fSizeZ);
	pt[2].set(fSizeX, -fSizeY, fSizeZ);
	pt[3].set(fSizeX, -fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, fSizeY, fSizeZ);
	pt[5].set(-fSizeX, fSizeY, -fSizeZ);
	pt[6].set(-fSizeX, -fSizeY, fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

	numFaces = 6;
	face = new Face[numFaces];

	//front face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[3].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;

	//right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 1;
	face[1].vert[3].vertIndex = 4;
	face[1].vert[2].vertIndex = 5;

	//left face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 2;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[3].vertIndex = 6;
	face[2].vert[2].vertIndex = 7;

	//back face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 4;
	face[3].vert[1].vertIndex = 5;
	face[3].vert[3].vertIndex = 6;
	face[3].vert[2].vertIndex = 7;

	//top face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 2;
	face[4].vert[3].vertIndex = 4;
	face[4].vert[2].vertIndex = 6;

	//top face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 1;
	face[5].vert[1].vertIndex = 3;
	face[5].vert[3].vertIndex = 5;
	face[5].vert[2].vertIndex = 7;
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
		//std::cout << pt[i].x << ' ' << pt[i].y << ' ' << pt[i].z << std::endl;
		angle += angle_increment;
	}

	angle = 0;

	for(int i = nSegment; i < nSegment * 2; ++i)
	{
		pt[i].set(fRadius * cos(DEG2RAD * angle), fHeight, fRadius * sin(DEG2RAD * angle));
		//std::cout << pt[i].x << ' ' << pt[i].y << ' ' << pt[i].z << std::endl;
		angle += angle_increment;
	}

	pt[2 * nSegment].set(0, -fHeight, 0);
	pt[2 * nSegment + 1].set(0, fHeight, 0);

	numFaces = nSegment;
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
}

void Mesh::CreateSphere(int nSlice, int nStack, float radius)
{
	float phi = 0.0f, theta = 0.0f;
	float phi_increment = 180.0f / nStack, theta_increment = 360.0f / nSlice;

	numVerts = (nStack + 1) * nSlice;
	pt = new Point3[numVerts];

	for(int i = 0; i < (nStack + 1); ++i)
	{
		for(int j = 0; j < nSlice; ++j)
		{
			pt[i * nSlice + j].set(radius * cos(DEG2RAD * theta) * sin(DEG2RAD * phi), radius * sin(DEG2RAD * theta) * sin(DEG2RAD * phi), radius * cos(DEG2RAD * phi));
			theta = theta + theta_increment;
		}
		phi = phi + phi_increment;
	}

	numFaces = (nStack + 1) * nSlice;
	face = new Face[numFaces];

	for(int i = 0; i < nStack; ++i)
	{
		for(int j = 0; j < nSlice; ++j)
		{
			face[i * nSlice + j].nVerts = 4;
			face[i * nSlice + j].vert = new VertexID[face[i * nSlice + j].nVerts];

			face[i * nSlice + j].vert[0].vertIndex = i * nSlice + j;
			face[i * nSlice + j].vert[1].vertIndex = i * nSlice + ((j + 1) % nSlice);
			face[i * nSlice + j].vert[3].vertIndex = i * nSlice + j + nSlice;
			face[i * nSlice + j].vert[2].vertIndex = i * nSlice + ((j + 1) % nSlice) + nSlice;
		}
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

			//std::cout << "( " << pt[i * numV + j].x << ", " << pt[i + numV + j].y << ", " << pt[i + numV + j].z << ")" << std::endl;
		}
	}
}

void Mesh::CreatePlatonic8(float fSize)
{
	numVerts = 6;
	pt = new Point3[numVerts];
	pt[0].set(0, fSize * sin(DEG2RAD * 45), 0);
	pt[1].set(fSize, 0, 0);
	pt[2].set(-fSize, 0, 0);
	pt[3].set(0, 0, fSize);
	pt[4].set(0, 0, -fSize);
	pt[5].set(0, -fSize * sin(DEG2RAD * 45), 0);

	numFaces = 8;
	face = new Face[numFaces];

	//Top front face
	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 3;

	//Top right face
	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 2;

	//Top back face
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 2;
	face[2].vert[2].vertIndex = 4;

	//Top left face
	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 0;
	face[3].vert[1].vertIndex = 4;
	face[3].vert[2].vertIndex = 1;

	//Bottom front face
	face[4].nVerts = 3;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 5;
	face[4].vert[1].vertIndex = 1;
	face[4].vert[2].vertIndex = 3;

	//Bottom right face
	face[5].nVerts = 3;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 5;
	face[5].vert[1].vertIndex = 3;
	face[5].vert[2].vertIndex = 2;

	//Bottom back face
	face[6].nVerts = 3;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 5;
	face[6].vert[1].vertIndex = 2;
	face[6].vert[2].vertIndex = 4;

	//Bottom left face
	face[7].nVerts = 3;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 5;
	face[7].vert[1].vertIndex = 4;
	face[7].vert[2].vertIndex = 1;
}

void Mesh::CreatePlatonic12(float fSize)
{
	float golden_ratio = (1 + sqrt(5)) / 2;
	float a = fSize / 2;
	float b = a * golden_ratio;
	float c = a + b;

	numVerts = 20;
	pt = new Point3[numVerts];
	pt[0].set(-b, -b, -b);
	pt[1].set(b, -b, -b);
	pt[2].set(-b, b, -b);
	pt[3].set(b, b, -b);
	pt[4].set(-b, -b, b);
	pt[5].set(b, -b, b);
	pt[6].set(-b, b, b);
	pt[7].set(b, b, b);
	pt[8].set(c, -a, 0);
	pt[9].set(c, a, 0);
	pt[10].set(-c, -a, 0);
	pt[11].set(-c, a, 0);
	pt[12].set(a, 0, -c);
	pt[13].set(-a, 0, -c);
	pt[14].set(a, 0, c);
	pt[15].set(-a, 0, c);
	pt[16].set(0, -c, -a);
	pt[17].set(0, -c, a);
	pt[18].set(0, c, -a);
	pt[19].set(0, c, a);

	numFaces = 12;
	face = new Face[numFaces];

	face[0].nVerts = 5;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 12;
	face[0].vert[2].vertIndex = 3;
	face[0].vert[3].vertIndex = 9;
	face[0].vert[4].vertIndex = 8;

	face[1].nVerts = 5;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 5;
	face[1].vert[1].vertIndex = 8;
	face[1].vert[2].vertIndex = 9;
	face[1].vert[3].vertIndex = 7;
	face[1].vert[4].vertIndex = 14;

	face[2].nVerts = 5;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 10;
	face[2].vert[2].vertIndex = 11;
	face[2].vert[3].vertIndex = 2;
	face[2].vert[4].vertIndex = 13;

	face[3].nVerts = 5;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 4;
	face[3].vert[1].vertIndex = 15;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 11;
	face[3].vert[4].vertIndex = 10;

	face[4].nVerts = 5;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 16;
	face[4].vert[2].vertIndex = 0;
	face[4].vert[3].vertIndex = 13;
	face[4].vert[4].vertIndex = 12;

	face[5].nVerts = 5;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 12;
	face[5].vert[2].vertIndex = 13;
	face[5].vert[3].vertIndex = 2;
	face[5].vert[4].vertIndex = 18;

	face[6].nVerts = 5;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 5;
	face[6].vert[1].vertIndex = 14;
	face[6].vert[2].vertIndex = 15;
	face[6].vert[3].vertIndex = 4;
	face[6].vert[4].vertIndex = 17;

	face[7].nVerts = 5;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 7;
	face[7].vert[1].vertIndex = 19;
	face[7].vert[2].vertIndex = 6;
	face[7].vert[3].vertIndex = 15;
	face[7].vert[4].vertIndex = 14;

	face[8].nVerts = 5;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 1;
	face[8].vert[1].vertIndex = 8;
	face[8].vert[2].vertIndex = 5;
	face[8].vert[3].vertIndex = 17;
	face[8].vert[4].vertIndex = 16;

	face[9].nVerts = 5;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 0;
	face[9].vert[1].vertIndex = 16;
	face[9].vert[2].vertIndex = 17;
	face[9].vert[3].vertIndex = 4;
	face[9].vert[4].vertIndex = 10;

	face[10].nVerts = 5;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 3;
	face[10].vert[1].vertIndex = 18;
	face[10].vert[2].vertIndex = 19;
	face[10].vert[3].vertIndex = 7;
	face[10].vert[4].vertIndex = 9;

	face[11].nVerts = 5;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 2;
	face[11].vert[1].vertIndex = 11;
	face[11].vert[2].vertIndex = 6;
	face[11].vert[3].vertIndex = 19;
	face[11].vert[4].vertIndex = 18;
}

void Mesh::CreatePlatonic20(float fSize)
{
	float golden_ratio = (1 + sqrt(5)) / 2;
	float a = fSize / 2;
	float b = a * golden_ratio;

	numVerts = 12;
	pt = new Point3[numVerts];
	pt[0].set(-a, -b, 0);
	pt[1].set(a, -b, 0);
	pt[2].set(-a, b, 0);
	pt[3].set(a, b, 0);
	pt[4].set(0, -a, -b);
	pt[5].set(0, a, -b);
	pt[6].set(0, -a, b);
	pt[7].set(0, a, b);
	pt[8].set(-b, 0, -a);
	pt[9].set(-b, 0, a);
	pt[10].set(b, 0, -a);
	pt[11].set(b, 0, a);

	numFaces = 20;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 4;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 10;

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 4;
	face[1].vert[1].vertIndex = 8;
	face[1].vert[2].vertIndex = 5;

	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 7;
	face[2].vert[1].vertIndex = 6;
	face[2].vert[2].vertIndex = 11;

	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 9;
	face[3].vert[2].vertIndex = 6;

	face[4].nVerts = 3;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 8;
	face[4].vert[1].vertIndex = 9;
	face[4].vert[2].vertIndex = 2;

	face[5].nVerts = 3;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 8;
	face[5].vert[1].vertIndex = 0;
	face[5].vert[2].vertIndex = 9;

	face[6].nVerts = 3;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 11;
	face[6].vert[1].vertIndex = 10;
	face[6].vert[2].vertIndex = 3;

	face[7].nVerts = 3;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 11;
	face[7].vert[1].vertIndex = 1;
	face[7].vert[2].vertIndex = 10;

	face[8].nVerts = 3;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 0;
	face[8].vert[1].vertIndex = 1;
	face[8].vert[2].vertIndex = 6;

	face[9].nVerts = 3;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 0;
	face[9].vert[1].vertIndex = 4;
	face[9].vert[2].vertIndex = 1;

	face[10].nVerts = 3;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 3;
	face[10].vert[1].vertIndex = 2;
	face[10].vert[2].vertIndex = 7;

	face[11].nVerts = 3;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 3;
	face[11].vert[1].vertIndex = 5;
	face[11].vert[2].vertIndex = 2;

	face[12].nVerts = 3;
	face[12].vert = new VertexID[face[12].nVerts];
	face[12].vert[0].vertIndex = 4;
	face[12].vert[1].vertIndex = 10;
	face[12].vert[2].vertIndex = 1;

	face[13].nVerts = 3;
	face[13].vert = new VertexID[face[13].nVerts];
	face[13].vert[0].vertIndex = 4;
	face[13].vert[1].vertIndex = 0;
	face[13].vert[2].vertIndex = 8;

	face[14].nVerts = 3;
	face[14].vert = new VertexID[face[14].nVerts];
	face[14].vert[0].vertIndex = 5;
	face[14].vert[1].vertIndex = 3;
	face[14].vert[2].vertIndex = 10;

	face[15].nVerts = 3;
	face[15].vert = new VertexID[face[15].nVerts];
	face[15].vert[0].vertIndex = 5;
	face[15].vert[1].vertIndex = 8;
	face[15].vert[2].vertIndex = 2;

	face[16].nVerts = 3;
	face[16].vert = new VertexID[face[16].nVerts];
	face[16].vert[0].vertIndex = 7;
	face[16].vert[1].vertIndex = 11;
	face[16].vert[2].vertIndex = 3;

	face[17].nVerts = 3;
	face[17].vert = new VertexID[face[17].nVerts];
	face[17].vert[0].vertIndex = 7;
	face[17].vert[1].vertIndex = 2;
	face[17].vert[2].vertIndex = 9;

	face[18].nVerts = 3;
	face[18].vert = new VertexID[face[18].nVerts];
	face[18].vert[0].vertIndex = 6;
	face[18].vert[1].vertIndex = 9;
	face[18].vert[2].vertIndex = 0;

	face[19].nVerts = 3;
	face[19].vert = new VertexID[face[19].nVerts];
	face[19].vert[0].vertIndex = 6;
	face[19].vert[1].vertIndex = 1;
	face[19].vert[2].vertIndex = 11;
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
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

Mesh    	cube;
Mesh		tetrahedron;
Mesh		cuboid;
Mesh		cylinder;
Mesh		sphere;
Mesh		torus;
Mesh		platonic8;
Mesh		platonic12;
Mesh		platonic20;

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
	glViewport(0, 0, screenWidth / 2, screenHeight);

	glPushMatrix();
	drawAxis();

	glRotatef(angle, 0, 1, 0);

	glColor3f(0, 0, 0);
	if (nChoice == 1)
		platonic8.DrawWireframe();
	else if (nChoice == 2)
		platonic12.DrawWireframe();
	else if (nChoice == 3)
		platonic20.DrawWireframe();


	/////////////////////////////////////////////////////////////
	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	glPopMatrix();
	drawAxis();
	glRotatef(angle, 0, 1, 0);

	if (nChoice == 1)
		platonic8.DrawColor();
	else if (nChoice == 2)
		platonic12.DrawColor();
	else if (nChoice == 3)
		platonic20.DrawColor();

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
	cout << "Press -> or <- to rotate" << endl;

	cout << "1. 8" << endl;
	cout << "2. 12" << endl;
	cout << "3. 20" << endl;

	cout << endl<< "Input the choice: " << endl;
	cin  >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2-Mesh"); // open the screen window

	myInit();
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);

	platonic8.CreatePlatonic8(5);
	platonic12.CreatePlatonic12(3);
	platonic20.CreatePlatonic20(3);

	glutMainLoop();
	return 0;
}
