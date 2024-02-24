#pragma once

#include "SFML/Graphics.hpp"
#include "World.h"

class Renderer
{
public:
	Renderer(World& world, sf::RenderWindow& window);

	Renderer& operator=(const Renderer&) = default;

	void Render();

private:
	World& world;
	sf::RenderWindow& window;
};