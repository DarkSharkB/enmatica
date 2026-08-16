/**
 * \brief 4 Component Unsigned Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_UIVEC4_HPP
#define ENMA_UIVEC4_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"
#include "uivec2.hpp"
#include "uivec3.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(16) uivec4
{
  union
  {
    uint32 _arr[4];
    struct
    {
        uint32 x, y, z, w;
    };
    struct 
    {
      uint32 r, g, b, a;
    };
    
    //__m128i_u g;
    UIVEC4_SWIZZLE(uivec4);
  };

  constexpr explicit uivec4(uint32 val = 0U);
  constexpr explicit uivec4(uint32 x, uint32 y, uint32 z = 0U, uint32 w = 0U);
  constexpr explicit uivec4(const uivec2& xy, const uivec2& zw);
  constexpr explicit uivec4(uint32 x, const uivec3& yzw);
  constexpr explicit uivec4(const uivec3& xyz, const uint32 w);

  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of atleast 4 uint32.
  */
  constexpr explicit uivec4(const uint32* arr);
  
  constexpr uivec4(const uivec4& v);

  uivec4 operator+(const uivec4& other) const;
  uivec4& operator+=(const uivec4& other);
  uivec4 operator-() const;
  uivec4 operator-(const uivec4& other) const;
  uivec4& operator-=(const uivec4& other);
  uivec4 operator*(const uivec4& other) const;
  uivec4& operator*=(const uivec4& other);
  uivec4 operator*(uint32 val) const;
  uivec4& operator*=(uint32 val);
  uivec4 operator/(const uivec4& other) const;
  uivec4& operator/=(const uivec4& other);
  uivec4 operator/(uint32 val) const;
  uivec4& operator/=(uint32 val);

  uint32 Dot(const uivec4& other) const;
  uint32 Distance(const uivec4& other) const;

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const uivec4& v);
  #endif // DEBUG

  /**
  * Shorthand to create a zero vector - uivec4(0, 0, 0, 0)
  * 
  */
  static const uivec4 zero;

  /**
  * Shorthand to create a unit vector - uivec4(1, 1, 1, 1)
  * 
  */
  static const uivec4 one;
};

inline uint32 Dot(const uivec4& v1, const uivec4& v2);
inline uint32 Distance(const uivec4& v1, const uivec4& v2);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr uivec4::uivec4(uint32 val)
: x(val), y(val), z(val), w(val) {}

inline constexpr uivec4::uivec4(uint32 x, uint32 y, uint32 z, uint32 w)
: x(x), y(y), z(z), w(w) {}

inline constexpr uivec4::uivec4(const uivec2& xy, const uivec2& zw)
: x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}

inline constexpr uivec4::uivec4(uint32 x, const uivec3& yzw)
: x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

inline constexpr uivec4::uivec4(const uivec3& xyz, uint32 w)
: x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

inline constexpr uivec4::uivec4(const uint32* arr)
: x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]) {}

/*
inline constexpr uivec4::uivec4(const uivec4& v)
: x(v.x), y(v.y), z(v.z), w(v.w) {}
*/

inline uivec4 uivec4::operator+(const uivec4& other) const
{
  return uivec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

inline uivec4& uivec4::operator+=(const uivec4& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  this->w += other.w;

  return *this;
}

inline uivec4 uivec4::operator-() const
{
  return uivec4(-x, -y, -z, -w);
}

inline uivec4 uivec4::operator-(const uivec4& other) const
{
  return uivec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

inline uivec4& uivec4::operator-=(const uivec4& other)
{
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  this->w -= other.w;

  return *this;
}

inline uivec4 uivec4::operator*(const uivec4& other) const
{
  return uivec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
}

inline uivec4& uivec4::operator*=(const uivec4& other)
{
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;
  this->w *= other.w;

  return *this;
}

inline uivec4 uivec4::operator*(uint32 val) const
{
  return uivec4(this->x * val, this->y * val, this->z * val, this->w * val);
}

inline uivec4& uivec4::operator*=(uint32 val)
{
  this->x *= val;
  this->y *= val;
  this->z *= val;
  this->w *= val;

  return *this;
}

inline uivec4 uivec4::operator/(const uivec4& other) const
{
  return uivec4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
}

inline uivec4& uivec4::operator/=(const uivec4& other)
{
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;
  this->w /= other.w;

  return *this;
}

inline uivec4 uivec4::operator/(uint32 val) const
{
  return uivec4(this->x / val, this->y / val, this->z / val, this->w / val);
}

inline uivec4& uivec4::operator/=(uint32 val)
{
  this->x /= val;
  this->y /= val;
  this->z /= val;
  this->w /= val;

  return *this;
}

inline uint32 uivec4::Dot(const uivec4& other) const
{
  return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

inline uint32 Dot(const uivec4& v1, const uivec4& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// Not Tested Yet - Maybe Removed
inline uint32 uivec4::Distance(const uivec4& other) const
{
  const float xt = this->x - other.x;
  const float yt = this->y - other.y;
  const float zt = this->z - other.z;
  const float wt = this->w - other.w;

  return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}

// Not Tested Yet - Maybe Removed
inline uint32 Distance(const uivec4& v1, const uivec4& v2)
{
  const float xt = v1.x - v2.x;
  const float yt = v1.y - v2.y;
  const float zt = v1.z - v2.z;
  const float wt = v1.w - v2.w;

  return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const uivec4& v)
{
  os << "( X: " << v.x << "\tY: "<< v.y << "\tZ: " << v.z << "\tW: " << v.w << " )";
  return os;
}
#endif // DEBUG

inline constexpr uivec4 uivec4::zero  = uivec4(0u, 0u, 0u, 0u);
inline constexpr uivec4 uivec4::one   = uivec4(1u, 1u, 1u, 1u);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_UIVEC4_HPP