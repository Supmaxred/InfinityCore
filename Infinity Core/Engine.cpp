#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	Init();
}

Engine::~Engine()
{
	Time::Delete();

	Exit();
}

void Engine::Init()
{
	Time::Init();

	world = World();
}

void Engine::Exit()
{
	windowShouldClose = true;
}

void Engine::Create(std::string title,
	unsigned int resx, unsigned int resy,
	bool vsync, sf::Color bgColor, int style)
{
	sf::ContextSettings config;
	config.depthBits = 12;
	config.antialiasingLevel = 1;

	sf::RenderWindow window(sf::VideoMode(resx, resy), title, style, config);

	window.setVerticalSyncEnabled(vsync);

	Renderer renderer(world, window);

	Start();
	world.Start();

	while (window.isOpen())
	{
		Time::Update();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Exit();
		}

		Update();
		world.Update();

		window.clear(bgColor);
		renderer.Render();
		window.display();

		if (windowShouldClose)
		{
			window.close();
		}
	}
}