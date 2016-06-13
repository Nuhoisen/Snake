#ifndef KKeyboard_H
#define	KKeyboard_H

#include "SnakeBoard.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class KKeyboard
{
public:
	KKeyboard();
	void HandleKeys(SnakeBoard * game);
	void ThrowThread();
private:
	
};


#endif // !KKeyboard_H
