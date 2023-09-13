#include "Game.h"

void Game::initGame()
{
	isVictory = false;
	isGameOver = false;
	float textSize = SCREEN_HEIGHT * TEXT_SIZE_PERCENT;
	float centerScreen = SCREEN_WIDTH / 2.f;
	float shiftTextForX = SCREEN_WIDTH * TEXT_SIZE_PERCENT;
	float shiftTextForY = textSize * TEXT_SIZE_PERCENT * 2;

	assert(font.loadFromFile(RESOURCES_PATH + "Fonts/better-vcr_0.ttf"));

	scoreFirstPlayerText.setFont(font);
	scoreFirstPlayerText.setString(std::to_string(scoreFirstPlayer));
	scoreFirstPlayerText.setCharacterSize((int)textSize);
	scoreFirstPlayerText.setPosition(centerScreen - shiftTextForX, shiftTextForY);

	scoreSecondPlayerText.setFont(font);
	scoreSecondPlayerText.setString(std::to_string(scoreSecondPlayer));
	scoreSecondPlayerText.setCharacterSize((int)textSize);
	scoreSecondPlayerText.setPosition(centerScreen + shiftTextForX, shiftTextForY);

	colonText.setFont(font);
	colonText.setString(":");
	colonText.setCharacterSize((int)textSize);
	colonText.setPosition(centerScreen, shiftTextForY);

	gameOverText.setFont(font);
	gameOverText.setString("GAME OVER!");
	gameOverText.setOrigin(180.f, 25.f);
	gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
	gameOverText.setCharacterSize(50);

	victoryText.setFont(font);
	victoryText.setString("YOU ARE VICTORY!");
	victoryText.setOrigin(280.f, 25.f);
	victoryText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
	victoryText.setCharacterSize(50);

	timerText.setFont(font);
	timerText.setString("3");
	timerText.setOrigin(10.f, 25.f);
	timerText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT * 0.3f);
	timerText.setCharacterSize(50);

	dividingLine.setSize(sf::Vector2f(SCREEN_WIDTH, 2));
	dividingLine.setOrigin(centerScreen, 2);
	dividingLine.setPosition(centerScreen, textSize + shiftTextForY * 2);

	playerPlatform.initPlatformShape(false);
	aiPlatform.initPlatformShape(true);
	ball.initBallShape();
}

void Game::initLastTime()
{
	lastTime = gameClock.getElapsedTime().asSeconds();
}

void Game::updateGame(int GameDifficult)
{
	float currentTime = gameClock.getElapsedTime().asSeconds();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	playerPlatform.updatePlatformShape(deltaTime, ball.getPosition().y);
	switch (GameDifficult)
	{
	case 0:
		if (SCREEN_WIDTH - SCREEN_WIDTH * 0.2f <= ball.getPosition().x)
		{
			aiPlatform.updatePlatformShape(deltaTime, ball.getPosition().y);
		}
		else 
		{
			aiPlatform.updatePlatformShape(deltaTime, (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f);
		}
		break;
	case 1:
		if (SCREEN_WIDTH - SCREEN_WIDTH * 0.3f <= ball.getPosition().x)
		{
			aiPlatform.updatePlatformShape(deltaTime, ball.getPosition().y);
		}
		else
		{
			aiPlatform.updatePlatformShape(deltaTime, (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f);
		}
		break;
	case 2:
		if (SCREEN_WIDTH - SCREEN_WIDTH * 0.4f <= ball.getPosition().x)
		{
			aiPlatform.updatePlatformShape(deltaTime, ball.getPosition().y);
		}
		else
		{
			aiPlatform.updatePlatformShape(deltaTime, (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f);
		}
		break;
	}
	
	ball.updateBallShape(deltaTime, playerPlatform, aiPlatform, scoreFirstPlayer, scoreSecondPlayer);
	scoreFirstPlayerText.setString(std::to_string(scoreFirstPlayer));
	scoreSecondPlayerText.setString(std::to_string(scoreSecondPlayer));
	if (scoreFirstPlayer == VICTORY_SCORE) 
	{
		isVictory = true;
	}
	else if (scoreSecondPlayer == VICTORY_SCORE)
	{
		isGameOver = true;
	}
}

void Game::drawGame(sf::RenderWindow& window)
{
	window.draw(scoreFirstPlayerText);
	window.draw(scoreSecondPlayerText);
	window.draw(colonText);
	window.draw(dividingLine);
	playerPlatform.drawPlatformShape(window);
	aiPlatform.drawPlatformShape(window);
	ball.drawBallShape(window);
}

void Game::drawTimer(sf::RenderWindow& window, int timer)
{
	if (timer == 0)
	{
		timerText.setString("GO!");
		timerText.setOrigin(20.f, 25.f);
	}
	else
	{
		timerText.setString(std::to_string(timer));
	}
	window.draw(timerText);
}

void Game::drawVictoryText(sf::RenderWindow& window)
{
	window.draw(victoryText);
}

void Game::drawGameOverText(sf::RenderWindow& window)
{
	window.draw(gameOverText);
}

bool Game::getIsVictory()
{
	return isVictory;
}

bool Game::getIsGameOger()
{
	return isGameOver;
}
