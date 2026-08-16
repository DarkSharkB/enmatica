/** Single Precision Floating-Point 4x3 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT4X3_HPP
#define ENMA_SFMAT4X3_HPP

#include <iomanip>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec3.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(64) sfmat4x3
{
  union
  {
    flt32 _arr[12];
    struct
    {
      flt32 m00, m01, m02;
      flt32 m10, m11, m12;
      flt32 m20, m21, m22;
      flt32 m30, m31, m32;
    };
    sfvec3 rows[4];
  };

  constexpr explicit sfmat4x3
  (
    flt32 x0 = 0.0f, flt32 y0 = 0.0f, flt32 z0 = 0.0f, 
    flt32 x1 = 0.0f, flt32 y1 = 0.0f, flt32 z1 = 0.0f, 
    flt32 x2 = 0.0f, flt32 y2 = 0.0f, flt32 z2 = 0.0f,
    flt32 x3 = 0.0f, flt32 y3 = 0.0f, flt32 z3 = 0.0f
  );

  constexpr explicit sfmat4x3
  (
    const sfvec3& row0,
    const sfvec3& row1,
    const sfvec3& row2,
    const sfvec3& row3
  );

  //constexpr sfmat4x3(const sfmat4x3& m);

  sfmat4x3 operator+(const sfmat4x3& other) const;
  sfmat4x3& operator+=(const sfmat4x3& other);
  sfmat4x3 operator-(const sfmat4x3& other) const;
  sfmat4x3& operator-=(const sfmat4x3& other);

  #ifdef USE_SIMD
  sfmat4x3(const __m128& r0, const __m128& r1, const __m128& r2, const __m128& r3);
  sfmat4x3 operator*(const sfmat4x3& other) const;
  #endif // USE_SIMD

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat4x3& m);
  #endif // DEBUG
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfmat4x3::sfmat4x3
(
  flt32 x0, flt32 y0, flt32 z0, 
  flt32 x1, flt32 y1, flt32 z1, 
  flt32 x2, flt32 y2, flt32 z2,
  flt32 x3, flt32 y3, flt32 z3
)
: m00(x0), m01(y0), m02(z0),
  m10(x1), m11(y1), m12(z1),
  m20(x2), m21(y2), m22(z2),
  m30(x3), m31(y3), m32(z3) {}

inline constexpr sfmat4x3::sfmat4x3
(
  const sfvec3& row0,
  const sfvec3& row1,
  const sfvec3& row2,
  const sfvec3& row3
)
: m00(row0.x), m01(row0.y), m02(row0.z),
  m10(row1.x), m11(row1.y), m12(row1.z),
  m20(row2.x), m21(row2.y), m22(row2.z),
  m30(row3.x), m31(row3.y), m32(row3.z) {}

/*
inline constexpr sfmat4x3::sfmat4x3(const sfmat4x3& m)
: m00(m.m00), m01(m.m01), m02(m.m02),
  m10(m.m10), m11(m.m11), m12(m.m12), 
  m20(m.m20), m21(m.m21), m22(m.m22),
  m30(m.m30), m31(m.m31), m32(m.m32) {}
*/

inline sfmat4x3 sfmat4x3::operator+(const sfmat4x3& other) const
{
  return sfmat4x3
  {
    this->rows[0] + other.rows[0],
    this->rows[1] + other.rows[1],
    this->rows[2] + other.rows[2],
    this->rows[3] + other.rows[3],
  };
}

inline sfmat4x3& sfmat4x3::operator+=(const sfmat4x3& other)
{
  this->rows[0] = this->rows[0] + other.rows[0];
  this->rows[1] = this->rows[1] + other.rows[1];
  this->rows[2] = this->rows[2] + other.rows[2];
  this->rows[3] = this->rows[3] + other.rows[3];

  return *this;
}

inline sfmat4x3 sfmat4x3::operator-(const sfmat4x3& other) const
{
  return sfmat4x3
  {
    this->rows[0] - other.rows[0],
    this->rows[1] - other.rows[1],
    this->rows[2] - other.rows[2],
    this->rows[3] - other.rows[3],
  };
}

inline sfmat4x3& sfmat4x3::operator-=(const sfmat4x3& other)
{
  this->rows[0] = this->rows[0] - other.rows[0];
  this->rows[1] = this->rows[1] - other.rows[1];
  this->rows[2] = this->rows[2] - other.rows[2];
  this->rows[3] = this->rows[3] - other.rows[3];

  return *this;
}

#ifdef USE_SIMD
inline sfmat4x3::sfmat4x3(const __m128& r0, const __m128& r1, const __m128& r2, const __m128& r3)
{
  this->rows[0] = r0;
  this->rows[1] = r1;
  this->rows[2] = r2;
  this->rows[3] = r3;
}

inline sfmat4x3 sfmat4x3::operator*(const sfmat4x3& other) const
{
  flt32 a[4] = { 0.0f }, 
        b[4] = { 0.0f }, 
        c[4] = { 0.0f }, 
        d[4] = { 0.0f }; 

  __m128 r00, r01, r02, r03;
  __m128 r10, r11, r12, r13;
  __m128 i1, i2, i3, i4;

  r00 = Set(this->rows[0]);
  r01 = Set(this->rows[1]);
  r02 = Set(this->rows[2]);
  r03 = Set(this->rows[3]);

  r10 = Set(other.rows[0]);
  r11 = Set(other.rows[1]);
  r12 = Set(other.rows[2]);
  r13 = Set(other.rows[3]);

  _MM_TRANSPOSE4_PS(r10, r11, r12, r13);

  i1 = _mm_dp_ps(r00, r10, 0xFF);
  i2 = _mm_dp_ps(r00, r11, 0xFF);
  i3 = _mm_dp_ps(r00, r12, 0xFF);
  i4 = _mm_dp_ps(r00, r13, 0xFF);

  a[0] = i1[0];
  a[1] = i2[0];
  a[2] = i3[0];
  a[3] = i4[0];


  i1 = _mm_dp_ps(r01, r10, 0xFF);
  i2 = _mm_dp_ps(r01, r11, 0xFF);
  i3 = _mm_dp_ps(r01, r12, 0xFF);
  i4 = _mm_dp_ps(r01, r13, 0xFF);

  b[0] = i1[0];
  b[1] = i2[0];
  b[2] = i3[0];
  b[3] = i4[0];

  i1 = _mm_dp_ps(r02, r10, 0xFF);
  i2 = _mm_dp_ps(r02, r11, 0xFF);
  i3 = _mm_dp_ps(r02, r12, 0xFF);
  i4 = _mm_dp_ps(r02, r13, 0xFF);

  c[0] = i1[0];
  c[1] = i2[0];
  c[2] = i3[0];
  c[3] = i4[0];

  i1 = _mm_dp_ps(r03, r10, 0xFF);
  i2 = _mm_dp_ps(r03, r11, 0xFF);
  i3 = _mm_dp_ps(r03, r12, 0xFF);
  i4 = _mm_dp_ps(r03, r13, 0xFF);

  d[0] = i1[0];
  d[1] = i2[0];
  d[2] = i3[0];
  d[3] = i4[0];

  return sfmat4x3
  {
    a[0], a[1], a[2],
    b[0], b[1], b[2],
    c[0], c[1], c[2]
  };
}
#endif

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat4x3& m)
{
  os << "{\t\t\t\t\t\t\t\t\t}\n"
  << "|\t" << std::setw(8) << m.m00 << "\t" << std::setw(8) << m.m01 << "\t" << std::setw(8) << m.m02 << "\t" << "\t|\n"
  << "|\t" << std::setw(8) << m.m10 << "\t" << std::setw(8) << m.m11 << "\t" << std::setw(8) << m.m12 << "\t" << "\t|\n"
  << "|\t" << std::setw(8) << m.m20 << "\t" << std::setw(8) << m.m21 << "\t" << std::setw(8) << m.m22 << "\t" << "\t|\n"
  << "|\t" << std::setw(8) << m.m30 << "\t" << std::setw(8) << m.m31 << "\t" << std::setw(8) << m.m32 << "\t" << "\t|\n{\t\t\t\t\t\t\t\t\t}";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFMAT4X3_HPP