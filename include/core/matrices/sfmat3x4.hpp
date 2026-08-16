/** Single Precision Floating-Point 3x4 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFMAT3X4_HPP
#define ENMA_SFMAT3X4_HPP

#include <iostream>
#include <iomanip>
#include "base.hpp"
#include "types.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct sfmat3x4
{
  union
  {
    struct
    {
      flt32 m00, m01, m02, m03;
      flt32 m10, m11, m12, m13;
      flt32 m20, m21, m22, m23;
    };
  };

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfmat3x4& m);
  #endif // DEBUG
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfmat3x4& m)
{
  os
  << "{\t\t\t\t\t}\n"
  << "|\t" << std::setw(8) << m.m00 << "\t" << std::setw(8) << m.m01 << "\t" << std::setw(8) << m.m02 << "\t" << std::setw(8) << m.m03 <<"\t|\n"
  << "|\t" << std::setw(8) << m.m10 << "\t" << std::setw(8) << m.m11 << "\t" << std::setw(8) << m.m12 << "\t" << std::setw(8) << m.m13 << "\t|\n"
  << "|\t" << std::setw(8) << m.m20 << "\t" << std::setw(8) << m.m21 << "\t" << std::setw(8) << m.m22 << "\t" << std::setw(8) << m.m23 << "\t|\n{\t\t\t\t\t}";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFMAT3X4_HPP