#pragma once
#include <iostream>
#include <vector>

#include "Piece.h"

class Board
{
public:
	Piece* m_cases[64];
	int m_lastMove;
	int m_startPos;
	int m_targetPos;
	Color m_turn;

	Board() : m_lastMove(0), m_startPos(-1), m_targetPos(-1) {};
	~Board() { };

	void InitializeBoard(char pieceToReplace);
	void InitializeBlackPieces(char pieceToReplace);
	void InitializeWhitePieces(char pieceToReplace);

	bool IsMinorPiece(Piece* piece);
	bool IsCheckmate(Color playerColor);
	bool IsStalemate(Color playerColor);
	bool IsInsufficientMaterial();
	bool operator==(const Board& other) const;
	bool IsThreefoldRepetition();
	bool IsFiftyMoveRule();
};