#pragma once
#include <chrono>

class Time {
private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point lastFrameTime;
    double time;      // время с запуска программы
    double deltaTime;  // время с последнего кадра
    static Time* instance;

    // Инициализация класса
    Time();

    static inline double ValidTest(double value);

public:
    static void Init();
    static void Delete();

    // Обновление переменных
    static void Update();

    static float GetTime();
    static float GetDelta();
};