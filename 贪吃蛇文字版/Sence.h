#pragma once

#include <deque>
#include <time.h>
#include "Position.h"
#include "SnakePart.h"

#define BoardRow 13
#define BoardCol 26
#define MaxLength 440

class Sence
{
public:

	void Init();
	void PlayGame();

private:
	bool move(char dir);
	void display();
	void InitBoard();
	// void updateBoard();
	bool is_out(int row, int col);
	bool is_food(int row, int col);
	void setFood();
	bool is_Body(int row, int col);

	char** Board;
	std::deque <SnakePart> Snake;
	// SnakePart* Snake;
	// int* Snake;
	
};

