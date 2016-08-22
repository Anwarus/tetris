#pragma once

#include <SFML/Graphics.hpp>

class Board
{
public:
	Board(int col, int row);
	~Board();

	sf::Color getColor(int column, int row);
	void setColor(int column, int row, sf::Color color);
	int checkForPoints();
	bool checkForGameOver();

private:
	int columns;
	int rows;

	void reload(int row);
	void clearRow(int row);

	sf::Color** fields;
};

