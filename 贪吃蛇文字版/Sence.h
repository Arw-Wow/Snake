#pragma once

#include <deque>
#include <time.h>
#include <easyx.h>
#include "Position.h"
#include "SnakePart.h"

#define BoardRow 23
#define BoardCol 23
#define MaxLength 440
#define GridSize 25

// #define HEAD 'O'
#define HEADUP '1'
#define HEADDOWN '2'
#define HEADLEFT '3'
#define HEADRIGHT '4'

#define BODY '5'
#define EMPTY '0'
#define FOOD '@'
#define WALL '6'
// #define TAIL 'o'

#define FPS 1000.f / 30



class Sence
{
public:

	void Init();
	void PlayGame();

private:
	bool move(BYTE dir);
	void display();
	void InitBoard();
	void InitGraph();
	// void updateBoard();
	bool is_out(int row, int col);
	bool is_food(int row, int col);
	void setFood();
	bool is_Body(int row, int col);
	void setImage(int row, int col, char type);
	void outputScore();

private:

	char** Board;
	std::deque <SnakePart> Snake;
	int EatFood;
	// SnakePart* Snake;
	// int* Snake;
	
};

