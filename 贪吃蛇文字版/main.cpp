#include <iostream>
#include "Sence.h"
#include "Position.h"
#include "SnakePart.h"

int main() {
	Sence* sence = new Sence;
	sence->Init();
	sence->PlayGame();

	return 0;
}