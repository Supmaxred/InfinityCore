#pragma once

#include <SFML/Graphics.hpp>

class Material
{
public:
	sf::Drawable &drawable;

	Material(sf::Drawable& drawable) : drawable(drawable) { }

	Material& operator=(const Material&) = default;

	sf::Drawable& GetDrawable();

	void DrawOnScreen(sf::RenderWindow& window);
};