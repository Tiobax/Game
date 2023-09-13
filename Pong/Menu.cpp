#include "Menu.h"

void Menu::initMenu()
{
	GameDifficult = 0;
	assert(logo.loadFromFile(RESOURCES_PATH + "PONG logo.png"));
	assert(font.loadFromFile(RESOURCES_PATH + "Fonts/better-vcr_0.ttf"));
	isStartGame = false;
	float textSize = SCREEN_HEIGHT * TEXT_SIZE_PERCENT;

	logo_sprite.setTexture(logo);
	logo_sprite.setOrigin(sf::Vector2f(450.f, 250.f));
	logo_sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, 300.f));

	easyButtonPosition.x = SCREEN_WIDTH / 2.f - BUTTON_WIDTH * 0.7f - 2;
	easyButtonPosition.y = (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f + (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f * 0.5f;

	easyButtonText.setFont(font);
	easyButtonText.setString("Easy");
	easyButtonText.setFillColor(sf::Color::Black);
	easyButtonText.setCharacterSize((int)(textSize * 0.7f));
	easyButtonText.setOrigin(sf::Vector2f(45.f, (textSize * 0.7f) / 2.f));
	easyButtonText.setPosition(easyButtonPosition);

	easyButton.setSize(sf::Vector2f(BUTTON_WIDTH * 0.7f, BUTTON_HEIGHT * 0.7f));
	easyButton.setFillColor(sf::Color::Yellow);
	easyButton.setOrigin(sf::Vector2f(BUTTON_WIDTH * 0.7f / 2.f, BUTTON_HEIGHT * 0.7f / 2.f));
	easyButton.setPosition(easyButtonPosition);

	mediumButtonPosition.x = SCREEN_WIDTH / 2.f;
	mediumButtonPosition.y = (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f + (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f * 0.5f;

	mediumButtonText.setFont(font);
	mediumButtonText.setString("Medium");
	mediumButtonText.setFillColor(sf::Color::Black);
	mediumButtonText.setCharacterSize((int)(textSize * 0.7f));
	mediumButtonText.setOrigin(sf::Vector2f(70.f, (textSize * 0.7f) / 2.f));
	mediumButtonText.setPosition(mediumButtonPosition);

	mediumButton.setSize(sf::Vector2f(BUTTON_WIDTH * 0.7f, BUTTON_HEIGHT * 0.7f));
	mediumButton.setFillColor(sf::Color::White);
	mediumButton.setOrigin(sf::Vector2f(BUTTON_WIDTH * 0.7f / 2.f, BUTTON_HEIGHT * 0.7f / 2.f));
	mediumButton.setPosition(mediumButtonPosition);

	highButtonPosition.x = SCREEN_WIDTH / 2.f + BUTTON_WIDTH * 0.7f + 2;
	highButtonPosition.y = (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f + (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f * 0.5f;

	highButtonText.setFont(font);
	highButtonText.setString("High");
	highButtonText.setFillColor(sf::Color::Black);
	highButtonText.setCharacterSize((int)(textSize * 0.7f));
	highButtonText.setOrigin(sf::Vector2f(45.f, (textSize * 0.7f) / 2.f));
	highButtonText.setPosition(highButtonPosition);

	highButton.setSize(sf::Vector2f(BUTTON_WIDTH * 0.7f, BUTTON_HEIGHT * 0.7f));
	highButton.setFillColor(sf::Color::White);
	highButton.setOrigin(sf::Vector2f(BUTTON_WIDTH * 0.7f / 2.f, BUTTON_HEIGHT * 0.7f / 2.f));
	highButton.setPosition(highButtonPosition);

	newGameButtonPosition.x = SCREEN_WIDTH / 2.f;
	newGameButtonPosition.y = (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f + (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f * 0.7f;

	newGameButtonText.setFont(font);
	newGameButtonText.setString("New Game");
	newGameButtonText.setFillColor(sf::Color::Black);
	newGameButtonText.setCharacterSize((int)textSize);
	newGameButtonText.setOrigin(sf::Vector2f(135.f, textSize / 2.f));
	newGameButtonText.setPosition(newGameButtonPosition);

	newGameButton.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
	newGameButton.setFillColor(sf::Color::White);
	newGameButton.setOrigin(sf::Vector2f(BUTTON_WIDTH / 2.f, BUTTON_HEIGHT / 2.f));
	newGameButton.setPosition(newGameButtonPosition);

	exitButtonPosition.x = SCREEN_WIDTH / 2.f;
	exitButtonPosition.y = (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f + (SCREEN_HEIGHT - UP_BOARD_POSITION) / 2.f * 0.9f;

	exitButtonText.setFont(font);
	exitButtonText.setString("Exit");
	exitButtonText.setFillColor(sf::Color::Black);
	exitButtonText.setCharacterSize((int)textSize);
	exitButtonText.setOrigin(sf::Vector2f(65.f, textSize / 2.f));
	exitButtonText.setPosition(exitButtonPosition);

	exitButton.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
	exitButton.setFillColor(sf::Color::White);
	exitButton.setOrigin(sf::Vector2f(BUTTON_WIDTH / 2.f, BUTTON_HEIGHT / 2.f));
	exitButton.setPosition(exitButtonPosition);
}

void Menu::updateMenu(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		if ((mousePosition.x >= exitButtonPosition.x - BUTTON_WIDTH / 2.f && mousePosition.x <= exitButtonPosition.x + BUTTON_WIDTH / 2.f)
			&& (mousePosition.y >= exitButtonPosition.y - BUTTON_HEIGHT / 2.f && mousePosition.y <= exitButtonPosition.y + BUTTON_HEIGHT / 2.f))
		{
			window.close();
		}
		else if ((mousePosition.x >= newGameButtonPosition.x - BUTTON_WIDTH / 2.f && mousePosition.x <= newGameButtonPosition.x + BUTTON_WIDTH / 2.f)
			&& (mousePosition.y >= newGameButtonPosition.y - BUTTON_HEIGHT / 2.f && mousePosition.y <= newGameButtonPosition.y + BUTTON_HEIGHT / 2.f))
		{
			isStartGame = true;
		}
		else if ((mousePosition.x >= easyButtonPosition.x - BUTTON_WIDTH * 0.7f / 2.f && mousePosition.x <= easyButtonPosition.x + BUTTON_WIDTH * 0.7f / 2.f)
			&& (mousePosition.y >= easyButtonPosition.y - BUTTON_HEIGHT * 0.7f / 2.f && mousePosition.y <= easyButtonPosition.y + BUTTON_HEIGHT * 0.7f / 2.f))
		{
			if (GameDifficult != 0)
			{
				GameDifficult = 0;
				easyButton.setFillColor(sf::Color::Yellow);
				mediumButton.setFillColor(sf::Color::White);
				highButton.setFillColor(sf::Color::White);
			}
		}
		else if ((mousePosition.x >= mediumButtonPosition.x - BUTTON_WIDTH * 0.7f / 2.f && mousePosition.x <= mediumButtonPosition.x + BUTTON_WIDTH * 0.7f / 2.f)
			&& (mousePosition.y >= mediumButtonPosition.y - BUTTON_HEIGHT * 0.7f / 2.f && mousePosition.y <= mediumButtonPosition.y + BUTTON_HEIGHT * 0.7f / 2.f))
		{
			if (GameDifficult != 1)
			{
				GameDifficult = 1;
				easyButton.setFillColor(sf::Color::White);
				mediumButton.setFillColor(sf::Color::Yellow);
				highButton.setFillColor(sf::Color::White);
			}
		}
		else if ((mousePosition.x >= highButtonPosition.x - BUTTON_WIDTH * 0.7f / 2.f && mousePosition.x <= highButtonPosition.x + BUTTON_WIDTH * 0.7f / 2.f)
			&& (mousePosition.y >= highButtonPosition.y - BUTTON_HEIGHT * 0.7f / 2.f && mousePosition.y <= highButtonPosition.y + BUTTON_HEIGHT * 0.7f / 2.f))
		{
			if (GameDifficult != 2)
			{
				GameDifficult = 2;
				easyButton.setFillColor(sf::Color::White);
				mediumButton.setFillColor(sf::Color::White);
				highButton.setFillColor(sf::Color::Yellow);
			}
		}
	}
}

void Menu::drawMenu(sf::RenderWindow& window)
{
	//sf::Sprite logo_sprite(logo);
	window.draw(logo_sprite);
	window.draw(easyButton);
	window.draw(easyButtonText);
	window.draw(mediumButton);
	window.draw(mediumButtonText);
	window.draw(highButton);
	window.draw(highButtonText);
	window.draw(newGameButton);
	window.draw(newGameButtonText);
	window.draw(exitButton);
	window.draw(exitButtonText);
}

bool Menu::getIsStartGame()
{
	return isStartGame;
}

int Menu::getGameDifficult()
{
	return GameDifficult;
}
