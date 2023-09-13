#include "Platform.h"

void Platform::initPlatformShape( bool _isAiPlatform)
{
	position.y = (SCREEN_HEIGHT + UP_BOARD_POSITION) / 2.f;
	halfLengthPlatform = PLATFORM_LENGTH / 2.f;
	halfWidthPlathorm = PLATFORM_WIDTH / 2.f;
	platformShape.setSize(sf::Vector2f(PLATFORM_WIDTH, PLATFORM_LENGTH));
	platformShape.setOrigin(sf::Vector2f(halfWidthPlathorm, halfLengthPlatform));
	isAiPlatform = _isAiPlatform;
	if (isAiPlatform) 
	{	
		position.x = SCREEN_WIDTH - (PLATFORM_SHIFT + halfWidthPlathorm);
		platformShape.setPosition(position);
	}
	else
	{
		position.x = PLATFORM_SHIFT + halfWidthPlathorm;
		platformShape.setPosition(position);
	}
	
}

void Platform::updatePlatformShape(float deltaTime, float ballPositionY)
{
	if (isAiPlatform)
	{
		updatePlatformShapeForAi(deltaTime, ballPositionY);
	}
	else
	{
		updatePlatformShapeForPlayer(deltaTime);
	}
}

void Platform::drawPlatformShape(sf::RenderWindow& window)
{
	window.draw(platformShape);
}

sf::Vector2f Platform::getPosition()
{
	return position;
}

int Platform::getDirection()
{
	return direction;
}

void Platform::updatePlatformShapeForPlayer(float deltaTime)
{
	float nextPlatformPosition = position.y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		nextPlatformPosition -= PLATFORM_SPEED * deltaTime;
		direction = 0;
		if (!isCollisionWithBoard(nextPlatformPosition))
		{
			position.y = nextPlatformPosition;
			platformShape.setPosition(position);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		nextPlatformPosition += PLATFORM_SPEED * deltaTime;
		direction = 1;
		if (!isCollisionWithBoard(nextPlatformPosition))
		{
			position.y = nextPlatformPosition;
			platformShape.setPosition(position);
		}
	}
}

void Platform::updatePlatformShapeForAi(float deltaTime, float ballPositionY)
{
	float nextPlatformPosition = position.y;
	if (ballPositionY < position.y)
	{
		nextPlatformPosition -= PLATFORM_AI_SPEED * deltaTime;
		direction = 0;
		if (!isCollisionWithBoard(nextPlatformPosition))
		{
			position.y = nextPlatformPosition;
			platformShape.setPosition(position);
		}
	}
	else if (ballPositionY > position.y)
	{
		nextPlatformPosition += PLATFORM_AI_SPEED * deltaTime;
		direction = 1;
		if (!isCollisionWithBoard(nextPlatformPosition))
		{
			position.y = nextPlatformPosition;
			platformShape.setPosition(position);
		}
	}
}

bool Platform::isCollisionWithBoard(float nextPlatformPosition)
{
	return nextPlatformPosition + halfLengthPlatform >= SCREEN_HEIGHT || nextPlatformPosition - halfLengthPlatform <= UP_BOARD_POSITION;
}
