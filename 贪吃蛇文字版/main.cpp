#include <iostream>
#include <easyx.h>
#include "Sence.h"
#include "Position.h"
#include "SnakePart.h"

int main() {
	Sence* sence = new Sence;
	sence->Init();
	sence->PlayGame();

	delete sence;

	return 0;
}

// int main() {
//	IMAGE m;

//	initgraph(300, 300);
//	setbkcolor(RGB(51, 51, 255));
//	cleardevice();

//	getimage(&m, 0, 0, 25, 25);
//	saveimage("res/image/6.png", &m);

//	return 0;
// }