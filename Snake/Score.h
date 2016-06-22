#pragma once

#ifndef SCORE_H_
#define SCORE_H_
#include <GL\freeglut.h>
#include <string>

using namespace std;

class Score
{
private:
	vector<string> Score::split(const string& , char);
	vector<string> &Score::split(const string &, char, vector<string> &);
public:
	Score();
	void Score::SaveScore(string, GLuint);
	void Score::loadHighScore();
	GLint score;
	string name;
};

#endif

