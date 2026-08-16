/**
 * \brief 3 Component Signed Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SIVEC3_HPP
#define ENMA_SIVEC3_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"
#include "sivec2.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(16) sivec3
{
  union
  {
    sint32 _arr[3];
    struct
    {
      sint32 x, y, z;
    };
    struct
    {
      sint32 r, g, b;
    };
  
    SIVEC3_SWIZZLE(sivec3);
  };

  constexpr explicit sivec3(sint32 x, sint32 y, sint32 z = 0);
  constexpr explicit sivec3(sint32 val = 0);
  constexpr explicit sivec3(sint32 x, const sivec2& yz);
  constexpr explicit sivec3(const sivec2& xy, sint32 z);

  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of atleast 3 sint32.
  */
  constexpr explicit sivec3(const sint32* arr);
  
  //constexpr sivec3(const sivec3& v);

  sivec3 operator+(const sivec3& other) const;
  sivec3& operator+=(const sivec3& other);
  sivec3 operator-() const;
  sivec3 operator-(const sivec3& other) const;
  sivec3& operator-=(const sivec3& other);
  sivec3 operator*(const sivec3& other) const;
  sivec3& operator*=(const sivec3& other);
  sivec3 operator*(sint32 val) const;
  sivec3& operator*=(sint32 val);
  sivec3 operator/(const sivec3& other) const;
  sivec3& operator/=(const sivec3& other);
  sivec3 operator/(sint32 val) const;
  sivec3& operator/=(sint32 val);

  flt32 Dot(const sivec3& other) const;
  sivec3 Cross(const sivec3& other) const;
  sint32 Distance(const sivec3& other) const;
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sivec3& v);
  #endif // DEBUG

  /**
  * Shorthand to create a zero vector - sivec2(0)
  * 
  */
  static const sivec3 zero;
  /**
  * Shorthand to create a unit vector - sivec2(1)
  * 
  */
  static const sivec3 one;
  /**
  * Shorthand to create a negative unit vector - sivec2(-1)
  * 
  */
  static const sivec3 neg;

  /**
  * Shorthand to create up vector - sivec3(0, 1, 0)
  * 
  */
  static const sivec3 up;
  /**
  * Shorthand to create down vector - sivec3(0, -1, 0)
  * 
  */
  static const sivec3 down;
  /**
  * Shorthand to create right vector - sivec3(1, 0, 0)
  * 
  */
  static const sivec3 right;
  /**
  * Shorthand to create left vector - sivec3(-1, 0, 0)
  * 
  */
  static const sivec3 left;
  /**
  * Shorthand to create forward vector - sivec3(1, 0, 0)
  * 
  */
  static const sivec3 forward;
  /**
  * Shorthand to create backward vector - sivec3(0, 0, -1)
  * 
  */
  static const sivec3 back;
};

inline flt32 Dot(const sivec3& v1, const sivec3& v2);
inline sivec3 Cross(const sivec3& v1, const sivec3& v2);
inline sint32 Distance(const sivec3& v1, const sivec3& v2);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sivec3::sivec3(sint32 val)
: x(val), y(val), z(val) {}

inline constexpr sivec3::sivec3(sint32 x, sint32 y, sint32 z)
: x(x), y(y), z(z) {}

inline constexpr sivec3::sivec3(sint32 x, const sivec2& yz)
: x(x), y(yz.x), z(yz.y) {}

inline constexpr sivec3::sivec3(const sivec2& xy, sint32 z)
: x(xy.x), y(xy.y), z(z) {}

inline constexpr sivec3::sivec3(const sint32* arr)
: x(arr[0]), y(arr[1]), z(arr[2]) {}

/*
inline constexpr sivec3::sivec3(const sivec3& v)
: x(v.x), y(v.y), z(v.z) {}
*/

inline sivec3 sivec3::operator+(const sivec3& other) const
{
  return sivec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

inline sivec3& sivec3::operator+=(const sivec3& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;

  return *this;
}

inline sivec3 sivec3::operator-() const
{
  return sivec3(-x, -y, -z);
}

inline sivec3 sivec3::operator-(const sivec3& other) const
{
  return sivec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

inline sivec3& sivec3::operator-=(const sivec3& other)
{
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  
  return *this;
}

inline sivec3 sivec3::operator*(const sivec3& other) const
{
  return sivec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

inline sivec3& sivec3::operator*=(const sivec3& other)
{
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;

  return *this;
}

inline sivec3 sivec3::operator*(sint32 val) const
{
  return sivec3(this->x * val, this->y * val, this->z * val);
}

inline sivec3& sivec3::operator*=(sint32 val)
{
  this->x *= val;
  this->y *= val;
  this->z *= val;

  return *this;
}

inline sivec3 sivec3::operator/(const sivec3& other) const
{
  return sivec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

inline sivec3& sivec3::operator/=(const sivec3& other)
{
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;

  return *this;
}

inline sivec3 sivec3::operator/(sint32 val) const
{
  return sivec3(this->x / val, this->y / val, this->z / val);
}

inline sivec3& sivec3::operator/=(sint32 val)
{
  this->x /= val;
  this->y /= val;
  this->z /= val;

  return *this;
}

inline flt32 sivec3::Dot(const sivec3& other) const
{
  return this->x * other.x + this->y * other.y + this->z * other.z;
}

inline flt32 Dot(const sivec3& v1, const sivec3& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}	

inline sivec3 sivec3::Cross(const sivec3& other) const
{
  return sivec3(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
}

inline sivec3 Cross(const sivec3& v1, const sivec3& v2)
{
  return sivec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

// Maybe Removed
inline sint32 sivec3::Distance(const sivec3& other) const
{
  const flt32 xt = this->x - other.x;
  const flt32 yt = this->y - other.y;
  const flt32 zt = this->z - other.z;

  return sqrt(xt * xt + yt * yt + zt * zt);
}

// Maybe Removed
inline sint32 Distance(const sivec3& v1, const sivec3& v2)
{
  const flt32 xt = v1.x - v2.x;
  const flt32 yt = v1.y - v2.y;
  const flt32 zt = v1.z - v2.z;

  return sqrt(xt * xt + yt * yt + zt * zt);
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sivec3& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";
  return os;
}
#endif // DEBUG

inline constexpr sivec3 sivec3::zero 		= sivec3(0, 0, 0);
inline constexpr sivec3 sivec3::one 	  = sivec3(1, 1, 1);
inline constexpr sivec3 sivec3::neg     = sivec3(-1, -1, -1);

inline constexpr sivec3 sivec3::up 		  = sivec3(0, 1, 0);
inline constexpr sivec3 sivec3::down 		= sivec3(0, -1, 0);
inline constexpr sivec3 sivec3::right   = sivec3(1, 0, 0);
inline constexpr sivec3 sivec3::left 		= sivec3(-1, 0, 0);
inline constexpr sivec3 sivec3::forward = sivec3(0, 0, 1);
inline constexpr sivec3 sivec3::back 		= sivec3(0, 0, -1);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SIVEC3_HPP