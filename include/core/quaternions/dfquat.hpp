/** Double Precision Floating-Point Quaternions
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_DFQUAT_HPP
#define ENMA_DFQUAT_HPP

#include <iostream>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec3.hpp"
#include "core/matrices/sfmat4x4.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(32) dfquat
{
  union
  {
    flt64 _arr[4];
    struct 
    {
      flt64 w, x, y, z;
    };
  };

  constexpr explicit dfquat(flt64 val = 0.0f);
  constexpr explicit dfquat(flt64 w, flt64 x, flt64 y = 0.0f, flt64 z = 0.0f);
  constexpr explicit dfquat(flt64 w, const sfvec3& xyz);
  
  //constexpr dfquat(const dfquat& q);
  
  dfquat operator+(const dfquat& other);
  dfquat& operator+=(const dfquat& other);
  dfquat operator-(const dfquat& other);
  dfquat& operator-=(const dfquat& other);
  dfquat operator*(const dfquat& other);
  dfquat operator*(flt64 val);
  dfquat& operator*=(flt64 val);
  dfquat operator/(flt64 val);
  dfquat& operator/=(flt64 val);

  static dfquat Conjugate(const dfquat& q);
  static dfquat Normalise(dfquat& q);
  static dfquat Inverse(const dfquat& q);
  static dfquat Rotate(flt64 angle, const sfvec3& axis);
  static dfquat ToQuaternion(sfvec3 rot);
  static sfvec3 ToEulerAngles(const dfquat& q);
  static sfmat4 ToRotationMatrix(const dfquat& q);

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const dfquat& q);
  #endif
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr dfquat::dfquat(flt64 val)
: w(1.0f), x(val), y(val), z(val) {}

inline constexpr dfquat::dfquat(flt64 w, flt64 x, flt64 y, flt64 z)
: w(w), x(x), y(y), z(z) {}

inline constexpr dfquat::dfquat(flt64 w, const sfvec3& xyz)
: w(w), x(xyz.x), y(xyz.y), z(xyz.z) {}

/*
inline constexpr dfquat::dfquat(const dfquat& q)
: w(q.w), x(q.x), y(q.y), z(q.z) {}
*/

inline dfquat dfquat::operator+(const dfquat& other)
{
  return dfquat(this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z);
}

inline dfquat& dfquat::operator+=(const dfquat& other)
{
  this->w += other.w;
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;

  return *this;
}

inline dfquat dfquat::operator-(const dfquat& other)
{
  return dfquat(this->w - other.w, this->x - other.x, this->y - other.y, this->z - other.z);
}

inline dfquat& dfquat::operator-=(const dfquat& other)
{
  this->w -= other.w;
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;

  return *this;
}

inline dfquat dfquat::operator*(const dfquat& other)
{
  return dfquat
  (
    this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,
    this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
    this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
    this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w
  );
}

inline dfquat dfquat::operator*(flt64 val)
{
  return dfquat(w * val, x * val, y * val, z * val);
}

inline dfquat& dfquat::operator*=(flt64 val)
{
  this->w *= val;
  this->x *= val;
  this->y *= val;
  this->z *= val;

  return *this;
}

inline dfquat dfquat::operator/(flt64 val)
{
  const flt64 div = 1.0f / val;

  return dfquat(w * div, x * div, y * div, z * div);
}

inline dfquat& dfquat::operator/=(flt64 val)
{
  const flt64 div = 1.0f / val;

  this->w *= div;
  this->x *= div;
  this->y *= div;
  this->z *= div;

  return *this;
}

inline dfquat dfquat::Conjugate(const dfquat& q)
{
  return dfquat(q.w, -q.x, -q.y, -q.z);
}

inline dfquat dfquat::Normalise(dfquat& q)
{
  const flt64 mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

  return q / mag;
}

inline dfquat dfquat::Inverse(const dfquat& q)
{
  const flt64 mag2 = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;

  return dfquat::Conjugate(q) / mag2;
}

/*dfquat dfquat::Rotate(flt64 angle, const sfvec3 &axis)
{
  const flt64 hang = angle * 0.5f;
  const flt64 cosha = cos(hang);
  const flt64 sinha = sin(hang);

  return { cosha, sinha * axis.x, sinha * axis.y, sinha * axis.z };
}

dfquat dfquat::ToQuaternion(sfvec3 eulerAngles)
{
  const sfvec3 heuler = eulerAngles * 0.5f;	// A little SIMD optimisation, not much

  const flt64 cr = cos(heuler.x);
  const flt64 cp = cos(heuler.y);
  const flt64 cy = cos(heuler.z);

  const flt64 sr = sin(heuler.x);
  const flt64 sp = sin(heuler.y);
  const flt64 sy = sin(heuler.z);

  return
  {
    cr * cp * cy + sr * sp * sy,
    sr * cp * cy - cr * sp * sy,
    cr * sp * cy + sr * cp * sy,
    cr * cp * sy - sr * sp * cy
  };
}

sfvec3 dfquat::ToEulerAngles(const dfquat &q)
{
  const flt64 y2 = q.y * q.y;
  const flt64 wysxz2 = 2 * (q.w * q.y - q.x * q.z);

  // X-axis Rotation
  const flt64 sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
  const flt64 cosr_cosp = 1 - 2 * (q.x * q.x + y2);
  const flt64 r = std::atan2(sinr_cosp, cosr_cosp);

  // Y-axis Rotation
  flt64 sinp = std::sqrt(1 + wysxz2);
  flt64 cosp = std::sqrt(1 - wysxz2);
  flt64 p = 2 * std::atan2(sinp, cosp) - pi / 2;	// Original

  const flt64 p = std::asin(wysxz2);	// Alternative - hope it's same

  // Z-axis Rotation
  const flt64 siny_cosp = 2 * (q.w * q.z + q.x * q.y);
  const flt64 cosy_cosp = 1 - 2 * (y2 + q.z * q.z);
  const flt64 y = std::atan2(siny_cosp, cosy_cosp);

  return { r, p, y };
}

sfmat4 dfquat::ToRotationMatrix(const dfquat &q)
{
  const flt64 x2 = q.x * q.x;
  const flt64 y2 = q.y * q.y;
  const flt64 z2 = q.z * q.z;

  const flt64 xy = q.x * q.y;
  const flt64 zw = q.w * q.z;

  const flt64 xz = q.x * q.z;
  const flt64 yw = q.w * q.y;

  const flt64 yz = q.y * q.z;
  const flt64 xw = q.w * q.x;

  return
  {
    1 - 2 * (y2 + z2), 2 * (xy - zw), 2 * (xz + yw), 0.0f,
    2 * (xy + zw), 1 - 2 * (x2 + z2), 2 * (yz - xw), 0.0f,
    2 * (xz - yw), 2 * (yz + xw), 1 - 2 * (x2 + y2), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
}*/

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const dfquat& q)
{
  os << "( W: " << q.w << "\tX: " << q.x << "\tY: " << q.y << "\tZ: " << q.z << " )";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_DFQUAT_HPP