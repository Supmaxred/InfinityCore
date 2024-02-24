#pragma once
#include <SFML/Graphics.hpp>

#include "WindowStyle.h"
#include "Time.h"
#include "World.h"
#include "Renderer.h"

class Engine
{
protected:
	std::string name;

	World world;

	bool windowShouldClose = false;

public:
	Engine();

	~Engine();

	virtual void Init();
	virtual void Create(std::string title,
		unsigned int resx = 1920U, unsigned int resy = 1080U,
		bool vsync = false, sf::Color bgColor = sf::Color::Black, int style = WindowStyle::Default);

	virtual void Start() = 0;
	virtual void Update() = 0;

	virtual void Exit();
};