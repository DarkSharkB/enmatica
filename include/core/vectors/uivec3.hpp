/**
 * \brief 3 Component Unsigned Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_UIVEC3_HPP
#define ENMA_UIVEC3_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"
#include "uivec2.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(16) uivec3
{
  union
  {
    uint32 _arr[3];
    struct
    {
      uint32 x, y, z;
    };
    struct 
    {
      uint32 r, g, b;
    };

    UIVEC3_SWIZZLE(uivec3);
  };

  constexpr explicit uivec3(uint32 val = 0U);
  constexpr explicit uivec3(uint32 x, uint32 y, uint32 z = 0U);
  constexpr explicit uivec3(uint32 x, const uivec2& yz);
  constexpr explicit uivec3(const uivec2& xy, uint32 z);

  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of atleast 3 uint32.
  */
  constexpr explicit uivec3(const uint32* arr);
  
  constexpr uivec3(const uivec3& v);

  uivec3 operator+(const uivec3& other) const;
  uivec3& operator+=(const uivec3& other);
  uivec3 operator-() const;
  uivec3 operator-(const uivec3& other) const;
  uivec3& operator-=(const uivec3& other);
  uivec3 operator*(const uivec3& other) const;
  uivec3& operator*=(const uivec3& other);
  uivec3 operator*(uint32 val) const;
  uivec3& operator*=(uint32 val);
  uivec3 operator/(const uivec3& other) const;
  uivec3& operator/=(const uivec3& other);
  uivec3 operator/(uint32 val) const;
  uivec3& operator/=(uint32 val);

  uint32 Dot(const uivec3& other) const;
  uivec3 Cross(const uivec3& other) const;
  uint32 Distance(const uivec3& other) const;
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const uivec3& v);
  #endif // DEBUG

  /**
  * Shorthand to create a zero vector - uivec3(0, 0, 0)
  * 
  */
  static const uivec3 zero;
  /**
  * Shorthand to create a unit vector - uivec3(1, 1, 1)
  * 
  */
  static const uivec3 one;
};

inline uint32 Dot(const uivec3& v1, const uivec3& v2);
inline uivec3 Cross(const uivec3& v1, const uivec3& v2);
inline uint32 Distance(const uivec3& v1, const uivec3& v2);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr uivec3::uivec3(uint32 val)
: x(val), y(val), z(val) {}

inline constexpr uivec3::uivec3(uint32 x, uint32 y, uint32 z)
: x(x), y(y), z(z) {}

inline constexpr uivec3::uivec3(uint32 x, const uivec2& yz)
: x(x), y(yz.x), z(yz.y) {}

inline constexpr uivec3::uivec3(const uivec2& xy, uint32 z)
: x(xy.x), y(xy.y), z(z) {}

inline constexpr uivec3::uivec3(const uint32* arr)
: x(arr[0]), y(arr[1]), z(arr[2]) {}

/*
inline constexpr uivec3::uivec3(const uivec3& v)
: x(v.x), y(v.y), z(v.z) {}
*/

inline uivec3 uivec3::operator+(const uivec3& other) const
{
  return uivec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

inline uivec3& uivec3::operator+=(const uivec3& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;

  return *this;
}

inline uivec3 uivec3::operator-() const
{
  return uivec3(-x, -y, -z);
}

inline uivec3 uivec3::operator-(const uivec3& other) const
{
  return uivec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

inline uivec3& uivec3::operator-=(const uivec3& other)
{
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  
  return *this;
}

inline uivec3 uivec3::operator*(const uivec3& other) const
{
  return uivec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

inline uivec3& uivec3::operator*=(const uivec3& other)
{
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;

  return *this;
}

inline uivec3 uivec3::operator*(uint32 val) const
{
  return uivec3(this->x * val, this->y * val, this->z * val);
}

inline uivec3& uivec3::operator*=(uint32 val)
{
  this->x *= val;
  this->y *= val;
  this->z *= val;

  return *this;
}

inline uivec3 uivec3::operator/(const uivec3& other) const
{
  return uivec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

inline uivec3& uivec3::operator/=(const uivec3& other)
{
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;

  return *this;
}

inline uivec3 uivec3::operator/(uint32 val) const
{
  return uivec3(this->x / val, this->y / val, this->z / val);
}

inline uivec3& uivec3::operator/=(uint32 val)
{
  this->x /= val;
  this->y /= val;
  this->z /= val;

  return *this;
}

inline uint32 uivec3::Dot(const uivec3& other) const
{
  return this->x * other.x + this->y * other.y + this->z * other.z;
}

inline uint32 Dot(const uivec3& v1, const uivec3& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}	

inline uivec3 uivec3::Cross(const uivec3& other) const
{
  return uivec3(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
}

inline uivec3 Cross(const uivec3& v1, const uivec3& v2)
{
  return uivec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

// Maybe Removed
inline uint32 uivec3::Distance(const uivec3& other) const
{
  const float xt = this->x - other.x;
  const float yt = this->y - other.y;
  const float zt = this->z - other.z;

  return sqrt(xt * xt + yt * yt + zt * zt);
}

// Note: Maybe Removed
inline uint32 Distance(const uivec3& v1, const uivec3& v2)
{
  const float xt = v1.x - v2.x;
  const float yt = v1.y - v2.y;
  const float zt = v1.z - v2.z;

  return sqrt(xt * xt + yt * yt + zt * zt);
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const uivec3& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";

  return os;
}
#endif // DEBUG

inline constexpr uivec3 uivec3::zero  = uivec3(0u, 0u, 0u);
inline constexpr uivec3 uivec3::one   = uivec3(1u, 1u, 1u);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_UIVEC3_HPP