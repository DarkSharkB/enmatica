/**                          Enmatica Library for Mathematical & Graphical Applications                    
 * @author DarkShark
 * @brief The Main Header file of the Enmatica library
 * @version 0.7.2
 * 
 * @copyright Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "empch.hpp"

#ifndef FORCE_RAD
#define FORCE_DEG
#else
#define FORCE_RAD
#endif

constexpr flt64 pi = 3.141592653589793;

template <typename T>
T Clamp01(T value)
{
    return std::max(static_cast<T>(0), std::min(value, static_cast<T>(1)));
}

template <typename T>
T Clamp(const T value, const T minimum, const T maximum)
{
    return std::max(minimum, std::min(value, maximum));
}

template <typename T>
T Lerp(T a, T b, T t)
{
    return (t * (b - a)) + a;
}

//flt32 BiLerp(flt32 a, flt32 b, flt32 c, flt32)
/**
 * @brief A function that convert degrees to radians
 * 
 * @tparam T The data type of the parameter and return value
 * @param degree The input value in degrees
 * @return Returns the input degrees that is converted to radians
 */
template <typename T>
T ToRadians(T degrees)
{
    return degrees * static_cast<T>(0.01745329251994329576923690768489);
}

/**
 * @brief A function that convert radians to degrees
 * 
 * @tparam T The data type of the parameter and return value
 * @param radian The input value in radians
 * @return Returns the input radians that is converted to degrees
 */
template <typename T>
T ToDegrees(T radians)
{
    return radians * static_cast<T>(57.295779513082320876798154814105);
}

#include "vector.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"