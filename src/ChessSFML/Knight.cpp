#include "pch.h"
#include "Knight.h"

bool Knight::IsMoveValid(int pos)
{
    int currentRow = m_pos / 8; 
    int currentCol = m_pos % 8; 
    int targetRow = pos / 8;
    int targetCol = pos % 8;

    int rowDiff = abs(currentRow - targetRow);
    int colDiff = abs(currentCol - targetCol);

    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
        return false;

    if (board.m_cases[pos] != nullptr && board.m_cases[pos]->m_color == m_color)
        return false;

    return true;
}

bool Knight::Move(int pos)
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

std::vector<int> Knight::GetPossibleMoves()
{
    std::vector<int> moves;
    const int knightOffsets[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };

    for (int offset : knightOffsets)
    {
        int newPos = m_pos + offset;
        if (newPos >= 0 && newPos < 64 && IsValidKnightMove(newPos))
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

bool Knight::IsValidKnightMove(int end)
{
    int rowDiff = abs((m_pos / 8) - (end / 8));
    int colDiff = abs((m_pos % 8) - (end % 8));
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}