#pragma once

#include "SFML/Graphics.hpp"

#include "PerlinNoise.h"
// #include "VoronoiNoise.h"

class Renderer
{
	int m_window_height;
	int m_window_width;

	sf::RenderWindow* m_window = nullptr;
	sf::Uint8* m_pixels = nullptr;

	friend class PerlinNoise;
	// friend class VoronoiNoise;
public:
	Renderer(const int& width, const int& height);
	~Renderer();

	void Run();
};