// Authored by Evgeny Buko

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <thread>
#include "GameSettings.h"
#include "Game.h"
#include "Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong!");
	sf::Event event;
	srand((int)time(nullptr));

	while (window.isOpen())
	{
		Menu menu;
		menu.initMenu();
		while (!menu.getIsStartGame() && window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					return 0;
				}
			}
			window.clear();
			menu.updateMenu(window);
			menu.drawMenu(window);
			window.display();
		}

		Game game;
		game.initGame();

		for (int i = 3; i >= 0; i--)
		{
			window.clear();
			game.drawGame(window);
			game.drawTimer(window, i);
			window.display();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		game.initLastTime();

		while (!game.getIsGameOger() && !game.getIsVictory() && window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			game.updateGame(menu.getGameDifficult());
			window.clear();
			game.drawGame(window);
			window.display();
		}

		if ((game.getIsGameOger() || game.getIsVictory()) && window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					return 0;
				}
			}
			window.clear();
			if (game.getIsGameOger())
			{
				game.drawGameOverText(window);
			}
			else if (game.getIsVictory()) 
			{
				game.drawVictoryText(window);
			}
			window.display();
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	}

	return 0;
}
