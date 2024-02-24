#include "Player.h"
#include <iostream>
#define SPEED 100.0f

void Player::Start()
{

}

void Player::Update()
{
	Vector2 move = shape->getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move = move + Vector2::Right() * Time::GetDelta() * SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move = move + -Vector2::Right() * Time::GetDelta() * SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move = move + -Vector2::Up() * Time::GetDelta() * SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move = move + Vector2::Up() * Time::GetDelta() * SPEED;
	}
	shape->setPosition((Vector2)move);
}