/** Single Precision Floating-Point Quaternions
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFQUAT_HPP
#define ENMA_SFQUAT_HPP

#include "base.hpp"
#include "types.hpp"
#include "trignometry.hpp"
#include "core/vectors/sfvec3.hpp"
#include "core/matrices/sfmat4x4.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(16) sfquat
{
  union
  {
    flt32 _arr[4];
    struct 
    {
      flt32 w, x, y, z;
    };
  };

  constexpr explicit sfquat(flt32 val = 0.0f);
  constexpr explicit sfquat(flt32 w, flt32 x, flt32 y = 0.0f, flt32 z = 0.0f);
  constexpr explicit sfquat(flt32 w, const sfvec3& xyz);
  
  //constexpr sfquat(const sfquat& q);
  
  sfquat operator+(const sfquat& other) const;
  sfquat& operator+=(const sfquat& other);
  sfquat operator-() const;
  sfquat operator-(const sfquat& other) const;
  sfquat& operator-=(const sfquat& other);
  sfquat operator*(const sfquat& other) const;
  sfquat operator*(flt32 val) const;
  sfquat& operator*=(flt32 val);
  sfquat operator/(flt32 val) const;
  sfquat& operator/=(flt32 val);

  flt32 Dot(const sfquat& other) const;
  sfquat Conjugate() const;
  sfquat Normalise() const;
  sfquat Inverse() const;

  sfvec3 ToEulerAngles() const;

  friend sfvec3 operator*(const sfvec3& v, const sfquat& q);

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfquat& q);
  #endif // DEBUG
};

inline flt32 Dot(const sfquat& qt1, const sfquat& qt2);
inline sfquat Conjugate(const sfquat& q);
inline sfquat Normalise(const sfquat& q);
inline sfquat Inverse(const sfquat& q);

//inline sfquat Rotate(const flt32 angle, const sfvec3& axis);
inline sfmat4x4 Rotate(const sfquat& q);
inline sfvec3 ToEulerAngles(const sfquat& q);
inline sfquat ToQuaternion(const sfvec3& eulerAngles);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfquat::sfquat(flt32 val)
: w(1.0f), x(val), y(val), z(val) {}

inline constexpr sfquat::sfquat(flt32 w, flt32 x, flt32 y, flt32 z)
: w(w), x(x), y(y), z(z) {}

inline constexpr sfquat::sfquat(flt32 w, const sfvec3& xyz)
: w(w), x(xyz.x), y(xyz.y), z(xyz.z) {}

inline sfquat sfquat::operator+(const sfquat& other) const
{
  return sfquat(this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z);
}

/*
inline constexpr sfquat::sfquat(const sfquat& q)
: w(q.w), x(q.x), y(q.y), z(q.z) {}
*/

inline sfquat& sfquat::operator+=(const sfquat& other)
{
  this->w += other.w;
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;

  return *this;
}

inline sfquat sfquat::operator-() const
{
  return sfquat(-w, -x, -y, -z);
}

inline sfquat sfquat::operator-(const sfquat& other) const
{
  return sfquat(this->w - other.w, this->x - other.x, this->y - other.y, this->z - other.z);
}

inline sfquat& sfquat::operator-=(const sfquat& other)
{
  this->w -= other.w;
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;

  return *this;
}

inline sfquat sfquat::operator*(const sfquat& other) const
{
  return sfquat
  {
    this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,
    this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
    this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
    this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w
  };
}

inline sfquat sfquat::operator*(flt32 val) const
{
  return sfquat(w * val, x * val, y * val, z * val);
}

inline sfquat& sfquat::operator*=(flt32 val)
{
  this->w *= val;
  this->x *= val;
  this->y *= val;
  this->z *= val;

  return *this;
}

inline sfquat sfquat::operator/(flt32 val) const
{
  const flt32 div = 1.0f / val;

  return sfquat(w * div, x * div, y * div, z * div);
}

inline sfquat& sfquat::operator/=(flt32 val)
{
  const flt32 div = 1.0f / val;

  this->w *= div;
  this->x *= div;
  this->y *= div;
  this->z *= div;

  return *this;
}

inline flt32 sfquat::Dot(const sfquat& other) const
{
  return this->w * other.w + this->x * other.x + this->y * other.y + this->z * other.z;
}

inline sfquat sfquat::Conjugate() const
{
  return sfquat(this->w, -this->x, -this->y, -this->z);
}

inline sfquat sfquat::Normalise() const
{
  const flt32 mag = std::sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);

  return *this / mag;
}

inline sfquat sfquat::Inverse() const
{
  const flt32 mag = std::sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);

  return Conjugate() / mag;
}

inline sfvec3 sfquat::ToEulerAngles() const
{
  flt32 heading, pitch, bank;
  const flt32 sX = -2.0f * (this->y * this->z - this->w * this->x);
  const flt32 hmX2 = 0.5f - this->x * this->x;

  const flt32 xzPwy = this->x * this->z + this->w * this->y;
  const flt32 y2 = this->y * this->y;
  const flt32 z2 = this->z * this->z;

  if(abs(sX) > 0.9999f)
  {
    pitch = HALF_PI * sX;
    heading = atan2(-xzPwy, 0.5f - y2 - z2);
    bank = 0.0f;
  }
  else
  {
    pitch = asin(sX);
    heading = atan2(xzPwy, hmX2 - y2);
    bank = atan2(this->x * this->y + this->w * this->z, hmX2 - z2);
  }

  auto sanitize = [](flt32 v) -> flt32
  {
    return v + 0.0f;
  };

  #ifdef USE_DEG
  return ToDegrees(sfvec3(sanitize(pitch), sanitize(heading), sanitize(bank)));
  #else
  return sfvec3
  {
    sanitize(pitch), sanitize(heading), sanitize(bank)
  };
  #endif
}

inline flt32 Dot(const sfquat& qt1, const sfquat& qt2)
{
  return qt1.w * qt2.w + qt1.x * qt2.x + qt1.y * qt2.y + qt1.z * qt2.z;
}

inline sfquat Conjugate(const sfquat& q)
{
  return sfquat(q.w, -q.x, -q.y, -q.z);
}

inline sfquat Normalise(const sfquat& q)
{
  const flt32 mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

  return q / mag;
}

inline sfquat Inverse(const sfquat& q)
{
  const flt32 mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

  return Conjugate(q) / mag;
}

/*inline sfquat Rotate(const flt32 angle, const sfvec3& axis)
{
  #ifdef USE_AUTO_DEG
  const flt32 hang = ToRadians(angle) * 0.5f;
  #else
  const flt32 hang = angle * 0.5f;
  #endif
  const flt32 cosha = cos(hang);
  const flt32 sinha = sin(hang);

  return sfquat(cosha, sinha * axis.x, sinha * axis.y, sinha * axis.z);
}*/

inline sfmat4x4 Rotate(const sfquat& q)
{
  const flt32 x2 = q.x * q.x;
  const flt32 y2 = q.y * q.y;
  const flt32 z2 = q.z * q.z;

  const flt32 xy = q.x * q.y;
  const flt32 wz = q.w * q.z;

  const flt32 xz = q.x * q.z;
  const flt32 wy = q.w * q.y;

  const flt32 yz = q.y * q.z;
  const flt32 wx = q.w * q.x;

  return sfmat4x4
  {
    1 - 2 * (y2 + z2),  2 * (xy + wz), 		  2 * (xz - wy), 		  0.0f,
    2 * (xy - wz),		  1 - 2 * (x2 + z2),  2 * (yz + wx), 		  0.0f,
    2 * (xz + wy),		  2 * (yz - wx), 		  1 - 2 * (x2 + y2),  0.0f,
    0.0f, 				      0.0f, 				      0.0f, 				      1.0f
  };
}

inline sfvec3 ToEulerAngles(const sfquat& q)
{
  return q.ToEulerAngles();
}

inline sfquat ToQuaternion(const sfvec3& eulerAngles)
{
  #ifdef USE_DEG
  const sfvec3 heuler = ToRadians(eulerAngles) * 0.5f; 	// A little optimisation, not much
  #else
  const sfvec3 heuler = eulerAngles * 0.5f;
  #endif

  const flt32 cX = cos(heuler.x);
  const flt32 cY = cos(heuler.y);
  const flt32 cZ = cos(heuler.z);

  const flt32 sX = sin(heuler.x);
  const flt32 sY = sin(heuler.y);
  const flt32 sZ = sin(heuler.z);

  return sfquat
  {
    cX * cY * cZ + sX * sY * sZ,
    sX * cY * cZ + cX * sY * sZ,
    cX * sY * cZ - sX * cY * sZ,
    cX * cY * sZ - sX * sY * cZ
  };
}

inline sfvec3 operator*(const sfvec3& v, const sfquat& q)
{
  sfquat p = sfquat(0.0, v);
  sfquat qConj = Conjugate(q);
  sfquat result = q * p * qConj;

  return sfvec3(result.x, result.y, result.z);
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfquat& q)
{
  os << "( W: " << q.w << "\tX: " << q.x << "\tY: " << q.y << "\tZ: " << q.z << " )";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFQUAT_HPP