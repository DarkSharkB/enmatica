#pragma once
#include "types.hpp"

constexpr flt64 PI = 3.141592653589793;
constexpr flt64 HALF_PI = 1.57079632679;
constexpr flt64 TWO_PI =  6.28318530718;
constexpr flt64 TAU = TWO_PI;
constexpr flt64 TO_RAD = 0.01745329251994329576923690768489;
constexpr flt64 TO_DEG = 57.295779513082320876798154814105;

/**
 * @brief Convert degrees to radians
 * 
 * @tparam T The type of the parameter and return value
 * @param degrees The input value in degrees
 * @return constexpr T Radians of given degrees
 */
template <typename T>
constexpr T ToRadians(const T& degrees)
{
    return degrees * TO_RAD;
}

/**
 * @brief Convert radians to degrees
 * 
 * @tparam T The type of the parameter and return value
 * @param radians The input value in radians
 * @return constexpr T Returns the input radians that is converted to degrees
 */
template <typename T>
constexpr T ToDegrees(const T& radians)
{
    return radians * TO_DEG;
}