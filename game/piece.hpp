#ifndef PIECE_HPP_
#define PIECE_HPP_

enum PieceType { EMPTY, PAWN, KING };
enum Color { NONE, BLACK, WHITE }; // BLACK moves up, WHITE moves down

class Piece {
	PieceType type;
	Color color;

public:
	Piece(PieceType type = EMPTY, Color color = NONE) : type(type), color(color) {}

	bool isKing() const { return type == KING; }
	bool isPawn() const { return type == PAWN; }
	void promote() { if (type == PAWN) type = KING; }

	PieceType getType() const { return type; }
	Color getColor() const { return color; }
	void setColor(Color color) { this->color = color; }
	void setType(PieceType type) { this->type = type; }
};



#endif // !PIECE_HPP_