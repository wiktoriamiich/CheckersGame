#ifndef START_SCREEN_HPP_
#define START_SCREEN_HPP_

#include "cScreen.hpp"

#define Max_menu_items 4

class StartScreen : public cScreen {
private:
	int alpha_max;
	int alpha_div;
	int selectedItemIndex;

public:
	StartScreen(void);
	virtual int Run(sf::RenderWindow& App);
};

#endif // !START_SCREEN_HPP_#pragma once
