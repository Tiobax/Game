#pragma once
#include "SFML/Graphics.hpp"
#include "GameSettings.h"
#include <assert.h>
#include "Game.h"

class Menu
{
private:
	// 0 - easy, 1 - medium, 2 - hard
	int GameDifficult;
	bool isStartGame;
	sf::Texture logo;
	sf::Sprite logo_sprite;
	sf::Text newGameButtonText;
	sf::RectangleShape newGameButton;
	sf::Vector2f newGameButtonPosition;
	sf::Text exitButtonText;
	sf::RectangleShape exitButton;
	sf::Vector2f exitButtonPosition;
	sf::Text easyButtonText;
	sf::RectangleShape easyButton;
	sf::Vector2f easyButtonPosition;
	sf::Text mediumButtonText;
	sf::RectangleShape mediumButton;
	sf::Vector2f mediumButtonPosition;
	sf::Text highButtonText;
	sf::RectangleShape highButton;
	sf::Vector2f highButtonPosition;
	sf::Font font;

public:
	void initMenu();
	void updateMenu(sf::RenderWindow& window);
	void drawMenu(sf::RenderWindow& window);
	bool getIsStartGame();
	int getGameDifficult();
};

