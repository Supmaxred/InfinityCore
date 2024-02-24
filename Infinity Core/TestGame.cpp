#include "TestGame.h"
#include <iostream>

void TestGame::Start()
{
	Player* player = new Player("Player", new sf::CircleShape(50));

	world.CreateEntity(player);
}

void TestGame::Update()
{
	
}