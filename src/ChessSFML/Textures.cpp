#include "pch.h"
#if defined(_WINDOWS)

#include "Textures.h"

void Textures::CreateTexture(const char* name)
{
	sf::Texture texture;

	if (!texture.loadFromFile(name))
	{
		return;
	}

	texture.setSmooth(true);

	m_textures.push_back(texture);
}

void Textures::InitializeVector()
{
	CreateTexture("..\\..\\..\\res\\Images\\black_king.png"); // 0
	CreateTexture("..\\..\\..\\res\\Images\\black_queen.png"); // 1
	CreateTexture("..\\..\\..\\res\\Images\\black_pawn.png"); // 2
	CreateTexture("..\\..\\..\\res\\Images\\black_bishop.png"); // 3
	CreateTexture("..\\..\\..\\res\\Images\\black_rook.png"); // 4
	CreateTexture("..\\..\\..\\res\\Images\\black_knight.png"); // 5
	CreateTexture("..\\..\\..\\res\\Images\\white_king.png"); // 6
	CreateTexture("..\\..\\..\\res\\Images\\white_queen.png"); // 7
	CreateTexture("..\\..\\..\\res\\Images\\white_pawn.png"); // 8
	CreateTexture("..\\..\\..\\res\\Images\\white_bishop.png"); // 9
	CreateTexture("..\\..\\..\\res\\Images\\white_rook.png"); // 10
	CreateTexture("..\\..\\..\\res\\Images\\white_knight.png"); // 11
}

#endif