#pragma once

#ifndef BOARD_H_
#define BOARD_H_

#include "Color.h"
#include <GL/freeglut.h>

class Board
{
public:
	Board();
	void draw(void);
private:
	RGBColor color;
	GLfloat size;
	GLfloat posX = 0;
	GLfloat posY = 0;
	GLfloat posZ = 0;
};


#endif