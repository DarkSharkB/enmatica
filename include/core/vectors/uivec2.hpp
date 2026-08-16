/**
 * \brief 2 Component Unsigned Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_UIVEC2_HPP
#define ENMA_UIVEC2_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(8) uivec2
{
  union
  {
    uint32 _arr[2];
    struct 
    {
      uint32 x, y;
    };
    struct 
    {
      uint32 r, g;
    };

    UIVEC2_SWIZZLE(uivec2);
  };

  constexpr explicit uivec2(uint32 val = 0U);
  constexpr explicit uivec2(uint32 x, uint32 y);

  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of atleast 2 uint32.
  */
  constexpr explicit uivec2(const uint32* arr);
  
  //constexpr uivec2(const uivec2& v);

  uivec2 operator+(const uivec2& other) const;
  uivec2& operator+=(const uivec2& other);
  uivec2 operator-() const;
  uivec2 operator-(const uivec2& other) const;
  uivec2& operator-=(const uivec2& other);
  uivec2 operator*(const uivec2& other) const;
  uivec2& operator*=(const uivec2& other);
  uivec2 operator*(uint32 val) const;
  uivec2& operator*=(uint32 val);
  uivec2 operator/(const uivec2& other) const;
  uivec2& operator/=(const uivec2& other);
  uivec2 operator/(uint32 val) const;
  uivec2& operator/=(uint32 val);

  uint32 Dot(const uivec2& other) const;
  uint32 Cross(const uivec2& other) const;
  uint32 Distance(const uivec2& other) const;

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const uivec2& vec);
  #endif // DEBUG

  /**
  * \brief Shorthand to create a zero vector - uivec2(0, 0)
  * 
  */
  static const uivec2 zero;

  /**
  * \brief Shorthand to create a unit vector - uivec2(1, 1)
  * 
  */
  static const uivec2 one;
};

inline uint32 Dot(const uivec2& v1, const uivec2& v2);
inline uint32 Cross(const uivec2& v1, const uivec2& v2);
inline uint32 Distance(const uivec2& v1, const uivec2& v2);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr uivec2::uivec2(uint32 val)
: x(val), y(val) {}

inline constexpr uivec2::uivec2(uint32 x, uint32 y)
: x(x), y(y) {}

inline constexpr uivec2::uivec2(const uint32* arr)
: x(arr[0]), y(arr[1]) {}

/*
inline constexpr uivec2::uivec2(const uivec2& v)
: x(v.x), y(v.y) {}
*/

inline uivec2 uivec2::operator+(const uivec2& other) const
{
  return uivec2(this->x + other.x, this->y + other.y);
}

inline uivec2& uivec2::operator+=(const uivec2& other)
{
  this->x += other.x;
  this->y += other.y;

  return *this;
}

inline uivec2 uivec2::operator-() const
{
  return uivec2(-x, -y);
}

inline uivec2 uivec2::operator-(const uivec2& other) const
{
  return uivec2(this->x - other.x, this->y - other.y);
}

inline uivec2& uivec2::operator-=(const uivec2& other)
{
  this->x -= other.x;
  this->y -= other.y;

  return *this;
}

inline uivec2 uivec2::operator*(const uivec2& other) const
{
  return uivec2(this->x * other.x, this->y * other.y);
}

inline uivec2& uivec2::operator*=(const uivec2& other)
{
  this->x *= other.x;
  this->y *= other.y;

  return *this;
}

inline uivec2 uivec2::operator*(uint32 val) const
{
  return uivec2(this->x * val, this->y * val);
}

inline uivec2& uivec2::operator*=(uint32 val)
{
  this->x *= val;
  this->y *= val;

  return *this;
}

inline uivec2 uivec2::operator/(const uivec2& other) const
{

  return uivec2(this->x / other.x, this->y / other.y);
}

inline uivec2& uivec2::operator/=(const uivec2& other)
{
  this->x /= other.x;
  this->y /= other.y;

  return *this;
}

inline uivec2 uivec2::operator/(uint32 val) const
{

  return uivec2(this->x / val, this->y / val);
}

inline uivec2& uivec2::operator/=(uint32 val)
{

  this->x *= val;
  this->y *= val;

  return *this;
}

inline uint32 uivec2::Dot(const uivec2& other) const
{
  return this->x * other.x + this->y * other.y;
}

inline uint32 Dot(const uivec2& v1, const uivec2& v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

// Returns the z-component of 2D cross product of the vector
inline uint32 uivec2::Cross(const uivec2& other) const
{
  return this->x * other.y - other.x * this->y;
}

// Returns the z-component of 2D cross product of the vector
inline uint32 Cross(const uivec2& v1, const uivec2& v2)
{
  return v1.x * v2.y - v2.x * v1.y;
}

// Maybe Removed
inline uint32 uivec2::Distance(const uivec2& other) const
{
  const uint32 xt = this->x - other.x;
  const uint32 yt = this->y - other.y;

  return sqrt(xt * xt + yt * yt);
}

// Maybe Removed
inline uint32 Distance(const uivec2& v1, const uivec2& v2)
{
  const uint32 xt = v1.x - v2.x;
  const uint32 yt = v1.y - v2.y;

  return sqrt(xt * xt + yt * yt);
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const uivec2& vec)
{
  os << "( X: " << vec.x << "\tY: "<< vec.y << " )";
  return os;
}
#endif // DEBUG

inline constexpr uivec2 uivec2::zero  = uivec2(0u, 0u);
inline constexpr uivec2 uivec2::one   = uivec2(1u, 1u);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_UIVEC2_HPP