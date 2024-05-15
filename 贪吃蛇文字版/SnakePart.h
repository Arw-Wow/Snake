#pragma once

#include "Position.h"
#include <easyx.h>

class SnakePart
{
public:
	// SnakePart(Position position, char Type) :position(position), Type(Type) {
	// }
	SnakePart(Position position) :position(position) {
	}


	Position position;
	// char Type;	// 是head还是tail还是body

private:


};

