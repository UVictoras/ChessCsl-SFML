#pragma once

#if defined(_WINDOWS)
#include <SFML/Graphics.hpp>
#endif
enum Color;

class Piece
{
public:
	int m_pos;

	char m_inGameChar;

	std::vector<int> m_possiblesMoves;

	Color m_color;

#if defined(_WINDOWS)
	sf::Sprite m_sprite;
#endif

	bool m_hasMoved;

	Piece() : m_pos(0), m_inGameChar(' '), m_color(), m_hasMoved(false) { };
	~Piece() { };

	void InitializePiece(int pos, char inGameChar, Color color);
	virtual bool IsMoveValid(int pos);
	virtual bool Move(int pos);
	bool IsPawn() const;
	bool IsRook() const;
	bool IsKing() const;
	virtual std::vector<int> GetPossibleMoves();
};