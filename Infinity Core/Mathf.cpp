#include "Mathf.h"

namespace Mathf 
{
	float Abs(float f) { return (f < 0.f) ? -f : f; }
	float Min(float a, float b) { return a < b ? a : b; }
	float Max(float a, float b) { return a > b ? a : b; }
	float Sign(float f) { return f >= 0. ? 1.f : -1.f; }
	float Clamp(float value, float min, float max)
	{
		if (value < min)
			value = min;
		else if (value > max)
			value = max;
		return value;
	}
	float Clamp01(float value)
	{
		if (value < 0.f)
			return 0.f;
		else if (value > 1.f)
			return 1.f;
		else
			return value;
	}
	float ClampAngle(float lfAngle, float lfMin, float lfMax)
	{
		if (lfAngle < -360.f) lfAngle += 360.f;
		if (lfAngle > 360.f) lfAngle -= 360.f;
		return Clamp(lfAngle, lfMin, lfMax);
	}
	float Repeat(float t, float length)
	{
		return Clamp(t - floor(t / length) * length, 0.f, length);
	}
	float Lerp(float a, float b, float t)
	{
		return a + (b - a) * Clamp01(t);
	}
	float LerpUnclamped(float a, float b, float t)
	{
		return a + (b - a) * t;
	}
	float LerpAngle(float a, float b, float t)
	{
		float delta = Repeat((b - a), 360.f);
		if (delta > 180.f)
			delta -= 360.f;
		return a + delta * Clamp01(t);
	}
	float MoveTowards(float current, float target, float maxDelta)
	{
		if (abs(target - current) <= maxDelta)
			return target;
		return current + Sign(target - current) * maxDelta;
	}
	float DeltaAngle(float current, float target)
	{
		float delta = Repeat((target - current), 360.f);
		if (delta > 180.f)
			delta -= 360.f;
		return delta;
	}
	float MoveTowardsAngle(float current, float target, float maxDelta)
	{
		float delAngle = DeltaAngle(current, target);
		if (-maxDelta < delAngle && delAngle < maxDelta)
			return target;
		target = current + delAngle;
		return MoveTowards(current, target, maxDelta);
	}
	float SmoothStep(float from, float to, float t)
	{
		t = Clamp01(t);
		t = -2.f * t * t * t + 3.f * t * t;
		return to * t + from * (1.f - t);
	}
	float Gamma(float value, float absmax, float gamma)
	{
		bool negative = value < 0.f;
		float absval = abs(value);
		if (absval > absmax)
			return negative ? -absval : absval;

		float result = pow(absval / absmax, gamma) * absmax;
		return negative ? -result : result;
	}
	bool Approximately(float a, float b)
	{
		return abs(b - a) < Max(0.000001f * Max(abs(a), abs(b)), Eps * 8);
	}
	float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
	{
		// Based on Game Programming Gems 4 Chapter 1.10
		smoothTime = Max(0.0001f, smoothTime);
		float omega = 2.f / smoothTime;

		float x = omega * deltaTime;
		float exp = 1.f / (1.f + x + 0.48f * x * x + 0.235f * x * x * x);
		float change = current - target;
		float originalTo = target;

		// Clamp maximum speed
		float maxChange = maxSpeed * smoothTime;
		change = Clamp(change, -maxChange, maxChange);
		target = current - change;

		float temp = (currentVelocity + omega * change) * deltaTime;
		currentVelocity = (currentVelocity - omega * temp) * exp;
		float output = target + (change + temp) * exp;

		// Prevent overshooting
		if (originalTo - current > 0.f == output > originalTo)
		{
			output = originalTo;
			currentVelocity = (output - originalTo) / deltaTime;
		}

		return output;
	}
	float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
	{
		target = current + DeltaAngle(current, target);
		return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
	}
	float PingPong(float t, float length)
	{
		t = Repeat(t, length * 2.f);
		return length - abs(t - length);
	}
	float InverseLerp(float a, float b, float value)
	{
		if (a != b)
			return Clamp01((value - a) / (b - a));
		else
			return 0.0f;
	}
}