#include "Camera.h"


Camera::Camera(GLfloat pX, GLfloat pY, GLfloat pZ, GLfloat rX, GLfloat rY, GLfloat rZ)
{
	posX = pX;
	posY = pY;
	posZ = pZ;
	rotX = rX;
	rotY = rY;
	rotZ = rZ;
}

void Camera::MoveCamera(GLfloat angle, GLfloat factor)
{
	posX += (GLfloat)cos((rotY + angle) / 180 * M_PI) * factor;
	posZ += (GLfloat)sin((rotY + angle) / 180 * M_PI) * factor;
}

void Camera::ZoomCamera(GLfloat value)
{
	posY += (GLfloat)sin((rotY + 0) / 180 * M_PI) * value;
}
