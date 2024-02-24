#pragma once

#include "consts.h"
#include <iostream>
#include <limits>
#include <cmath>

namespace Mathf
{
	constexpr float PI = 3.14159265358979323846264338327950288f;
	constexpr float Deg2Rad = (PI * 2.f) / 360.f;
	constexpr float Rad2Deg = 360.f / (PI * 2.f);
	constexpr float Eps = std::numeric_limits<float>::epsilon();

	float	Abs(float f);
	float	Min(float a, float b);
	float	Max(float a, float b);
	float	Sign(float f);
	float	Clamp(float value, float min, float max);
	float	ClampAngle(float lfAngle, float lfMin, float lfMax);
	float	Clamp01(float value);
	float	Repeat(float t, float length);
	float	Lerp(float a, float b, float t);
	float	LerpUnclamped(float a, float b, float t);
	float	LerpAngle(float a, float b, float t);
	float	MoveTowards(float current, float target, float maxDelta);
	float	DeltaAngle(float current, float target);
	float	MoveTowardsAngle(float current, float target, float maxDelta);
	float	SmoothStep(float from, float to, float t);
	float	Gamma(float value, float absmax, float gamma);
	bool	Approximately(float a, float b);
	float	SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
	float	SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
	float	PingPong(float t, float length);
	float	InverseLerp(float a, float b, float value);
}