#pragma once

#include <vector>
#include "GameObject.h"
#include "Player.h"

class World {
private:
    std::vector<GameObject*> gameObjects;

public:

    World();

    const std::vector<GameObject*>& GetGameObjects() const;

    void CreateEntity(GameObject* entity);
    bool FindGameObjectByName(const std::string& name, GameObject*& out);
    void RemoveEntity(GameObject* entity);

    void Start();
    void Update();
};
