#include "material.h"

sf::Drawable& Material::GetDrawable()
{
	return drawable;
}

void Material::DrawOnScreen(sf::RenderWindow& window)
{
	window.draw(drawable);
}