#include "Keyboard.h"

KKeyboard::KKeyboard()
{
}

void KKeyboard::HandleKeys(SnakeBoard * game)
{
	/*sf::RenderWindow window(sf::VideoMode(800, 600), "Snake", sf::Style::Resize);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				game->SetDirection(LEFT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				game->SetDirection(RIGHT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				game->SetDirection(DOWN);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				game->SetDirection(UP);
			if (event.type == sf::Event::Closed)
				window.close();
		}

	}*/





	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

	DWORD InputsNum = 0; 
	DWORD InputsRead = 0;
	INPUT_RECORD irInput;
	GetNumberOfConsoleInputEvents(hInput, &InputsNum);
	while(ReadConsoleInput(hInput, &irInput, 1, &InputsRead))
	{	
		switch (irInput.Event.KeyEvent.wVirtualKeyCode)
		{
		case VK_LEFT:
			game->SetDirection(LEFT);break;

		case VK_RIGHT:
			game->SetDirection(RIGHT);break;


		case VK_DOWN:
			game->SetDirection(DOWN); break;

		case VK_UP:
			game->SetDirection(UP); break;
		case VK_ESCAPE:
			game->SetDirection(EXIT); break;
		default:
			break;
		}
	}

}

void KKeyboard::ThrowThread()
{

}



