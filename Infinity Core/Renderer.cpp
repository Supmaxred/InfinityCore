#include "Renderer.h"

Renderer::Renderer(World& world, sf::RenderWindow& window) : world(world), window(window) {}

void Renderer::Render()
{
	for (GameObject* obj : world.GetGameObjects()) {
		obj->Draw(window);
	}
}