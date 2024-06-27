#include "Game.h"


void Game::initVar()
{
	std::ifstream inputFile("words.txt");
	std::string word;
	while (std::getline(inputFile, word))
	{
		words.push_back(word);
	}

	std::ifstream inputFile2("definitions.txt");
	std::string definition;
	while (std::getline(inputFile2, definition))
	{
		definitions.push_back(definition);
	}
	
	if (!font.loadFromFile("lucon.ttf")) {
		std::cout << "font error";
	}

	for (int i=0; i < definitions.size(); i++)
	{
		sf::Text text;
		sf::Text shadow;
		std::string string;
		string.append(std::to_string(i));
		string.append(". ");
		string.append(definitions[i]);
		text.setString(string);
		shadow.setString(string);
		text.setCharacterSize(20);
		shadow.setCharacterSize(20);
		text.setFont(font);
		shadow.setFont(font);
		def_texts.push_back(text);
		shadow.setFillColor(sf::Color(0, 0, 0, 200));
		def_texts_shadow.push_back(shadow);
	}

	active_box = { 0,1 };

	logo_texture.loadFromFile("straightword.png");
	logo_sprite.setTexture(logo_texture);
	logo_sprite.setOrigin(logo_texture.getSize().x / 2.0f, logo_texture.getSize().y / 2.0f);
	logo_sprite.setPosition(800, 50);

	bg_texture.loadFromFile("galaxy.jpg");
	bg_sprite.setTexture(bg_texture);

	for (int j = 0; j < words.size(); j++)
	{
		std::vector<InputField> fieldvec;
		bool firstiter = true;
		for (int i = 0; i < words[j].size()+1; i++)
		{	
			if (firstiter == true)
			{
				InputField infield = InputField({ j,i }, words[j][i]);
				float ypos = j * 50 + 150;
				float xpos = i * 40 + 250;
				sf::Vector2f infpos = { xpos, ypos };
				infield.setpos(infpos);

				char number = static_cast<char>(j + '0');
				infield.setinputletter(number);
				firstiter = false;
				infield.setinactivecolor();
				fieldvec.push_back(infield);
				def_texts[j].setPosition(xpos + 450, ypos-17);
				def_texts_shadow[j].setPosition(def_texts[j].getPosition().x + 2, def_texts[j].getPosition().y + 2);

				continue;
			}

			InputField infield = InputField({ j,i }, words[j][i-1]);
			float ypos = j * 50 + 150;
			float xpos = i * 40 + 250;
			sf::Vector2f infpos = { xpos, ypos };
			infield.setpos(infpos);				

			fieldvec.push_back(infield);			
		}
		inputmap[j] = fieldvec;		
	}
}


void Game::initWindow()
{
	this->videoMode.height = 900;
	this->videoMode.width = 1600;

	this->window = new sf::RenderWindow(this->videoMode, "straightword 1.0", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(75);
}


const bool Game::getWindow()
{
	return this->window->isOpen();
}


void Game::update()
{
	this->pollEvents();

	for (auto& a : inputmap)
	{
		for (int i=1;i<a.second.size(); i++)
		{
			if (active_box.first == a.first && active_box.second == i)
			{
				a.second[i].setactivecolor();
			}
			else if (a.second[i].isinputcorrect())
			{
				a.second[i].setcorrectcolor();
			}
			else
			{
				a.second[i].setincorrectcolor();
			}			
		}
	}
}


void Game::render()
{
	//Clear current frame
	this->window->clear();

	window->draw(bg_sprite);

	//get mouse position (temporary)
	/*sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	std::cout << "Mouse Position: " << mousePosition.x << ", " << mousePosition.y << std::endl;*/
	for (const auto& first_instance : inputmap) {
		// Loop through the vector inside the pair
		for (auto second_instance : first_instance.second) {
			second_instance.draw(window);
		}
	}

	for (const auto& def : def_texts_shadow)
	{
		window->draw(def);
	}

	for (const auto& def : def_texts)
	{
		window->draw(def);
	}

	window->draw(logo_sprite);

	//Display objects
	this->window->display();
}


void Game::pollEvents()
{
	bool moved = false;

	auto it = inputmap.find(active_box.first);
	int wordsize;
	if (it != inputmap.end())
	{
		wordsize = it->second.size();
	}

	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			window->close();
		}
		if (this->event.type == sf::Event::KeyPressed)
		{			
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				if (active_box.first != 0)
				{
					active_box.first--;
					active_box.second = 1;
				}
				break;
			case sf::Keyboard::Down:
				if (active_box.first != 9)
				{
					active_box.first++;
					active_box.second = 1;
				}
				break;
			case sf::Keyboard::Right:
				if (active_box.second < wordsize-1)
					active_box.second++;
				break;
			case sf::Keyboard::Left:
				if (active_box.second != 1)
					active_box.second--;
				break;
			case sf::Keyboard::BackSpace:
				for (auto& a : inputmap)
				{
					for (int i = 0; i < a.second.size(); i++)
					{
						if (active_box.first == a.first && active_box.second == i)
						{
							a.second[i].setinputletter(' ');
						}
					}
				}
				break;
			default:
				break;
			}
		}
		else if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128 && event.text.unicode != 8) {
				char enteredChar = static_cast<char>(event.text.unicode);

				for (auto& a : inputmap)
				{
					for (int i = 0; i < a.second.size(); i++)
					{
						if (active_box.first == a.first && active_box.second == i)
						{
							a.second[i].setinputletter(enteredChar);							
						}
					}
				}
				if (active_box.second < wordsize - 1)
					active_box.second++;
				else if (active_box.first != 9)
				{
					active_box.first++;
					active_box.second = 1;
				}
			}
		}
	}
}

Game::Game()
{
	this->initVar();
	this->initWindow();
}


Game::~Game()
{
	delete this->window;
}