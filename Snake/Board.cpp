#include "Board.h"

Board::Board()
{
	color.setRGBColor(0.08f, 0.08f, 0.08f);
	size = 20.0f;
}
void Board::draw(void)
{
	glPushMatrix();
	GLfloat lightPosition[] = { 0, 5, 0, 0 };
	GLfloat lightA[] = { 1,1,1,1 };
	GLfloat Ambient[] = { 0,0,0 };
	GLfloat Diffuse[] = { 0.5f, 0.5f, 0.8f, 1.0f };
	GLfloat Specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat s = 5.0f;

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightA);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
	glMaterialf(GL_FRONT, GL_SHININESS, s);


	// TOP
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, -size);
	glVertex3f(-size, 0.0f, -size);
	glVertex3f(-size, 0.0f, size);

	// BACK
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(size, -0.8f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(-size, 0.0f, size);
	glVertex3f(-size, -0.8f, size);

	// LEFT
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-size, -0.8f, size);
	glVertex3f(-size, 0.0f, size);
	glVertex3f(-size, 0.0f, -size);
	glVertex3f(-size, -0.8f, -size);

	// RIGHT
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(size, -0.8f, -size);
	glVertex3f(size, 0.0f, -size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, -0.8f, size);

	// FRONT
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(size, -0.8f, -size);
	glVertex3f(size, 0.0f, -size);
	glVertex3f(-size, 0.0f, -size);
	glVertex3f(-size, -0.8f, -size);

	// BOTTOM
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(size, -0.8f, -size);
	glVertex3f(size, -0.8f, size);
	glVertex3f(-size, -0.8f, size);
	glVertex3f(-size, -0.8f, -size);
	glEnd();
	glPopMatrix();
}
