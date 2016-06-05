#include "Board.h"

Board::Board()
{
	color.setRGBColor(0.1f, 0.1f, 0.2f);
	size = 15.0f;
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

	glColor4f(color.getRed(), color.getGreen(), color.getBlue(), 0.6f);

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
