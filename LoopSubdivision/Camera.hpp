
#pragma once

// -----------------------------------------------------------------------------------------------TYPE DE CAMERA----------------------------------------------------------------------------------------------
int CamType = 0;
// FPS = 0
// Orbit = 1
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Camera variables
int width = 1000;
int height = 1000;
float posX = 0.0f;
float posY = -4.7f;
float posZ = -17.0f;
float moveSpeed = 100000.0f;
float rotSpeed = 0.8f;
float rotX = 0.0f;
float rotY = 0.0f;
float distance = -60.0f;

int lastposX = height * 0.5f;
int lastposY = width * 0.5f;

float deltaAngle = 0.0f;
int xOrigin = -1;


void ChangeCam(int type)
{
	switch (type)
	{
	case 0:
		CamType = 0;
		rotX = 0.0f;
		rotY = 0.0f;
		posX = 0.0f;
		posY = -0.5f;
		posZ = -10.0f;
		rotSpeed = 0.3f;
		break;
	case 1:
		CamType = 1;
		rotX = 0.0f;
		rotY = 0.0f;
		posX = 0.0f;
		posY = -0.5f;
		posZ = 0.0f;
		distance = -10.0f;
		break;
	}

}