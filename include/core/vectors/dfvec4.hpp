/**
 * \brief 4 Component Double Precision Floating-Point Vector
 * 
 * \note This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_DFVEC4_HPP
#define ENMA_DFVEC4_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(32) dfvec4
{
  union
  {
    flt64 _arr[4];
    struct
    {
      flt64 x, y, z, w;
    };
    struct
    {
      flt64 r, g, b, a;
    };

    DFVEC4_SWIZZLE(dfvec4);
  };
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const dfvec4& v);
  #endif // DEBUG
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const dfvec4& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << "\tW: " << v.w << " )";
  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_DFVEC4_HPP