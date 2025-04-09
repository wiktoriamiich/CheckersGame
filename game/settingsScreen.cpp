#include "settingsScreen.hpp"
#include "board.hpp"

/*
const int TILE_SIZE = 80; // Size of each tile on the board
const int IMG_SIZE = 64; // Size of each piece image
*/


int SettingsScreen::Run(sf::RenderWindow& App) {

    sf::Texture texture;
    sf::Sprite sprite;
    int alpha = 0;

    sf::RenderWindow mainWindow(sf::VideoMode(600, 600), "Rules");
    mainWindow.clear(sf::Color(255, 209, 220));


    mainWindow.setMouseCursorVisible(false);

    if (!texture.loadFromFile("rules.png"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    
    sprite.setTexture(texture);
  

    bool running = true;
    while (running) {
        sf::Event event;
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return -1;
            }
        }

        //App.clear(sf::Color::White);
        mainWindow.draw(sprite);
        mainWindow.display();
        sf::sleep(sf::milliseconds(10000));
        mainWindow.close();
    }
    return -1;
}