#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Platform.h"

class Ball
{
private:
	sf::CircleShape ballShape;
	sf::Vector2f position;
	sf::Vector2f nextBorderCollisionPosition;
	//����������� �� ��� x (0 - �����, 1 - ������) � �� ��� y (0 - �����, 1 - ����)
	sf::Vector2i direction;
	float halfHeigthScreen;
	float angle;
	bool isNeedCheck;

public:
	void initBallShape();
	void updateBallShape(float deltaTime, Platform playerPlatform, Platform aiPlatform, int& scoreFirstPlayer, int& scoreSecondPlayer);
	void drawBallShape(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::Vector2i getDirection();

private:
	void initFirstBorderCollisionPosition();
	void initNextBorderCollisionPosition();
	void initDirection();
	void changeDirectionWhenBorderCollision(); 
	void changeDirectionWhenFrontPlatformCollision();
	void changeDirectionWhenSidePlatformCollision(Platform platform, sf::Vector2f currentPosition);
	void initAngle();
	bool isFrontPlayerPlatformCollision(Platform playerPlatform, sf::Vector2f currentPosition);
	bool isUpPlayerPlatformCollision(Platform playerPlatform, sf::Vector2f currentPosition);
	bool isDownPlayerPlatformCollision(Platform playerPlatform, sf::Vector2f currentPosition);
	bool isFrontAiPlatformCollision(Platform aiPlatform, sf::Vector2f currentPosition);
	bool isUpAiPlatformCollision(Platform aiPlatform, sf::Vector2f currentPosition);
	bool isDownAiPlatformCollision(Platform aiPlatform, sf::Vector2f currentPosition);
	bool isGoalCollision(sf::Vector2f currentPosition);
	bool isBorderCollision(sf::Vector2f currentPosition);
	void increaseAngleWhenPlatformCollision(Platform platform);
};

