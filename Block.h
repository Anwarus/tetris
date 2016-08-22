#pragma once

#include <SFML/Graphics.hpp>

#include <ctime>
#include <iostream>

struct BlockPosition{
	sf::Vector2f pos1;
	sf::Vector2f pos2;
	sf::Vector2f pos3;
	sf::Vector2f pos4;
};

class Block
{
public:
	Block();
	~Block() {};

	void move(sf::Vector2f pos);
	virtual void rotate() = 0;

	sf::Color getColor() { return color; };
	sf::Vector2f getPosition(int posIndex);

protected:
	BlockPosition position;
	sf::Color color;
	int rotationIndex;
};

class IBlock : public Block
{
public:
	IBlock();
	~IBlock() {};

	void rotate();
};

class JBlock : public Block
{
public:
	JBlock();
	~JBlock() {};

	void rotate();
};

class LBlock : public Block
{
public:
	LBlock();
	~LBlock() {};

	void rotate();
};

class OBlock : public Block
{
public:
	OBlock();
	~OBlock() {};

	void rotate();
};

class ZBlock : public Block
{
public:
	ZBlock();
	~ZBlock() {};

	void rotate();
};

class TBlock : public Block
{
public:
	TBlock();
	~TBlock() {};

	void rotate();
};

class SBlock : public Block
{
public:
	SBlock();
	~SBlock() {};

	void rotate();
};
