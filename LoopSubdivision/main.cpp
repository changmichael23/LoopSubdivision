#include <math.h>
#include <vector>
#include "Camera.hpp"
#include "Controller.hpp"
#include "EnvInc.hpp"
#ifdef _MSC_VER
#pragma comment(lib, "opengl32.lib")
#include <windows.h>
#endif

#ifdef _MSC_VER
#pragma comment(lib, "glew32.lib")
#endif


#include "../common/EsgiShader.h"
#include "../common/mat4.h"


// format des vertices : X, Y, Z, ?, ?, ?, ?, ? = 8 floats
//#include "../data/DragonData.h"

int sizetab, sizeind;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
EsgiShader g_BasicShader;

std::vector<Point> p3D, tmpVectorPoints;           // Tous les points en 3D
float* tabPoints, *tmpPoints;         //Tous les points en 3D
GLushort* createInd(int);
GLushort* indi,*indTmp;			// Tab indice


GLuint VAO;
GLuint VBO0;	// identifiant du Vertex Buffer Object 0
GLuint VBO1;	// identifiant du Vertex Buffer Object 1
GLuint IBO,IBO1;	// identifiant du Index Buffer Object
GLuint TexObj; // identifiant du Texture Object


float colore[4];

std::vector<Face*> *tmpFace = new std::vector<Face*>();
std::vector<Colore> col;

float * structToTabColor(std::vector<Point> newPoints, std::vector<Colore> c)
{
	float* tabP = new float[newPoints.size() * 9];
	int j = 0;
	for (int i = 0; i < newPoints.size() * 9; i += 9)
	{
		tabP[i] = newPoints[j].x;
		tabP[i + 1] = newPoints[j].y;
		tabP[i + 2] = newPoints[j].z;

		tabP[i + 3] = newPoints[j].n1;
		tabP[i + 4] = newPoints[j].n2;
		tabP[i + 5] = newPoints[j].n3;

		if (c[j] == Colore(purple))
		{
			tabP[i + 6] = RandomFloat(0,1);
			tabP[i + 7] = RandomFloat(0, 1);
			tabP[i + 8] = RandomFloat(0, 1);
		}
		if (c[j] == Colore(red))
		{
			tabP[i + 6] = RandomFloat(0, 1);
			tabP[i + 7] = RandomFloat(0, 1);
			tabP[i + 8] = RandomFloat(0, 1);
		}
		if (c[j] == Colore(blue))
		{
			tabP[i + 6] = RandomFloat(0, 1);
			tabP[i + 7] = RandomFloat(0, 1);
			tabP[i + 8] = RandomFloat(0, 1);
		}
		/*
		tabP[i + 6] = 0;
		tabP[i + 7] = 1;
		tabP[i + 8] = 0;*/
		j++;
	}

	return tabP;
}




bool Initialize()
{
	colore[0] = 0.0;
	colore[1] = 1.0;
	colore[2] = 1.0;
	colore[3] = 1.0;

	std::vector<Point> centerPoints3D = createRandomPoints(10);

	Graph * tmpGraph = new Graph();
	EnvInc testEnv = *new EnvInc(tmpGraph,centerPoints3D);
	testEnv.initializeGraph();
	testEnv.algo();
	tmpFace = testEnv.getGraph()->getFaceList();

	for (int i = 0; i < tmpFace->size(); i++)
	{
		tmpVectorPoints.push_back(tmpFace->at(i)->getPoints()[0]);
		col.push_back(tmpFace->at(i)->getColor());
		tmpVectorPoints.push_back(tmpFace->at(i)->getPoints()[1]);
		col.push_back(tmpFace->at(i)->getColor());
		tmpVectorPoints.push_back(tmpFace->at(i)->getPoints()[2]);
		col.push_back(tmpFace->at(i)->getColor());

	}
	
	std::vector<Colore> tmpColore;
	
	p3D = transformPointsToCube(centerPoints3D);

	for (int i = 0; i < p3D.size(); i++)
	{
		tmpColore.push_back(Colore(red));
	}

	tabPoints = structToTabColor(p3D,tmpColore);

	indi = createInd(centerPoints3D.size()*24);
	indTmp = createInd(tmpVectorPoints.size());
	tmpPoints = structToTabColor(tmpVectorPoints,col);

	glewInit();
	g_BasicShader.LoadVertexShader("basic.vs");
	g_BasicShader.LoadFragmentShader("basic.fs");
	g_BasicShader.CreateProgram();

	glGenTextures(1, &TexObj);
	glBindTexture(GL_TEXTURE_2D, TexObj);
	int w, h, c; //largeur, hauteur et # de composantes du fichier

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //GL_NEAREST)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenVertexArrays(1, &VBO0); // Créer le VAO
	glBindVertexArray(VBO0); // Lier le VAO pour l'utiliser
	glEnableVertexAttribArray(0);


	//glGenBuffers(1, &VBO0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBufferData(GL_ARRAY_BUFFER, p3D.size() * 9 * sizeof(float), tabPoints, GL_STATIC_DRAW);
	//---
	glGenVertexArrays(1, &VBO1); // Créer le VAO
	glBindVertexArray(VBO1); // Lier le VAO pour l'utiliser
	glEnableVertexAttribArray(0);


	//glGenBuffers(1, &VBO0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, tmpVectorPoints.size() * 9 * sizeof(float), tmpPoints, GL_STATIC_DRAW);

	// rendu indexe
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p3D.size() * sizeof(GLushort), indi, GL_STATIC_DRAW);
	glGenBuffers(1, &IBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tmpVectorPoints.size() * sizeof(GLushort), indTmp, GL_STATIC_DRAW);

	// le fait de specifier 0 comme BO desactive l'usage des BOs
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	ChangeCam(CamType);


	

	return true;
}

void Terminate()
{
	glDeleteTextures(1, &TexObj);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO0);
	glDeleteBuffers(1, &IBO1);
	glDeleteBuffers(1, &VBO1);
	g_BasicShader.DestroyProgram();
}

void update()
{
	glutPostRedisplay();
}

void animate()
{


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// afin d'obtenir le deltatime actuel
	TimeSinceAppStartedInMS = glutGet(GLUT_ELAPSED_TIME);
	TimeInSeconds = TimeSinceAppStartedInMS / 1000.0f;
	DeltaTime = (TimeSinceAppStartedInMS - OldTime) / 1000.0f;
	OldTime = TimeSinceAppStartedInMS;

	glViewport(0, 0, width, height);
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	//glColorMask(GL_TRUE, GL_FALSE, GL_TRUE, GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	auto program = g_BasicShader.GetProgram();
	glUseProgram(program);

	/*	uint32_t texUnit = 0;
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, TexObj);
	auto texture_location = glGetUniformLocation(program, "u_Texture");
	glUniform1i(texture_location, texUnit);
	*/
	// UNIFORMS
	Esgi::Mat4 worldMatrix;
	worldMatrix.MakeScale(1.0f, 1.0f, 1.0f);

	//  Camera Matrix
	Esgi::Mat4 cameraMatrix;
	switch (CamType)
	{
	case 0:	//FPS
		cameraMatrix = FPSCamera(posX, posY, posZ, rotX, rotY);
		break;
	case 1:	//Orbit
		cameraMatrix = OrbitCamera(posX, posY, posZ, distance, rotX, rotY);
		break;
	}

	//

	auto world_location = glGetUniformLocation(program, "u_WorldMatrix");
	glUniformMatrix4fv(world_location, 1, GL_FALSE, worldMatrix.m);

	Esgi::Mat4 projectionMatrix;
	float w = glutGet(GLUT_WINDOW_WIDTH), h = glutGet(GLUT_WINDOW_HEIGHT);
	// ProjectionMatrix
	float aspectRatio = w / h;			// facteur d'aspect
	float fovy = 45.0f;					// degree d'ouverture
	float nearZ = 0.1f;
	float farZ = 10000.0f;
	projectionMatrix.Perspective(fovy, aspectRatio, nearZ, farZ);

	//projectionMatrix.MakeScale(1.0f / (0.5f*w), 1.0f / (0.5f*h), 1.0f);

	auto projection_location = glGetUniformLocation(program, "u_ProjectionMatrix");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, projectionMatrix.m);

	auto camera_location = glGetUniformLocation(program, "u_CameraMatrix");
	glUniformMatrix4fv(camera_location, 1, GL_FALSE, cameraMatrix.m);

	auto time_location = glGetUniformLocation(program, "u_Time");
	glUniform1f(time_location, TimeInSeconds);

	/*auto c_location = glGetUniformLocation(program, "color");
	glUniform4fv(c_location, 1, colore);*/

	// ATTRIBUTES
	auto normal_location = glGetAttribLocation(program, "a_Normal");
	auto position_location = glGetAttribLocation(program, "a_Position");
	auto color_location = glGetAttribLocation(program, "a_Color");
	//auto texcoords_location = glGetAttribLocation(program, "a_TexCoords");
	//glVertexAttrib3f(color_location, 0.0f, 1.0f, 0.0f);

	// Le fait de specifier la ligne suivante va modifier le fonctionnement interne de glVertexAttribPointer
	// lorsque GL_ARRAY_BUFFER != 0 cela indique que les donnees sont stockees sur le GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO0);

	//glBindVertexArray(VAO);

	glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<const void *>(0 * sizeof(float)));
	glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<const void *>(3 * sizeof(float)));
	glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<const void *>(6 * sizeof(float)));
	// on interprete les 3 valeurs inconnues comme RGB alors que ce sont les normales
	//glVertexAttribPointer(texcoords_location, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<const void *>(6 * sizeof(float)));

	//glEnableVertexAttribArray(texcoords_location);
	glEnableVertexAttribArray(position_location);
	glEnableVertexAttribArray(normal_location);
	glEnableVertexAttribArray(color_location);
	//glEnableVertexAttribArray(texcoords_location);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_QUADS, p3D.size(), GL_UNSIGNED_SHORT, nullptr);

	//-----------

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);

	//glBindVertexArray(VAO);

	glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<const void *>(0 * sizeof(float)));
	glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<const void *>(3 * sizeof(float)));
	glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<const void *>(6 * sizeof(float)));
	// on interprete les 3 valeurs inconnues comme RGB alors que ce sont les normales
	//glVertexAttribPointer(texcoords_location, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<const void *>(6 * sizeof(float)));

	//glEnableVertexAttribArray(texcoords_location);
	glEnableVertexAttribArray(position_location);
	glEnableVertexAttribArray(normal_location);
	glEnableVertexAttribArray(color_location);
	//glEnableVertexAttribArray(texcoords_location);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
	glDrawElements(GL_TRIANGLES, tmpVectorPoints.size(), GL_UNSIGNED_SHORT, nullptr);

	//----------------
	//glPointSize(10);
	glDisableVertexAttribArray(position_location);
	glDisableVertexAttribArray(normal_location);
	glDisableVertexAttribArray(color_location);
	//glDisableVertexAttribArray(texcoords_location);
	glUseProgram(0);

	
	//Repositionnement du curseur 
	//glutWarpPointer(width*0.5f, height*0.5f);
	glEnd();


	glutSwapBuffers();

}

int main(int argc, const char* argv[])
{


	// passe les parametres de la ligne de commande a glut
	glutInit(&argc, (char**)argv);
	// defini deux color buffers (un visible, un cache) RGBA
	// GLUT_DEPTH alloue egalement une zone mémoire pour le depth buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	// positionne et dimensionne la fenetre
	glutInitWindowPosition(100, 10);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Transformation");
	gluOrtho2D(-400, 400, -400, 400);						// Repère 2D délimitant les abscisses et les ordonnées
															// creation de la fenetre ainsi que du contexte de rendu

	glClearColor(1.0, 1.0, 1.0, 0.5);
	glColor3f(1.0, 1.0, 1.0);			     	 // couleur: blanc
	glPointSize(2.0);
#ifdef FREEGLUT
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

#ifdef NO_GLEW
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)
		wglGetProcAddress("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)
		wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)
		wglGetProcAddress("glDisableVertexAttribArray");
#else
	glewInit();
#endif
	Initialize();
	glutIdleFunc(update);
	glutDisplayFunc(animate);

	glutPassiveMotionFunc(mouse);
	glutSpecialFunc(SpecialInput);
	glutKeyboardFunc(keyboard);


	glutMainLoop();

	Terminate();

	return 1;
}

GLushort* createInd(int n)
{
	GLushort* tmp = new GLushort[n];
	for (int i = 0; i < n ; i++)
	{
		tmp[i] = i;
	}
	return tmp;
}
