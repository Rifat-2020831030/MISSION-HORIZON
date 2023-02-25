#include "Menu.h"
//#include "SFML/Audio.hpp"
#pragma warning(disable : 4996)


Menu::Menu(float width, float height)
{

	if (!font.loadFromFile("fonts/ModernWarfare.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setScale(2.f, 2.f);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::Blue);
	menu[1].setString("Options");
	menu[1].setScale(2.f, 2.f);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::Blue);
	menu[2].setString("Exit");
	menu[2].setScale(2.f, 2.f);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::Blue);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedIndex].setColor(sf::Color::Blue);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}