/**
 * \brief 4 Component Boolean Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_BVEC4_HPP
#define ENMA_BVEC4_HPP

#include <iostream>
#include "base.hpp"
#include "types.hpp"
#include "bvec2.hpp"
#include "bvec3.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct bvec4
{
  union
  {
    bln8 _arr[4];
    struct
    {
      bln8 x, y, z, w;
    };
  };

  constexpr explicit bvec4(bln8 val = false);
  constexpr explicit bvec4(bln8 x, bln8 y, bln8 z = false, bln8 w = false);
  constexpr explicit bvec4(const bvec2& xy, const bvec2& zw);
  constexpr explicit bvec4(bln8 x, const bvec3& yzw);
  constexpr explicit bvec4(const bvec3& xyz, bln8 w);
  
  //constexpr bvec4(const bvec4& v);

  bln8 operator==(const bvec4& other);
  bln8 operator!=(const bvec4& other);
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const bvec4& v);
  #endif // DEBUG
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr bvec4::bvec4(bln8 val)
: x(val), y(val), z(val), w(val) {}

inline constexpr bvec4::bvec4(bln8 x, bln8 y, bln8 z, bln8 w)
: x(x), y(y), z(z), w(w) {}

inline constexpr bvec4::bvec4(const bvec2& xy, const bvec2& zw)
: x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}

inline constexpr bvec4::bvec4(bln8 x, const bvec3& yzw)
: x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

inline constexpr bvec4::bvec4(const bvec3& xyz, bln8 w)
: x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

/*
inline constexpr bvec4::bvec4(const bvec4& v)
: x(v.x), y(v.y), z(v.z), w(v.w) {}
*/

inline bln8 bvec4::operator==(const bvec4& other)
{
  return this->x == other.x & this->y == other.y & this->z == other.z & this->w == other.w;
}

inline bln8 bvec4::operator!=(const bvec4& other)
{
  return this->x != other.x & this->y != other.y & this->z != other.z & this->w != other.w;
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const bvec4& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << "\tW: " << v.w << " )";
  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_BVEC4_HPP