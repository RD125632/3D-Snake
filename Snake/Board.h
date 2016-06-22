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
	void draw(void);
private:
	RGBColor color;
	GLfloat size;
	GLuint texture;
	GLuint Board::loadTexture(const char *);
};


#endif