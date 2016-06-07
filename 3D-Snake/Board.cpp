#include "Board.h"

Board::Board()
{
	color.setRGBColor(0.1f, 0.14f, 0.1f);
	size = 19.0f;
}

void Board::draw(void)
{

	// TOP
	glBegin(GL_QUADS);
	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), 0.6f);
	glVertex3f(size + posX, 0.8f, size + posY);
	glVertex3f(size + posX, 0.8f, -size + posY);
	glVertex3f(-size + posX, 0.8f, -size + posY);
	glVertex3f(-size + posX, 0.8f, size + posY);

	// BACK
	glVertex3f(size + posX, -0.8f, size + posY);
	glVertex3f(size + posX, 0.8f, size + posY);
	glVertex3f(-size + posX, 0.8f, size + posY);
	glVertex3f(-size + posX, -0.8f, size + posY);

	// LEFT
	glVertex3f(-size + posX, -0.8f, size + posY);
	glVertex3f(-size + posX, 0.8f, size + posY);
	glVertex3f(-size + posX, 0.8f, -size + posY);
	glVertex3f(-size + posX, -0.8f, -size + posY);

	// RIGHT
	glVertex3f(size + posX, -0.8f, -size + posY);
	glVertex3f(size + posX, 0.8f, -size + posY);
	glVertex3f(size + posX, 0.8f, size + posY);
	glVertex3f(size + posX, -0.8f, size + posY);

	// FRONT
	glVertex3f(size + posX, -0.8f, -size + posY);
	glVertex3f(size + posX, 0.8f, -size + posY);
	glVertex3f(-size + posX, 0.8f, -size + posY);
	glVertex3f(-size + posX, -0.8f, -size + posY);

	// BOTTOM
	glVertex3f(size + posX, -0.8f, -size + posY);
	glVertex3f(size + posX, -0.8f, size + posY);
	glVertex3f(-size + posX, -0.8f, size + posY);
	glVertex3f(-size + posX, -0.8f, -size + posY);
	glEnd();
}
