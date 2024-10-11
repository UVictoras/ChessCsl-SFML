#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:

	Pawn() { };
	~Pawn() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
	std::vector<int> GetPossibleMoves() override; 
};