/*-------------------------------------------------------------------------*/
/*				INCLUDES						                           */
/*-------------------------------------------------------------------------*/

#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <cstdio>
#include <iostream>

#include "GL/freeglut.h"
#include "ObjModel.h"
#include "Camera.h"
#include "Board.h"
#include "Snake.h"
#include "Book.h"

using namespace std;

/*-------------------------------------------------------------------------*/
/*				Local Variable                                             */
/*-------------------------------------------------------------------------*/

//Init Variables
GLfloat WIDTH = 800;
GLfloat HEIGHT = 600;
Camera camera = Camera(-20, -30, 0, 50, -90, 0);
GLfloat  lightPos[] = { 1.0f, 1.0f, 75.0f, 1.0f };
GLfloat  specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat  spotDir[] = { 0.0f, 0.0f, -1.0f };
Board playBoard;
Snake snake;
Snake randomCube;
Book book;

bool keys[255];

//History trackers
GLfloat frameTime = 0;
GLint lastX = 0;
GLint lastY = 0;

//Flags
bool jump = false;

/*-------------------------------------------------------------------------*/
/*				Function Prototyping                                       */
/*-------------------------------------------------------------------------*/

void Idle(void);
void SetupWindow(void);
void PaintComponent(void);

void ReshapeWindow(GLint, GLint);

void MouseMotionEvent(int, int);
void MouseWheelEvent(int, int, int, int);
void KeyEvent(unsigned char, int, int);
void KeyEventUp(unsigned char, int, int);

/*-------------------------------------------------------------------------*/
/*              Start Code												   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*              -- Window Functions										   */
/*-------------------------------------------------------------------------*/


void Idle(void)
{
	GLfloat newFrameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	GLfloat deltaTime = newFrameTime - frameTime;
	frameTime = newFrameTime;

	const GLfloat speed = 10;
	if (keys['a']) camera.MoveCamera(0, deltaTime*speed);
	if (keys['d']) camera.MoveCamera(180, deltaTime*speed);
	if (keys['w']) camera.MoveCamera(90, deltaTime*speed);
	if (keys['s']) camera.MoveCamera(270, deltaTime*speed);

	glutPostRedisplay();
}

void SetupWindow(void)
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// The light is composed of just diffuse and specular components
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// Specific spot effects
	// Cut off angle is 60 degrees
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0f);

	// Fairly shiny spot
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 20.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

	glViewport(0, 0, WIDTH, HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, WIDTH / HEIGHT, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glRotatef(camera.rotZ, 0, 0, 1);
	glTranslatef(camera.posX, camera.posY, camera.posZ);
}

void PaintComponent(void)
{
	SetupWindow();

	playBoard.draw();
	randomCube.draw();

	glPushMatrix();
	glTranslatef(5.0f, 3.0f, 0.0f);

	//NO TEXTURE
	book.model->draw();

	glPopMatrix();

	glPushMatrix();
		snake.move();
		snake.draw();
		randomCube.draw();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void ReshapeWindow(GLint w, GLint h)
{
	WIDTH = w;
	HEIGHT = h;
}


/*-------------------------------------------------------------------------*/
/*              -- Event Handlers										   */
/*-------------------------------------------------------------------------*/

void KeyEvent(unsigned char key, int mouseX, int mouseY)
{
	if (key == 27)
		exit(0);
	keys[key] = true;
}

void SpecialKeyEvent(int key, int x, int y)
{
	std::cout << key << endl;
	switch (key)
	{
	case GLUT_KEY_UP:
		snake.dir = Snake::Direction::UP;
		break;
	case GLUT_KEY_DOWN:
		snake.dir = Snake::Direction::DOWN;
		break;
	case GLUT_KEY_LEFT:
		snake.dir = Snake::Direction::LEFT;
		break;
	case GLUT_KEY_RIGHT:
		snake.dir = Snake::Direction::RIGHT;
		break;

	}
}

void KeyEventUp(unsigned char key, int, int)
{
	keys[key] = false;
}

void MouseMotionEvent(int x, int y)
{
	int dx = lastX - x;
	int dy = lastY - y;

	lastX = x;
	lastY = y;

	if (jump)
	{
		jump = false;
		return;
	}

	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY -= dx / 10.0f;
		camera.rotX -= dy / 10.0f;
		jump = true;
		glutWarpPointer(WIDTH / 2, HEIGHT / 2);
	}
}

void MouseWheelEvent(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		camera.ZoomCamera(-1);
	}
	else
	{
		camera.ZoomCamera(1);
	}
}


/*-------------------------------------------------------------------------*/
/*              - MAIN													   */
/*-------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	cout << "$->Starting..." << endl;
	cout << "->Creating Window..." << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("3D-Snake");
	glutFullScreen();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	cout << "->Window Created" << endl;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutIdleFunc(Idle);
	glutDisplayFunc(PaintComponent);
	glutReshapeFunc(ReshapeWindow);
	glutKeyboardFunc(KeyEvent);
	glutKeyboardUpFunc(KeyEventUp);
	glutSpecialFunc(SpecialKeyEvent);
	glutPassiveMotionFunc(MouseMotionEvent);
	glutMouseWheelFunc(MouseWheelEvent);
	glutWarpPointer(WIDTH / 2, HEIGHT / 2);

	playBoard = Board(1);
	snake = Snake(1);
	randomCube = Snake(2);

	glutMainLoop();
	return 0;
}







