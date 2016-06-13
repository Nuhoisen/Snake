#include "SnakeBoard.h"
#include "Keyboard.h"

SnakeBoard::SnakeBoard(short x, short y) : xDim(x), yDim(y), snakeList(1, { 4, 5 }), mDirection(RIGHT), mouse({6,6}), speedOffset(0)
{}

void SnakeBoard::MakeBoard()
{
	DWORD word = 0;
	const CHAR output = 254;

	FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), output, xDim, { 0, 0 }, &word);
	FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), output, xDim, { 0, yDim }, &word);

	for (short i = 0; i <= yDim; i++)
	{
		FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), output, 1, { 0, i }, &word);
		FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), output, 1, { xDim, i }, &word);
	}
	NewMouse();
	FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), output, 1, { mouse.X, mouse.Y}, &word);
}

void SnakeBoard::MakeMove()
{
	DWORD word = 0;
	FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), 254, 1, { snakeList.front().X, snakeList.front().Y }, &word);
}

void SnakeBoard::TailMove(short xDim, short yDim)
{
	DWORD word = 0;
	FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), 32, 1, { xDim, yDim }, &word);	//reset old

}

void SnakeBoard::MoveSnake()
{
	DWORD word = 0;
	if (MouseCheck())
	{	
		COORD newTail = { snakeList.back().X - 1, snakeList.back().Y - 1 };
		FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), 254, 1, { mouse.X, mouse.Y }, &word);
		snakeList.push_back(newTail);
	}
	list<COORD>::iterator it = snakeList.begin();
	COORD temp = { it->X, it->Y }, temp2 = { snakeList.back().X, snakeList.back().Y};
	
	switch (mDirection)
	{
	case UP:
		snakeList.front().Y--;
		break;

	case DOWN:
		snakeList.front().Y++;
		break;

	case LEFT:
		snakeList.front().X--;
		break;

	case RIGHT:
		snakeList.front().X++;
		break;
	default:
		break;
	}



	MakeMove();
	
	
	it++;
	while (it != snakeList.end())
	{
		temp2.X = it->X;
		temp2.Y = it->Y;
		it->X = temp.X;
		it->Y = temp.Y;
		temp = temp2;
		it++;
	}
	
	TailMove(temp2.X, temp2.Y);
}

void SnakeBoard::GameLogic()
{

	COORD tempCoord;
	MoveSnake();
	KKeyboard object;
	std::thread thread1(&KKeyboard::HandleKeys, &object,  this);
	thread1.detach();
	MakeBoard();

	while (mDirection != EXIT)
	{
		if (WallCheck() || HitCheck())
			break;
		MoveSnake();
	
		if ((300 - speedOffset) > 50)
			Sleep(300 - speedOffset);
		else
			Sleep(50);
	}

}

void SnakeBoard::SetDirection(int direction)
{
	mDirection = direction;
}

void SnakeBoard::NewMouse()
{
	mouse.X = (short)rand() % (xDim-1);
	mouse.Y = (short)rand() % (yDim-1);
}

bool SnakeBoard::MouseCheck()
{
	bool hit = false;
	if (snakeList.front().X == mouse.X && snakeList.front().Y == mouse.Y)
	{
		hit = true;
		speedOffset += 50;
		NewMouse();
	}
	return hit;
}

bool SnakeBoard::WallCheck()
{
	bool outOfBounds = false;
	if (snakeList.front().X == 0 || snakeList.front().X == xDim)
		outOfBounds = true;

	else if (snakeList.front().Y == 0 || snakeList.front().Y == yDim)
		outOfBounds = true;

	return outOfBounds;
}

bool SnakeBoard::HitCheck()
{
	list<COORD>::iterator it = snakeList.begin();
	bool hit = false;
	it++;
	while (it != snakeList.end() && !hit)
	{
		if (snakeList.front().X == it->X && snakeList.front().Y == it->Y)
		
			hit = true;
			
		
		else
			it++;

	}

	return hit;
}


