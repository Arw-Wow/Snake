#include <iostream>
#include "Sence.h"
#include <conio.h>

void Sence::Init()
{
	srand(time(0));

	//init Board
	InitBoard();

	// Snake = new SnakePart[MaxLength];
	Snake.push_front(SnakePart(Position(BoardRow / 2, BoardCol / 2), HEAD));
	Board[BoardRow / 2][BoardCol / 2] = HEAD;
	// Board[2][2] == BODY;

	//生成初始FOOD
	setFood();

	display();
	
}

void Sence::PlayGame()
{
	char dir;

	while (1) {
		dir = _getch();
		// dir = getchar();
		// getchar();

		if (!move(dir)) {
			std::cout << "你输了！" << std::endl;
			break;
		}

		display();

	}
}

bool Sence::move(char dir)
{
	// static int stepCount = -1;	//每五步生成一个FOOD
	// stepCount++;

	int tailRow = Snake.back().position.row;
	int tailCol = Snake.back().position.col;
	

	int oheadRow = Snake.front().position.row;
	int oheadCol = Snake.front().position.col;
	int headRow = oheadRow;
	int headCol = oheadCol;

	if (dir == 'w') {
		headRow--;
	}
	else if (dir == 's') {
		headRow++;
	}
	else if (dir == 'a') {
		headCol--;
	}
	else if (dir == 'd') {
		headCol++;
	}	
	
	if (is_out(headRow, headCol) || is_Body(headRow, headCol))
		return false;

	if (!is_food(headRow, headCol)) {
		Snake.pop_back();
		Board[tailRow][tailCol] = EMPTY;
	}
	else {
		setFood();
	}

	Snake.push_front(SnakePart(Position(headRow, headCol), HEAD));
	Board[headRow][headCol] = HEAD;
	if (Snake.size() > 1) {
		Snake[1].Type = BODY;
		Board[oheadRow][oheadCol] = BODY;
	}


	return true;
}

void Sence::display()
{
	// clrscr();
	system("cls");	//每次先清屏

	for (int i = 0; i < BoardRow; i++) {
		for (int j = 0; j < BoardCol; j++) {
			std::cout << Board[i][j];
		}
		std::cout << std::endl;
	}
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
			Board[i][j] = ' ';
		}
	}

	for (int i = 0; i < BoardRow; i++) {
		Board[i][0] = '#';
		Board[i][BoardCol - 1] = '#';
	}
	for (int i = 0; i < BoardCol; i++) {
		Board[0][i] = '#';
		Board[BoardRow - 1][i] = '#';
	}

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
	if (Board[row][col] == BODY || Board[row][col] == HEAD)
		return true;

	return false;
}

// void Sence::updateBoard()
// {
	
// }
