/** 
 * Trignometry 
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_TRIGNOMETRY_HPP
#define ENMA_TRIGNOMETRY_HPP

#include "base.hpp"
#include "types.hpp"

ENMA_NS_START
constexpr const flt64 PI        = 3.141592653589793;
constexpr const flt64 HALF_PI   = PI * 0.5;
constexpr const flt64 TWO_PI    = PI * 2.0;
constexpr const flt64 TAU       = TWO_PI;

constexpr const flt64 TO_RAD    = 0.0174532925199432957692369076848;
constexpr const flt64 TO_DEG    = 57.295779513082320876798154814105;

/**
* \brief Converts the input angle from degrees to radians
* 
* \tparam _Type The type of the parameter and return value
* \param degrees The input angle in degrees
* \return constexpr const _Type Returns the result of the input angle converted from degrees to radians
*/
template <typename _Type>
constexpr const _Type ToRadians(const _Type& degrees)
{
  return degrees * TO_RAD;
}

/**
* \brief Converts the input angle from radians to degrees
* 
* \tparam _Type The type of the parameter and return value
* \param radians The input angle in radians
* \return constexpr const _Type Returns the result of the input angle converted from radians to degrees
*/
template <typename _Type>
constexpr const _Type ToDegrees(const _Type& radians)
{
  return radians * TO_DEG;
}
ENMA_NS_END

#endif // ENMA_TRIGNOMETRY_HPP