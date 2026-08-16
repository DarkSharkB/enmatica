/** Single Precision Floating-Point 4x2 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT4X2_HPP
#define ENMA_SFMAT4X2_HPP

#include <iostream>
#include <iomanip>
#include "base.hpp"
#include "types.hpp"
#include "core/vectors/sfvec2.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(32) sfmat4x2
{
  union
  {
    flt32 _arr[8];
    struct
    {
      flt32 m00, m01;
      flt32 m10, m11;
      flt32 m20, m21;
      flt32 m30, m31;
    };
    sfvec2 rows[4];
  };
    
  constexpr explicit sfmat4x2
  (
    flt32 x0, flt32 y0,
    flt32 x1, flt32 y1, 
    flt32 x2, flt32 y2,
    flt32 x3, flt32 y3
  );

  constexpr sfmat4x2(const sfmat4x2& m);

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat4x2& m);
  #endif
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfmat4x2::sfmat4x2
(
  flt32 x0, flt32 y0, 
  flt32 x1, flt32 y1, 
  flt32 x2, flt32 y2, 
  flt32 x3, flt32 y3
)
: m00(x0), m01(y0), 
  m10(x1), m11(y1),
  m20(x2), m21(y2),
  m30(x3), m31(y3) {}

/*
inline constexpr sfmat4x2::sfmat4x2(const sfmat4x2& m)
: m00(m.m00), m01(m.m01),
  m10(m.m10), m11(m.m11),
  m20(m.m20), m21(m.m21),
  m30(m.m30), m31(m.m31) {}
*/
    
#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat4x2& m)
{
  os << "{\t\t\t\t\t}\n"
  << "|\t" << std::setw(8) << m.m00 << "\t" << std::setw(8) << m.m01 << "\t|\n"
  << "|\t" << std::setw(8) << m.m10 << "\t" << std::setw(8) << m.m11 << "\t|\n"
  << "|\t" << std::setw(8) << m.m20 << "\t" << std::setw(8) << m.m21 << "\t|\n"
  << "|\t" << std::setw(8) << m.m30 << "\t" << std::setw(8) << m.m31 << "\t|\n{\t\t\t\t\t}";

  return os;
}
#endif // DEBUG
ENMA_NS_END

#endif // ENMA_SFMAT4X2_HPP