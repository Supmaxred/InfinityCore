#include "gameObject.h"

std::string GameObject::GetName()
{
    return this->name;
}

void GameObject::Draw(sf::RenderWindow& window)
{
    window.draw(*shape);
}