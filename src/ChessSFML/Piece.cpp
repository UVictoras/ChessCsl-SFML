#include "pch.h"
#include "Piece.h"



void Piece::InitializePiece(int pos, char inGameChar, Color color)
{
	m_pos = pos;
	m_inGameChar = inGameChar;
	m_color = color;
}

bool Piece::IsMoveValid(int pos)
{
	return false;
}

bool Piece::Move(int pos)
{
	if (!IsMoveValid(pos))
	{
		return false;
	}

	board.m_cases[m_pos] = nullptr;

	m_pos = pos;
	board.m_cases[m_pos] = this;

	return true;
}

bool Piece::IsPawn() const
{
	return m_inGameChar == 'P';
}

bool Piece::IsRook() const
{
	return m_inGameChar == 'R';
}

bool Piece::IsKing() const
{
	return m_inGameChar == 'K';
}

std::vector<int> Piece::GetPossibleMoves()
{
	return m_possiblesMoves;
}