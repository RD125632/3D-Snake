#pragma once

#ifndef COLOR_H_
#define COLOR_H_

#include <GL/freeglut.h>

class RGBColor
{
private:
	GLfloat red;
	GLfloat green;
	GLfloat blue;
public:
	RGBColor() {}
	RGBColor(GLfloat r, GLfloat g, GLfloat b) { setRGBColor(r, g, b); }
	void RGBColor::setRGBColor(GLfloat r, GLfloat g, GLfloat b)
	{
		red = r;
		green = g;
		blue = b;
	}
	GLfloat RGBColor::getRed()	{ return red;   }
	GLfloat RGBColor::getGreen(){ return green; }
	GLfloat RGBColor::getBlue()	{ return blue;  }
};

#endif



