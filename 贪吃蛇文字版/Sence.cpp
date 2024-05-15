#include <iostream>
#include "Sence.h"
#include <conio.h>

void Sence::Init()
{
	srand(time(0));

	EatFood = 0;

	//init Board
	InitBoard();

	InitGraph();

	// Snake = new SnakePart[MaxLength];
	Snake.push_front(SnakePart(Position(BoardRow / 2, BoardCol / 2)));
	Board[BoardRow / 2][BoardCol / 2] = HEADUP;
	// Board[2][2] == BODY;

	//生成初始FOOD
	setFood();

	display();

	outputScore();
	
}

void Sence::PlayGame()
{
	char dir;

	time_t beginTime = 0;
	time_t endTime = clock();
	while (1) {
		// dir = _getch();
		// dir = getchar();
		// getchar();
		
		beginTime = clock();
		if (double(beginTime - endTime) < FPS) {
			Sleep(double(FPS - (beginTime - endTime)));
		}

		ExMessage m;
		if (peekmessage(&m, EX_KEY)) {
			flushmessage();
			BYTE dir = m.vkcode;
			if (!move(dir)) {
				// std::cout << "你输了！" << std::endl;
				MessageBox(0, "Game Over!", "游戏结束", MB_OK);
				break;
			}
		}
		else {
			if (!move(0)) {
				// std::cout << "你输了！" << std::endl;
				MessageBox(0, "Game Over!", "游戏结束", MB_OK);
				break;
			}
		}

		display();
		outputScore();

		endTime = beginTime;
	}
}

bool Sence::move(BYTE dir)
{
	// static int stepCount = -1;	//每五步生成一个FOOD
	// stepCount++;

	static char LastHeadType = HEADUP;

	int tailRow = Snake.back().position.row;
	int tailCol = Snake.back().position.col;
	

	int oheadRow = Snake.front().position.row;
	int oheadCol = Snake.front().position.col;
	int headRow = oheadRow;
	int headCol = oheadCol;

	char HeadType;

	if (dir == 0) {
		if (LastHeadType == HEADUP) {
			headRow--;
		}
		else if (LastHeadType == HEADDOWN) {
			headRow++;
		}
		else if (LastHeadType == HEADLEFT) {
			headCol--;
		}
		else if (LastHeadType == HEADRIGHT) {
			headCol++;
		}
		HeadType = LastHeadType;
	}

	else if (dir == VK_UP) {
		headRow--;
		HeadType = HEADUP;
	}
	else if (dir == VK_DOWN) {
		headRow++;
		HeadType = HEADDOWN;
	}
	else if (dir == VK_LEFT) {
		headCol--;
		HeadType = HEADLEFT;
	}
	else if (dir == VK_RIGHT) {
		headCol++;
		HeadType = HEADRIGHT;
	}
	else
		return true;

	
	if (is_out(headRow, headCol) || is_Body(headRow, headCol))
		return false;

	// std::cout << headRow << " " << headCol << std::endl;

	if (!is_food(headRow, headCol)) {
		Snake.pop_back();
		Board[tailRow][tailCol] = EMPTY;
	}
	else {
		EatFood++;
		setFood();
	}

	Snake.push_front(SnakePart(Position(headRow, headCol)));
	Board[headRow][headCol] = HeadType;
	if (Snake.size() > 1) {
		// Snake[1].Type = BODY;
		Board[oheadRow][oheadCol] = BODY;
	}

	LastHeadType = HeadType;

	return true;
}

void Sence::display()
{
	for (int i = 0; i < BoardRow; i++) {
		for (int j = 0; j < BoardCol; j++) {
			setImage(i, j, Board[i][j]);
		}
	}



	// clrscr();
	// system("cls");	//每次先清屏

	// for (int i = 0; i < BoardRow; i++) {
	//	for (int j = 0; j < BoardCol; j++) {
	//		std::cout << Board[i][j];
	//	}
	//	std::cout << std::endl;
	// }
	// for (int i = 0; i < 20; i++) {
	//	std::cout << std::endl;
	// }
}

void Sence::InitBoard()	//蛇默认生成到中央
{
	Board = new char* [BoardRow];
	for (int i = 0; i < BoardRow; i++) {
		Board[i] = new char[BoardCol];
	}

	for (int i = 0; i < BoardRow; i++) {
		for (int j = 0; j < BoardCol; j++) {
			Board[i][j] = EMPTY;
		}
	}

	for (int i = 0; i < BoardRow; i++) {
		Board[i][0] = WALL;
		Board[i][BoardCol - 1] = WALL;
	}
	for (int i = 0; i < BoardCol; i++) {
		Board[0][i] = WALL;
		Board[BoardRow - 1][i] = WALL;
	}

}

void Sence::InitGraph()
{
	initgraph(BoardCol * GridSize, BoardRow * GridSize + 30);
	setbkcolor(RGB(255, 229, 204));
	cleardevice();

	// load the backimage
	// loadimage(0, "res/image/bk.jpg", BoardCol * GridSize, BoardRow * GridSize);
	


}

bool Sence::is_out(int row, int col)
{	
	if (row < 1 || row >= BoardRow - 1 || col < 1 || col >= BoardCol - 1)
		return true;

	return false;
}

bool Sence::is_food(int row, int col)
{
	if (Board[row][col] == FOOD)
		return true;

	return false;
}

void Sence::setFood()
{
	int f_row = 1 + rand() % (BoardRow - 2);
	int f_col = 1 + rand() % (BoardCol - 2);

	if (Board[f_row][f_col] != EMPTY)
		setFood();
	else {
		Board[f_row][f_col] = FOOD;
	}
}

bool Sence::is_Body(int row, int col)
{
	if (Board[row][col] <= '6' && Board[row][col] >= '1')
		return true;

	return false;
}

void Sence::setImage(int row, int col, char type)
{
	char filename[100] = { 0 };
	sprintf_s(filename, sizeof(filename), "res/image/%c.png", type);

	IMAGE m;
	loadimage(&m, filename);
	putimage(col * GridSize, row * GridSize, &m);
}

void Sence::outputScore()
{
	static time_t beginTime = clock();
	static char time_str[100] = { 0 };

	// 抵消之前的文字
	settextcolor(RGB(255, 229, 204));
	outtextxy(BoardCol * GridSize - 100, BoardRow * GridSize + 5, time_str);

	time_t curTime = clock();
	sprintf_s(time_str, sizeof(time_str), "得分：%d", EatFood * 5 + (curTime - beginTime) / 1000);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(BoardCol * GridSize - 100, BoardRow * GridSize + 5, time_str);
}

// void Sence::updateBoard()
// {
	
// }
