#pragma once

#include "Position.h"

#define HEAD 'O'
#define BODY 'o'
// #define TAIL 'o'
#define EMPTY ' '
#define FOOD '*'

class SnakePart
{
public:
	SnakePart(Position position, char Type) :position(position), Type(Type) {
	}

	Position position;
	char Type;	// 是head还是tail还是body

private:


};

