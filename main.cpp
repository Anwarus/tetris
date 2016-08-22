#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Block.h"
#include "Board.h"

using namespace std;

sf::RenderWindow* window;

//Game board size
const int COLUMNS = 10;
const int ROWS = 18;
const int GRID_SIZE = 40;
const int OFFSET_X = 10;
const int OFFSET_Y = 10;
//Window dimensions
const int WIDTH = COLUMNS * GRID_SIZE + 2 * OFFSET_X;
const int HEIGHT = ROWS * GRID_SIZE + 6 * OFFSET_Y;
const int FPS = 30;


//Resources
sf::Font font;
sf::Music music;
sf::Sound sound;
sf::SoundBuffer soundBuffer;
sf::Text menuText;
sf::Text gamePointsText;
sf::Text gameRecordText;
sf::Text pauseText;
sf::Text overPointsText;
sf::Text overRestartText;

//Entities
Block* block;
Board* board;

int points;
int record;
bool acceleration;

enum State {
	MENU,
	GAME,
	PAUSE,
	OVER
} state;

void init();
void input();
void update(sf::Clock &clk);
void draw();

bool checkCollisions();
void moveBlockIntoBoard();
void moveIfValid(sf::Vector2f x);
void rotateIfValid();
void randBlock();

int main()
{
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Tetris");

	init();

	state = MENU;

	sf::Clock clock;
	sf::Clock blockClock;
	while (window->isOpen())
	{
		input();
		if (clock.getElapsedTime().asSeconds() >= 1.0 / FPS)
		{
			update(blockClock);
			draw();
			clock.restart();
		}
	}

	delete window;

	return 0;
}

void init() 
{
	block = nullptr;
	board = nullptr;

	points = 0;
	record = 0;
	acceleration = false;

	if (!font.loadFromFile("font.ttf"))
		cout << "Failed to load font!" << endl;
	if (!music.openFromFile("music.wav"))
		cout << "Failed to load music!" << endl;
	if (!soundBuffer.loadFromFile("sound.wav"))
		cout << "Failed to load sound!" << endl;
	else
		sound.setBuffer(soundBuffer);
	
	menuText.setFont(font);
	menuText.setString("SPACE to start");
	menuText.setPosition(WIDTH / 2 - menuText.getGlobalBounds().width/2, HEIGHT / 2);

	gamePointsText.setFont(font);
	gamePointsText.setString("Points: " + to_string(points));
	gamePointsText.setPosition(OFFSET_X, OFFSET_Y);

	gameRecordText.setFont(font);
	gameRecordText.setString("Record: " + to_string(record));
	gameRecordText.setPosition(WIDTH - OFFSET_X - gameRecordText.getGlobalBounds().width, OFFSET_Y);

	pauseText.setFont(font);
	pauseText.setString("PAUSE");
	pauseText.setPosition(WIDTH / 2 - pauseText.getGlobalBounds().width / 2, HEIGHT / 2);

	overPointsText = gamePointsText;
	overPointsText.setPosition(WIDTH / 2 - overPointsText.getGlobalBounds().width / 2, HEIGHT / 2);

	overRestartText.setFont(font);
	overRestartText.setString("SPACE to restart");
	overRestartText.setPosition(WIDTH / 2 - overRestartText.getGlobalBounds().width / 2, HEIGHT / 2 + OFFSET_Y + overPointsText.getGlobalBounds().height);
}

void input()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyPressed)
			sound.play();
		switch (state)
		{
			case MENU:
			{
				if (event.type == sf::Event::KeyPressed)
					if (event.key.code == sf::Keyboard::Space)
					{
						state = GAME;
						music.play();
					}		
				break;
			}
			case GAME:
			{
				if (block != nullptr)
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Up)
							rotateIfValid();
						if (event.key.code == sf::Keyboard::Right)
							moveIfValid(sf::Vector2f(1, 0));
						if (event.key.code == sf::Keyboard::Down)
							acceleration = true;
						if (event.key.code == sf::Keyboard::Left)
							moveIfValid(sf::Vector2f(-1, 0));
						if (event.key.code == sf::Keyboard::P)
						{
							state = PAUSE;
							music.pause();
						}
					}
					if (event.type == sf::Event::KeyReleased)
						if (event.key.code == sf::Keyboard::Down)
							acceleration = false;
				}
				break;
			}
			case PAUSE:
			{
				if (event.type == sf::Event::KeyPressed)
					if (event.key.code == sf::Keyboard::P)
					{
						state = GAME;
						music.play();
					}
				break;
			}
			case OVER:
			{
				if(event.type == sf::Event::KeyPressed)
					if (event.key.code == sf::Keyboard::Space)
					{
						if (points > record)
							record = points;
						points = 0;
						if(board != nullptr)
							delete board;
						board = nullptr;
						acceleration = false;
						state = GAME;
						music.play();
					}
				break;
			}
		}
	}
}

void update(sf::Clock &clk)
{
	if (state == GAME)
	{
		if (board == nullptr)
		{
			board = new Board(COLUMNS, ROWS);
			return;
		}
		if (block == nullptr)
		{
			randBlock();
			acceleration = false;
			clk.restart();
			return;
		}

		if (clk.getElapsedTime().asSeconds() >= 0.5 || acceleration)
		{
			if (board->checkForGameOver())
			{
				overPointsText.setString(gamePointsText.getString());
				state = OVER;
				music.stop();
			}
			if (checkCollisions())
			{
				moveBlockIntoBoard();
				return;
			}
			points += board->checkForPoints();
			gamePointsText.setString("Points: " + to_string(points));
			gameRecordText.setString("Record: " + to_string(record));
			gameRecordText.setPosition(WIDTH - OFFSET_X - gameRecordText.getGlobalBounds().width, OFFSET_Y);
			block->move(sf::Vector2f(0, 1));
			clk.restart();
		}
	}
}

void draw()
{
	window->clear(sf::Color::Black);

	switch (state)
	{
		case MENU:
		{
			window->draw(menuText);
			break;
		}
		case GAME:
		{
			sf::RectangleShape rect;
			//Draw board rect
			rect.setOutlineColor(sf::Color::White);
			rect.setFillColor(sf::Color(0, 0, 0, 0));
			rect.setOutlineThickness(1);
			rect.setPosition(OFFSET_X, 2 * OFFSET_Y + gamePointsText.getGlobalBounds().height);
			rect.setSize(sf::Vector2f(COLUMNS * GRID_SIZE, ROWS * GRID_SIZE));
			window->draw(rect);

			//Draw filled board fields
			if (board != nullptr)
			{
				rect.setOutlineThickness(0);
				rect.setSize(sf::Vector2f(GRID_SIZE - 4, GRID_SIZE - 4));
				for (int i = 0; i < COLUMNS; i++)
				{
					for (int j = 0; j < ROWS; j++)
					{
						if (board->getColor(i, j).a > 0)
						{
							rect.setPosition(i * GRID_SIZE + OFFSET_X + 2, j * GRID_SIZE + 2 * OFFSET_Y + gamePointsText.getGlobalBounds().height + 2);
							rect.setFillColor(board->getColor(i, j));
							window->draw(rect);
						}
					}
				}
			}

			//Draw block
			if (block == nullptr)
				return;
			for (int i = 1; i <= 4; i++)
			{
				rect.setPosition(block->getPosition(i).x * GRID_SIZE + OFFSET_X + 2, block->getPosition(i).y * GRID_SIZE + 2 * OFFSET_Y + gamePointsText.getGlobalBounds().height + 2);
				rect.setFillColor(block->getColor());
				window->draw(rect);
			}

			window->draw(gamePointsText);
			window->draw(gameRecordText);

			break;
		}
		case PAUSE:
		{
			window->draw(pauseText);
			break;
		}
		case OVER:
		{
			window->draw(overPointsText);
			window->draw(overRestartText);
			break;
		}
	}

	window->display();
}

bool checkCollisions()
{
	bool collision = false;
	for (int i = 1; i <= 4; i++)
	{
		if (block->getPosition(i).y == ROWS - 1)
		{
			collision = true;
			break;
		}
		if (board->getColor(block->getPosition(i).x, block->getPosition(i).y + 1).a > 0)
		{
			collision = true;
			break;
		}
	}

	if (collision)
		return true;
	return false;
}

void moveBlockIntoBoard()
{
	for (int i = 1; i <= 4; i++)
	{
		if(block->getPosition(i).y >= 0)
			board->setColor(block->getPosition(i).x, block->getPosition(i).y, block->getColor());
	}
	delete block;
	block = nullptr;
}

void moveIfValid(sf::Vector2f x)
{
	for (int i = 1; i <= 4; i++)
	{
		if (block->getPosition(i).x + x.x > COLUMNS - 1 || block->getPosition(i).x + x.x < 0)
			return;
		if (block->getPosition(i).y + x.y > ROWS - 1 || block->getPosition(i).y + x.y > ROWS < 0)
			return;
		if (board->getColor(block->getPosition(i).x + x.x, block->getPosition(i).y + x.y).a > 0)
			return;
	}
	block->move(x);
}

void randBlock()
{
	srand(time(NULL));
	int i = rand() % 7;
	switch (i)
	{
	case 0:
		block = new IBlock();
		break;
	case 1:
		block = new JBlock();
		break;
	case 2:
		block = new LBlock();
		break;
	case 3:
		block = new OBlock();
		break;
	case 4:
		block = new ZBlock();
		break;
	case 5:
		block = new TBlock();
		break;
	case 6:
		block = new SBlock();
		break;
	}
	block->move(sf::Vector2f(COLUMNS/3, 0));
}

void rotateIfValid()
{
	int x = 0;
	block->rotate();
	for (int i = 1; i <= 4; i++)
	{
		if (block->getPosition(i).x >= 0 && block->getPosition(i).x < COLUMNS &&
			block->getPosition(i).y >= 0 && block->getPosition(i).y < ROWS)
		{
			if (board->getColor(block->getPosition(i).x, block->getPosition(i).y).a == 0)
				x++;
		}
	}

	if (x == 4)
		return;
	for (int i = 0; i < 3; i++)
		block->rotate();
}