#pragma once

#include <array>
#include <string>
#include <SFML/System/Vector2.hpp>

class Vector2 final {
public:
    float x, y;

    Vector2() = default;

    Vector2(const Vector2& vec);
    Vector2(const sf::Vector2f& vec);
    Vector2(const sf::Vector2i& vec);

    explicit Vector2(float x, float y);

    explicit Vector2(float a);

    Vector2& operator=(const Vector2&) = default;
    Vector2& operator=(const sf::Vector2f& vec);

    [[nodiscard]] Vector2 operator-() const;

    // Boolean operations
    bool operator==(const Vector2& vec) const;
    bool operator!=(const Vector2& vec) const;

    [[nodiscard]] Vector2 operator+(const Vector2& vec) const;
    [[nodiscard]] Vector2 operator-(const Vector2& vec) const;
    [[nodiscard]] Vector2 operator*(const Vector2& vec) const;
    [[nodiscard]] Vector2 operator/(const Vector2& vec) const;

    [[nodiscard]] Vector2 operator+(float number) const;
    [[nodiscard]] Vector2 operator-(float number) const;
    [[nodiscard]] Vector2 operator*(float number) const;
    [[nodiscard]] Vector2 operator/(float number) const;

    operator sf::Vector2f() const;

    [[nodiscard]] float Dot(const Vector2& vec) const; // Returns dot product
    [[nodiscard]] float SqrMagnitude() const;
    [[nodiscard]] float Magnitude() const;
    [[nodiscard]] Vector2 Normalized() const;
    [[nodiscard]] Vector2 ClampMagnitude(float maxMag) const;
    [[nodiscard]] Vector2 SetMagnitude(float maxMag) const;
    [[nodiscard]] sf::Vector2f SFML() const;
    [[nodiscard]] std::string ToString() const;
    [[nodiscard]] Vector2 Perpendicular() const;

    static Vector2 Lerp(const Vector2& current, const Vector2& target, float time);
    static Vector2 LerpUnclamped(const Vector2& current, const Vector2& target, float time);
    static Vector2 LerpMag(const Vector2& current, const Vector2& target, float time);
    static Vector2 LerpMagUnclamped(const Vector2& current, const Vector2& target, float time);
    static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDelta);
    static Vector2 SmoothDamp(const Vector2& current, Vector2& target, Vector2& currentVel, float smoothTime, float maxSpeed, float deltaTime);
    static Vector2 Reflect(const Vector2& inDir, const Vector2& inNormal);
    static Vector2 Project(const Vector2& vector, const Vector2& onNormal);
    static Vector2 ProjectOnPlane(const Vector2& vector, const Vector2& planeNormal);
    static float Angle(const Vector2& from, const Vector2& to);
    static float SignedAngle(const Vector2& from, const Vector2& to);
    static float Distance(const Vector2& from, const Vector2& to);
    static Vector2 Max(const Vector2& f, const Vector2& s);
    static Vector2 Min(const Vector2& f, const Vector2& s);

    static Vector2 Up();
    static Vector2 Right();
};