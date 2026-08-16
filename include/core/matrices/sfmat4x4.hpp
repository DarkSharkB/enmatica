/** Single Precision Floating-Point 4x4 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT4X4_HPP
#define ENMA_SFMAT4X4_HPP

#include <iostream>
#include <iomanip>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec4.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct sfmat4x4
{
  union
  {
    flt32 _arr[16];
    struct
    {
      flt32 m00, m01, m02, m03;
      flt32 m10, m11, m12, m13;
      flt32 m20, m21, m22, m23;
      flt32 m30, m31, m32, m33;
    };
    sfvec4 rows[4];
    
    #ifdef USE_SIMD
    __m128 _vals[4];
    __m256_u _vals2[2];
    #endif // USE_SIMD
  };

  constexpr explicit sfmat4x4(flt32 val = 0.0f);
  constexpr explicit sfmat4x4
  (
    flt32 x0, flt32 y0, flt32 z0, flt32 w0,
    flt32 x1, flt32 y1, flt32 z1, flt32 w1,
    flt32 x2, flt32 y2, flt32 z2, flt32 w2,
    flt32 x3, flt32 y3, flt32 z3, flt32 w3
  );
  constexpr explicit sfmat4x4
  (
    const sfvec4& row0,
    const sfvec4& row1,
    const sfvec4& row2,
    const sfvec4& row3
  );

  #ifdef USE_SIMD
  sfmat4x4(const __m128& r1, const __m128& r2, const __m128& r3, const __m128& r4);
  sfmat4x4(const __m256& r12, const __m256& r34);
  #endif // USE_SIMD

  /*
  constexpr sfmat4x4(const sfmat4x4& m);
  sfmat4x4& operator=(const sfmat4x4& other);
  */

  sfvec4 operator[](uint32 rowIndex) const;

  sfmat4x4 operator+(const sfmat4x4& other) const;
  sfmat4x4& operator+=(const sfmat4x4& other);
  sfmat4x4 operator+(flt32 val) const;
  sfmat4x4 operator-() const;
  sfmat4x4 operator-(const sfmat4x4& other) const;
  sfmat4x4& operator-=(const sfmat4x4& other);
  sfmat4x4 operator*(const sfmat4x4& other) const;
  sfmat4x4& operator*=(const sfmat4x4& other);
  sfmat4x4 operator*(flt32 val) const;
  sfmat4x4 operator/(flt32 val) const;
  sfvec4 operator*(const sfvec4& other) const;

  static constexpr sfmat4x4 Identity();
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat4x4& m);
  #endif // DEBUG

  static const sfmat4x4 zero;
  static const sfmat4x4 identity;
};
using sfmat4 = sfmat4x4;

inline sfmat4x4 Transpose(const sfmat4x4& m);
inline sfmat4x4 AffineInverse(const sfmat4x4& m);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfmat4x4::sfmat4x4(flt32 val)
: m00(val), m01(val), m02(val), m03(val),
  m10(val), m11(val), m12(val), m13(val), 
  m20(val), m21(val), m22(val), m23(val),
  m30(val), m31(val), m32(val), m33(val) {}

inline constexpr sfmat4x4::sfmat4x4
(
  flt32 x0, flt32 y0, flt32 z0, flt32 w0,
  flt32 x1, flt32 y1, flt32 z1, flt32 w1,
  flt32 x2, flt32 y2, flt32 z2, flt32 w2,
  flt32 x3, flt32 y3, flt32 z3, flt32 w3
) 
: m00(x0), m01(y0), m02(z0), m03(w0),
  m10(x1), m11(y1), m12(z1), m13(w1),
  m20(x2), m21(y2), m22(z2), m23(w2),
  m30(x3), m31(y3), m32(z3), m33(w3) {}

/*
inline constexpr sfmat4x4::sfmat4x4(const sfmat4x4& m)
: m00(m.m00), m01(m.m01), m02(m.m02), m03(m.m03),
  m10(m.m10), m11(m.m11), m12(m.m12), m13(m.m13), 
  m20(m.m20), m21(m.m21), m22(m.m22), m23(m.m23),
  m30(m.m30), m31(m.m31), m32(m.m32), m33(m.m33) {}

inline sfmat4x4& sfmat4x4::operator=(const sfmat4x4& other)
{
  if(this != &other)
  {
    this->rows[0] = other.rows[0];
    this->rows[1] = other.rows[1];
    this->rows[2] = other.rows[2];
    this->rows[3] = other.rows[3];
  }
  return *this;
}
*/

inline sfmat4x4 sfmat4x4::operator-() const
{
  return sfmat4x4(
    -m00, -m01, -m02, -m03, 
    -m10, -m11, -m12, -m13, 
    -m20, -m21, -m22, -m23, 
    -m30, -m31, -m32, -m33
  );
}

#ifndef USE_SIMD
inline sfmat4x4::sfmat4x4(const sfvec4& row0, const sfvec4& row1, const sfvec4& row2, const sfvec4& row3)
{
  memcpy(this->_arr, row0._arr, 4 * sizeof(flt32));
  memcpy(this->_arr+4  * sizeof(flt32), row1._arr, 4 * sizeof(flt32));
  memcpy(this->_arr+8  * sizeof(flt32), row2._arr, 4 * sizeof(flt32));
  memcpy(this->_arr+12 * sizeof(flt32), row3._arr, 4 * sizeof(flt32));
}

#else // USE_SIMD
inline constexpr sfmat4x4::sfmat4x4
(
  const sfvec4& row0,
  const sfvec4& row1,
  const sfvec4& row2,
  const sfvec4& row3
)
: m00(row0.x), m01(row0.y), m02(row0.z), m03(row0.w),
  m10(row1.x), m11(row1.y), m12(row1.z), m13(row1.w),
  m20(row2.x), m21(row2.y), m22(row2.z), m23(row2.w),
  m30(row3.x), m31(row3.y), m32(row3.z), m33(row3.w) {}

inline sfmat4x4::sfmat4x4
(
  const __m128& r1,
  const __m128& r2,
  const __m128& r3,
  const __m128& r4
)
{
  this->_vals[0] = r1;
  this->_vals[1] = r2;
  this->_vals[2] = r3;
  this->_vals[3] = r4;
}

inline sfmat4x4::sfmat4x4(const __m256& r12, const __m256& r34)
{
  this->_vals2[0] = r12;
  this->_vals2[1] = r34;
}

inline sfvec4 sfmat4x4::operator[](uint32 rowIndex) const
{
  return this->rows[rowIndex];
}

inline sfmat4x4 sfmat4x4::operator+(const sfmat4x4& other) const
{
  __m256 r11 = this->_vals2[0];
  __m256 r12 = this->_vals2[1];

  __m256 r21 = other._vals2[0];
  __m256 r22 = other._vals2[1];


  r11 = _mm256_add_ps(r11, r21);
  r12 = _mm256_add_ps(r12, r22);

  return sfmat4x4(r11, r12);
}

inline sfmat4x4& sfmat4x4::operator+=(const sfmat4x4& other)
{
  __m256 r11 = this->_vals2[0];
  __m256 r12 = this->_vals2[1];

  __m256 r21 = other._vals2[0];
  __m256 r22 = other._vals2[1];

  r11 = _mm256_add_ps(r11, r21);
  r12 = _mm256_add_ps(r12, r22);

  *this = sfmat4x4(r11, r12);

  return *this;
}

inline sfmat4x4 sfmat4x4::operator+(flt32 val) const
{
  __m256 addv = _mm256_set1_ps(val);

  __m256 r1 = this->_vals2[0];
  __m256 r2 = this->_vals2[1];

  r1 = _mm256_add_ps(r1, addv);
  r2 = _mm256_add_ps(r2, addv);

  return sfmat4x4(r1, r2);
}

inline sfmat4x4 sfmat4x4::operator-(const sfmat4x4& other) const
{
  __m256 r11 = this->_vals2[0];
  __m256 r12 = this->_vals2[1];

  __m256 r21 = other._vals2[0];
  __m256 r22 = other._vals2[1];

  r11 = _mm256_sub_ps(r11, r21);
  r12 = _mm256_sub_ps(r12, r22);

  return sfmat4x4(r11, r12);
}
  
inline sfmat4x4& sfmat4x4::operator-=(const sfmat4x4& other)
{
  __m256 r11 = this->_vals2[0];
  __m256 r12 = this->_vals2[1];

  __m256 r21 = other._vals2[0];
  __m256 r22 = other._vals2[1];

  r11 = _mm256_sub_ps(r11, r21);
  r12 = _mm256_sub_ps(r12, r22);

  *this = sfmat4x4(r11, r12);

  return *this;
}

inline sfmat4x4 sfmat4x4::operator*(const sfmat4x4& other) const
{
  flt32 a[4] = { 0, 0, 0, 0 }, 
        b[4] = { 0, 0, 0, 0 }, 
        c[4] = { 0, 0, 0, 0 }, 
        d[4] = { 0, 0, 0, 0 }; 

  __m128 r00, r01, r02, r03;
  __m128 r10, r11, r12, r13;
  __m128 i1, i2, i3, i4;

  r00 = this->_vals[0];
  r01 = this->_vals[1];
  r02 = this->_vals[2];
  r03 = this->_vals[3];

  r10 = other._vals[0];
  r11 = other._vals[1];
  r12 = other._vals[2];
  r13 = other._vals[3];

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

  return sfmat4x4
  {
    a[0], a[1], a[2], a[3],
    b[0], b[1], b[2], b[3],
    c[0], c[1], c[2], c[3],
    d[0], d[1], d[2], d[3]
  };
}

/*inline sfvec4 sfvec4::operator*(const sfmat4x4& other)
{
  sfvec4 v = this->_vals;
  sfmat4x4 m = Transpose(other);

  flt32 x = _mm_dp_ps(v, m._vals[0], 0xFF)[0];
  flt32 y = _mm_dp_ps(v, m._vals[1], 0xFF)[0];
  flt32 z = _mm_dp_ps(v, m._vals[2], 0xFF)[0];
  flt32 w = _mm_dp_ps(v, m._vals[3], 0xFF)[0];

  return sfvec4(x, y, z, w);
}*/

inline sfvec4 sfmat4x4::operator*(const sfvec4& other) const
{
  __m128 r00 = this->_vals[0];
  __m128 r01 = this->_vals[1];
  __m128 r02 = this->_vals[2];
  __m128 r03 = this->_vals[3];

  __m128 v41 = other;

  r00 = _mm_dp_ps(r00, v41, 0xFF);
  r01 = _mm_dp_ps(r01, v41, 0xFF);
  r02 = _mm_dp_ps(r02, v41, 0xFF);
  r03 = _mm_dp_ps(r03, v41, 0xFF);

  return sfvec4(r00[0], r01[0], r02[0], r03[0]);
}

inline sfmat4x4& sfmat4x4::operator*=(const sfmat4x4& other)
{
  /*flt32 	a[4] = { 0, 0, 0, 0 }, 
      b[4] = { 0, 0, 0, 0 }, 
      c[4] = { 0, 0, 0, 0 }, 
      d[4] = { 0, 0, 0, 0 }; */
      
  __m128 r00 = this->_vals[0];
  __m128 r01 = this->_vals[1];
  __m128 r02 = this->_vals[2];
  __m128 r03 = this->_vals[3];

  __m128 r10 = other._vals[0];
  __m128 r11 = other._vals[1];
  __m128 r12 = other._vals[2];
  __m128 r13 = other._vals[3];

  _MM_TRANSPOSE4_PS(r10, r11, r12, r13);
  
  __m128 i1 = _mm_dp_ps(r00, r10, 0xFF);
  __m128 i2 = _mm_dp_ps(r00, r11, 0xFF);
  __m128 i3 = _mm_dp_ps(r00, r12, 0xFF);
  __m128 i4 = _mm_dp_ps(r00, r13, 0xFF);

  this->_arr[0] = i1[0];
  this->_arr[1] = i2[0];
  this->_arr[2] = i3[0];
  this->_arr[3] = i4[0];

  i1 = _mm_dp_ps(r01, r10, 0xFF);
  i2 = _mm_dp_ps(r01, r11, 0xFF);
  i3 = _mm_dp_ps(r01, r12, 0xFF);
  i4 = _mm_dp_ps(r01, r13, 0xFF);

  this->_arr[4] = i1[0];
  this->_arr[5] = i2[0];
  this->_arr[6] = i3[0];
  this->_arr[7] = i4[0];

  i1 = _mm_dp_ps(r02, r10, 0xFF);
  i2 = _mm_dp_ps(r02, r11, 0xFF);
  i3 = _mm_dp_ps(r02, r12, 0xFF);
  i4 = _mm_dp_ps(r02, r13, 0xFF);

  /*c[0] = i1[0];
  c[1] = i2[0];
  c[2] = i3[0];
  c[3] = i4[0];*/

  this->_arr[8] = i1[0];
  this->_arr[9] = i2[0];
  this->_arr[10] = i3[0];
  this->_arr[11] = i4[0];


  i1 = _mm_dp_ps(r03, r10, 0xFF);
  i2 = _mm_dp_ps(r03, r11, 0xFF);
  i3 = _mm_dp_ps(r03, r12, 0xFF);
  i4 = _mm_dp_ps(r03, r13, 0xFF);

  this->_arr[12] = i1[0];
  this->_arr[13] = i2[0];
  this->_arr[14] = i3[0];
  this->_arr[15] = i4[0];


  //*this = sfmat4x4(sfvec4(a), sfvec4(b), sfvec4(c), sfvec4(d));

  return *this;
}

inline sfmat4x4 sfmat4x4::operator*(flt32 val) const
{
  __m256 rfl = _mm256_set1_ps(val);

  __m256 r12 = this->_vals2[0];
  __m256 r34 = this->_vals2[1];

  return sfmat4x4(_mm256_mul_ps(r12, rfl), _mm256_mul_ps(r34, rfl));
}

inline sfmat4x4 sfmat4x4::operator/(flt32 val) const
{
  __m256 rfl = _mm256_div_ps(_mm256_set1_ps(1.0f), _mm256_set1_ps(val));

  __m256 r12 = this->_vals2[0];
  __m256 r34 = this->_vals2[1];

  return sfmat4x4(_mm256_mul_ps(r12, rfl), _mm256_mul_ps(r34, rfl));
}

inline constexpr sfmat4x4 sfmat4x4::Identity()
{
  return sfmat4x4
  {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
} 

inline sfmat4x4 Transpose(const sfmat4x4& m)
{
  __m128 r1 = m._vals[0];
  __m128 r2 = m._vals[1];
  __m128 r3 = m._vals[2];
  __m128 r4 = m._vals[3];

  _MM_TRANSPOSE4_PS(r1, r2, r3, r4);

  return sfmat4x4(r1, r2, r3, r4);
}
#endif // !USE_SIMD && USE_SIMD

inline sfmat4x4 Inverse(const sfmat4x4& m)
{
  // TODO: Implementation
  return m;
}

inline sfmat4x4 AffineInverse(const sfmat4x4& m)
{
  sfvec3 t = -sfvec3(m.rows[3].xyz);
  sfvec3 position = sfvec3
                    (
                      sfvec3(m.rows[0].xyz).Dot(t),
                      sfvec3(m.rows[1].xyz).Dot(t),
                      sfvec3(m.rows[2].xyz).Dot(t)
                    );

  flt32 m01 = m.m10;
  flt32 m02 = m.m20;
  flt32 m12 = m.m21;

  return sfmat4x4
  {
    m.m00,  m01,    m02,    0.0f,
    m.m01,  m.m11,  m12,    0.0f,
    m.m02,  m.m12,  m.m22,  0.0f,
    position.x, position.y, position.z, 1.0f
  };
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat4x4& m)
{
  os 
  << "\n{\t\t\t\t\t\t\t\t\t}\n"
  << "|\t" << std::setw(8) << m.m00 << "\t" << std::setw(8) << m.m01 << "\t" << std::setw(8) << m.m02 << "\t" << std::setw(8) << m.m03 << "\t|\n"
  << "|\t" << std::setw(8) << m.m10 << "\t" << std::setw(8) << m.m11 << "\t" << std::setw(8) << m.m12 << "\t" << std::setw(8) << m.m13 << "\t|\n"
  << "|\t" << std::setw(8) << m.m20 << "\t" << std::setw(8) << m.m21 << "\t" << std::setw(8) << m.m22 << "\t" << std::setw(8) << m.m23 << "\t|\n"
  << "|\t" << std::setw(8) << m.m30 << "\t" << std::setw(8) << m.m31 << "\t" << std::setw(8) << m.m32 << "\t" << std::setw(8) << m.m33 << "\t|\n{\t\t\t\t\t\t\t\t\t}";

  return os;
}
#endif // DEBUG

inline constexpr sfmat4x4 sfmat4x4::zero     = sfmat4x4();
inline constexpr sfmat4x4 sfmat4x4::identity = sfmat4x4::Identity();

//================ Implementation Ends ================//
ENMA_NS_END


#endif // ENMA_SFMAT4X4_HPP