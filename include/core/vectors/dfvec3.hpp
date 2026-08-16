/**
 * \brief 3 Component Double Precision Floating-Point Vector
 * 
 * \note This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_DFVEC3_HPP
#define ENMA_DFVEC3_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(32) dfvec3
{
  union 
  {
    flt64 _arr[3];
    struct
    {
      flt64 x, y, z;
    };
    struct
    {
      flt64 r, g, b;
    };

    DFVEC3_SWIZZLE(dfvec3);
  };
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const dfvec3& v);
  #endif // DEBUG
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const dfvec3& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";
  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_DFVEC3_HPP