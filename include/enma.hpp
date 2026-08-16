/** 
 * \brief              Enmatica
 *        Mathematics Library For High Performance
 *         Computation & Graphical Applications
 *
 * \note      The header file of the Enmatica library
 * \version   0.85.4
 * 
 * \copyright Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_HPP
#define ENMA_HPP

#include "config.hpp" // IWYU pragma: keep
#include "base.hpp"

#if !defined(USE_ONLY_RAD) && !defined(USE_AUTO_DEG)
#define USE_ONLY_RAD
#endif

ENMA_NS_START

/**
 * \brief Returns the larger of two values.
 * 
 * \tparam _Type The type of the values being compared.
 * \param a The first value.
 * \param b The second value.
 * \return  The larger of \param a and \param b.
 *
 * \note If \param a and \param b compare equal, then \param a is returned.
 */
template <typename _Type>
constexpr _Type Max(_Type a, _Type b)
{
  return a >= b ? a : b;
}

template <typename _Type, typename _Compare>
constexpr const _Type& Max(const _Type& a, const _Type& b, _Compare compare)
{
  return compare(a, b) ? a : b;
}

/**
 * \brief Returns the smaller of two values.
 * 
 * \tparam _Type The type of the values being compared.
 * \param a The first value.
 * \param b The second value.
 * \return  The smaller of \param a and \param b.
 *
 * \note If \param a and \param b compare equal, then \param a is returned.
 */
template <typename _Type>
constexpr _Type Min(_Type a, _Type b)
{
  return a <= b ? a : b;
}

template <typename _Type, typename _Compare>
constexpr const _Type& Min(const _Type& a, const _Type& b, _Compare compare)
{
  return compare(a, b) ? a : b;
}

 /**
 * \brief Clamps a value to the range [0, 1].
 *
 * \tparam _Type The type of the value.
 * \param value The value to clamp.
 * \return The value clamped to the range [0, 1].
 */
template <typename _Type>
constexpr _Type Clamp01(const _Type& value)
{
  return Max(static_cast<_Type>(0), Min(value, static_cast<_Type>(1)));
}

/**
 * \brief Clamps a value to the range [minimum, maximum].
 *
 * \tparam _Type The type of the value.
 * \param value  The value to clamp.
 * \param minimum The minimum value of clamp range.
 * \param maximum The maximum value of clamp range.
 * \return The value clamped to the range [ \param minimum, \param maximum ].
 */
template <typename _Type>
constexpr _Type Clamp(const _Type& value, const _Type& minimum, const _Type& maximum)
{
  return Max(minimum, Min(value, maximum));
}

/**
 * \brief Linearly interpolates values between two values based on \param t
 * 
 * \tparam _ValueType Type of the interpolated values
 * \tparam _InterpolantType Type of the interpolatant value
 * \param a First interpolated value 
 * \param b Second interpolated value
 * \param t Interpolant value
 * \return The resultant value of interpolation between \param a and \param b using \param t
 */
template <typename _ValueType, typename _InterpolantType>
constexpr _ValueType Lerp(const _ValueType& a, const _ValueType& b, const _InterpolantType& t)
{
  return (t * (b - a)) + a;
}
ENMA_NS_END

#include "trignometry.hpp"    // IWYU pragma: export

#include "vector.hpp"         // IWYU pragma: export
#include "matrix.hpp"         // IWYU pragma: export
#include "quaternion.hpp"     // IWYU pragma: export

#include "extensions.hpp"     // IWYU pragma: export

#endif // ENMA_HPP