#include "pch.h"
#include "King.h"

bool King::IsMoveValid(int pos)
{
    int currentRow = m_pos / 8;
    int currentCol = m_pos % 8;
    int targetRow = pos / 8;
    int targetCol = pos % 8;

    int rowDiff = abs(currentRow - targetRow);
    int colDiff = abs(currentCol - targetCol);

    if (rowDiff > 1 || colDiff > 1)
    {
        if (rowDiff == 0 && (colDiff == 2)) 
        {
            int rookCol = (targetCol == 6) ? 7 : 0; 
            Piece* rook = board.m_cases[currentRow * 8 + rookCol]; 

            if (rook != nullptr && rook->m_color == m_color && !rook->m_hasMoved && !m_hasMoved)
            {
                int step = (rookCol == 7) ? 1 : -1;
                for (int col = currentCol + step; col != rookCol; col += step)
                {
                    if (board.m_cases[currentRow * 8 + col] != nullptr)
                        return false;
                }

                if (IsUnderAttack(currentRow, currentCol + step) ||
                    IsUnderAttack(currentRow, targetCol))
                {
                    return false;
                }

                return true; 
            }
        }
        return false; 
    }

    if (board.m_cases[pos] != nullptr && board.m_cases[pos]->m_color == m_color)
        return false;

    return true;
}

bool King::Move(int pos)
{
    int targetRow = pos / 8;
    int targetCol = pos % 8;

    if (!IsMoveValid(pos))
    {
        return false;
    }

    if (abs(m_pos - pos) == 2)
    {
        int rookCol = (targetCol == 6) ? 7 : 0;
        Piece* piece = board.m_cases[targetRow * 8 + rookCol];

        if (piece != nullptr && piece->IsRook() && !piece->m_hasMoved && !m_hasMoved)
        {
            Rook* rook = reinterpret_cast<Rook*>(piece);
            int direction = (targetCol == 6) ? -1 : 1;
            int newRookCol = rookCol + direction;
            int newRookPos = targetRow * 8 + newRookCol + direction; 

            int oldRookPos = rook->m_pos;
            board.m_cases[newRookPos] = rook;
            rook->m_pos = newRookPos;
            board.m_cases[oldRookPos] = nullptr; 
        }
    }

    board.m_cases[m_pos] = nullptr;
    m_pos = pos;
    board.m_cases[m_pos] = this;
    m_hasMoved = true;

    return true;
}

bool King::IsUnderAttack(int row, int col)
{
    for (int i = 0; i < 64; ++i)
    {
        Piece* piece = board.m_cases[i];
        if (piece != nullptr && piece->m_color != m_color)
        {
            if (piece->IsMoveValid(row * 8 + col))
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> King::GetPossibleMoves()
{
    std::vector<int> moves;
    const int kingOffsets[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };

    for (int offset : kingOffsets)
    {
        int newPos = m_pos + offset;
        if (newPos >= 0 && newPos < 64 && IsMoveValid(newPos))
        {
            if (board.m_cases[newPos] == nullptr || board.m_cases[newPos]->m_color != m_color)
            {
                moves.push_back(newPos);
            }
        }
    }

    m_possiblesMoves = moves;

    return moves;
}