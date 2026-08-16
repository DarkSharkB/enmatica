/** 
 * Single Precision Floating-Point 2x2 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT2X2_HPP
#define ENMA_SFMAT2X2_HPP

#include <iomanip>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec2.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(16) sfmat2x2
{
  union
  {
    flt32 _arr[4];
    struct
    {
      flt32 m00, m01;
      flt32 m10, m11;
    };
    sfvec2 rows[2];
  };

  constexpr explicit sfmat2x2(flt32 val = 0.0f);
  constexpr explicit sfmat2x2
  (
    flt32 x0, flt32 y0,
    flt32 x1, flt32 y1
  );
  constexpr explicit sfmat2x2
  (
    const sfvec2& row0,
    const sfvec2& row1
  );
  #ifdef USE_SIMD
  sfmat2x2(const __m128& vals);
  #endif // USE_SIMD

  /*
  constexpr sfmat2x2(const sfmat2x2& m);
  sfmat2x2& operator=(const sfmat2x2& other);
  */

  sfmat2x2 operator+(const sfmat2x2& other) const;
  sfmat2x2 operator+=(const sfmat2x2& other);
  sfmat2x2 operator-(const sfmat2x2& other) const;
  sfmat2x2 operator-=(const sfmat2x2& other);
  sfmat2x2 operator*(const sfmat2x2& other) const;
  sfmat2x2 operator*=(const sfmat2x2& other);
  sfmat2x2 operator*(flt32 val) const;
  sfmat2x2 operator*=(flt32 val);
  sfmat2x2 operator/(flt32 val) const;
  sfmat2x2 operator/=(flt32 val);

  flt32 Determinant() const;
  sfmat2x2 Transpose();

  static constexpr sfmat2x2 Identity();

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat2x2& m);
  #endif // DEBUG
};
using sfmat2 = sfmat2x2;

inline sfmat2x2 Transpose(const sfmat2x2& m);

//inline sfmat2x2 operator*(const sfmat2x3 m1, const sfmat3x2 m2);
//inline sfmat2x2 operator*(const sfmat2x4 m1, const sfmat4x2 m2);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfmat2x2::sfmat2x2(flt32 val)
: m00(val), m01(val),
  m10(val), m11(val) {}

inline constexpr sfmat2x2::sfmat2x2
(
  flt32 x0, flt32 y0,
  flt32 x1, flt32 y1
) 
: m00(x0), m01(y0), 
  m10(x1), m11(y1) {}

inline constexpr sfmat2x2::sfmat2x2
(
  const sfvec2& row0,
  const sfvec2& row1
)
: m00(row0.x), m01(row0.y),
  m10(row1.x), m11(row1.y) {}

/*
inline constexpr sfmat2x2::sfmat2x2(const sfmat2x2& m)
: m00(m.m00), m01(m.m01),
  m10(m.m10), m11(m.m11) {}

inline sfmat2x2& sfmat2x2::operator=(const sfmat2x2& other)
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
inline sfmat2x2::sfmat2x2(const __m128& vals)
{
  this->_arr[0] = vals[0];
  this->_arr[1] = vals[1];
  this->_arr[2] = vals[2];
  this->_arr[3] = vals[3];
}

inline sfmat2x2 sfmat2x2::operator+(const sfmat2x2& other) const
{
  __m128 m1 = _mm_load_ps(this->_arr);
  __m128 m2 = _mm_load_ps(other._arr);

  return _mm_add_ps(m1, m2);
}

inline sfmat2x2 sfmat2x2::operator+=(const sfmat2x2& other)
{
  __m128 m1 = _mm_load_ps(this->_arr);
  __m128 m2 = _mm_load_ps(other._arr);

  _mm_store_ps(this->_arr, _mm_add_ps(m1, m2));

  return *this;
}

inline sfmat2x2 sfmat2x2::operator-(const sfmat2x2& other) const
{
  __m128 m1 = _mm_load_ps(this->_arr);
  __m128 m2 = _mm_load_ps(other._arr);

  return _mm_sub_ps(m1, m2);
}

inline sfmat2x2 sfmat2x2::operator-=(const sfmat2x2& other)
{
  __m128 m1 = _mm_load_ps(this->_arr);
  __m128 m2 = _mm_load_ps(other._arr);

  _mm_store_ps(this->_arr, _mm_sub_ps(m1, m2));

  return *this;
}

inline sfmat2x2 sfmat2x2::operator*(const sfmat2x2& other) const
{
  // Need a better way
  __m128 r1 = _mm_load_ps(this->_arr);     // First Matrix
  __m128 r3 = _mm_load_ps(other._arr);     // Second Matrix

  __m128 r2 = _mm_shuffle_ps(r1, r1, 0xEE);
  r1 = _mm_shuffle_ps(r1, r1, 0x44);
  r3 = _mm_shuffle_ps(r3, r3, 0xD8);

  r1 = _mm_dp_ps(r1, r3, 0xFF);
  r2 = _mm_dp_ps(r2, r3, 0xFF);

  /*r1 = _mm_hadd_ps(r1, r1);
  r2 = _mm_hadd_ps(r2, r2);*/

  r2 = _mm_shuffle_ps(r1, r2, 0xE4);

  return sfmat2x2(r2);
}

inline sfmat2x2 sfmat2x2::operator*=(const sfmat2x2& other)
{
  // Same as above, right?
  __m128 r1 = _mm_load_ps(this->_arr);   // First Matrix
  __m128 r3 = _mm_load_ps(other._arr);       // Second Matrix

  __m128 r2 = _mm_shuffle_ps(r1, r1, 0xEE);
  r1 = _mm_shuffle_ps(r1, r1, 0x44);
  r3 = _mm_shuffle_ps(r3, r3, 0xD8);

  r1 = _mm_dp_ps(r1, r3, 0XFF);
  r2 = _mm_dp_ps(r2, r3, 0xFF);

  /*r1 = _mm_hadd_ps(r1, r1);
  r2 = _mm_hadd_ps(r2, r2);*/

  r2 = _mm_shuffle_ps(r1, r2, 0xE4);

  *this = r2;

  return *this;
}

inline sfmat2x2 sfmat2x2::operator*(flt32 val) const
{
  __m128 m = _mm_load_ps(this->_arr);
  __m128 fl = _mm_load1_ps(&val);

  return sfmat2x2(_mm_mul_ps(m, fl));
}

inline sfmat2x2 sfmat2x2::operator*=(flt32 val)
{
  __m128 m = _mm_load_ps(this->_arr);
  __m128 fl = _mm_load1_ps(&val);

  _mm_store_ps(this->_arr, _mm_mul_ps(m, fl));

  return *this;
}

inline sfmat2x2 sfmat2x2::operator/(flt32 val) const
{
  __m128 m = _mm_load_ps(this->_arr);
  __m128 fl = _mm_load1_ps(&val);

  return sfmat2x2(_mm_div_ps(m, fl));
}

inline sfmat2x2 sfmat2x2::operator/=(flt32 val)
{
  __m128 m = _mm_load_ps(this->_arr);
  __m128 fl = _mm_load1_ps(&val);

  _mm_store_ps(this->_arr, _mm_div_ps(m, fl));
      
  return *this;
}

inline sfmat2x2 sfmat2x2::Transpose()
{
  __m128 r = _mm_load_ps(this->_arr);

  return sfmat2x2(_mm_shuffle_ps(r, r, _MM_SHUFFLE(3, 1, 2, 0)));
}

inline flt32 sfmat2x2::Determinant() const
{
  __m128 m = _mm_load_ps(this->_arr);
  __m128 n = _mm_shuffle_ps(m, m, 0xBB);

  m = _mm_mul_ps(m, n);

  return m[0] - m[1];
}

inline sfmat2x2 Transpose(const sfmat2x2& m)
{
  __m128 r = _mm_load_ps(m._arr);

  r = _mm_shuffle_ps(r, r, _MM_SHUFFLE(3, 1, 2, 0));

  return sfmat2x2(r);
}
#endif // USE_SIMD

inline constexpr sfmat2x2 sfmat2x2::Identity()
{
  return sfmat2x2
  {
    1.0f, 0.0f,
    0.0f, 1.0f
  };
} 

/*#include "sfmat2x3.hpp"
#include "sfmat3x2.hpp"
inline sfmat2x2 operator*(const sfmat2x3 m1, const sfmat3x2 m2)
{
  return sfmat2x2(2.0f);
}*/

/*#include "sfmat2x4.hpp"
#include "sfmat4x2.hpp"
inline sfmat2x2 operator*(const sfmat2x4 m1, const sfmat4x2 m2)
{
  sfmat2x2 m;

  m._arr[0] = m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m13 * m2.m31 + m1.m14 * m2.m41;
  m._arr[1] = m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m13 * m2.m32 + m1.m14 * m2.m42;
  m._arr[2] = m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m23 * m2.m31 + m1.m24 * m2.m41;
  m._arr[3] = m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m23 * m2.m32 + m1.m24 * m2.m42;

  return m;
}*/

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat2x2& m)
{
  os << std::fixed << std::setprecision(4)
  << "{ " << std::setw(12) << " }\n"
  << "| " << m.m00 << " " << m.m01 << " |\n"
  << "| " << m.m10 << " " << m.m11 << " |\n"
  << "{ " << std::setw(12) << " }\n";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFMAT2X2_HPP