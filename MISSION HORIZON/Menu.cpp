#include "Menu.h"
#pragma warning(disable : 4996)


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("space.otf"))
	{
		// handle error
	}

	name.setString("Mission Horizon");
	name.setFont(font);
	name.setPosition(30, 10);
	name.setCharacterSize(60);

	selects.loadFromFile("button pressed.wav");
	changes.loadFromFile("selection change.wav");
	select.setBuffer(selects);
	change.setBuffer(changes);
	
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setScale(2.f, 2.f);
	menu[0].setPosition(sf::Vector2f(width / 2-100, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color(76, 215, 95));
	menu[1].setString("Instruction");
	menu[1].setScale(2.f, 2.f);
	menu[1].setPosition(sf::Vector2f(width / 2-100, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color(76, 215, 95));
	menu[2].setString("Exit");
	menu[2].setScale(2.f, 2.f);
	menu[2].setPosition(sf::Vector2f(width / 2-100, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(name);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	change.play();
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color(76, 215, 95));
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	change.play();
	if (selectedIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedIndex].setColor(sf::Color(76, 215, 95));
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}
