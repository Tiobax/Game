#pragma once
#include "GameSettings.h"
#include "SFML/Graphics.hpp"

class Platform
{
private:
	sf::RectangleShape platformShape;
	sf::Vector2f position;
	float halfLengthPlatform;
	float halfWidthPlathorm;
	bool isAiPlatform;
	//направление платформы: 0 - вверх, 1 - вниз
	int direction;

public:
	void initPlatformShape(bool _isAiPlatform);
	void updatePlatformShape(float deltaTime, float ballPositionY);
	void drawPlatformShape(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	int getDirection();

private:
	void updatePlatformShapeForPlayer(float deltaTime);
	void updatePlatformShapeForAi(float deltaTime, float ballPositionY);
	bool isCollisionWithBoard(float nextPlatformPosition);
};

