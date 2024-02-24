#include "Time.h"
#include "Math.h"

Time* Time::instance = nullptr;

Time::Time() {
    startTime = std::chrono::high_resolution_clock::now();
    lastFrameTime = startTime;
    time = 0.00001;
    deltaTime = 0.00001;
}

inline double Time::ValidTest(double value) {
    return instance != nullptr ? value : 0.00001;
}

void Time::Init() {
    delete instance;
    instance = new Time();
}

void Time::Delete() {
    delete instance;
    instance = nullptr;
}

void Time::Update() {
    if (instance == nullptr)
        return;

    auto t = std::chrono::high_resolution_clock::now();
    instance->time = std::chrono::duration<double>(t - instance->startTime).count();
    instance->deltaTime = std::chrono::duration<double>(t - instance->lastFrameTime).count();
    instance->deltaTime = Mathf::Clamp01(instance->deltaTime);;
    instance->lastFrameTime = t;
}

float Time::GetTime() {
    return ValidTest(instance->time);
}

float Time::GetDelta() {
    return ValidTest(instance->deltaTime);
}