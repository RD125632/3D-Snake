#pragma once

#ifndef SNAKE_H_
#define SNAKE_H_
#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES

#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <GL\freeglut.h>
#include "Food.h"
#include "Color.h"

using namespace std;

class Snake
{
private:
	const GLfloat snakeSquareSize = 2.0f;
	vector<Position> body;
	RGBColor color;
	void Snake::drawPart(Position);
public:
	enum Direction { LEFT, RIGHT, UP, DOWN };
	Direction dir = DOWN;
	GLint snakeSize = 3;
	Snake(void);
	void draw(void);
	int Snake::move(void);
	void eat(Food & food);
	void reset(void);
};

#endif

