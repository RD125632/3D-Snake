/*-------------------------------------------------------------------------*/
//		Created by: Richard Danen
/*-------------------------------------------------------------------------*/
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <cstdio>
#include <string>

#include "ObjModel.h"
#include "GL/freeglut.h"
#include "Snake.h"
#include "Food.h"
#include "Camera.h"
#include "Board.h"
#include "Score.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									Prototyping															////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Idle(void);
void SetupWindow(void);
void PaintComponent(void);
void UpdateLogic(void);

void ReshapeWindow(GLint, GLint);

void drawScore(void);
void MouseMotionEvent(int, int);
void MouseWheelEvent(int, int, int, int);
void KeyEvent(unsigned char, int, int);
void KeyEventUp(unsigned char, int, int);


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									Global Variables and Objects										////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLfloat WINDOWWIDTH = 800;
GLfloat WINDOWHEIGHT = 600;
Camera camera = Camera(-20, -50, 0, 70, -90, 0);
Snake snake = Snake();
Food food = Food();
Board board = Board();
Score score = Score();
ObjModel* model;
bool keys[255];
GLfloat WHITE[] = { 1, 1, 1 };

//	History trackers
GLfloat frameTime = 0;
GLfloat updateTimer = 1;
GLint lastX = 0;
GLint lastY = 0;

//	Flags
bool jump = false;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									Render Events														////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Idle(void)
{
	GLfloat newFrameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	GLfloat deltaTime = newFrameTime - frameTime;
	frameTime = newFrameTime;
	updateTimer -= deltaTime;


	const GLfloat speed = 10;
	if (keys['a']) camera.MoveCamera(0, deltaTime*speed);
	if (keys['d']) camera.MoveCamera(180, deltaTime*speed);
	if (keys['w']) camera.MoveCamera(90, deltaTime*speed);
	if (keys['s']) camera.MoveCamera(270, deltaTime*speed);

	if (updateTimer <= 0)
	{
		UpdateLogic();
		updateTimer = 1;
	}

	glutPostRedisplay();
}

void SetupWindow(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

	glViewport(0, 0, (GLsizei)WINDOWWIDTH, (GLsizei)WINDOWHEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, WINDOWWIDTH / WINDOWWIDTH, 0.01f, 100.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glRotatef(camera.rotZ, 0, 0, 1);
	glTranslatef(camera.posX, camera.posY, camera.posZ);
}

void UpdateLogic(void)
{
	snake.eat(food);
	int is_End = snake.move();
	if (is_End == 1)
	{
		if (snake.snakeSize > score.score)
		{
			string scoreName;
			cout << "Type your name: ";
			cin >> scoreName;

			score.SaveScore(scoreName, snake.snakeSize);
			bool flag = false;
			while (!flag)
			{
				cout << "Type N for a new game or E to EXIT" << endl;
				cin >> scoreName;

				if (scoreName == "N")
				{
					camera = Camera(-20, -50, 0, 70, -90, 0);
					snake.reset();
					food.newFood();
					score.loadHighScore();
					flag = true;
				}
				else if (scoreName == "E")
				{
					glutLeaveMainLoop();
				}
			}
			glutSetWindow(1);
		}
		else
		{
			glutLeaveMainLoop();
		}
	}
}

void PaintComponent(void)
{
	SetupWindow();

	board.draw();

	glPushMatrix();
		glTranslatef(food.position.getX(), food.position.getY(), food.position.getZ());
		model->draw();
	glPopMatrix(); 

	//food.draw();
	snake.draw();
	
	drawScore();
	glFlush();
	glutSwapBuffers();
}

void drawScore()
{
	glMatrixMode(GL_PROJECTION);
	GLdouble *matrix = new GLdouble[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glLoadIdentity();
	glRasterPos2i(10,50);
	string s = "Record: " + to_string(score.score) + " by " + score.name;
	string s1 = "Current: " + to_string(snake.snakeSize);
	for (unsigned int i = 0; i<s.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
	}
	glRasterPos2i(10, 35);
	for (unsigned int i = 0; i<s1.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s1[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void ReshapeWindow(GLint w, GLint h)
{
	WINDOWWIDTH = (GLfloat)w;
	WINDOWHEIGHT = (GLfloat)h;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									Input Handlers														////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		if (snake.dir != Snake::Direction::DOWN)
		{
			snake.dir = Snake::Direction::UP;
		}
		break;
	case GLUT_KEY_DOWN:
		if (snake.dir != Snake::Direction::UP)
		{
			snake.dir = Snake::Direction::DOWN;
		}
		break;
	case GLUT_KEY_LEFT:
		if (snake.dir != Snake::Direction::RIGHT)
		{
			snake.dir = Snake::Direction::LEFT;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (snake.dir != Snake::Direction::LEFT)
		{
			snake.dir = Snake::Direction::RIGHT;
		}
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
		glutWarpPointer((int)WINDOWWIDTH / 2, (int)WINDOWHEIGHT / 2);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									MAIN																////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize((int)WINDOWWIDTH, (int)WINDOWHEIGHT);
	glutCreateWindow("Snake");
	glEnable(GL_DEPTH_TEST);
	glutIdleFunc(Idle);
	glutDisplayFunc(PaintComponent);
	glutReshapeFunc(ReshapeWindow);
	glutKeyboardFunc(KeyEvent);
	glutKeyboardUpFunc(KeyEventUp);
	glutSpecialFunc(SpecialKeyEvent);
	glutPassiveMotionFunc(MouseMotionEvent);
	glutMouseWheelFunc(MouseWheelEvent);
	glutWarpPointer((int)WINDOWWIDTH / 2, (int)WINDOWHEIGHT / 2);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	model = new ObjModel("models/cheese/object.obj");

	glutMainLoop();


	return 0;
}