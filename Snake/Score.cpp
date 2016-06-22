#include <vector>
#include "Score.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Score::Score(void)
{
	loadHighScore();
}

void Score::SaveScore(string scorename, GLuint i)
{
	ofstream myfile("Score.txt");
	if (myfile.is_open())
	{
		myfile << i << ":" << scorename;
		myfile.close();
	}
}


void Score::loadHighScore()
{
	ifstream input("Score.txt");
	string line;

	for (string line; getline(input, line); )
	{
		vector<string> parts = Score::split(line, ':');
		score = stoi(parts.at(0));
		name = parts.at(1);
	}
}

vector<string> &Score::split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> Score::split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}
