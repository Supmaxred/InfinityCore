#pragma once
#include "GameObject.h"
#include "Time.h"
#include "Vector2.h"


class Player : public GameObject
{
public:
	void Start() override;
	void Update() override;

	Player(std::string _name, sf::Shape* s) : GameObject(_name, s) {}
};