#pragma once
#ifndef POSITION_H_
#define POSITION_H_
#include <GL\freeglut.h>
#include <ctime>

class Position
{
private:
	GLfloat x, y, z;
public:
	Position() {}
	Position(GLfloat nX, GLfloat nY, GLfloat nZ) { x = nX; y = nY; z = nZ; }
	GLfloat getX() { return x; }
	GLfloat getY() { return y; }
	GLfloat getZ() { return z; }
	void setX(GLfloat n) { x = n; }
	void setY(GLfloat n) { y = n; }
	void setZ(GLfloat n) { z = n; }
	void set(GLfloat nX, GLfloat nY, GLfloat nZ) { 
		x = nX;
		y = nY;
		z = nZ;
	}
	void random() {
		static bool seed = false;
		if (seed == false) {
			seed = true;
			srand((int)time(NULL));			// Initialize the random seed to the current time
		}
		else
		{
			srand(rand());				// Randomize the current seed
		}

		setX((GLfloat)(rand() % 36) - 18);
		setZ((GLfloat)(rand() % 36) - 18);
	}
};
#endif