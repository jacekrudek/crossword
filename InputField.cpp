#pragma once

#include "InputField.h"


InputField::InputField(std::pair<int, int> idd, char letterr)
	:id(idd), letter(letterr), input_initialized(false), position(0,0)
{
	field.setFillColor(sf::Color::Blue);
	field.setSize({ 40.f,40.f });
	field.setOutlineThickness(2.f);
	field.setOutlineColor(sf::Color::White);

	/*if (!font.loadFromFile("lucon.ttf")) {
		std::cout << "drfytugscaigubascibiujsacbiojosbiacjbscja";
	} 
	letter_displayable.setFont(font);
	letter_displayable.setFillColor(sf::Color::White);
	letter_displayable.setCharacterSize(30);*/

	/*sf::FloatRect textbounds = letter_displayable.getLocalBounds();
	letter_displayable.setOrigin(textbounds.width / 2.0f, textbounds.height / 2.0f);*/
};


void InputField::draw(sf::RenderWindow* window)
{
	sf::FloatRect fieldbounds = field.getLocalBounds();
	field.setOrigin(fieldbounds.width / 2.0f, fieldbounds.height / 2.0f);

	field.setPosition(position);

	window->draw(field);
	if (input_initialized)
	{
		sf::Font font;
		sf::Text letter_displayable;
		sf::Text letter_displayable_shadow;
		std::string inputstring{ inputletter };
		if (!font.loadFromFile("lucon.ttf")) {
			std::cout << "font error";
		}
		letter_displayable.setFont(font);
		letter_displayable_shadow.setFont(font);
		letter_displayable.setFillColor(sf::Color::White);
		letter_displayable_shadow.setFillColor(sf::Color(0, 0, 0, 150));
		letter_displayable.setCharacterSize(30);
		letter_displayable_shadow.setCharacterSize(30);
		letter_displayable.setString(inputstring);
		letter_displayable_shadow.setString(inputstring);
		/*sf::FloatRect textbounds = letter_displayable.getLocalBounds();
		letter_displayable.setOrigin(textbounds.width / 2.0f, textbounds.height / 2.0f);*/
		letter_displayable.setPosition(position.x-13, position.y-22);
		letter_displayable_shadow.setPosition(letter_displayable.getPosition().x + 2, letter_displayable.getPosition().y + 2);
		window->draw(letter_displayable_shadow);
		window->draw(letter_displayable);
	}
	return;
}

void InputField::setpos(const sf::Vector2f& posvec)
{
	position = posvec;
}

void InputField::setactivecolor()
{
	sf::Color activecolor(239, 251, 81, 120);

	this->field.setFillColor(activecolor);

	return;
}

void InputField::setinactivecolor()
{
	sf::Color inactivecolor(99, 99, 99, 120);

	this->field.setFillColor(inactivecolor);

	return;
}

void InputField::setinputletter(const char& lett)
{
	this->input_initialized = true;
	this->inputletter = lett;
}

void InputField::setcorrectcolor()
{
	sf::Color correctcolor(67, 255, 43, 120);

	this->field.setFillColor(correctcolor);

	return;
}

void InputField::setincorrectcolor()
{
	sf::Color incorrectcolor(255, 34, 34, 120);

	this->field.setFillColor(incorrectcolor);

	return;
}

bool InputField::isinputcorrect()
{
	if (this->inputletter == this->letter)
	{
		return true;
	}
	return false;
}

bool InputField::isinput()
{
	return input_initialized;
}
