#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:

	Bishop() { };
	~Bishop() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
	std::vector<int> GetPossibleMoves() override;
	void AddDiagonalMoves(std::vector<int>& moves);
};