#include "pch.h"
#include "Board.h"

void Board::InitializeBoard(char pieceToReplace)
{
    std::fill(std::begin(m_cases), std::end(m_cases), nullptr);
#if defined(_WINDOWS)
    textures.InitializeVector();
#endif
    InitializeBlackPieces(pieceToReplace);
    InitializeWhitePieces(pieceToReplace);
}

void Board::InitializeBlackPieces(char pieceToReplace)
{
    for (int i = 0; i < 16; i++)
    {
        Piece* piece = nullptr;
        char inGameChar;
        int position = i;

        if (i == 0 || i == 7) 
        { 
            if (pieceToReplace == 'R')
            {
                inGameChar = 'P'; piece = new Pawn(); 
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[2]);
#endif
            }
            else
            {
                inGameChar = 'R'; piece = new Rook(); 
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[4]);
#endif
            }
        }
        else if (i == 1 || i == 6) 
        { 
            if (pieceToReplace == 'N')
            {
                inGameChar = 'P'; piece = new Pawn();
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[2]);
#endif
            }
            else
            {
                inGameChar = 'N'; piece = new Knight();
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[5]);
#endif
            }
        }
        else if (i == 2 || i == 5) 
        { 
            if (pieceToReplace == 'B')
            {
                inGameChar = 'P'; piece = new Pawn();
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[2]);
#endif
            }
            else
            {
                inGameChar = 'B'; piece = new Bishop();
#if defined(_WINDOWS) 
                piece->m_sprite.setTexture(textures.m_textures[3]);
#endif
            }
        }
        else if (i == 3)
        { 
            inGameChar = 'Q'; piece = new Queen(); 
#if defined(_WINDOWS)
            piece->m_sprite.setTexture(textures.m_textures[1]);
#endif
        }
        else if (i == 4) 
        { 
            inGameChar = 'K'; piece = new King(); 
#if defined(_WINDOWS)
            piece->m_sprite.setTexture(textures.m_textures[0]);
#endif
        }
        else 
        { 
            inGameChar = 'P'; piece = new Pawn(); 
#if defined(_WINDOWS)
            piece->m_sprite.setTexture(textures.m_textures[2]);
#endif
        }

        piece->InitializePiece(position, inGameChar, Black);
        m_cases[position] = piece;
    }
}

void Board::InitializeWhitePieces(char pieceToReplace)
{
    Piece* piece = nullptr;
    char inGameChar;
    int position;

    for (int i = 0; i < 16; i++)
    {
        position = i + 48;

        if (i < 8) 
        { 
            inGameChar = 'P'; piece = new Pawn(); 
#if defined(_WINDOWS)
            piece->m_sprite.setTexture(textures.m_textures[8]);
#endif
        }
        else if (i == 8 || i == 15) 
        {
            if (pieceToReplace == 'R')
            {
                inGameChar = 'P'; piece = new Pawn();
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[8]); 
#endif
            }
            else
            {
                inGameChar = 'R'; piece = new Rook();
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[10]);
#endif
            }
        }
        else if (i == 9 || i == 14) 
        { 
            if (pieceToReplace == 'N')
            {
                inGameChar = 'P'; piece = new Pawn();
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[8]); 
#endif
            }
            else
            {
                inGameChar = 'N'; piece = new Knight();
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[11]);
#endif
            }
        }
        else if (i == 10 || i == 13) 
        { 
            if (pieceToReplace == 'B') 
            {
                inGameChar = 'P'; piece = new Pawn(); 
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[8]); 
#endif
            }
            else
            {
                inGameChar = 'B'; piece = new Bishop(); 
#if defined(_WINDOWS)
                piece->m_sprite.setTexture(textures.m_textures[9]);
#endif
            }
        }
        else if (i == 11) 
        { 
            inGameChar = 'Q'; piece = new Queen(); 
#if defined(_WINDOWS)
            piece->m_sprite.setTexture(textures.m_textures[7]);
#endif
        }
        else 
        { 
            inGameChar = 'K'; piece = new King(); 
#if defined(_WINDOWS)
            piece->m_sprite.setTexture(textures.m_textures[6]);
#endif
        }

        piece->InitializePiece(position, inGameChar, White);
        m_cases[position] = piece;
    }
}

bool Board::IsMinorPiece(Piece* piece)
{
    return reinterpret_cast<Knight*>(piece) != nullptr || reinterpret_cast<Bishop*>(piece) != nullptr;
}

bool Board::IsCheckmate(Color playerColor)
{
    King* king = nullptr;
    int kingPos = -1;

    for (int i = 0; i < 64; i++)
    {
        if (m_cases[i] != nullptr && m_cases[i]->m_color == playerColor && m_cases[i]->IsKing())
        {
            king = reinterpret_cast<King*>(m_cases[i]);
            kingPos = i;
            break;
        }
    }

    if (king == nullptr)
        return false;

    if (!king->IsUnderAttack(kingPos / 8, kingPos % 8))
        return false;

    for (int i = 0; i < 64; i++)
    {
        Piece* piece = m_cases[i];
        if (piece != nullptr && piece->m_color == playerColor)
        {
            std::vector<int> possibleMoves = piece->GetPossibleMoves();
            for (int targetPos : possibleMoves)
            {
                Piece* capturedPiece = m_cases[targetPos];

                m_cases[targetPos] = piece;
                m_cases[i] = nullptr;

                if (!king->IsUnderAttack(kingPos / 8, kingPos % 8))
                {
                    m_cases[i] = piece;
                    m_cases[targetPos] = capturedPiece;
                    return false;
                }

                m_cases[i] = piece;
                m_cases[targetPos] = capturedPiece;
            }
        }
    }

    return true;
}

bool Board::IsStalemate(Color playerColor)
{
    King* king = nullptr;
    int kingPos = -1;

    for (int i = 0; i < 64; i++)
    {
        if (m_cases[i] != nullptr && m_cases[i]->m_color == playerColor && m_cases[i]->IsKing())
        {
            king = reinterpret_cast<King*>(m_cases[i]);
            kingPos = i;
            break;
        }
    }

    if (king == nullptr)
        return false;

    if (king->IsUnderAttack(kingPos / 8, kingPos % 8))
        return false;

    for (int i = 0; i < 64; i++)
    {
        Piece* piece = m_cases[i];
        if (piece != nullptr && piece->m_color == playerColor)
        {
            std::vector<int> possibleMoves = piece->GetPossibleMoves();
            for (int targetPos : possibleMoves)
            {
                Piece* capturedPiece = m_cases[targetPos];

                m_cases[targetPos] = piece;
                m_cases[i] = nullptr;

                if (!king->IsUnderAttack(kingPos / 8, kingPos % 8))
                {
                    m_cases[i] = piece;
                    m_cases[targetPos] = capturedPiece;
                    return false;
                }

                m_cases[i] = piece;
                m_cases[targetPos] = capturedPiece;
            }
        }
    }

    return true;
}

bool Board::IsInsufficientMaterial()
{
    int whitePieces = 0, blackPieces = 0;
    bool whiteHasMinorPiece = false, blackHasMinorPiece = false;

    for (int i = 0; i < 64; i++)
    {
        if (m_cases[i] != nullptr)
        {
            if (m_cases[i]->m_color == White)
            {
                whitePieces++;
                if (IsMinorPiece(m_cases[i])) whiteHasMinorPiece = true;
            }
            else
            {
                blackPieces++;
                if (IsMinorPiece(m_cases[i])) blackHasMinorPiece = true;
            }
        }
    }

    if ((whitePieces == 1 && blackPieces == 1) ||
        (whitePieces == 2 && whiteHasMinorPiece && blackPieces == 1) ||
        (blackPieces == 2 && blackHasMinorPiece && whitePieces == 1))
    {
        return true;
    }

    return false;
}

bool Board::operator==(const Board& other) const
{
    for (int i = 0; i < 64; i++)
    {
        Piece* thisPiece = m_cases[i];
        Piece* otherPiece = other.m_cases[i];

        if ((thisPiece == nullptr && otherPiece != nullptr) ||
            (thisPiece != nullptr && otherPiece == nullptr))
        {
            return false;
        }

        if (thisPiece != nullptr && otherPiece != nullptr)
        {
            if (thisPiece->m_inGameChar != otherPiece->m_inGameChar ||
                thisPiece->m_color != otherPiece->m_color)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::IsThreefoldRepetition()
{
    int count = 0;

    for (const auto& previousBoardState : gameHistory)
    {
        if (board == previousBoardState)
        {
            count++;
        }
    }

    return count >= 3;
}

bool Board::IsFiftyMoveRule()
{
    return halfMoveClock >= MAX_TURN;
}
