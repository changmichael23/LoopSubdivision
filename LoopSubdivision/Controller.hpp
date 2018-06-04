#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>

float TimeInSeconds;
int TimeSinceAppStartedInMS;
int OldTime = 0;
float DeltaTime;


float COS(float angle)
{
	return cos(angle * 2 * 0.00872665);
}
float SIN(float angle)
{
	return sin(angle * 2 * 0.00872665);
}


void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		if (CamType == 0)
		{
			posZ += moveSpeed *  DeltaTime * COS(rotY);
			posX += moveSpeed *  DeltaTime * -SIN(rotY);
			posY += moveSpeed *  DeltaTime * SIN(rotX);
		}
		else
		{
			distance += moveSpeed *  DeltaTime;
		}
	}
	if (key == 'a')
	{
		posZ += moveSpeed *  DeltaTime * COS(rotY - 90);
		posX += moveSpeed *  DeltaTime * -SIN(rotY - 90);

	}
	if (key == 's')
	{
		if (CamType == 0)
		{
			posZ -= moveSpeed *  DeltaTime * COS(rotY);
			posX -= moveSpeed *  DeltaTime * -SIN(rotY);
			posY -= moveSpeed *  DeltaTime * SIN(rotX);
		}
		else
		{
			distance -= moveSpeed *  DeltaTime;
		}
	}
	if (key == 'd')
	{
		posZ -= moveSpeed *  DeltaTime * COS(rotY - 90);
		posX -= moveSpeed *  DeltaTime * -SIN(rotY - 90);
	}
	if (key == 27)	// Echap
	{
		exit(0);
	}
	if (key == 32)	// Space Bar
	{
		posY -= moveSpeed *  DeltaTime;
	}
	if (key == 'f')
	{
		posY += moveSpeed *  DeltaTime;
	}
	if (key == '1')	 // 1 Mode FPS
	{
		ChangeCam(0);
	}
	if (key == '2')	 // 2 Mode Orbit
	{
		ChangeCam(1);
	}
}

void mouse(int x, int y)
{

	//rotX = (float)(y-height*0.5f) * rotSpeed;
	//rotY = (float)(x-width*0.5f) * rotSpeed;
	if (abs(y - lastposY) < 10 && abs(x - lastposX) < 10)
	{
		rotX += (y - lastposY)* rotSpeed;
		rotY += (x - lastposX)* rotSpeed;
	}
	lastposX = x;
	lastposY = y;

}

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case GLUT_KEY_DOWN:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

	}
	glutPostRedisplay();
}

