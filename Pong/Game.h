#pragma once
#include "GameSettings.h"
#include "Platform.h"
#include "Ball.h"
#include "SFML/Graphics.hpp"
#include <time.h>
#include <assert.h>

class Game
{
private:
	int scoreFirstPlayer = 0;
	int scoreSecondPlayer = 0;
	float lastTime;
	bool isVictory;
	bool isGameOver;

	Platform playerPlatform;
	Platform aiPlatform;
	Ball ball;

	sf::Clock gameClock;
	sf::Font font;
	sf::Text scoreFirstPlayerText;
	sf::Text scoreSecondPlayerText;
	sf::Text colonText;
	sf::Text gameOverText;
	sf::Text victoryText;
	sf::Text timerText;
	sf::RectangleShape dividingLine;

public:
	void initGame();
	void initLastTime();
	void updateGame(int GameDifficult);
	void drawGame(sf::RenderWindow& window);
	void drawTimer(sf::RenderWindow& window, int timer);
	void drawVictoryText(sf::RenderWindow& window);
	void drawGameOverText(sf::RenderWindow& window);
	bool getIsVictory();
	bool getIsGameOger();
};

