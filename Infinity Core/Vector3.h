#pragma once

#include <array>
#include <SFML/System/Vector3.hpp>

class Vector3 final {
public:
    float x, y, z;

    Vector3() = default;

    Vector3(const Vector3& vec);

    explicit Vector3(float x, float y, float z = 0.0f);

    explicit Vector3(float a);

    Vector3& operator=(const Vector3&) = default;
    //vector3& operator=(const vector3&) const = default;

    [[nodiscard]] Vector3 operator-() const;

    // Boolean operations
    bool operator==(const Vector3& vec) const;
    bool operator!=(const Vector3& vec) const;
    
    [[nodiscard]] Vector3 operator+(const Vector3& vec) const;
    [[nodiscard]] Vector3 operator-(const Vector3& vec) const;
    [[nodiscard]] Vector3 operator*(const Vector3& vec) const;
    [[nodiscard]] Vector3 operator/(const Vector3& vec) const;

    // Operations with numbers
    [[nodiscard]] Vector3 operator+(float number) const;
    [[nodiscard]] Vector3 operator-(float number) const;
    [[nodiscard]] Vector3 operator*(float number) const;
    [[nodiscard]] Vector3 operator/(float number) const;

    [[nodiscard]] float Dot(const Vector3& vec) const; // Returns dot product
    [[nodiscard]] Vector3 Cross(const Vector3& vec) const; // Returns cross product
    [[nodiscard]] float SqrMagnitude() const;
    [[nodiscard]] float Magnitude() const;
    [[nodiscard]] Vector3 Nomalized() const;
    [[nodiscard]] Vector3 ClampMagnitude(float maxMag) const;
    [[nodiscard]] Vector3 SetMagnitude(float maxMag) const;
    [[nodiscard]] sf::Vector3f SFML() const;
    [[nodiscard]] std::string ToString() const;

    static Vector3 Lerp(const Vector3& current, const Vector3& target, float time);
    static Vector3 LerpUnclamped(const Vector3& current, const Vector3& target, float time);
    static Vector3 LerpMag(const Vector3& current, const Vector3& target, float time);
    static Vector3 LerpMagUnclamped(const Vector3& current, const Vector3& target, float time);
    static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float maxDelta);
    static Vector3 SmoothDamp(const Vector3& current, Vector3& target, Vector3& currentVel, float smoothTime, float maxSpeed, float deltaTime);
    static Vector3 Reflect(const Vector3& inDir, const Vector3& inNormal);
    static Vector3 Project(const Vector3& vector, const Vector3& onNormal);
    static Vector3 ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal);
    static float Angle(const Vector3& from, const Vector3& to);
    static float SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);
    static float Distance(const Vector3& from, const Vector3& to);
    static Vector3 Max(const Vector3& f, const Vector3& s);
    static Vector3 Min(const Vector3& f, const Vector3& s);
};