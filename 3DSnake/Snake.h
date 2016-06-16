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
	void Snake::move(void);
	enum Direction { LEFT, RIGHT, UP, DOWN };
	Direction dir = DOWN;
	GLfloat rotation = 0;
private:
	RGBColor color;
	GLfloat size = 2.0f;
	GLfloat posX = 0;
	GLfloat posY = 0.9f;
	GLfloat posZ = 0;
	GLuint textureTop, textureLeft, textureRight, textureBottom, textureFront, textureBack;
	GLuint Snake::loadTexture(const char *);
};


#endif