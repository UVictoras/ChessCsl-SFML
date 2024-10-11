#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:

	Rook() { };
	~Rook() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
	std::vector<int> GetPossibleMoves() override;
	void AddStraightLineMoves(std::vector<int>& moves);
};