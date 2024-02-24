#pragma once
#include <cmath>
#include "Mathf.h"

namespace Transitions
{

#pragma region Sine
	float EaseInSine(float x)
	{
		return 1 - cosf((x * Mathf::PI) / 2);
	}
	float EaseOutSine(float x)
	{
		return sinf((x * Mathf::PI) / 2);
	}
	float EaseInOutSine(float x)
	{
		return -(cosf(Mathf::PI * x) - 1) / 2;
	}
#pragma endregion

#pragma region Power
	float EaseInPower(float x, float val)
	{
		return powf(x, val);
	}
	float EaseOutPower(float x, float val)
	{
		return 1 - powf(1 - x, val);
	}
	float EaseInOutPower(float x, float val)
	{
		return x < .5f ?
			powf(2.f, val) / 2.f * powf(x, val) :
			1.f - powf(-2.f * x + 2.f, val) / 2.f;
	}
#pragma endregion

#pragma region Expo
	float EaseInExpo(float x)
	{
		return x == 0. ? 0. : powf(2., 10. * x - 10.);
	}
	float EaseOutExpo(float x)
	{
		return x == 1. ? 1. : 1. - powf(2., -10. * x);
	}
	float EaseInOutExpo(float x)
	{
		return x == 0.
			? 0.
			: x == 1.
			? 1.
			: x < 0.5 ? powf(2., 20. * x - 10.) / 2.
			: (2. - powf(2., -20. * x + 10.)) / 2.;
	}
#pragma endregion

#pragma region Circ
	float EaseInCirc(float x)
	{
		return 1. - sqrtf(1. - powf(x, 2.));
	}
	float EaseOutCirc(float x)
	{
		return sqrtf(1. - powf(x - 1., 2.));
	}
	float EaseInOutCirc(float x)
	{
		return x < 0.5
			? (1. - sqrtf(1. - powf(2. * x, 2.))) / 2.
			: (sqrtf(1. - powf(-2. * x + 2., 2.)) + 1.) / 2.;
	}
#pragma endregion

#pragma region Elastic
	float EaseInElastic(float x)
	{
		return x == 0.
			? 0.
			: x == 1.
			? 1.
			: -powf(2, 10 * x - 10) * sinf((x * 10 - 10.75) * ((2 * Mathf::PI) / 3));
	}
	float EaseOutElastic(float x)
	{
		return x == 0.
			? 0.
			: x == 1.
			? 1.
			: powf(2., -10. * x) * sinf((x * 10. - 0.75) * (2 * Mathf::PI) / 3) + 1.;
	}
	float EaseInOutElastic(float x)
	{
		float c5 = (2 * Mathf::PI) / 4.5;

		return x == 0.
			? 0.
			: x == 1.
			? 1.
			: x < 0.5
			? -(powf(2., 20. * x - 10.) * sinf((20. * x - 11.125) * c5)) / 2.
			: (powf(2., -20. * x + 10.) * sinf((20. * x - 11.125) * c5)) / 2. + 1.;
	}
#pragma endregion

#pragma region Bounce
	//float EaseInBounce(float x)
	//{
	//	return 1 - Transitions::EaseOutBounce(1 - x);
	//}
	float EaseOutBounce(float x)
	{
		float n1 = 7.5625;
		float d1 = 2.75;

		if (x < 1 / d1) {
			return n1 * x * x;
		}
		else if (x < 2 / d1) {
			return n1 * (x -= 1.5 / d1) * x + 0.75;
		}
		else if (x < 2.5 / d1) {
			return n1 * (x -= 2.25 / d1) * x + 0.9375;
		}
		else {
			return n1 * (x -= 2.625 / d1) * x + 0.984375;
		}
	}
	//float EaseInOutBounce(float x)
	//{
	//	return x < 0.5
	//		? (1 - Transitions::EaseOutBounce(1 - 2 * x)) / 2
	//		: (1 + Transitions::EaseOutBounce(2 * x - 1)) / 2;
	//}
#pragma endregion
}