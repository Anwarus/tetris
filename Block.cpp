#include "Block.h"

Block::Block()
{
	position.pos1 = sf::Vector2f(0, 0);
	srand(time(NULL));
	color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	rotationIndex = 0;
}

void Block::move(sf::Vector2f pos)
{
	position.pos1 += pos;
	position.pos2 += pos;
	position.pos3 += pos;
	position.pos4 += pos;
}

sf::Vector2f Block::getPosition(int posIndex)
{
	switch (posIndex)
	{
	case 1:
		return position.pos1;
		break;
	case 2:
		return position.pos2;
		break;
	case 3:
		return position.pos3;
		break;
	case 4:
		return position.pos4;
		break;
	default:
		return position.pos1;
		break;
	}
}

IBlock::IBlock()
{ 
	position.pos2 = sf::Vector2f(0, 1);
	position.pos3 = sf::Vector2f(0, 2);
	position.pos4 = sf::Vector2f(0, 3);
}

void IBlock::rotate()
{
	if (rotationIndex == 0)
	{
		position.pos1 += sf::Vector2f(2, 1);
		position.pos2 += sf::Vector2f(1, 0);
		position.pos3 += sf::Vector2f(0, -1);
		position.pos4 += sf::Vector2f(-1, -2);
		rotationIndex++;
	}
	else if (rotationIndex == 1)
	{
		position.pos1 += sf::Vector2f(-1, 2);
		position.pos2 += sf::Vector2f(0, 1);
		position.pos3 += sf::Vector2f(1, 0);
		position.pos4 += sf::Vector2f(2, -1);
		rotationIndex++;
	}
	else if (rotationIndex == 2)
	{
		position.pos1 += sf::Vector2f(-2, -1);
		position.pos2 += sf::Vector2f(-1, 0);
		position.pos3 += sf::Vector2f(0, 1);
		position.pos4 += sf::Vector2f(1, 2);
		rotationIndex++;
	}
	else if (rotationIndex == 3)
	{
		position.pos1 += sf::Vector2f(1, -2);
		position.pos2 += sf::Vector2f(0, -1);
		position.pos3 += sf::Vector2f(-1, 0);
		position.pos4 += sf::Vector2f(-2, 1);
		rotationIndex = 0;
	}
}

JBlock::JBlock()
{
	position.pos1 = sf::Vector2f(1, 0);
	position.pos2 = sf::Vector2f(1, 1);
	position.pos3 = sf::Vector2f(1, 2);
	position.pos4 = sf::Vector2f(0, 2);
}

void JBlock::rotate()
{
	if (rotationIndex == 0)
	{
		position.pos1 += sf::Vector2f(1, 1);
		position.pos2 += sf::Vector2f(0, 0);
		position.pos3 += sf::Vector2f(-1, -1);
		position.pos4 += sf::Vector2f(0, -2);
		rotationIndex++;
	}
	else if (rotationIndex == 1)
	{
		position.pos1 += sf::Vector2f(-1, 1);
		position.pos2 += sf::Vector2f(0, 0);
		position.pos3 += sf::Vector2f(1, -1);
		position.pos4 += sf::Vector2f(2, 0);
		rotationIndex++;
	}
	else if (rotationIndex == 2)
	{
		position.pos1 += sf::Vector2f(-1, -1);
		position.pos2 += sf::Vector2f(0, 0);
		position.pos3 += sf::Vector2f(1, 1);
		position.pos4 += sf::Vector2f(0, 2);
		rotationIndex++;
	}
	else if (rotationIndex == 3)
	{
		position.pos1 += sf::Vector2f(1, -1);
		position.pos2 += sf::Vector2f(0, 0);
		position.pos3 += sf::Vector2f(-1, 1);
		position.pos4 += sf::Vector2f(-2, 0);
		rotationIndex = 0;
	}
}

LBlock::LBlock()
{
	position.pos2 = sf::Vector2f(0, 1);
	position.pos3 = sf::Vector2f(0, 2);
	position.pos4 = sf::Vector2f(1, 2);
}

void LBlock::rotate()
{
	if (rotationIndex == 0)
	{
		position.pos1 += sf::Vector2f(2, 0);
		position.pos2 += sf::Vector2f(1, -1);
		position.pos3 += sf::Vector2f(0, -2);
		position.pos4 += sf::Vector2f(-1, -1);
		rotationIndex++;
	}
	else if (rotationIndex == 1)
	{
		position.pos1 += sf::Vector2f(0, 2);
		position.pos2 += sf::Vector2f(1, 1);
		position.pos3 += sf::Vector2f(2, 0);
		position.pos4 += sf::Vector2f(1, -1);
		rotationIndex++;
	}
	else if (rotationIndex == 2)
	{
		position.pos1 += sf::Vector2f(-2, 0);
		position.pos2 += sf::Vector2f(-1, 1);
		position.pos3 += sf::Vector2f(0, 2);
		position.pos4 += sf::Vector2f(1, 1);
		rotationIndex++;
	}
	else if (rotationIndex == 3)
	{
		position.pos1 += sf::Vector2f(0, -2);
		position.pos2 += sf::Vector2f(-1, -1);
		position.pos3 += sf::Vector2f(-2, 0);
		position.pos4 += sf::Vector2f(-1, 1);
		rotationIndex = 0;
	}
}

OBlock::OBlock()
{
	position.pos2 = sf::Vector2f(1, 0);
	position.pos3 = sf::Vector2f(1, 1);
	position.pos4 = sf::Vector2f(0, 1);
}

void OBlock::rotate()
{
	//square
}

ZBlock::ZBlock()
{
	position.pos2 = sf::Vector2f(1, 0);
	position.pos3 = sf::Vector2f(1, 1);
	position.pos4 = sf::Vector2f(2, 1);
}

void ZBlock::rotate()
{
	if (rotationIndex == 0)
	{
		position.pos1 += sf::Vector2f(2, 0);
		position.pos2 += sf::Vector2f(1, 1);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(-1, 1);
		rotationIndex++;
	}
	else if (rotationIndex == 1)
	{
		position.pos1 += sf::Vector2f(0, 2);
		position.pos2 += sf::Vector2f(-1, 1);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(-1, -1);
		rotationIndex++;
	}
	else if (rotationIndex == 2)
	{
		position.pos1 += sf::Vector2f(-2, 0);
		position.pos2 += sf::Vector2f(-1, -1);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(1, -1);
		rotationIndex++;
	}
	else if (rotationIndex == 3)
	{
		position.pos1 += sf::Vector2f(0, -2);
		position.pos2 += sf::Vector2f(1, -1);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(1, 1);
		rotationIndex = 0;
	}
}

TBlock::TBlock()
{
	position.pos1 = sf::Vector2f(1, 0);
	position.pos2 = sf::Vector2f(0, 1);
	position.pos3 = sf::Vector2f(1, 1);
	position.pos4 = sf::Vector2f(2, 1);
}

void TBlock::rotate()
{
	if (rotationIndex == 0)
	{
		position.pos1 += sf::Vector2f(1, 1);
		position.pos2 += sf::Vector2f(1, -1);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(-1, 1);
		rotationIndex++;
	}
	else if (rotationIndex == 1)
	{
		position.pos1 += sf::Vector2f(-1, 1);
		position.pos2 += sf::Vector2f(1, 1);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(-1, -1);
		rotationIndex++;
	}
	else if (rotationIndex == 2)
	{
		position.pos1 += sf::Vector2f(-1, -1);
		position.pos2 += sf::Vector2f(-1, 1);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(1, -1);
		rotationIndex++;
	}
	else if (rotationIndex == 3)
	{
		position.pos1 += sf::Vector2f(1, -1);
		position.pos2 += sf::Vector2f(-1, -1);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(1, 1);
		rotationIndex = 0;
	}
}

SBlock::SBlock()
{
	position.pos1 = sf::Vector2f(1, 0);
	position.pos2 = sf::Vector2f(2, 0);
	position.pos3 = sf::Vector2f(1, 1);
	position.pos4 = sf::Vector2f(0, 1);
}

void SBlock::rotate()
{
	if (rotationIndex == 0)
	{
		position.pos1 += sf::Vector2f(1, 1);
		position.pos2 += sf::Vector2f(0, 2);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(1, -1);
		rotationIndex++;
	}
	else if (rotationIndex == 1)
	{
		position.pos1 += sf::Vector2f(-1, 1);
		position.pos2 += sf::Vector2f(-2, 0);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(1, 1);
		rotationIndex++;
	}
	else if (rotationIndex == 2)
	{
		position.pos1 += sf::Vector2f(-1, -1);
		position.pos2 += sf::Vector2f(0, -2);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(-1, 1);
		rotationIndex++;
	}
	else if (rotationIndex == 3)
	{
		position.pos1 += sf::Vector2f(1, -1);
		position.pos2 += sf::Vector2f(2, 0);
		position.pos3 += sf::Vector2f(0, 0);
		position.pos4 += sf::Vector2f(-1, -1);
		rotationIndex = 0;
	}
}