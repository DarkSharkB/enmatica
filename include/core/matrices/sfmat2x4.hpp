/** 
 * Single Precision Floating-Point 2x4 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT2X4_HPP
#define ENMA_SFMAT2X4_HPP

#include <iomanip>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec4.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(32) sfmat2x4
{
  union
  {
    struct
    {
      flt32 m00, m01, m02, m03;
      flt32 m10, m11, m12, m13;
    };
    flt32 arr[8];
    sfvec4 rows[2];
  };

  constexpr explicit sfmat2x4(flt32 val = 0.0f);
  constexpr explicit sfmat2x4
  (
    flt32 x0, flt32 y0, flt32 z0, flt32 w0,
    flt32 x1, flt32 y1, flt32 z1, flt32 w1
  );
  
  constexpr explicit sfmat2x4
  (
    const sfvec2& hrow00, const sfvec2& hrow01,
    const sfvec2& hrow10, const sfvec2& hrow11
  );
  constexpr explicit sfmat2x4
  (
    const sfvec4& row0,
    const sfvec4& row1
  );
  #ifdef USE_SIMD
  sfmat2x4(const __m256& m);
  #endif // USE_SIMD

  /*
  constexpr sfmat2x4(const sfmat2x4& m);
  sfmat2x4& operator=(const sfmat2x4& other);
  */

  sfmat2x4 operator+(const sfmat2x4& other) const;
  sfmat2x4 operator+=(const sfmat2x4& other);
  sfmat2x4 operator-(const sfmat2x4& other) const;
  sfmat2x4 operator-=(const sfmat2x4& other);
  sfmat2x4 operator*(flt32 val) const;
  sfmat2x4 operator*=(flt32 val);
  sfmat2x4 operator/(flt32 val) const;
  sfmat2x4 operator/=(flt32 val);

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat2x4& m);
  #endif // DEBUG
};

//inline sfmat2x4 Transpose(const sfmat4x2& m);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfmat2x4::sfmat2x4(const flt32 val)
: m00(val), m01(val), m02(val), m03(val),
  m10(val), m11(val), m12(val), m13(val) {}

inline constexpr sfmat2x4::sfmat2x4
(
  flt32 x0, flt32 y0, flt32 z0, flt32 w0,
  flt32 x1, flt32 y1, flt32 z1, flt32 w1
) 
: m00(x0), m01(y0), m02(z0), m03(w0),
  m10(x1), m11(y1), m12(z1), m13(w1) {}

inline constexpr sfmat2x4::sfmat2x4
(
  const sfvec4& row0,
  const sfvec4& row1
)
: m00(row0.x), m01(row0.y), m02(row0.z), m03(row0.w),
  m10(row1.x), m11(row1.y), m12(row1.z), m13(row1.w) {}

/*
inline constexpr sfmat2x4::sfmat2x4(const sfmat2x4& m)
: m00(m.m00), m01(m.m01), m02(m.m02), m03(m.m03),
  m10(m.m10), m11(m.m11), m12(m.m12), m13(m.m13) {}

inline sfmat2x4& sfmat2x4::operator=(const sfmat2x4& other)
{
  if(this != &other)
  {
    this->rows[0] = other.rows[0];
    this->rows[1] = other.rows[1];
  }
  return *this;
}
*/

#ifdef USE_SIMD
inline sfmat2x4::sfmat2x4(const __m256& m)
{
  this->arr[0] = m[0];
  this->arr[1] = m[1];
  this->arr[2] = m[2];
  this->arr[3] = m[3];
  this->arr[4] = m[4];
  this->arr[5] = m[5];
  this->arr[6] = m[6];
  this->arr[7] = m[7];
}

inline sfmat2x4 sfmat2x4::operator+(const sfmat2x4& other) const
{
  __m256 m1 = _mm256_load_ps(this->arr);
  __m256 m2 = _mm256_load_ps(other.arr);

  return sfmat2x4(_mm256_add_ps(m1, m2));
}

inline sfmat2x4 sfmat2x4::operator+=(const sfmat2x4& other)
{
  __m256 m1 = _mm256_load_ps(this->arr);
  __m256 m2 = _mm256_load_ps(other.arr);

  *this = _mm256_add_ps(m1, m2);

  return *this;
}

inline sfmat2x4 sfmat2x4::operator-(const sfmat2x4& other) const
{
  __m256 m1 = _mm256_load_ps(this->arr);
  __m256 m2 = _mm256_load_ps(other.arr);

  m1 = _mm256_sub_ps(m1, m2);

  return sfmat2x4(m1);
}

inline sfmat2x4 sfmat2x4::operator-=(const sfmat2x4& other)
{
  __m256 m1 = _mm256_load_ps(this->arr);
  __m256 m2 = _mm256_load_ps(other.arr);

  *this = _mm256_sub_ps(m1, m2);

  return *this;
}

inline sfmat2x4 sfmat2x4::operator*(flt32 val) const
{
  __m256 fl = _mm256_set1_ps(val);
  __m256 m1 = _mm256_load_ps(this->arr);

  return _mm256_mul_ps(m1, fl);
}

inline sfmat2x4 sfmat2x4::operator*=(flt32 val)
{
  __m256 fl = _mm256_set1_ps(val);
  __m256 m1 = _mm256_load_ps(this->arr);

  *this = _mm256_mul_ps(m1, fl);

  return *this;
}

inline sfmat2x4 sfmat2x4::operator/(flt32 val) const
{
  __m256 fl = _mm256_set1_ps(val);
  __m256 m1 = _mm256_load_ps(this->arr);

  return _mm256_div_ps(m1, fl);
}

inline sfmat2x4 sfmat2x4::operator/=(flt32 val)
{
  __m256 fl = _mm256_set1_ps(val);
  __m256 m1 = _mm256_load_ps(this->arr);

  *this = _mm256_div_ps(m1, fl);
  
  return *this;
}
#endif // USE_SIMD

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat2x4& m)
{
    os
    << "{\t\t\t\t\t\t\t   }\n"
    << "|\t\t\t\t\t\t\t   |\n"
    << "|  " << std::setw(12) << m.m00 << "  " << std::setw(12) << m.m01 << "  " << std::setw(12) << m.m02 << "  " << std::setw(12) << m.m03 << "  |\n"
    << "|  " << std::setw(12) << m.m10 << "  " << std::setw(12) << m.m11 << "  " << std::setw(12) << m.m12 << "  " << std::setw(12) << m.m13 << "  |\n"
    << "|\t\t\t\t\t\t\t   |\n"
    << "{\t\t\t\t\t\t\t   }";

    return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFMAT2X4_HPP