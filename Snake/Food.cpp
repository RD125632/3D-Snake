#include "Food.h"
#include <ctime>
#include <iostream>

Food::Food()
{
	model = new ObjModel("models/cheese/object.obj");
	newFood();
}

void Food::newFood() 
{
	position.random();
}

void Food::draw()
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), position.getZ());

	//Back face
	glBegin(GL_QUADS);
	glVertex3f(hitbox / 2, hitbox / 2, hitbox / 2);
	glVertex3f(-hitbox / 2, hitbox / 2, hitbox / 2);
	glVertex3f(-hitbox / 2, -hitbox / 2, hitbox / 2);
	glVertex3f(hitbox / 2, -hitbox / 2, hitbox / 2);

	//Left face
	glVertex3f(-hitbox / 2, hitbox / 2, hitbox / 2);
	glVertex3f(-hitbox / 2, hitbox / 2, -hitbox / 2);
	glVertex3f(-hitbox / 2, -hitbox / 2, -hitbox / 2);
	glVertex3f(-hitbox / 2, -hitbox / 2, hitbox / 2);

	//Right face
	glVertex3f(hitbox / 2, hitbox / 2, -hitbox / 2);
	glVertex3f(hitbox / 2, hitbox / 2, hitbox / 2);
	glVertex3f(hitbox / 2, -hitbox / 2, hitbox / 2);
	glVertex3f(hitbox / 2, -hitbox / 2, -hitbox / 2);

	//Top face
	glVertex3f(-hitbox / 2, hitbox / 2, -hitbox / 2);
	glVertex3f(-hitbox / 2, hitbox / 2, hitbox / 2);
	glVertex3f(hitbox / 2, hitbox / 2, hitbox / 2);
	glVertex3f(hitbox / 2, hitbox / 2, -hitbox / 2);

	//Front face
	glVertex3f(hitbox / 2, -hitbox / 2, -hitbox / 2);
	glVertex3f(hitbox / 2, hitbox / 2, -hitbox / 2);
	glVertex3f(-hitbox / 2, hitbox / 2, -hitbox / 2);
	glVertex3f(-hitbox / 2, -hitbox / 2, -hitbox / 2);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}
