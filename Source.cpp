//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <iostream>
//#include <vector>
//#include <sstream>
//#include "Window.h"
#include "Game.h"



int main()
{
	Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Render();
	}
}