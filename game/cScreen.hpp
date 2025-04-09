#ifndef C_SCREEN_HPP_
#define C_SCREEN_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class cScreen {
public:
	virtual int Run(sf::RenderWindow& App) = 0;
};

#endif // !C_SCREEN_HPP_#pragma once
