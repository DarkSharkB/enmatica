/**                          Enmatica Library for Mathematical & Graphical Applications                    
 * @author DarkShark
 * @brief The Main Header file of the Enmatica library
 * @version 0.7.5
 * 
 * @copyright Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "empch.hpp"
#include "config.hpp"

#if !defined(USE_ONLY_RAD) && !defined(USE_AUTO_DEG)
#define USE_ONLY_RAD
#endif

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

template <typename T, typename P>
T Lerp(T a, T b, P t)
{
    return (t * (b - a)) + a;
}

//flt32 BiLerp(flt32 a, flt32 b, flt32 c, flt32)

#include "trignometry.hpp"

#include "vector.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"

#include "extensions.hpp"