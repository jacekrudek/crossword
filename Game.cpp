#include "Game.h"


void Game::initVar()
{
	std::vector<std::string> words = {"hello", "whatsup", "lalalal", "ishbjca", "hello", "whatsup", "lalalal", "ishbjca" , "ishbjca" };

	active_box = { 0,0 };

	for (int j = 0; j < words.size(); j++)
	{
		std::vector<InputField> fieldvec;
		for (int i = 0; i < words[j].size(); i++)
		{
			InputField infield = InputField({ j,i }, words[j][i]);
			float temp1 = j * 50 + 50;
			float temp2 = i * 40 + 50;
			sf::Vector2f infpos = { temp2, temp1 };
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

	this->window = new sf::RenderWindow(this->videoMode, "Chadword 1.0", sf::Style::Titlebar | sf::Style::Close);

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
		for (int i=0;i<a.second.size(); i++)
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

	//get mouse position (temporary)
	/*sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	std::cout << "Mouse Position: " << mousePosition.x << ", " << mousePosition.y << std::endl;*/
	for (const auto& first_instance : inputmap) {
		// Loop through the vector inside the pair
		for (auto second_instance : first_instance.second) {
			second_instance.draw(window);
		}
	}

	//Display objects
	this->window->display();
}


void Game::pollEvents()
{
	bool moved = false;

	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			window->close();
		}
		if (this->event.type == sf::Event::KeyPressed)
		{
			auto it = inputmap.find(active_box.first);
			int wordsize;
			if (it != inputmap.end())
			{
				wordsize = it->second.size();
			}
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				if (active_box.first != 0)
				{
					active_box.first--;
					active_box.second = 0;
				}
				break;
			case sf::Keyboard::Down:
				if (active_box.first != 9)
				{
					active_box.first++;
					active_box.second = 0;
				}
				break;
			case sf::Keyboard::Right:
				if (active_box.second < wordsize-1)
					active_box.second++;
				break;
			case sf::Keyboard::Left:
				if (active_box.second != 0)
					active_box.second--;
				break;
			default:
				break;
			}
		}
		else if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128) {
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