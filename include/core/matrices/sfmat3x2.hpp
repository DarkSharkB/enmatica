/** 
 * Single Precision Floating-Point 3x2 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT3X2_HPP
#define ENMA_SFMAT3X2_HPP

#include <iomanip>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec2.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(32) sfmat3x2
{
  union
  {
    flt32 _arr[6];
    struct
    {
      flt32 m00, m01;
      flt32 m10, m11;
      flt32 m20, m21;
    };
    sfvec2 rows[3];
  };

  constexpr explicit sfmat3x2(flt32 val = 0.0f);
  constexpr explicit sfmat3x2
  (
    flt32 x0, flt32 y0,
    flt32 x1, flt32 y1,
    flt32 x2, flt32 y2
  );

  constexpr explicit sfmat3x2
  (
    const sfvec2& row0,
    const sfvec2& row1,
    const sfvec2& row2
  );

  #ifdef USE_SIMD
  sfmat3x2(const __m128& hr0, const __m128& hr1);
  #endif // USE_SIMD
  
  //constexpr sfmat3x2(const sfmat3x2& m);

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat3x2& m);
  #endif // DEBUG
};

//inline sfmat3x2 Transpose(const sfmat2x3& m);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfmat3x2::sfmat3x2(flt32 val)
: m00(val), m01(val),
  m10(val), m11(val),
  m20(val), m21(val) {}

inline constexpr sfmat3x2::sfmat3x2
(
  flt32 x0, flt32 y0,
  flt32 x1, flt32 y1,
  flt32 x2, flt32 y2
)
: m00(x0), m01(y0), 
  m10(x1), m11(y1),
  m20(x2), m21(y2) {}

inline constexpr sfmat3x2::sfmat3x2
(
  const sfvec2& row0,
  const sfvec2& row1,
  const sfvec2& row2
)
: m00(row0.x), m01(row0.y), 
  m10(row1.x), m11(row1.y),
  m20(row2.x), m21(row2.y) {}

#ifdef USE_SIMD
inline sfmat3x2::sfmat3x2(const __m128& hr0, const __m128& hr1)
{
  this->_arr[0] = hr0[0];
  this->_arr[1] = hr0[1];
  this->_arr[2] = hr0[2];
  this->_arr[3] = hr1[0];
  this->_arr[4] = hr1[1];
  this->_arr[5] = hr1[2];
}
#endif // USE_SIMD

/*
inline constexpr sfmat3x2::sfmat3x2(const sfmat3x2& m)
: m00(m.m00), m01(m.m01),
  m10(m.m10), m11(m.m11),
  m20(m.m20), m21(m.m21) {}
  */

/*#include "sfmat2x3.hpp"
inline sfmat3x2 Transpose(const sfmat2x3& m)
{
  const __m128 r1 = _mm_loadu_ps(&m.arr[0]);
  const __m128 r2 = _mm_loadu_ps(&m._arr[2]);

  __m128 s1 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(0, 1, 3, 0));
  __m128 s2 = _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(2, 3, 0, 2));

  return sfmat3x2(s1, s2);
}*/

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat3x2& m)
{
  os 
  << "{\t\t\t       }\n"
  << "|\t\t\t       |\n"
  << "|  " << std::setw(12) << m.m00 << "  " << std::setw(12) << m.m01 << "  |\n"
  << "|  " << std::setw(12) << m.m10 << "  " << std::setw(12) << m.m11 << "  |\n"
  << "|  " << std::setw(12) << m.m20 << "  " << std::setw(12) << m.m21 << "  |\n"
  << "|\t\t\t       |\n"
  << "{\t\t\t       }";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFMAT3X2_HPP