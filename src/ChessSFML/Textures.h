#pragma once

#if defined(_WINDOWS)

#include <SFML/Graphics.hpp>

class Textures
{
public:
	std::vector<sf::Texture>	m_textures;

	Textures() { } ;
	~Textures() { };

	void CreateTexture(const char* name);
	void InitializeVector();
};

#endif