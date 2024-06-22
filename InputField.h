#pragma once

#include "libraries.h"

class InputField 
{
	sf::RectangleShape field;

	//pair(which word, which letter)
	std::pair<int, int> id;
	char letter;
	char inputletter;

	bool input_initialized;

	sf::Vector2f position;
public:
	InputField(std::pair<int, int> idd, char letterr);

	void draw(sf::RenderWindow* window);

	void setpos(const sf::Vector2f& posvec);

	void setactivecolor();

	void setinactivecolor();

	void setinputletter(const char& lett);

	void setcorrectcolor();

	void setincorrectcolor();

	bool isinputcorrect();

	bool isinput();
};