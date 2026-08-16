/**
 * \brief 3 Component Boolean Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_BVEC3_HPP
#define ENMA_BVEC3_HPP

#include <iostream>
#include "base.hpp"
#include "types.hpp"
#include "bvec2.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct bvec3
{
  union 
  {
    bln8 _arr[3];
    struct
    {
      bln8 x, y, z;
    };
  };
  
  constexpr explicit bvec3(bln8 val = false);
  constexpr explicit bvec3(bln8 x, bln8 y, bln8 z = false);
  constexpr explicit bvec3(bln8 x, const bvec2& yz);
  constexpr explicit bvec3(const bvec2& xy, bln8 z);
  
  //constexpr bvec3(const bvec3& v);
  //bvec3& operator=(const bvec3& other);

  bln8 operator==(const bvec3& other);
  bln8 operator!=(const bvec3& other);

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const bvec3& v);
  #endif // DEBUG
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//


inline constexpr bvec3::bvec3(bln8 val)
: x(val), y(val), z(val) {}

inline constexpr bvec3::bvec3(bln8 x, bln8 y, bln8 z)
: x(x), y(y), z(z) {}

inline constexpr bvec3::bvec3(bln8 x, const bvec2& yz)
: x(x), y(yz.x), z(yz.y) {}

inline constexpr bvec3::bvec3(const bvec2& xy, bln8 z)
: x(xy.x), y(xy.y), z(z) {}

/*
inline constexpr bvec3::bvec3(const bvec3& v) : x(v.x), y(v.y), z(v.z) {}

inline bvec3& bvec3::operator=(const bvec3& other)
{
  if(this != &other)
  {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
  }
  return *this;
}*/

inline bln8 bvec3::operator==(const bvec3& other)
{
  return this->x == other.x & this->y == other.y & this->z == other.z;
}

inline bln8 bvec3::operator!=(const bvec3& other)
{
  return this->x != other.x & this->y != other.y & this->z != other.z;
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const bvec3& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";
  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_BVEC3_HPP