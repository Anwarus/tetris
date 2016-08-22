#include "Board.h"

Board::Board(int col, int row)
{
	columns = col;
	rows = row;

	fields = new sf::Color*[columns];
	for (int i = 0; i < columns; i++)
		fields[i] = new sf::Color[rows];

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			fields[i][j] = sf::Color(0, 0, 0, 0);
		}
	}
}


Board::~Board()
{
		for (int j = 0; j < columns; j++)
			delete[] fields[j];
		delete[] fields;
}

sf::Color Board::getColor(int column, int row)
{
	return fields[column][row];
}

void Board::setColor(int column, int row, sf::Color color)
{
	fields[column][row] = color;
}

int Board::checkForPoints()
{
	int points = 0;
	for (int i = rows - 1; i >= 0; i--)
	{
		int x = 0;
		for (int j = 0; j < columns; j++)
		{
			if (fields[j][i].a > 0)
				x++;
		}
		if (x == columns)
		{
			points++;
			clearRow(i);
			reload(i);
		}
	}
	return points;
}

bool Board::checkForGameOver()
{
	for (int i = 0; i < columns; i++)
	{
		if (fields[i][0].a > 0)
			return true;
	}
	return false;
}

void Board::reload(int row)
{
	if (row == rows)
		return;

	for (int i = row; i > 0; i--)
	{
		for (int j = 0; j < columns; j++)
			fields[j][i] = fields[j][i - 1];
	}
}

void Board::clearRow(int row)
{
	for (int i = 0; i < columns; i++)
		fields[i][row] = sf::Color(0, 0, 0, 0);
}