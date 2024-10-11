#include "pch.h"
#include "Queen.h"

bool Queen::IsMoveValid(int pos)
{
    int currentRow = m_pos / 8;
    int currentCol = m_pos % 8;
    int targetRow = pos / 8;
    int targetCol = pos % 8;

    int rowDiff = abs(currentRow - targetRow);
    int colDiff = abs(currentCol - targetCol);

    if (currentRow != targetRow && currentCol != targetCol && rowDiff != colDiff)
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
    else 
    {
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
    }

    if (board.m_cases[pos] != nullptr && board.m_cases[pos]->m_color == m_color)
        return false;

    return true;
}

bool Queen::Move(int pos)
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

std::vector<int> Queen::GetPossibleMoves()
{
    std::vector<int> moves;
    AddStraightLineMoves(moves);
    AddDiagonalMoves(moves);
    m_possiblesMoves = moves;
    return moves;
}

void Queen::AddStraightLineMoves(std::vector<int>& moves)
{
    const int directions[4] = { -8, 8, -1, 1 };

    for (int dir : directions)
    {
        int newPos = m_pos + dir;
        while (newPos >= 0 && newPos < 64)
        {
            if (!IsMoveValid(newPos))
            {
                break;
            }

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

void Queen::AddDiagonalMoves(std::vector<int>& moves)
{
    const int directions[4] = { -9, -7, 7, 9 };

    for (int dir : directions)
    {
        int newPos = m_pos + dir;
        while (newPos >= 0 && newPos < 64)
        {
            if (!IsMoveValid(newPos))
            {
                break;
            }

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