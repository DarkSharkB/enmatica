/**
 * Single Precision Floating-Point 2x3 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT2X3_HPP
#define ENMA_SFMAT2X3_HPP

#include <iomanip>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec3.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(32) sfmat2x3
{
  union
  {
    flt32 _arr[6];
    struct
    {
      flt32 m00, m01, m02;
      flt32 m10, m11, m12;
    };
    sfvec3 rows[2];
  };

  constexpr explicit sfmat2x3(flt32 val = 0.0f);
  constexpr explicit sfmat2x3
  (
    flt32 x0, flt32 y0, flt32 z0,
    flt32 x1, flt32 y1, flt32 z1
  );

  constexpr explicit sfmat2x3(
    const sfvec3& row0,
    const sfvec3& row1
  );
  #ifdef USE_SIMD
  sfmat2x3
  (
    const __m128& r0,
    const __m128& r1
  );
  #endif // USE_SIMD

  //constexpr sfmat2x3(const sfmat2x3& m);
  
  sfmat2x3 operator+(const sfmat2x3& other) const;
  sfmat2x3 operator+=(const sfmat2x3& other);
  sfmat2x3 operator-(const sfmat2x3& other) const;
  sfmat2x3 operator-=(const sfmat2x3& other);
  sfmat2x3 operator*(flt32 val) const;
  sfmat2x3 operator*=(flt32 val);
  sfmat2x3 operator/(flt32 val) const;
  sfmat2x3 operator/=(flt32 val);

  flt32 Determinant();
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat2x3& m);
  #endif // DEBUG
};

//inline sfmat2x3 Transpose(const sfmat3x2& m);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfmat2x3::sfmat2x3
(
  flt32 x0, flt32 y0, flt32 z0,
  flt32 x1, flt32 y1, flt32 z1
)
: m00(x0), m01(y0), m02(z0),
  m10(x1), m11(y1), m12(z1) {}

inline constexpr sfmat2x3::sfmat2x3(flt32 val)
: m00(val), m01(val), m02(val),
  m10(val), m11(val), m12(val) {}

inline constexpr sfmat2x3::sfmat2x3
(
  const sfvec3& row0,
  const sfvec3& row1
)
: m00(row0.x), m01(row0.y), m02(row0.z),
  m10(row1.x), m11(row1.y), m12(row1.z) {}

/*
inline constexpr sfmat2x3::sfmat2x3(const sfmat2x3& m)
: m00(m.m00), m01(m.m01), m02(m.m02),
  m10(m.m10), m11(m.m11), m12(m.m12) {}
*/

#ifdef USE_SIMD
inline sfmat2x3::sfmat2x3
(
  const __m128& r0,
  const __m128& r1
)
{
  this->_arr[0] = r0[0];
  this->_arr[1] = r0[1];
  this->_arr[2] = r0[2];
  this->_arr[3] = r1[0];
  this->_arr[4] = r1[1];
  this->_arr[5] = r1[2];
}
#endif

inline sfmat2x3 sfmat2x3::operator+(const sfmat2x3& other) const
{
  sfvec3 r11 = this->rows[0];
  sfvec3 r12 = this->rows[1];

  sfvec3 r21 = other.rows[0];
  sfvec3 r22 = other.rows[1];

  return sfmat2x3(r11 + r12, r21 + r22);
}

inline sfmat2x3 sfmat2x3::operator+=(const sfmat2x3& other)
{
  __m128 m1 = _mm_loadu_ps(this->_arr);
  __m128 m2 = _mm_loadu_ps(other._arr);

  _mm_store_ps(this->_arr, _mm_add_ps(m1, m2));

  return *this;
}

inline sfmat2x3 sfmat2x3::operator-(const sfmat2x3& other) const
{
  sfvec3 r11 = this->rows[0];
  sfvec3 r12 = this->rows[1];

  sfvec3 r21 = other.rows[0];
  sfvec3 r22 = other.rows[1];

  return sfmat2x3(r11 - r12, r21 - r22);
}

inline sfmat2x3 sfmat2x3::operator-=(const sfmat2x3& other)
{
  __m128 m1 = _mm_loadu_ps(this->_arr);
  __m128 m2 = _mm_loadu_ps(other._arr);

  _mm_store_ps(this->_arr, _mm_sub_ps(m1, m2));

  return *this;
}

inline flt32 sfmat2x3::Determinant()
{
  __m128 m = _mm_load_ps(this->_arr);
  __m128 n = _mm_shuffle_ps(m, m, 0xBB);

  m = _mm_mul_ps(m, n);

  return m[0] - m[1];
}

/*
sfmat2x3 operator*(const sfmat2x3& other)
{
    __m128 r1 = _mm_load_ps(this->_arr);   // First Matrix
    __m128 r3 = _mm_load_ps(other._arr);       // Second Matrix

    __m128 r2 = _mm_shuffle_ps(r1, r1, 0xEE);
    r1 = _mm_shuffle_ps(r1, r1, 0x44);
    r3 = _mm_shuffle_ps(r3, r3, 0xD8);

    r1 = _mm_mul_ps(r1, r3);
    r2 = _mm_mul_ps(r2, r3);

    r1 = _mm_hadd_ps(r1, r1);
    r2 = _mm_hadd_ps(r2, r2);

    r2 = _mm_shuffle_ps(r1, r2, 0xE4);

    return sfmat2x3(r2);
}

sfmat2x3 operator*=(const sfmat2x3& other)
{
    __m128 r1 = _mm_load_ps(this->_arr);   // First Matrix
    __m128 r3 = _mm_load_ps(other._arr);       // Second Matrix

    __m128 r2 = _mm_shuffle_ps(r1, r1, 0xEE);
    r1 = _mm_shuffle_ps(r1, r1, 0x44);
    r3 = _mm_shuffle_ps(r3, r3, 0xD8);

    r1 = _mm_mul_ps(r1, r3);
    r2 = _mm_mul_ps(r2, r3);

    r1 = _mm_hadd_ps(r1, r1);
    r2 = _mm_hadd_ps(r2, r2);

    r2 = _mm_shuffle_ps(r1, r2, 0xE4);

    _mm_store_ps(this->_arr, r2);

    return *this;
}

sfmat2x3 operator*(flt32 f)
{
    __m128 m = _mm_load_ps(this->_arr);
    __m128 fl = _mm_load1_ps(&f);

    return sfmat2x3(_mm_mul_ps(m, fl));
}

sfmat2x3 operator*=(flt32 f)
{
    __m128 m = _mm_load_ps(this->_arr);
    __m128 fl = _mm_load1_ps(&f);

    _mm_store_ps(this->_arr, _mm_mul_ps(m, fl));

    return *this;
}

sfmat2x3 operator/(flt32 f)
{
    __m128 m = _mm_load_ps(this->_arr);
    __m128 fl = _mm_load1_ps(&f);

    return sfmat2x3(_mm_div_ps(m, fl));
}

sfmat2x3 operator/=(flt32 f)
{
    __m128 m = _mm_load_ps(this->_arr);
    __m128 fl = _mm_load1_ps(&f);

    _mm_store_ps(this->_arr, _mm_div_ps(m, fl));
    
    return *this;
}*/

/*#include "sfmat3x2.hpp"
inline sfmat2x3 Transpose(const sfmat3x2& m)
{
  __m128 r1 = _mm_loadu_ps(&m._arr[0]);
  __m128 r2 = _mm_loadu_ps(&m._arr[2]);

  __m128 s1 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 2, 2, 0));
  __m128 s2 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 3, 3, 1));

  return sfmat2x3(s1, s2);
}*/

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat2x3& m)
{
  os 
  << "{\t\t\t\t\t     }\n"
  << "|\t\t\t\t\t     |\n"
  << "|  " << std::setw(12) << m.m00 << "  " << std::setw(12) << m.m01 << "  " << std::setw(12) << m.m02 << "  |\n"
  << "|  " << std::setw(12) << m.m10 << "  " << std::setw(12) << m.m11 << "  " << std::setw(12) << m.m12 << "  |\n"
  << "|\t\t\t\t\t     |\n"
  << "{\t\t\t\t\t     }";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFMAT2X3_HPP