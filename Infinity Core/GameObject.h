#pragma once

#include <SFML/Graphics.hpp>
#include "Material.h"

class GameObject {
protected:
    std::string name;
    //Material& material;
    sf::Shape* shape;
public:
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Draw(sf::RenderWindow& window);
    virtual std::string GetName();
    GameObject(std::string _name, sf::Shape* s) : shape(s), name(_name) {}
    virtual ~GameObject() = default;
};