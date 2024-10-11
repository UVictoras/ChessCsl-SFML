#pragma once

#define NOMINMAX 

#include <iostream>
#include <vector>
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

#if defined(_WINDOWS) 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Textures.h"

#endif

#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Graphics.h"

enum Color
{
	White,
	Black
};

extern Board board;
extern std::vector<Board> gameHistory;
extern int MAX_TURN;
extern int halfMoveClock;
extern Graphics graphics;
#if defined(_WINDOWS)
extern Textures textures;
extern std::vector<sf::RectangleShape> rectangles;
#endif