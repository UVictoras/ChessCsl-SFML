#pragma once
class Graphics
{
public:
	Graphics() { };
	~Graphics() { };

	void DrawBoard();
	void DrawBoard(char piecePos);
#if defined(_WINDOWS)
	void DrawBoard(sf::RenderWindow* window);
#endif
};