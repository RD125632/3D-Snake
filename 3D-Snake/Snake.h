#pragma once

#ifndef SNAKE_H_
#define SNAKE_H_
#define _CRT_SECURE_NO_DEPRECATE

#include "Color.h"
#include "Texture.h"
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

class Snake
{
public:
	Snake();
	Snake(GLint);
	void draw(void);
private:
	RGBColor color;
	GLfloat size = 0;
	GLfloat headSize = 2.0f;
	GLfloat posX = 0;
	GLfloat posY = 0;
	GLfloat posZ = 0;
	GLuint texture;
	GLuint Snake::loadTexture(const char *);
};


#endif