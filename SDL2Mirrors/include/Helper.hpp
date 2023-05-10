
#include <cmath> // for remainder operation

#pragma once
#if __cplusplus >= 202002L
	// C++20 (and later) code
	#define USECPLUSPLUS20FEATURES
	#include <numbers> 
#endif


namespace AngleHelper {
#ifndef USECPLUSPLUS20FEATURES
	constexpr double MY_PI = 3.14159265358979323846;
#endif

double degToRad(const int deg){
	// obtain the radians for 1 deg than mpy by the deg 
#ifdef USECPLUSPLUS20FEATURES
	return ((2 * std::numbers::pi) / 360) * (deg % 360);
#else
	return ((2 * AngleHelper::MY_PI) / 360) * (deg % 360);
#endif
}

double radToDeg(const double rad) {
	// obtain the deg for 1 rad than mutiply by rad
#ifdef USECPLUSPLUS20FEATURES
	return (360 / (2 * std::numbers::pi)) * (rad);
#else
	return (360 / (2 * AngleHelper::MY_PI)) * (rad);
#endif
}


double addDegreesOnAngle(double deg, int degToAdd) {
	double rem = std::remainder(deg, 1);
	return (((int)deg + degToAdd) % 360) + rem;
}

}