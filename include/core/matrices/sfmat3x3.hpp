/** Single Precision Floating-Point 3x3 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT3X3_HPP
#define ENMA_SFMAT3X3_HPP

#include <intrin.h>
#include <iostream>
#include <iomanip>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec3.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct sfmat3x3
{
  union
  {
    flt32 _arr[9];
    struct
    {
      flt32 m00, m01, m02;
      flt32 m10, m11, m12;
      flt32 m20, m21, m22;
    };
  };

  constexpr explicit sfmat3x3(flt32 val = 0.0f);
  constexpr explicit sfmat3x3
  (
    flt32 x0, flt32 y0, flt32 z0,
    flt32 x1, flt32 y1, flt32 z1,
    flt32 x2, flt32 y2, flt32 z2
  );

  constexpr explicit sfmat3x3
  (
    const sfvec3& row0,
    const sfvec3& row1,
    const sfvec3& row2
  );

  /*
  constexpr sfmat3x3(const sfmat3x3& m);
  sfmat3x3& operator=(const sfmat3x3& other);
  */

  #ifdef USE_SIMD
  sfmat3x3
  (
    const __m128& r0,
    const __m128& r1,
    const __m128& r2
  );
  sfmat3x3(const __m256& t1, flt32 f);
  #endif // USE_SIMD
  
  sfmat3x3 operator+(const sfmat3x3& other) const;
  sfmat3x3& operator+=(const sfmat3x3& other);
  sfmat3x3 operator-(const sfmat3x3& other) const;
  sfmat3x3& operator-=(const sfmat3x3& other);
  sfmat3x3 operator*(const sfmat3x3& other) const;
  sfmat3x3& operator*=(const sfmat3x3& other);
  sfmat3x3 operator*(flt32 val) const;
  sfmat3x3& operator*=(flt32 val);
  sfmat3x3 operator/(flt32 val) const;
  sfmat3x3& operator/=(flt32 val);

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat3x3& m);
  #endif // DEBUG
};
using sfmat3 = sfmat3x3;

inline sfmat3x3 Transpose(const sfmat3x3& m);
inline flt32 Determinant(const sfmat3x3& m);
inline sfmat3x3 Inverse(const sfmat3x3& m);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfmat3x3::sfmat3x3(flt32 val)
: m00(val),  m01(val), m02(val),
  m10(val), m11(val),  m12(val),
  m20(val), m21(val), m22(val) {}

inline constexpr sfmat3x3::sfmat3x3
(
  flt32 x0, flt32 y0, flt32 z0,
  flt32 x1, flt32 y1, flt32 z1,
  flt32 x2, flt32 y2, flt32 z2
)
: m00(x0), m01(y0), m02(z0), 
  m10(x1), m11(y1), m12(z1), 
  m20(x2), m21(y2), m22(z2) {}

inline constexpr sfmat3x3::sfmat3x3
(
  const sfvec3& row0,
  const sfvec3& row1,
  const sfvec3& row2
)
: m00(row0.x), m01(row0.y), m02(row0.z), 
  m10(row1.x), m11(row1.y), m12(row1.z), 
  m20(row2.x), m21(row2.y), m22(row2.z) {}

/*
inline constexpr sfmat3x3::sfmat3x3(const sfmat3x3& m)
: m00(m.m00), m01(m.m01), m02(m.m02),
  m10(m.m10), m11(m.m11), m12(m.m12), 
  m20(m.m20), m21(m.m21), m22(m.m22) {}

inline sfmat3x3& sfmat3x3::operator=(const sfmat3x3& other)
{
  if(this != &other)
  {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m02 = other.m02;
    this->m10 = other.m10;
    this->m11 = other.m11;
    this->m12 = other.m12;
    this->m20 = other.m20;
    this->m21 = other.m21;
    this->m22 = other.m22;
  }
  return *this;
}
*/

#ifdef USE_SIMD
inline sfmat3x3::sfmat3x3(const __m128& r0, const __m128& r1, const __m128& r2)
{
  this->_arr[0] = r0[0];
  this->_arr[1] = r0[1];
  this->_arr[2] = r0[2];
  this->_arr[3] = r1[0];
  this->_arr[4] = r1[1];
  this->_arr[5] = r1[2];
  this->_arr[6] = r2[0];
  this->_arr[7] = r2[1];
  this->_arr[8] = r2[2];
}

inline sfmat3x3::sfmat3x3(const __m256& f8vals, flt32 val)
{
  this->_arr[0] = f8vals[0];
  this->_arr[1] = f8vals[1];
  this->_arr[2] = f8vals[2];
  this->_arr[3] = f8vals[3];
  this->_arr[4] = f8vals[4];
  this->_arr[5] = f8vals[5];
  this->_arr[6] = f8vals[6];
  this->_arr[7] = f8vals[7];
  this->_arr[8] = val;
}
#endif // USE_SIMD

inline sfmat3x3 sfmat3x3::operator+(const sfmat3x3& m) const
{
  __m256 t1 = _mm256_loadu_ps(this->_arr);
  __m256 t2 = _mm256_loadu_ps(m._arr);
  flt32 l = this->m22 + m.m22;

  t1 = _mm256_add_ps(t1, t2);
  
  return sfmat3x3(t1, l);
}

inline sfmat3x3& sfmat3x3::operator+=(const sfmat3x3& m)
{
  __m256 t1 = _mm256_load_ps(this->_arr);
  __m256 t2 = _mm256_load_ps(m._arr);
  this->m22 += m.m22;

  t1 = _mm256_add_ps(t1, t2);

  _mm256_store_ps(this->_arr, t1);

  return *this;
}

inline sfmat3x3 sfmat3x3::operator-(const sfmat3x3& m) const
{
  __m256 t1 = _mm256_load_ps(this->_arr);
  __m256 t2 = _mm256_load_ps(m._arr);
  flt32 l = this->m22 - m.m22;

  t1 = _mm256_sub_ps(t1, t2);
  
  return sfmat3x3(t1, l);
}

inline sfmat3x3& sfmat3x3::operator-=(const sfmat3x3& m)
{
  __m256 t1 = _mm256_load_ps(this->_arr);
  __m256 t2 = _mm256_load_ps(m._arr);
  this->m22 -= m.m22;

  t1 = _mm256_sub_ps(t1, t2);

  _mm256_store_ps(this->_arr, t1);

  return *this;
}

inline sfmat3x3 sfmat3x3::operator*(const sfmat3x3& other) const
{
  flt32 m1 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20;
  flt32 m2 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21;
  flt32 m3 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22;

  flt32 m4 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20;
  flt32 m5 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21;
  flt32 m6 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22;

  flt32 m7 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20;
  flt32 m8 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21;
  flt32 m9 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22;

  return sfmat3x3(m1, m2, m3, m4, m5, m6, m7, m8, m9);
}

inline sfmat3x3& sfmat3x3::operator*=(const sfmat3x3& other)
{
  flt32 m1 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20;
  flt32 m2 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21;
  flt32 m3 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22;

  flt32 m4 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20;
  flt32 m5 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21;
  flt32 m6 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22;

  flt32 m7 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20;
  flt32 m8 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21;
  flt32 m9 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22;

  *this = sfmat3x3(m1, m2, m3, m4, m5, m6, m7, m8, m9);

  return *this;
}

inline sfmat3x3 sfmat3x3::operator*(flt32 val) const
{
  __m256 t1 = _mm256_load_ps(this->_arr);
  __m256 t2 = _mm256_set1_ps(val);
  flt32 l = this->m22 * val;

  t1 = _mm256_mul_ps(t1, t2);
  
  return sfmat3x3(t1, l);
}

inline sfmat3x3& sfmat3x3::operator*=(flt32 val)
{
  __m256 t1 = _mm256_loadu_ps(this->_arr);
  __m256 t2 = _mm256_set1_ps(val);
  this->m22 *= val;

  t1 = _mm256_mul_ps(t1, t2);

  _mm256_store_ps(this->_arr, t1);

  return *this;
}

inline sfmat3x3 sfmat3x3::operator/(flt32 val) const
{
  const flt32 rec = 1.0f / val;

  __m256 t1 = _mm256_loadu_ps(this->_arr);
  __m256 t2 = _mm256_set1_ps(rec);

  flt32 l = this->m22 * rec;

  t1 = _mm256_mul_ps(t1, t2);
  
  return sfmat3x3(t1, l);
}

inline sfmat3x3& sfmat3x3::operator/=(flt32 val)
{
  const flt32 rec = 1.0f / val;

  __m256 t1 = _mm256_loadu_ps(this->_arr);
  __m256 t2 = _mm256_set1_ps(rec);
  this->m22 *= rec;

  t1 = _mm256_mul_ps(t1, t2);

  _mm256_storeu_ps(this->_arr, t1);

  return *this;
}

inline sfmat3x3 Transpose(const sfmat3x3& m)
{
  flt32 m01 = m.m10;
  flt32 m02 = m.m20;
  flt32 m12 = m.m21;

  return sfmat3x3(m.m00, m01, m02, m.m01, m.m11, m12, m.m02, m.m12, m.m22);
}

inline flt32 Determinant(const sfmat3x3& m)
{
  flt32 d1 = m.m00 * (m.m11 * m.m22 - m.m12 * m.m21);
  flt32 d2 = m.m01 * (m.m12 * m.m20 - m.m10 * m.m22);
  flt32 d3 = m.m02 * (m.m10 * m.m21 - m.m11 * m.m20);

  return d1 + d2 + d3;
}

inline sfmat3x3 Inverse(const sfmat3x3& m)
{
  flt32 m1 = m.m11 * m.m22 - m.m12 * m.m21;
  flt32 m2 = m.m12 * m.m20 - m.m10 * m.m22;
  flt32 m3 = m.m10 * m.m21 - m.m11 * m.m20;
  
  flt32 m4 = m.m02 * m.m21 - m.m01 * m.m22;
  flt32 m5 = m.m00 * m.m22 - m.m02 * m.m20;
  flt32 m6 = m.m20 * m.m01 - m.m00 * m.m21;
  
  flt32 m7 = m.m01 * m.m12 - m.m11 * m.m02;
  flt32 m8 = m.m10 * m.m02 - m.m00 * m.m12;
  flt32 m9 = m.m00 * m.m11 - m.m01 * m.m10;

  flt32 det = m.m00 * m1 + m.m01 * m2 + m.m02 * m3;

  return sfmat3x3(m1, m4, m7, m2, m5, m8, m3, m6, m9) / det;
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat3x3& m)
{
  os 
  << "\n{\t\t\t\t\t\t\t}\n"
  << "|\t" << std::setw(12) << m.m00 << "  " << std::setw(12) << m.m01 << "  " << std::setw(12) << m.m02 <<  "\t|\n"
  << "|\t" << std::setw(12) << m.m10 << "  " << std::setw(12) << m.m11 << "  " << std::setw(12) << m.m12 <<  "\t|\n"
  << "|\t" << std::setw(12) << m.m20 << "  " << std::setw(12) << m.m21 << "  " << std::setw(12) << m.m22 <<  "\t|\n"
  << "{\t\t\t\t\t\t\t}";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFMAT3X3_HPP