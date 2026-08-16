/**
 * \brief 4 Component Signed Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SIVEC4_HPP
#define ENMA_SIVEC4_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"
#include "sivec2.hpp"
#include "sivec3.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(16) sivec4
{
  union 
  {
    sint32 _arr[4];
    struct
    {
      sint32 x, y, z, w;
    };
    struct
    {
      sint32 r, g, b, a;
    };

    SIVEC4_SWIZZLE(sivec4);

    #ifdef USE_SIMD
    __m128i vals;
    #endif
  };

  constexpr explicit sivec4(sint32 x, sint32 y, sint32 z = 0, sint32 w = 0);
  constexpr explicit sivec4(sint32 val = 0);
  constexpr explicit sivec4(const sivec2& xy, const sivec2& zw);
  constexpr explicit sivec4(sint32 x, const sivec3& yzw);
  constexpr explicit sivec4(const sivec3& xyz, sint32 w);

  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of atleast 4 sint32.
  */
  constexpr explicit sivec4(const sint32* arr);
  
  constexpr sivec4(const sivec4& v);
  
  sivec4 operator+(const sivec4& other) const;
  sivec4& operator+=(const sivec4& other);
  sivec4 operator-() const;
  sivec4 operator-(const sivec4& other) const;
  sivec4& operator-=(const sivec4& other);
  sivec4 operator*(const sivec4& other) const;
  sivec4& operator*=(const sivec4& other);
  sivec4 operator*(sint32 val) const;
  sivec4& operator*=(sint32 val);
  sivec4 operator/(const sivec4& other) const;
  sivec4& operator/=(const sivec4& other);
  sivec4 operator/(sint32 val) const;
  sivec4& operator/=(sint32 val);

  sint32 Dot(const sivec4& other) const;
  sint32 Distance(const sivec4& other) const;

  #ifdef USE_SIMD
  sivec4(const __m128i& vals);
  #endif

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sivec4& v);
  #endif // DEBUG
  
  static const sivec4 zero;
  static const sivec4 one;
  static const sivec4 neg;
};

inline sint32 Dot(const sivec4& v1, const sivec4& v2);
inline sint32 Distance(const sivec4& v1, const sivec4& v2);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sivec4::sivec4(sint32 val)
: x(val), y(val), z(val), w(val) {}

inline constexpr sivec4::sivec4(sint32 x, sint32 y, sint32 z, sint32 w)
: x(x), y(y), z(z), w(w) {}

inline constexpr sivec4::sivec4(const sivec2& xy, const sivec2& zw)
: x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}

inline constexpr sivec4::sivec4(sint32 x, const sivec3& yzw)
: x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

inline constexpr sivec4::sivec4(const sivec3& xyz, sint32 w)
: x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

inline constexpr sivec4::sivec4(const sint32* arr)
: x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]) {}

/*
inline constexpr sivec4::sivec4(const sivec4& v)
: x(v.x), y(v.y), z(v.z), w(v.w) {}
*/

#ifdef USE_SIMD
inline sivec4::sivec4(const __m128i& vals)
{
  this->vals = vals;
}
#endif // USE_SIMD

inline sivec4 sivec4::operator+(const sivec4& other) const
{
  return sivec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

inline sivec4& sivec4::operator+=(const sivec4& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  this->w += other.w;

  return *this;
}

inline sivec4 sivec4::operator-() const
{
  return sivec4(-x, -y, -z, -w);
}

inline sivec4 sivec4::operator-(const sivec4& other) const
{
  return sivec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

inline sivec4& sivec4::operator-=(const sivec4& other)
{
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  this->w -= other.w;

  return *this;
}

inline sivec4 sivec4::operator*(const sivec4& other) const
{
  return sivec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
}

inline sivec4& sivec4::operator*=(const sivec4& other)
{
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;
  this->w *= other.w;
  
  return *this;
}

inline sivec4 sivec4::operator*(sint32 val) const
{
  return sivec4(this->x * val, this->y * val, this->z * val, this->w * val);
}

inline sivec4& sivec4::operator*=(sint32 val)
{
  this->x *= val;
  this->y *= val;
  this->z *= val;
  this->w *= val;

  return *this;
}

inline sivec4 sivec4::operator/(const sivec4& other) const
{
  return sivec4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
}

inline sivec4& sivec4::operator/=(const sivec4& other)
{
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;
  this->w /= other.w;

  return *this;
}

inline sivec4 sivec4::operator/(sint32 val) const
{

  return sivec4(this->x / val, this->y / val, this->z / val, this->w / val);
}

inline sivec4& sivec4::operator/=(sint32 val)
{
  this->x /= val;
  this->y /= val;
  this->z /= val;
  this->w /= val;

  return *this;
}

inline sint32 sivec4::Dot(const sivec4& other) const
{
  return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

inline sint32 Dot(const sivec4& v1, const sivec4& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// Maybe Removed
inline sint32 sivec4::Distance(const sivec4& other) const
{
  const flt32 xt = this->x - other.x;
  const flt32 yt = this->y - other.y;
  const flt32 zt = this->z - other.z;
  const flt32 wt = this->w - other.w;

  return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}

// Maybe Removed
inline sint32 Distance(const sivec4& v1, const sivec4& v2)
{
  const flt32 xt = v1.x - v2.x;
  const flt32 yt = v1.y - v2.y;
  const flt32 zt = v1.z - v2.z;
  const flt32 wt = v1.w - v2.w;

  return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sivec4& v)
{
  os << "( X: " << v.x << "\tY: "<< v.y << "\tZ: " << v.z << "\tW: " << v.w << " )";
  return os;
}
#endif // DEBUG

inline constexpr sivec4 sivec4::zero  = sivec4(0, 0, 0, 0);
inline constexpr sivec4 sivec4::one   = sivec4(1, 1, 1, 1);
inline constexpr sivec4 sivec4::neg   = sivec4(-1, -1, -1, -1);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFVEC4_HPP