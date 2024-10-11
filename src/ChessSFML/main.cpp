#include "pch.h"
#include "main.h"

struct Point
{
	int x;
	int y;
};

Board board;
Graphics graphics;

std::vector<Board> gameHistory;
int halfMoveClock = 0;

#if defined(_WINDOWS)
std::vector<sf::RectangleShape> rectangles; 
Textures textures;

#endif

#if defined(_DEMO)
int MAX_TURN = 4;
#else
int MAX_TURN = 50; 
#endif

#if defined(_WINDOWS)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int ConvertXYToNumber(int x, int y)
{
	return (y / 112) * 8 + x / 112;
}

std::vector<sf::RectangleShape> CreateBoard()
{
	std::vector<sf::RectangleShape> rectangles;

	int rectSize = 112;  
	int gridSize = 8;    
	int xOffset = 0;   
	int yOffset = 0;   

	for (int row = 0; row < gridSize; ++row)
	{
		for (int col = 0; col < gridSize; ++col)
		{
			sf::RectangleShape rectangle(sf::Vector2f(rectSize, rectSize));

			if ((row + col) % 2 == 0)
				rectangle.setFillColor(sf::Color(251, 204, 156)); 
			else
				rectangle.setFillColor(sf::Color(211, 140, 68)); 

			rectangle.setPosition(sf::Vector2f(xOffset + col * rectSize, yOffset + row * rectSize));

			rectangles.push_back(rectangle);
		}
	}

	return rectangles;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = nullptr;
	wcex.lpszClassName  = L"WinAppClass";
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if ( RegisterClassExW(&wcex)==0 )
		return 0;

	HWND hWnd = CreateWindowW(L"WinAppClass", L"Chess", WS_OVERLAPPEDWINDOW, 0, 0, 910, 935, nullptr, nullptr, hInstance, nullptr);
	if ( hWnd==NULL )
		return 0;

	sf::RenderWindow window((sf::WindowHandle)hWnd);   
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	rectangles = CreateBoard();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	board.InitializeBoard(' ');
	board.m_turn = White;

	MSG msg;
	while (true)
	{
		while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		window.clear();
		graphics.DrawBoard(&window);
		window.display();

	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Point pt;
	bool isValidTurn = false;

	switch (message)
	{
		case WM_COMMAND:
		{
			int id = LOWORD(wParam);
			int notif = HIWORD(wParam);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			pt.x = GET_X_LPARAM(lParam);
			pt.y = GET_Y_LPARAM(lParam);

			if (board.m_startPos == -1)
			{
				board.m_startPos = ConvertXYToNumber(pt.x, pt.y);

				if (board.m_cases[board.m_startPos] == nullptr || board.m_turn != board.m_cases[board.m_startPos]->m_color)
				{
					board.m_startPos = -1;
				}
			}
			else
			{

				board.m_targetPos = ConvertXYToNumber(pt.x, pt.y);
				if (std::find(std::begin(board.m_cases[board.m_startPos]->m_possiblesMoves), std::end(board.m_cases[board.m_startPos]->m_possiblesMoves), board.m_targetPos) == std::end(board.m_cases[board.m_startPos]->m_possiblesMoves) && board.m_cases[board.m_startPos]->IsKing() == false)
				{
					board.m_startPos = -1;
					board.m_targetPos = -1;
					break;
				}
				else 
				{
					isValidTurn = true;
				}

				if (isValidTurn)
				{
					board.m_cases[board.m_startPos]->Move(board.m_targetPos);
					board.m_turn = board.m_turn == White ? Black : White;
					board.m_startPos = -1;
					board.m_targetPos = -1;
				}

				Color currentPlayer = board.m_turn;

				if (board.IsCheckmate(currentPlayer))
				{
					std::cout << (currentPlayer == White ? "Black wins by checkmate!" : "White wins by checkmate!") << std::endl;
					PostQuitMessage(0); 
				}
				else if (board.IsStalemate(currentPlayer))
				{
					std::cout << "The game is a draw by stalemate!" << std::endl;
					PostQuitMessage(0); 
				}
				else if (board.IsInsufficientMaterial())
				{
					std::cout << "The game is a draw by insufficient material!" << std::endl;
					PostQuitMessage(0);
				}
				else if (board.IsThreefoldRepetition())
				{
					std::cout << "The game is a draw by threefold repetition!" << std::endl;
					PostQuitMessage(0); 
				}
				else if (board.IsFiftyMoveRule())
				{
					std::cout << "The game is a draw by the 50-move rule!" << std::endl;
					PostQuitMessage(0); 
				}
			}

			if (board.m_startPos == board.m_targetPos)
			{
				board.m_startPos = -1;
				board.m_targetPos = -1;
			}
		}
		break;

		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	}
	return 0;
}
#elif defined(_CONSOLE)
int ConvertChessNotationToIndex(const std::string& position)
{
	if (position.length() != 2)
		return -1;

	char column = position[0];
	char row = position[1];

	if (column < 'A' || column > 'H' || row < '1' || row > '8')
		return -1;

	int colIndex = column - 'A';
	int rowIndex = row - '1';
	return rowIndex * 8 + colIndex;
}

int main()
{
#if defined(_COMPLETE) || defined(_DEMO)
	board.InitializeBoard(' ');
#elif defined(_LIGHT)
	srand(time(NULL));
	char letters[3] = { 'R', 'N', 'B' };
	int random = rand() % 3;
	char pieceToReplace = letters[random];
	board.InitializeBoard(pieceToReplace);
#endif
	Color currentPlayer = White;
	Graphics graphics;

	std::string startPosStr, targetPosStr;
	int startPos;
	int targetPos;
	bool isValidMove = false;

	Piece* piece;

	while (true)
	{
		graphics.DrawBoard();
		std::cout << (currentPlayer == White ? "White's turn" : "Black's turn") << std::endl;

		std::cout << "Enter move (startPos e.g., A7): ";
		std::cin >> startPosStr;
		std::cout << std::endl;

		startPos = ConvertChessNotationToIndex(startPosStr);

		graphics.DrawBoard(startPos);
		std::cout << "Enter where you want to move : ";
		std::cin >> targetPosStr;

		targetPos = ConvertChessNotationToIndex(targetPosStr);

		if (startPos == -1 || targetPos == -1)
		{
			std::cout << "Invalid input. Try again." << std::endl;
			continue;
		}

		piece = board.m_cases[startPos];
		if (piece == nullptr || piece->m_color != currentPlayer)
		{
			std::cout << "Invalid move. Try again." << std::endl;
			continue;
		}

		if (piece->m_inGameChar == 'P')
		{
			Pawn* pawn = dynamic_cast<Pawn*>(piece);
			if (pawn->Move(targetPos)) isValidMove = true;
		}
		else if (piece->m_inGameChar == 'N')
		{
			Knight* knight = dynamic_cast<Knight*>(piece);
			if (knight->Move(targetPos)) isValidMove = true;
		}
		else if (piece->m_inGameChar == 'B')
		{
			Bishop* bishop = dynamic_cast<Bishop*>(piece);
			if (bishop->Move(targetPos)) isValidMove = true;
		}
		else if (piece->m_inGameChar == 'R')
		{
			Rook* rook = dynamic_cast<Rook*>(piece);
			if (rook->Move(targetPos)) isValidMove = true;
		}
		else if (piece->m_inGameChar == 'Q')
		{
			Queen* queen = dynamic_cast<Queen*>(piece);
			if (queen->Move(targetPos)) isValidMove = true;
		}
		else if (piece->m_inGameChar == 'K')
		{
			King* king = dynamic_cast<King*>(piece);
			if (king->Move(targetPos)) isValidMove = true;
		}

		if (isValidMove == true)
		{
			board.m_lastMove = targetPos;

			currentPlayer = (currentPlayer == White) ? Black : White;
			halfMoveClock++;

			gameHistory.push_back(board);
		}
		else
		{
			std::cout << "Invalid move. Try again." << std::endl;
		}

		if (board.IsCheckmate(currentPlayer))
		{
			std::cout << (currentPlayer == White ? "Black wins by checkmate!" : "White wins by checkmate!") << std::endl;
			break;
		}
		else if (board.IsStalemate(currentPlayer))
		{
			std::cout << "The game is a draw by stalemate!" << std::endl;
			break;
		}
		else if (board.IsInsufficientMaterial())
		{
			std::cout << "The game is a draw by insufficient material!" << std::endl;
			break;
		}
		else if (board.IsThreefoldRepetition())
		{
			std::cout << "The game is a draw by threefold repetition!" << std::endl;
			break;
		}
		else if (board.IsFiftyMoveRule())
		{
			std::cout << "The game is a draw by the 50-move rule!" << std::endl;
			break;
		}

		system("cls");
		isValidMove = false;
	}

	return 0;
}
#endif
