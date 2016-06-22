#pragma once

#ifndef FOODS_H_
#define FOODS_H_
#include <GL\freeglut.h>
#include "Position.h"
#include "ObjModel.h"

class Food
{
private:

public:
	Food();
	void newFood();
	ObjModel* model;
	void draw();

	Position position;
	GLfloat hitbox = 2.0f;
};
#endif
