#pragma once

#pragma once
#ifndef GAME_H
#define GAME_H

#include "libraries.h"

#include "InputField.h"

class Game
{
	//the game window
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;
	
	sf::Texture logo_texture;
	sf::Sprite logo_sprite;
	sf::Font font;

	//pair(vertical, horizontal)
	std::pair<int, int> active_box;

	void initVar();
	void initWindow();

	//map(which word, pair(which symbol is active, vector of chars))
	std::map<int, std::vector<InputField>> inputmap;

	std::vector<std::string> definitions;
	std::vector<sf::Text> def_texts;
public:
	Game();
	~Game();

	const bool getWindow();

	void update();
	void render();
	void pollEvents();
};


#endif // !GAME_H

