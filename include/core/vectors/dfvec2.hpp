/**
 * \brief 2 Component Double Precision Floating-Point Vector
 * 
 * \note This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_DFVEC2_HPP
#define ENMA_DFVEC2_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(16) dfvec2
{
  union 
  {
    flt64 _arr[2];
    struct
    {
      flt64 x, y;
    };
    struct
    {
      flt64 r, g;
    };
    struct
    {
      flt64 u, v;
    };

    DFVEC2_SWIZZLE(dfvec2);
  };

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const dfvec2& v);
  #endif // DEBUG
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const dfvec2& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << " )";
  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_DFVEC2_HPP