#include "startScreen.hpp"


StartScreen::StartScreen(void) {
	alpha_max = 10 * 255;
	alpha_div = 3;
	selectedItemIndex = 0;
}

int StartScreen::Run(sf::RenderWindow& App) {
	sf::Event Event;
	bool Running = true;
	sf::Texture texture;
	sf::Sprite sprite;
	int alpha = 0;
	sf::Font Font;
	sf::Text menu[Max_menu_items];

	App.setMouseCursorVisible(false);

	if (!texture.loadFromFile("background.png"))
	{
		std::cerr << "Error loading presentation.gif" << std::endl;
		return (-1);
	}
	sprite.setTexture(texture);

	if (!Font.loadFromFile("balmy.ttf")) {
		return -1;
	};

	menu[0].setFont(Font);
	menu[0].setCharacterSize(20);
	menu[0].setString("New Game: Player vs Computer");
	menu[0].setPosition({ 140.f, 240.f });

	menu[1].setFont(Font);
	menu[1].setCharacterSize(20);
	menu[1].setString("New Game: Player vs Computer  //IN PROGRESS");
	menu[1].setPosition({ 100.f, 280.f });

	menu[2].setFont(Font);
	menu[2].setCharacterSize(20);
	menu[2].setString("Rules");
	menu[2].setPosition({ 260.f, 320.f });

	menu[3].setFont(Font);
	menu[3].setCharacterSize(20);
	menu[3].setString("Exit");
	menu[3].setPosition({ 270.f, 360.f });

	while (Running) {
		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed) {
				return -1;
			}

			if (Event.type == sf::Event::KeyPressed) {
				if (Event.key.code == sf::Keyboard::Up) {
					if (selectedItemIndex - 1 >= 0) {
						menu[selectedItemIndex].setFillColor(sf::Color::White);
						selectedItemIndex--;
					}
				}

				if (Event.key.code == sf::Keyboard::Down) {
					if (selectedItemIndex + 1 < Max_menu_items) {
						menu[selectedItemIndex].setFillColor(sf::Color::White);
						selectedItemIndex++;
					}
				}

				if (Event.key.code == sf::Keyboard::Return) {
					switch (selectedItemIndex) {
					case 0:
						std::cout << "New Game vs Computer\n";
						return 1;
					case 1:
						std::cout << "New Game vs Player\n";
						return 2;
					case 2:
						std::cout << "Rules\n";
						return 3;
					case 3:
						std::cout << "Exit\n";
						return -1;
					}
				}
			}
		}

		if (alpha < alpha_max) {
			alpha++;
		}
		//sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));

		for (int i = 0; i < Max_menu_items; i++) {
			if (i == selectedItemIndex)
				menu[i].setFillColor(sf::Color::Red);
			else
				menu[i].setFillColor(sf::Color::White);
		}

		App.clear();
		App.draw(sprite);

		if (alpha == alpha_max) {
			for (int i = 0; i < Max_menu_items; i++) {
				App.draw(menu[i]);
			}
			App.display();
		}
	}
	return -1;
}