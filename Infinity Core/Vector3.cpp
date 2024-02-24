#include <cmath>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Vector3.h"
#include "Mathf.h"
#include "consts.h"

Vector3::Vector3(const Vector3& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}
Vector3::Vector3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}
Vector3::Vector3(float _a) {
    x = _a;
    y = _a;
    z = _a;
}
Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}
bool Vector3::operator==(const Vector3& vec) const {
    return (*this - vec).SqrMagnitude() < Mathf::Eps;
}
bool Vector3::operator!=(const Vector3& vec) const {
    return !(*this == vec);
}
Vector3 Vector3::operator+(const Vector3& vec) const {
    return Vector3(x + vec.x, y + vec.y, z + vec.z);
}
Vector3 Vector3::operator-(const Vector3& vec) const {
    return *this + -vec;
}
Vector3 Vector3::operator*(const Vector3& vec) const {
    return Vector3(x * vec.x, y * vec.y, z * vec.z);
}
Vector3 Vector3::operator/(const Vector3& vec) const {
    return Vector3(x / vec.x, y / vec.y, z / vec.z);
}
Vector3 Vector3::operator+(float number) const {
    return Vector3(x + number, y + number, z + number);
}
Vector3 Vector3::operator-(float number) const {
    return Vector3(x - number, y - number, z - number);
}
Vector3 Vector3::operator*(float number) const {
    return Vector3(x * number, y * number, z * number);
}
Vector3 Vector3::operator/(float number) const {
    if (std::abs(number) > Mathf::Eps) {
        return *this * (1.0f / number);
    }
    else {
        throw std::domain_error{ "vector3::operator/(float number): division by zero" };
    }
}
float Vector3::Dot(const Vector3& vec) const {
    return vec.x * x + vec.y * y + vec.z * z;
}
Vector3 Vector3::Cross(const Vector3& vec) const {
    return Vector3{vec.y * z - vec.z * y,
                   vec.z * x - vec.x * z,
                   vec.x * y - vec.y * x};
}
float Vector3::SqrMagnitude() const {
    return x * x + y * y + z * z;
}
float Vector3::Magnitude() const {
    return ::sqrt(x * x + y * y + z * z);
}
Vector3 Vector3::Nomalized() const {
    float mag = Magnitude();
    if (mag > Mathf::Eps) {
        return *this / mag;
    }
    else {
        return Vector3(0);
    }
}
Vector3 Vector3::ClampMagnitude(float maxMag) const {
    float mag = this->Magnitude();
    if (mag > maxMag)
    {
        return this->SetMagnitude(maxMag);
    }
    return *this;
}
Vector3 Vector3::SetMagnitude(float mag) const {
    return this->Nomalized() * mag;
}
sf::Vector3f Vector3::SFML() const
{
    return sf::Vector3f(x, y, z);
}
std::string Vector3::ToString() const
{
    return '(' + std::to_string(x) + ';' + std::to_string(y) + ';' + std::to_string(z) + ')';
}
Vector3 Vector3::Lerp(const Vector3& current, const Vector3& target, float time)
{
    float t = Mathf::Clamp01(time);
    return Vector3(
        current.x + (target.x - current.x) * t,
        current.y + (target.y - current.y) * t,
        current.z + (target.z - current.z) * t
        );
}
Vector3 Vector3::LerpUnclamped(const Vector3& current, const Vector3& target, float time)
{
    float t = time;
    return Vector3(
        current.x + (target.x - current.x) * t,
        current.y + (target.y - current.y) * t,
        current.z + (target.z - current.z) * t
    );
}
Vector3 Vector3::LerpMag(const Vector3& current, const Vector3& target, float time)
{
    return current.SetMagnitude(Mathf::Lerp(current.Magnitude(), target.Magnitude(), time));
}
Vector3 Vector3::LerpMagUnclamped(const Vector3& current, const Vector3& target, float time)
{
    return current.SetMagnitude(Mathf::LerpUnclamped(current.Magnitude(), target.Magnitude(), time));
}
Vector3 Vector3::MoveTowards(const Vector3& current, const Vector3& target, float maxDelta)
{
    // avoid vector ops because current scripting backends are terrible at inlining
    float toVector_x = target.x - current.x;
    float toVector_y = target.y - current.y;
    float toVector_z = target.z - current.z;
    Vector3 toVector = Vector3(
        target.x - current.x,
        target.y - current.y,
        target.z - current.z
        );

    float sqdist = toVector.x * toVector.x + toVector.y * toVector.y + toVector.z * toVector.z;

    if (sqdist == 0.f || (maxDelta >= 0.f && sqdist <= maxDelta * maxDelta))
        return target;
    float dist = ::sqrt(sqdist);

    return Vector3(current.x + toVector_x / dist * maxDelta,
        current.y + toVector_y / dist * maxDelta,
        current.z + toVector_z / dist * maxDelta);
}
Vector3 Vector3::SmoothDamp(const Vector3& current, Vector3& target, Vector3& currentVel, float smoothTime, float maxSpeed, float deltaTime)
{
    Vector3 output = Vector3(0.f);

    // Based on Unity CSReference
    smoothTime = Mathf::Max(0.0001f, smoothTime);
    float omega = 2.f / smoothTime;

    float x = omega * deltaTime;
    float exp = ::exp(x);

    Vector3 change = current - target;
    Vector3 originalTo = target;

    float maxChange = maxSpeed * smoothTime;

    float maxChangeSq = maxChange * maxChange;
    float sqrmag = change.SqrMagnitude();
    if (sqrmag > maxChangeSq)
    {
        change = change.Nomalized() * maxChange;
    }
    target = current - change;
    Vector3 temp = (currentVel + change * omega) * deltaTime;
    currentVel = (currentVel - temp * omega) * exp;
    output = target + (change + temp) * exp;

    Vector3 origMinusCurrent = originalTo - current;
    Vector3 outMinusOrig = output - originalTo;

    if(origMinusCurrent.Dot(outMinusOrig) > 0.f)
    {
        output = originalTo;
        currentVel = (output - originalTo) / deltaTime;
    }

    return output;
}
Vector3 Vector3::Reflect(const Vector3& inDir, const Vector3& inNormal)
{
    float factor = -2.f * inNormal.Dot(inDir);
    return inNormal * factor + inDir;
}
Vector3 Vector3::Project(const Vector3& vector, const Vector3& onNormal)
{
    float sqrMag = onNormal.SqrMagnitude();
	return sqrMag < Mathf::Eps ? Vector3(0.f) : onNormal * vector.Dot(onNormal) / sqrMag;
}
Vector3 Vector3::ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal)
{
    float sqrMag = planeNormal.SqrMagnitude();
	return sqrMag < Mathf::Eps ? vector : vector - planeNormal * vector.Dot(planeNormal) / sqrMag;
}
float Vector3::Angle(const Vector3& from, const Vector3& to)
{
    float denominator = ::sqrt(from.SqrMagnitude() * to.SqrMagnitude());
    if (denominator < Mathf::Eps)
        return 0.;

    float dot = Mathf::Clamp(from.Dot(to) / denominator, -1.f, 1.f);
    return (::acos(dot)) * Mathf::Rad2Deg;
}
//fix bug please
float Vector3::SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis)
{
    float unsignedAngle = Angle(from, to);

    Vector3 cross = from.Cross(to);
    float sign = Mathf::Sign(axis.Dot(cross));
    return unsignedAngle * sign;
}
float Vector3::Distance(const Vector3& from, const Vector3& to)
{
    return (from - to).Magnitude();
}
Vector3 Vector3::Max(const Vector3& f, const Vector3& s)
{
    return Vector3(Mathf::Max(f.x, s.x), Mathf::Max(f.y, s.y), Mathf::Max(f.z, s.z));
}
Vector3 Vector3::Min(const Vector3& f, const Vector3& s)
{
    return Vector3(Mathf::Min(f.x, s.x), Mathf::Min(f.y, s.y), Mathf::Min(f.z, s.z));
}