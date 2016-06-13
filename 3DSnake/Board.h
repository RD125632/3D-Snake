#pragma once

#ifndef BOARD_H_
#define BOARD_H_
#define _CRT_SECURE_NO_DEPRECATE

#include "Color.h"
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

class Board
{
public:
	Board();
	Board(GLint);
	void draw(void);
private:
	RGBColor color;
	GLfloat size;
	GLfloat posX = 0;
	GLfloat posY = 0;
	GLfloat posZ = 0;
	GLuint texture;
	GLuint Board::loadTexture(const char *);
};


#endif