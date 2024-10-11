#pragma once

#include "Piece.h"

class King : public Piece
{
public:

	King() { };
	~King() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
	bool IsUnderAttack(int row, int col);
	std::vector<int> GetPossibleMoves() override;
};