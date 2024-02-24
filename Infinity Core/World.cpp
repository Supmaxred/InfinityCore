#include "World.h"
#include <algorithm>
#include <iostream>

World::World()
{
    gameObjects = std::vector<GameObject*>();
}

const std::vector<GameObject*>& World::GetGameObjects() const {
    return gameObjects;
}

void World::CreateEntity(GameObject* entity) {
    GameObject* ptr = nullptr;
    if (FindGameObjectByName(entity->GetName(), ptr))
    {

        return;
    }

    gameObjects.push_back(entity);
}

bool World::FindGameObjectByName(const std::string& name, GameObject*& out) {
    for (GameObject* obj : GetGameObjects()) {
        if (obj->GetName() == name) {
            out = obj;
            return true;
        }
    }

    out = nullptr;
    return false;
}

void World::RemoveEntity(GameObject* entity) {
    auto it = std::find(gameObjects.begin(), gameObjects.end(), entity);
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
    }
}

void World::Start()
{
    for (GameObject* obj : GetGameObjects()) {
        obj->Start();
    }

    //for (int i = 0; i < gameObjects.size(); i++) {
    //    GameObject* obj = gameObjects[i];
    //    if (obj == nullptr)
    //        continue;
    //    std::cout << obj << '\n';
    //    std::cout << "updating " << obj->GetName() << '\n';
    //    obj->Update();
    //    std::cout << "finish updating " << obj->GetName() << '\n';
    //}
}

void World::Update()
{
    for (GameObject* obj : GetGameObjects()) {
        obj->Update();
    }
    //std::cout << "start update" << '\n';
    //for (int i = 0; i < gameObjects.size(); i++) {
    //    GameObject* obj = gameObjects[i];
    //    if (obj == nullptr)
    //        continue;
    //    std::cout << obj << '\n';
    //    std::cout << "updating " << obj->GetName() << '\n';
    //    obj->Update();
    //    std::cout << "finish updating " << obj->GetName() << '\n';
    //}
}