#include "pch.h"
#include "Bishop.h"

bool Bishop::IsMoveValid(int pos)
{
    int currentRow = m_pos / 8;
    int currentCol = m_pos % 8;
    int targetRow = pos / 8;
    int targetCol = pos % 8;

    int rowDiff = abs(currentRow - targetRow);
    int colDiff = abs(currentCol - targetCol);

    if (rowDiff != colDiff)
        return false;

    int rowStep = (targetRow > currentRow) ? 1 : -1;
    int colStep = (targetCol > currentCol) ? 1 : -1;

    int row = currentRow + rowStep;
    int col = currentCol + colStep;

    while (row != targetRow && col != targetCol)
    {
        if (board.m_cases[row * 8 + col] != nullptr)
            return false;
        row += rowStep;
        col += colStep;
    }

    if (board.m_cases[pos] != nullptr && board.m_cases[pos]->m_color == m_color)
        return false;

    return true;
}

bool Bishop::Move(int pos)
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

std::vector<int> Bishop::GetPossibleMoves()
{
    std::vector<int> moves;
    AddDiagonalMoves(moves);
    m_possiblesMoves = moves;
    return moves;
}

void Bishop::AddDiagonalMoves(std::vector<int>& moves)
{
    const int directions[4] = { -9, -7, 7, 9 };
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
