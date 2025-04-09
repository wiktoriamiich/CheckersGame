#pragma once
#ifndef GAME_SCREEN_HPP_
#define GAME_SCREEN_HPP_

#include "cScreen.hpp"
#include "game.hpp"
#include "algorithm.hpp"

const int TILE_SIZE = 80; // Size of each tile on the board
const int IMG_SIZE = 64; // Size of each piece image

class GameScreen : public cScreen {
private:
	Game game;

	sf::Texture whiteTexture, blackTexture, wKingTexture, bKingTexture;
	sf::Sprite whitePiece, blackPiece, whiteKing, blackKing;

	bool pieceSelected;
	sf::Vector2i selectedPiecePosition;

	std::vector<sf::RectangleShape> validMoveTiles; // Store the valid move tiles
	sf::CircleShape selectedPieceHighlight; // Highlight the selected piece

public:
	GameScreen(void) : game(true, true, 3), pieceSelected(false) {

		if (!whiteTexture.loadFromFile("pink_normal.png")) {
			std::cerr << "Error loading image\n";
		}
		if (!blackTexture.loadFromFile("black_normal.png")) {
			std::cerr << "Error loading image\n";
		}
		if (!wKingTexture.loadFromFile("pink_king.png")) {
			std::cerr << "Error loading image\n";
		}
		if (!bKingTexture.loadFromFile("black_king.png")) {
			std::cerr << "Error loading image\n";
		}

		whitePiece.setTexture(whiteTexture);
		blackPiece.setTexture(blackTexture);
		whiteKing.setTexture(wKingTexture);
		blackKing.setTexture(bKingTexture);
	}

	virtual int Run(sf::RenderWindow& App);
	void drawBoard(sf::RenderWindow& App);
	void handleMouseClick(int x, int y);
};


#endif // !GAME_SCREEN_HPP_#pragma once
