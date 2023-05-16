#pragma once
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

double degToRad(const double deg){
	// obtain the radians for 1 deg than mpy by the deg 
	double rem = std::remainder(deg, 1);
	int angle = (((int)deg) % 360);
#ifdef USECPLUSPLUS20FEATURES
	return ((2 * std::numbers::pi) / 360) * (angle + rem);
#else
	return ((2 * AngleHelper::MY_PI) / 360) * (angle + rem);
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
	int angle = (((int)deg + degToAdd) % 360);
	if (angle < 0) {
		return 360 + angle + rem;
	}
	return angle + rem;
}


// reflect an angle that hits a top side for example a line
constexpr inline double reflectAngleTop(double inputAngle) noexcept {
	if (inputAngle > 0 && inputAngle < 90) {
		return 180 - inputAngle;
	}
	else { // between 270 and 360
		//180 - angle
		return AngleHelper::addDegreesOnAngle(-inputAngle, 180);
	}

}

constexpr inline double reflectAngleRight(double inputAngle) {
	//if (inputAngle > 0 && inputAngle < 90) {
	//	return 360 - inputAngle;
	//}
	//else { // between 270 and 360
	//	return 360 - inputAngle;
	//}
	return 360 - inputAngle;
}

constexpr inline double reflectAngleBot(double inputAngle) {
	if (inputAngle> 90 && inputAngle< 180) {
		return 180 - inputAngle;
	}
	else { // between 180 and 270
		//reflectedAngle = -180 + startHitLine.angle;
		return 270 + (270 - inputAngle);
	}
}

constexpr inline double reflectAngleLeft(double inputAngle) {
	if (inputAngle > 180 && inputAngle < 270) {
		// 360 - angle
		return AngleHelper::addDegreesOnAngle(-inputAngle, 360);
	}
	else { // between 270 and 360
		return 360 - inputAngle;
	}
}

}