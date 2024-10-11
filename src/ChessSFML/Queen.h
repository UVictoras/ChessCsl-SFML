#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:

	Queen() { };
	~Queen() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
	std::vector<int> GetPossibleMoves() override;
	void AddStraightLineMoves(std::vector<int>& moves);
	void AddDiagonalMoves(std::vector<int>& moves);
};