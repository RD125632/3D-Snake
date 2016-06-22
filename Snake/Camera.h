#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_
#define _USE_MATH_DEFINES

#include <cmath>
#include "GL/freeglut.h"

class Camera
{
public:
	Camera(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	void MoveCamera(GLfloat angle, GLfloat factor);
	void ZoomCamera(GLfloat);
	GLfloat posX;
	GLfloat posY;
	GLfloat posZ;
	GLfloat rotX;
	GLfloat rotY;
	GLfloat rotZ;
};


#endif