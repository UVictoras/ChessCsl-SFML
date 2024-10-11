#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:

	Knight() { };
	~Knight() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
	std::vector<int> GetPossibleMoves() override;
	bool IsValidKnightMove(int end);
};