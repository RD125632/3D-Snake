#include "Snake.h"
#include "Score.h"

using namespace std;

Snake::Snake(void)
{
	color.setRGBColor(1.0f, 0.3f, 0.3f);
	snakeSize = 2;
	body.push_back(Position( 0.0f, 0.0f, 0.0f));
}

void Snake::reset(void)
{
	Direction dir = DOWN;
	body.clear();
	body.push_back(Position(0.0f, 0.0f, 0.0f));
	snakeSize = 2;
}

int Snake::move(void)
{
	if (body.size() >= (unsigned)snakeSize)
	{
		body.erase(body.begin());
	}

	GLfloat nX = body.back().getX();
	GLfloat nY = body.back().getY();
	GLfloat nZ = body.back().getZ();
	Position newPos = Position();

	switch (dir)
	{
	case Direction::UP:
		if (body.back().getX() > -19.0f)
		{
			newPos.set(nX - 2.0f, nY, nZ);		
		}
		else
		{
			std::cout << "GAME OVER!!" << endl;
			return 1;
		}
		break;
	case Direction::DOWN:
		if (body.back().getX() < 19.0f)
		{
			newPos.set(nX + 2.0f, nY, nZ);
		}
		else
		{
			std::cout << "GAME OVER!!" << endl;
			return 1;
		}
		break;
	case Direction::LEFT:
		if (body.back().getZ() < 19.0f)
		{
			newPos.set(nX, nY, nZ + 2.0f);
		}
		else
		{
			std::cout << "GAME OVER!!" << endl;
			return 1;
		}
		break;
	case Direction::RIGHT:
		if (body.back().getZ() > -19.0f)
		{
			newPos.set(nX, nY, nZ - 2.0f);
		}
		else
		{
			std::cout << "GAME OVER!!" << endl;
			return 1;
		}
		break;
	default:
		return 0;
	}
	body.push_back(newPos);
	return 0;
}

void Snake::draw()
{

	GLfloat lightPosition[] = { 5, 5, 6, 0 };
	GLfloat lightA[] = { 0.5,0.5,0.5,1 };
	GLfloat Ambient[] = { 0.4,0,0 };
	GLfloat Diffuse[] = { color.getRed(),  color.getGreen(), color.getBlue(), 1.0f };
	GLfloat Specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat s = 5.0f;

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightA);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	int viewpoint = 0;
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);

	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
	glMaterialf(GL_FRONT, GL_SHININESS, s);

	for (Position p : body)
	{
		drawPart(p);
	}
}

void Snake::drawPart(Position p)
{

	glPushMatrix();

	glTranslatef(p.getX(), p.getY(), p.getZ());


	//Back face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(snakeSquareSize / 2, snakeSquareSize / 2, snakeSquareSize / 2);
	glVertex3f(-snakeSquareSize / 2, snakeSquareSize / 2, snakeSquareSize / 2);
	glVertex3f(-snakeSquareSize / 2, -snakeSquareSize / 2, snakeSquareSize / 2);
	glVertex3f(snakeSquareSize / 2, -snakeSquareSize / 2, snakeSquareSize / 2);

	//Left face
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-snakeSquareSize / 2, snakeSquareSize / 2, snakeSquareSize / 2);
	glVertex3f(-snakeSquareSize / 2, snakeSquareSize / 2, -snakeSquareSize / 2);
	glVertex3f(-snakeSquareSize / 2, -snakeSquareSize / 2, -snakeSquareSize / 2);
	glVertex3f(-snakeSquareSize / 2, -snakeSquareSize / 2, snakeSquareSize / 2);

	//Right face
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(snakeSquareSize / 2, snakeSquareSize / 2, -snakeSquareSize / 2);
	glVertex3f(snakeSquareSize / 2, snakeSquareSize / 2, snakeSquareSize / 2);
	glVertex3f(snakeSquareSize / 2, -snakeSquareSize / 2, snakeSquareSize / 2);
	glVertex3f(snakeSquareSize / 2, -snakeSquareSize / 2, -snakeSquareSize / 2);

	//Top face
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-snakeSquareSize / 2, snakeSquareSize / 2, -snakeSquareSize / 2);
	glVertex3f(-snakeSquareSize / 2, snakeSquareSize / 2, snakeSquareSize / 2);
	glVertex3f(snakeSquareSize / 2, snakeSquareSize / 2, snakeSquareSize / 2);
	glVertex3f(snakeSquareSize / 2, snakeSquareSize / 2, -snakeSquareSize / 2);

	//Front face
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(snakeSquareSize / 2, -snakeSquareSize / 2, -snakeSquareSize / 2);
	glVertex3f(snakeSquareSize / 2, snakeSquareSize / 2, -snakeSquareSize / 2);
	glVertex3f(-snakeSquareSize / 2, snakeSquareSize / 2, -snakeSquareSize / 2);
	glVertex3f(-snakeSquareSize / 2, -snakeSquareSize / 2, -snakeSquareSize / 2);
	glEnd();
	glPopMatrix();
}

void Snake::eat(Food & food) {

	Position a = body.back();
	GLfloat aS = snakeSquareSize / 2;
	Position b = food.position;
	GLfloat bS = food.hitbox / 2;

	if ((a.getX() + aS >= b.getX()) &&
		(a.getX() <= b.getX() + bS) &&
		(a.getZ() + aS >= b.getZ()) &&
		(a.getZ() <= b.getZ() + bS))
	{
		food.newFood();
		snakeSize++;
	}

}
