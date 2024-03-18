#pragma once
#include "types.hpp"

const flt64 PI = 3.141592653589793;
const flt64 HALF_PI = 1.57079632679;
const flt64 TWO_PI =  6.28318530718;
const flt64 TAU = TWO_PI;

/**
 * @brief Convert degrees to radians
 * 
 * @tparam T The data type of the parameter and return value
 * @param degrees The input value in degrees
 * @return Radians of given degrees
 */
template <typename T>
T ToRadians(T degrees)
{
    return degrees * static_cast<T>(0.01745329251994329576923690768489);
}

/**
 * @brief Convert radians to degrees
 * 
 * @tparam T The data type of the parameter and return value
 * @param radians The input value in radians
 * @return Returns the input radians that is converted to degrees
 */
template <typename T>
T ToDegrees(T radians)
{
    return radians * static_cast<T>(57.295779513082320876798154814105);
}