#pragma once

#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <vector>
#include "ObjModel.h"

class Book
{
public:
	Book();
	Book(int);
	ObjModel* model = new ObjModel("book/spellbook.obj");
};

#endif