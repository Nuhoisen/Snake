#ifndef SNAKE_BOARD_H
#define SNAKE_BOARD_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <thread>
#include <Windows.h>
#include <iostream>

using std::cin;
using std::cout;
using std::list;

enum DIRECTIONS
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	EXIT
};

class SnakeBoard
{
public:

	SnakeBoard(short x, short y);
	void MakeBoard();
	void MoveSnake();
	void MakeMove();
	void TailMove(short xDim, short yDim);
	void GameLogic();
	void SetDirection(int);
	void NewMouse();
	bool MouseCheck();
	bool WallCheck();
	bool HitCheck();
private:

	short xDim;
	short yDim;
	list<COORD> snakeList;
	int mDirection;
	COORD mouse;
	int speedOffset;
};

#endif // !SNAKE_BOARD_H
