#include "Ball.h"

void Ball::initBallShape()
{
	isNeedCheck = true;
	halfHeigthScreen = (SCREEN_HEIGHT + UP_BOARD_POSITION) / 2.f;
	position.x = SCREEN_WIDTH / 2.f;
	position.y = halfHeigthScreen;
	initFirstBorderCollisionPosition();
	ballShape.setRadius(BALL_RADIUS);
	ballShape.setOrigin(BALL_RADIUS, BALL_RADIUS);
	ballShape.setPosition(position);
	initDirection();
	initAngle();
}

void Ball::updateBallShape(float deltaTime, Platform playerPlatform, Platform aiPlatform, int& scoreFirstPlayer, int& scoreSecondPlayer)
{
	float vectorLength = sqrtf(powf(position.x - nextBorderCollisionPosition.x, 2) + powf(position.y - nextBorderCollisionPosition.y, 2));
	float vextorX = (nextBorderCollisionPosition.x - position.x) / vectorLength * BALL_SPEED;
	float vextorY = (nextBorderCollisionPosition.y - position.y) / vectorLength * BALL_SPEED;
	sf::Vector2f currentPosition;
	currentPosition.x = position.x + vextorX * deltaTime;
	currentPosition.y = position.y + vextorY * deltaTime;

	if (isGoalCollision(currentPosition))
	{
		if (currentPosition.x - BALL_RADIUS <= 0)
		{
			scoreSecondPlayer += 1;
		}
		else if (currentPosition.x + BALL_RADIUS >= SCREEN_WIDTH)
		{
			scoreFirstPlayer += 1;
		}
		initBallShape();
	}
	else if (isBorderCollision(currentPosition))
	{
		changeDirectionWhenBorderCollision();
		initNextBorderCollisionPosition();
		initAngle();
	}
	else if ((isUpPlayerPlatformCollision(playerPlatform, currentPosition) || isDownPlayerPlatformCollision(playerPlatform, currentPosition)) && isNeedCheck)
	{
		changeDirectionWhenSidePlatformCollision(playerPlatform, currentPosition);
		initNextBorderCollisionPosition();
		initAngle();
		isNeedCheck = false;
	}
	else if ((isUpAiPlatformCollision(aiPlatform, currentPosition) || isDownAiPlatformCollision(aiPlatform, currentPosition)) && isNeedCheck)
	{
		changeDirectionWhenSidePlatformCollision(aiPlatform, currentPosition);
		initNextBorderCollisionPosition();
		initAngle();
		isNeedCheck = false;
	}
	else if (isFrontPlayerPlatformCollision(playerPlatform, currentPosition) && isNeedCheck)
	{
		changeDirectionWhenFrontPlatformCollision();
		increaseAngleWhenPlatformCollision(playerPlatform);
		initNextBorderCollisionPosition();
		initAngle();
		isNeedCheck = false;
	}
	else if (isFrontAiPlatformCollision(aiPlatform, currentPosition) && isNeedCheck)
	{
		changeDirectionWhenFrontPlatformCollision();
		increaseAngleWhenPlatformCollision(aiPlatform);
		initNextBorderCollisionPosition();
		initAngle();
		isNeedCheck = false;
	}
	else
	{
		position = currentPosition;
	}

	ballShape.setPosition(position);
	if (SCREEN_WIDTH / 2.f - SCREEN_WIDTH * 0.1f <= position.x && position.x <= SCREEN_WIDTH / 2.f + SCREEN_WIDTH * 0.1f)
	{
		isNeedCheck = true;
	}
}

void Ball::drawBallShape(sf::RenderWindow& window)
{
	window.draw(ballShape);
}

void Ball::initFirstBorderCollisionPosition()
{
	int direction = rand() % 2;
	switch (direction)
	{
	case 0:
		nextBorderCollisionPosition.x = 0;
		break;
	case 1:
		nextBorderCollisionPosition.x = SCREEN_WIDTH;
		break;
	default:
		nextBorderCollisionPosition.x = 0;
		break;
	}
	nextBorderCollisionPosition.y = UP_BOARD_POSITION + (float)rand() / RAND_MAX * (SCREEN_HEIGHT - UP_BOARD_POSITION);
}

void Ball::initNextBorderCollisionPosition()
{
	sf::Vector2f nextPosition;
	if (nextBorderCollisionPosition.x == 0 || nextBorderCollisionPosition.x == SCREEN_WIDTH)
	{
		float length1; 
		if (nextBorderCollisionPosition.x == 0)
		{
			length1 = SCREEN_WIDTH - position.x;
			nextPosition.x = SCREEN_WIDTH;
		}
		else
		{
			length1 = position.x;
			nextPosition.x = 0;
		}
		float length2 = length1 * angle;
		if (direction.y == 0)
		{
			nextPosition.y = position.y - length2;
		}
		else
		{
			nextPosition.y = position.y + length2;
		}
		if (nextPosition.y < UP_BOARD_POSITION || nextPosition.y > SCREEN_HEIGHT)
		{
			float k = (position.y - nextPosition.y) / (position.x - nextPosition.x);
			float b = position.y - k * position.x;
			if (nextPosition.y < UP_BOARD_POSITION)
			{
				nextPosition.y = UP_BOARD_POSITION;
			}
			else
			{
				nextPosition.y = SCREEN_HEIGHT;
			}
			nextPosition.x = (nextPosition.y - b) / k;

		}
	}
	else if (nextBorderCollisionPosition.y == UP_BOARD_POSITION || nextBorderCollisionPosition.y == SCREEN_HEIGHT)
	{
		float length1;
		if (nextBorderCollisionPosition.y == UP_BOARD_POSITION)
		{
			length1 = SCREEN_HEIGHT - position.y;
			nextPosition.y = SCREEN_HEIGHT;
		}
		else
		{
			length1 = position.y - UP_BOARD_POSITION;
			nextPosition.y = UP_BOARD_POSITION;
		}
		float length2 = length1 * angle;
		if (direction.x == 0)
		{
			nextPosition.x = position.x - length2;
		}
		else
		{
			nextPosition.x = position.x + length2;
		}
		if (nextPosition.x < 0 || nextPosition.x > SCREEN_WIDTH)
		{
			float k = (position.y - nextPosition.y) / (position.x - nextPosition.x);
			float b = position.y - k * position.x;
			if (nextPosition.x < 0)
			{
				nextPosition.x = 0;
			}
			else
			{
				nextPosition.x = SCREEN_WIDTH;
			}
			nextPosition.y = k * nextPosition.x + b;

		}
	}
	nextBorderCollisionPosition = nextPosition;
}

bool Ball::isFrontPlayerPlatformCollision(Platform playerPlatform, sf::Vector2f currentPosition)
{
	bool frontCollision = playerPlatform.getPosition().x + PLATFORM_WIDTH / 2.f >= currentPosition.x - BALL_RADIUS &&
		 playerPlatform.getPosition().y - PLATFORM_LENGTH / 2.f - BALL_RADIUS <= currentPosition.y + BALL_RADIUS && currentPosition.y - BALL_RADIUS <= playerPlatform.getPosition().y + PLATFORM_LENGTH / 2.f + BALL_RADIUS;
	return  frontCollision;
}

bool Ball::isUpPlayerPlatformCollision(Platform playerPlatform, sf::Vector2f currentPosition)
{
	bool upSidePlayerPlatformCollision = (playerPlatform.getPosition().x - PLATFORM_WIDTH / 2.f <= currentPosition.x) &&
		(currentPosition.x < playerPlatform.getPosition().x + PLATFORM_WIDTH / 2.f) &&
		(playerPlatform.getPosition().y - PLATFORM_LENGTH / 2.f <= currentPosition.y + BALL_RADIUS) &&
		(currentPosition.y + BALL_RADIUS <= playerPlatform.getPosition().y);
	return upSidePlayerPlatformCollision;
}

bool Ball::isDownPlayerPlatformCollision(Platform playerPlatform, sf::Vector2f currentPosition)
{
	bool downSidePlayerPlatformCollision = (playerPlatform.getPosition().x - PLATFORM_WIDTH / 2.f <= currentPosition.x) &&
		(currentPosition.x < playerPlatform.getPosition().x + PLATFORM_WIDTH / 2.f) &&
		(playerPlatform.getPosition().y <= currentPosition.y - BALL_RADIUS) &&
		(currentPosition.y - BALL_RADIUS <= playerPlatform.getPosition().y + PLATFORM_LENGTH / 2.f);
	return downSidePlayerPlatformCollision;
}

bool Ball::isFrontAiPlatformCollision(Platform aiPlatform, sf::Vector2f currentPosition)
{
	bool frontCollision = aiPlatform.getPosition().x - PLATFORM_WIDTH / 2.f <= currentPosition.x + BALL_RADIUS &&
		 aiPlatform.getPosition().y - PLATFORM_LENGTH / 2.f - BALL_RADIUS <= currentPosition.y + BALL_RADIUS && currentPosition.y - BALL_RADIUS <= aiPlatform.getPosition().y + PLATFORM_LENGTH / 2.f + BALL_RADIUS;
	return frontCollision;
}

bool Ball::isUpAiPlatformCollision(Platform aiPlatform, sf::Vector2f currentPosition)
{
	bool upSideAiPlatformCollision = (aiPlatform.getPosition().x - PLATFORM_WIDTH / 2.f < currentPosition.x) &&
		(currentPosition.x <= aiPlatform.getPosition().x + PLATFORM_WIDTH / 2.f) &&
		(aiPlatform.getPosition().y - PLATFORM_LENGTH / 2.f <= currentPosition.y + BALL_RADIUS) &&
		(currentPosition.y + BALL_RADIUS <= aiPlatform.getPosition().y);
	return upSideAiPlatformCollision;
}

bool Ball::isDownAiPlatformCollision(Platform aiPlatform, sf::Vector2f currentPosition)
{	
	bool downSideAiplatformCollision = (aiPlatform.getPosition().x - PLATFORM_WIDTH / 2.f < currentPosition.x) &&
		(currentPosition.x <= aiPlatform.getPosition().x + PLATFORM_WIDTH / 2.f) &&
		(aiPlatform.getPosition().y <= currentPosition.y - BALL_RADIUS) &&
		(currentPosition.y - BALL_RADIUS <= aiPlatform.getPosition().y + PLATFORM_LENGTH / 2.f);
	return downSideAiplatformCollision;
}

bool Ball::isBorderCollision(sf::Vector2f currentPosition)
{
	return currentPosition.y - BALL_RADIUS <= UP_BOARD_POSITION || currentPosition.y + BALL_RADIUS >= SCREEN_HEIGHT;
}

bool Ball::isGoalCollision(sf::Vector2f currentPosition)
{
	return currentPosition.x - BALL_RADIUS <= 0 || currentPosition.x + BALL_RADIUS >= SCREEN_WIDTH;
}

void Ball::initAngle()
{
	if (nextBorderCollisionPosition.x == 0 || nextBorderCollisionPosition.x == SCREEN_WIDTH)
	{
		angle = abs(nextBorderCollisionPosition.y - position.y) / abs(nextBorderCollisionPosition.x - position.x);
	}
	else if (nextBorderCollisionPosition.y == UP_BOARD_POSITION || nextBorderCollisionPosition.y == SCREEN_HEIGHT)
	{
		angle = abs(nextBorderCollisionPosition.x - position.x) / abs(nextBorderCollisionPosition.y - position.y);
	}
}

void Ball::initDirection()
{
	if (nextBorderCollisionPosition.x < position.x)
	{
		direction.x = 0;
	}
	else
	{
		direction.x = 1;
	}

	if (nextBorderCollisionPosition.y < position.y)
	{
		direction.y = 0;
	}
	else 
	{
		direction.y = 1;
	}
}

void Ball::changeDirectionWhenBorderCollision()
{
	direction.y = direction.y == 0 ? 1 : 0;
}

void Ball::changeDirectionWhenFrontPlatformCollision()
{
	direction.x = direction.x == 0 ? 1 : 0;
}

void Ball::changeDirectionWhenSidePlatformCollision(Platform platform, sf::Vector2f currentPosition)
{
	bool changeDirectionUp = currentPosition.y < platform.getPosition().y;
	bool changeDirectionDown = currentPosition.y > platform.getPosition().y;
	if (changeDirectionUp)
	{
		direction.y = 0;
	}
	else if (changeDirectionDown) {
		direction.y = 1;
	}
}

void Ball::increaseAngleWhenPlatformCollision(Platform platform)
{
	float part = PLATFORM_LENGTH / 6.f;
	float platformPositionY = platform.getPosition().y;
	if (platformPositionY - part <= position.y && position.y <= platformPositionY + part)
	{
		angle = 0.25f;
	}
	else if (( platformPositionY - 2 * part <= position.y && position.y < platformPositionY - part) 
		|| (platformPositionY + part < position.y && position.y <= platformPositionY + 2 * part))
	{
		angle = 0.55f;
	}
	else
	{
		angle = 0.95f;
	}
}

sf::Vector2f Ball::getPosition()
{
	return position;
}

sf::Vector2i Ball::getDirection()
{
	return direction;
}
