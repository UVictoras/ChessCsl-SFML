#include "pch.h"
#include "Rook.h"

bool Rook::IsMoveValid(int pos)
{
    int currentRow = m_pos / 8;
    int currentCol = m_pos % 8;
    int targetRow = pos / 8;
    int targetCol = pos % 8;

    if (currentRow != targetRow && currentCol != targetCol)
        return false;

    if (currentRow == targetRow)
    {
        int startCol = std::min(currentCol, targetCol) + 1;
        int endCol = std::max(currentCol, targetCol);
        for (int col = startCol; col < endCol; ++col)
        {
            if (board.m_cases[currentRow * 8 + col] != nullptr)
                return false;
        }
    }
    else if (currentCol == targetCol)
    {
        int startRow = std::min(currentRow, targetRow) + 1;
        int endRow = std::max(currentRow, targetRow);
        for (int row = startRow; row < endRow; ++row)
        {
            if (board.m_cases[row * 8 + currentCol] != nullptr)
                return false;
        }
    }

    if (board.m_cases[pos] != nullptr && board.m_cases[pos]->m_color == m_color)
        return false;

    return true;
}

bool Rook::Move(int pos)
{
    if (!IsMoveValid(pos))
    {
        return false;
    }

    board.m_cases[m_pos] = nullptr;

    m_pos = pos;
    board.m_cases[m_pos] = this;

    m_hasMoved = true;

    return true;
}

std::vector<int> Rook::GetPossibleMoves()
{
    std::vector<int> moves;
    AddStraightLineMoves(moves);
    m_possiblesMoves = moves;
    return moves;
}

void Rook::AddStraightLineMoves(std::vector<int>& moves)
{
    const int directions[4] = { -8, 8, -1, 1 };

    for (int dir : directions)
    {
        int newPos = m_pos + dir;
        while (newPos >= 0 && newPos < 64 && IsMoveValid(newPos))
        {
            if (board.m_cases[newPos] == nullptr)
            {
                moves.push_back(newPos);
            }
            else
            {
                if (board.m_cases[newPos]->m_color != m_color)
                {
                    moves.push_back(newPos);
                }
                break;
            }
            newPos += dir;
        }
    }
}
