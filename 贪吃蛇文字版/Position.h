#pragma once
class Position
{
public:
	Position() = default;
	Position(int row, int col) : row(row), col(col) {}

	int row;
	int col;
};

