#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "board.hpp"

const int TILE_SIZE_I = 80; // Size of each tile on the board
const int IMG_SIZE_I = 64; // Size of each piece image

class CheckersGame {
private:
    sf::RenderWindow window;
    Board board; // Assuming you have the Board class from your question

    sf::Texture whiteTexture, blackTexture, wKingTexture, bKingTexture;
    sf::Sprite whitePiece, blackPiece, whiteKing, blackKing;

    bool isWhiteTurn;
    bool pieceSelected;
    sf::Vector2i selectedPiecePosition;

    std::vector<sf::RectangleShape> validMoveTiles; // Store the valid move tiles
    sf::CircleShape selectedPieceHighlight; // Highlight the selected piece

public:
    CheckersGame() : window(sf::VideoMode(BOARD_SIZE* TILE_SIZE_I, BOARD_SIZE* TILE_SIZE_I), "SFML Checkers"), board(true, true, 3), isWhiteTurn(true), pieceSelected(false) {
        if (!whiteTexture.loadFromFile("piece_white.png")) {
            // Handle error
        }
        if (!blackTexture.loadFromFile("piece_black.png")) {
            // Handle error
        }
        if (!wKingTexture.loadFromFile("king_white.png")) {
            // Handle error
        }
        if (!bKingTexture.loadFromFile("king_black.png")) {
            // Handle error
        }

        whitePiece.setTexture(whiteTexture);
        blackPiece.setTexture(blackTexture);
        whiteKing.setTexture(wKingTexture);
        blackKing.setTexture(bKingTexture);

        run();
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
            }

            window.clear(sf::Color::White);
            drawBoard();
            window.display();
        }
    }

    void drawBoard() {
        sf::RectangleShape tile(sf::Vector2f(TILE_SIZE_I, TILE_SIZE_I));

        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                tile.setPosition(col * TILE_SIZE_I, row * TILE_SIZE_I);

                if ((row + col) % 2 == 0) {
                    tile.setFillColor(sf::Color::White);
                }
                else {
                    tile.setFillColor(sf::Color(139, 69, 19)); // Brown color
                }

                window.draw(tile);

                Piece* piece = board.getPiece(row, col);
                sf::Sprite sprite;
                if (piece->getType() == PAWN) {
                    sprite = (piece->getColor() == WHITE) ? whitePiece : blackPiece;
                    sprite.setPosition(col * TILE_SIZE_I + ((TILE_SIZE_I - IMG_SIZE_I) / 2), row * TILE_SIZE_I + ((TILE_SIZE_I - IMG_SIZE_I) / 2));
                }
                else if (piece->getType() == KING) {
                    sprite = (piece->getColor() == WHITE) ? whiteKing : blackKing;
                    sprite.setPosition(col * TILE_SIZE_I + ((TILE_SIZE_I - IMG_SIZE_I) / 2), row * TILE_SIZE_I + ((TILE_SIZE_I - IMG_SIZE_I) / 2));
                }
                window.draw(sprite);
            }
        }

        // Draw the valid move tiles
        for (const auto& validMoveTile : validMoveTiles) {
            window.draw(validMoveTile);
        }

        // Draw the selected piece highlight
        if (pieceSelected) {
            window.draw(selectedPieceHighlight);
            Piece* piece = board.getPiece(selectedPiecePosition.x, selectedPiecePosition.y);

            sf::Sprite sprite;
            if (piece->getType() == PAWN) {
                sprite = (piece->getColor() == WHITE) ? whitePiece : blackPiece;
                sprite.setPosition(selectedPiecePosition.y * TILE_SIZE_I + ((TILE_SIZE_I - IMG_SIZE_I) / 2), selectedPiecePosition.x * TILE_SIZE_I + ((TILE_SIZE_I - IMG_SIZE_I) / 2));
            }
            else if (piece->getType() == KING) {
                sprite = (piece->getColor() == WHITE) ? whiteKing : blackKing;
                sprite.setPosition(selectedPiecePosition.y * TILE_SIZE_I + ((TILE_SIZE_I - IMG_SIZE_I) / 2), selectedPiecePosition.x * TILE_SIZE_I + ((TILE_SIZE_I - IMG_SIZE_I) / 2));
            }
            window.draw(sprite);
        }
    }

    void handleMouseClick(int mouseX, int mouseY) {
        int row = mouseY / TILE_SIZE_I;
        int col = mouseX / TILE_SIZE_I;

        // If no piece is selected and the clicked tile has a piece of the current player's color
        if (!pieceSelected && board.getPiece(row, col)->getColor() == (isWhiteTurn ? WHITE : BLACK)) {
            pieceSelected = true;
            selectedPiecePosition = sf::Vector2i(row, col);
            selectedPieceHighlight.setRadius(IMG_SIZE_I / 2 + 6);
            selectedPieceHighlight.setFillColor(sf::Color(255, 255, 0));
            selectedPieceHighlight.setOrigin(IMG_SIZE_I / 2 + 6, IMG_SIZE_I / 2 + 6);
            selectedPieceHighlight.setPosition(col * TILE_SIZE_I + TILE_SIZE_I / 2, row * TILE_SIZE_I + TILE_SIZE_I / 2);
            std::vector<std::pair<int, int>> validMoves;
            // Check if there are any jumps available
            if (board.allAvailableJumps(board.getPiece(row, col)->getColor()).size() == 0) validMoves = board.getValidMoves(row, col);
            else {
                // If there are jumps available, only show the jumps
                if (board.getValidJumps(row, col).size() == 0) return;
                validMoves = board.getValidJumps(row, col);
            }

            for (const auto& move : validMoves) {
                int endRow = move.first;
                int endCol = move.second;
                sf::RectangleShape validMoveTile(sf::Vector2f(TILE_SIZE_I, TILE_SIZE_I));
                validMoveTile.setPosition(endCol * TILE_SIZE_I, endRow * TILE_SIZE_I);
                validMoveTile.setFillColor(sf::Color(0, 255, 0, 128)); // Semi-transparent green
                validMoveTiles.push_back(validMoveTile); // Add the valid move tile to the vector
            }
        }
        else if (pieceSelected) {
            // Try to move the selected piece to the clicked tile
            int startRow = selectedPiecePosition.x;
            int startCol = selectedPiecePosition.y;
            int endRow = row;
            int endCol = col;

            bool moveSuccess = false;
            if (board.isJump(startRow, startCol, endRow, endCol)) {
                moveSuccess = board.movePiece(startRow, startCol, endRow, endCol);
                // If a jump was made, check if there are more jumps available
                if (moveSuccess && board.getValidJumps(endRow, endCol).size() > 0) {
                    // If there are more jumps available, keep the piece selected
                    pieceSelected = true;
                    selectedPiecePosition = sf::Vector2i(endRow, endCol);
                    selectedPieceHighlight.setPosition(endCol * TILE_SIZE_I + TILE_SIZE_I / 2, endRow * TILE_SIZE_I + TILE_SIZE_I / 2);
                    validMoveTiles.clear(); // Clear the valid move tiles vector
                    for (const auto& move : board.getValidJumps(endRow, endCol)) {
                        int jumpEndRow = move.first;
                        int jumpEndCol = move.second;
                        sf::RectangleShape validMoveTile(sf::Vector2f(TILE_SIZE_I, TILE_SIZE_I));
                        validMoveTile.setPosition(jumpEndCol * TILE_SIZE_I, jumpEndRow * TILE_SIZE_I);
                        validMoveTile.setFillColor(sf::Color(0, 255, 0, 128)); // Semi-transparent green
                        validMoveTiles.push_back(validMoveTile); // Add the valid move tile to the vector
                    }
                }
                else {
                    // If there are no more jumps available, switch turns
                    isWhiteTurn = !isWhiteTurn;
                }
            }
            else {
                if (board.movePiece(startRow, startCol, endRow, endCol)) isWhiteTurn = !isWhiteTurn;
            }

            // Reset selection state
            pieceSelected = false;
            validMoveTiles.clear(); // Clear the valid move tiles vector
        }
    }
};

#endif // !INTERFACE_HPP_#pragma once
