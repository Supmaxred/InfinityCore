#include <cmath>
#include <stdexcept>
#include <string>
#include <iostream>

#include "vector2.h"
#include "Mathf.h"
#include "consts.h"

Vector2::Vector2(const Vector2& vec) {
    x = vec.x;
    y = vec.y;
}
Vector2::Vector2(const sf::Vector2f& vec) {
    x = vec.x;
    y = vec.y;
}
Vector2::Vector2(const sf::Vector2i& vec) {
    x = vec.x;
    y = vec.y;
}
Vector2::Vector2(float _x, float _y) {
    x = _x;
    y = _y;
}
Vector2::Vector2(float _a) {
    x = _a;
    y = _a;
}
Vector2& Vector2::operator=(const sf::Vector2f& vec)
{
    *this = Vector2(vec.x, vec.y);
    return *this;
}
Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}
bool Vector2::operator==(const Vector2& vec) const {
    return (*this - vec).SqrMagnitude() < Mathf::Eps;
}
bool Vector2::operator!=(const Vector2& vec) const {
    return !(*this == vec);
}
Vector2 Vector2::operator+(const Vector2& vec) const {
    return Vector2(x + vec.x, y + vec.y);
}
Vector2 Vector2::operator-(const Vector2& vec) const {
    return *this + -vec;
}
Vector2 Vector2::operator*(const Vector2& vec) const {
    return Vector2(x * vec.x, y * vec.y);
}
Vector2 Vector2::operator/(const Vector2& vec) const {
    return Vector2(x / vec.x, y / vec.y);
}
Vector2 Vector2::operator+(float number) const {
    return Vector2(x + number, y + number);
}
Vector2 Vector2::operator-(float number) const {
    return Vector2(x - number, y - number);
}
Vector2 Vector2::operator*(float number) const {
    return Vector2(x * number, y * number);
}
Vector2 Vector2::operator/(float number) const {
    if (std::abs(number) > Mathf::Eps) {
        return *this * (1.f / number);
    }
    else {
        throw std::domain_error{ "vector2::operator/(float number): division by zero" };
    }
}
Vector2::operator sf::Vector2f() const {
    return sf::Vector2f(x, y);
}
float Vector2::Dot(const Vector2& vec) const {
    return vec.x * x + vec.y * y;
}
float Vector2::SqrMagnitude() const {
    return x * x + y * y;
}
float Vector2::Magnitude() const {
    return ::sqrt(x * x + y * y);
}
Vector2 Vector2::Normalized() const {
    float mag = Magnitude();
    if (mag > Mathf::Eps) {
        return *this / mag;
    }
    else {
        return Vector2(0.f);
    }
}
Vector2 Vector2::ClampMagnitude(float maxMag) const {
    float sqrmag = this->Magnitude();
    if (sqrmag > maxMag)
    {
        return this->SetMagnitude(maxMag);
    }
    return *this;
}
Vector2 Vector2::SetMagnitude(float mag) const {
    return this->Normalized() * mag;
}
sf::Vector2f Vector2::SFML() const
{
    return sf::Vector2f(this->x, this->y);
}
std::string Vector2::ToString() const
{
    return '(' + std::to_string(this->x) + ';' + std::to_string(this->y) + ')';
}
Vector2 Vector2::Perpendicular() const
{
    return Vector2(-this->y, this->x);
}
Vector2 Vector2::Lerp(const Vector2& current, const Vector2& target, float time)
{
    float t = Mathf::Clamp01(time);
    return Vector2(
        current.x + (target.x - current.x) * t,
        current.y + (target.y - current.y) * t
    );
}
Vector2 Vector2::LerpUnclamped(const Vector2& current, const Vector2& target, float time)
{
    return Vector2(
        current.x + (target.x - current.x) * time,
        current.y + (target.y - current.y) * time
    );
}
Vector2 Vector2::LerpMag(const Vector2& current, const Vector2& target, float time)
{
    return current.SetMagnitude(Mathf::Lerp(current.Magnitude(), target.Magnitude(), time));
}
Vector2 Vector2::LerpMagUnclamped(const Vector2& current, const Vector2& target, float time)
{
    return current.SetMagnitude(Mathf::LerpUnclamped(current.Magnitude(), target.Magnitude(), time));
}
Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float maxDelta)
{
    // avoid vector ops because current scripting backends are terrible at inlining
    float toVector_x = target.x - current.x;
    float toVector_y = target.y - current.y;
    Vector2 toVector = Vector2(
        target.x - current.x,
        target.y - current.y
    );

    float sqdist = toVector.x * toVector.x + toVector.y * toVector.y;

    if (sqdist == 0.f || (maxDelta >= 0.f && sqdist <= maxDelta * maxDelta))
        return target;
    float dist = ::sqrt(sqdist);

    return Vector2(current.x + toVector_x / dist * maxDelta,
        current.y + toVector_y / dist * maxDelta);
}
Vector2 Vector2::SmoothDamp(const Vector2& current, Vector2& target, Vector2& currentVel, float smoothTime, float maxSpeed, float deltaTime)
{
    //float output_x = 0;
    //float output_y = 0;
    //float output_z = 0;
    Vector2 output = Vector2(0.f);

    // Based on Unity CSReference
    smoothTime = Mathf::Max(0.0001f, smoothTime);
    float omega = 2.f / smoothTime;

    float x = omega * deltaTime;
    //float exp = 1 / (1 + x + 0.48 * x * x + 0.235 * x * x * x);
    float expv = exp(x);

    //float change_x = current.x - target.x;
    //float change_y = current.y - target.y;
    //float change_z = current.z - target.z;
    Vector2 change = current - target;
    Vector2 originalTo = target;

    // Clamp maximum speed
    float maxChange = maxSpeed * smoothTime;

    float maxChangeSq = maxChange * maxChange;
    float sqrmag = change.SqrMagnitude();
    if (sqrmag > maxChangeSq)
    {
        //float mag = ::sqrt(sqrmag);
        //change_x = change_x / mag * maxChange;
        //change_y = change_y / mag * maxChange;
        //change_z = change_z / mag * maxChange;
        change = change.Normalized() * maxChange;
    }

    //target.x = current.x - change_x;
    //target.y = current.y - change_y;
    //target.z = current.z - change_z;
    target = current - change;

    //float temp_x = (currentVelocity.x + omega * change_x) * deltaTime;
    //float temp_y = (currentVelocity.y + omega * change_y) * deltaTime;
    //float temp_z = (currentVelocity.z + omega * change_z) * deltaTime;
    Vector2 temp = (currentVel + change * omega) * deltaTime;

    //currentVelocity.x = (currentVelocity.x - omega * temp_x) * exp;
    //currentVelocity.y = (currentVelocity.y - omega * temp_y) * exp;
    //currentVelocity.z = (currentVelocity.z - omega * temp_z) * exp;
    currentVel = (currentVel - temp * omega) * expv;

    //output_x = target.x + (change_x + temp_x) * exp;
    //output_y = target.y + (change_y + temp_y) * exp;
    //output_z = target.z + (change_z + temp_z) * exp;
    output = target + (change + temp) * expv;

    // Prevent overshooting
    //float origMinusCurrent_x = originalTo.x - current.x;
    //float origMinusCurrent_y = originalTo.y - current.y;
    //float origMinusCurrent_z = originalTo.z - current.z;
    //float outMinusOrig_x = output_x - originalTo.x;
    //float outMinusOrig_y = output_y - originalTo.y;
    //float outMinusOrig_z = output_z - originalTo.z;
    Vector2 origMinusCurrent = originalTo - current;
    Vector2 outMinusOrig = output - originalTo;

    //if (origMinusCurrent_x * outMinusOrig_x + origMinusCurrent_y * outMinusOrig_y + origMinusCurrent_z * outMinusOrig_z > 0)
    if (origMinusCurrent.Dot(outMinusOrig) > 0.f)
    {
        //output_x = originalTo.x;
        //output_y = originalTo.y;
        //output_z = originalTo.z;
        output = originalTo;

        //currentVelocity.x = (output_x - originalTo.x) / deltaTime;
        //currentVelocity.y = (output_y - originalTo.y) / deltaTime;
        //currentVelocity.z = (output_z - originalTo.z) / deltaTime;
        currentVel = (output - originalTo) / deltaTime;
    }

    return output;
}
Vector2 Vector2::Reflect(const Vector2& inDir, const Vector2& inNormal)
{
    float factor = -2.f * inNormal.Dot(inDir);
    return inNormal * factor + inDir;
}
Vector2 Vector2::Project(const Vector2& vector, const Vector2& onNormal)
{
    float sqrMag = onNormal.SqrMagnitude();
    return sqrMag < Mathf::Eps ? Vector2(0) : onNormal * vector.Dot(onNormal) / sqrMag;
}
Vector2 Vector2::ProjectOnPlane(const Vector2& vector, const Vector2& planeNormal)
{
    float sqrMag = planeNormal.SqrMagnitude();
    return sqrMag < Mathf::Eps ? vector : vector - planeNormal * vector.Dot(planeNormal) / sqrMag;
}
float Vector2::Angle(const Vector2& from, const Vector2& to)
{
    float denominator = sqrt(from.SqrMagnitude() * to.SqrMagnitude());
    if (denominator < Mathf::Eps)
        return 0.;

    float dot = Mathf::Clamp(from.Dot(to) / denominator, -1.f, 1.f);
    return (acos(dot)) * Mathf::Rad2Deg;
}
float Vector2::SignedAngle(const Vector2& from, const Vector2& to)
{
    float unsignedAngle = Angle(from, to);

    float sign = Mathf::Sign(from.x * to.y - from.y * to.x);
    return unsignedAngle * sign;
}
float Vector2::Distance(const Vector2& from, const Vector2& to)
{
    return (from - to).Magnitude();
}
Vector2 Vector2::Max(const Vector2& f, const Vector2& s)
{
    return Vector2(Mathf::Max(f.x, s.x), Mathf::Max(f.y, s.y));
}
Vector2 Vector2::Min(const Vector2& f, const Vector2& s)
{
    return Vector2(Mathf::Min(f.x, s.x), Mathf::Min(f.y, s.y));
}

Vector2 Vector2::Up()
{
    return Vector2(0, 1);
}

Vector2 Vector2::Right()
{
    return Vector2(1, 0);
}