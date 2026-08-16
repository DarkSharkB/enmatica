/**
 * \brief 2 Component Boolean Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_BVEC2_HPP
#define ENMA_BVEC2_HPP

#include <iostream>
#include "base.hpp"
#include "types.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct bvec2
{
  union 
  {
    bln8 _arr[2];
    struct
    {
      bln8 x, y;
    };
  };

  constexpr explicit bvec2(bln8 val = false);
  constexpr explicit bvec2(bln8 x, bln8 y);

  /*
  constexpr bvec2(const bvec2& v);
  bvec2& operator=(const bvec2& other);
  */

  bln8 operator==(const bvec2& other);
  bln8 operator!=(const bvec2& other);

  bvec2 Equals(const bvec2& other);
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const bvec2& v);
  #endif // DEBUG
};

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr bvec2::bvec2(bln8 val)
: x(val), y(val) {}

inline constexpr bvec2::bvec2(bln8 x, bln8 y)
: x(x), y(y) {}

/*
inline constexpr bvec2::bvec2(const bvec2& v)
: x(v.x), y(v.y) {}

inline bvec2& bvec2::operator=(const bvec2& other)
{
  if(this != &other)
  {
    this->x = other.x;
    this->y = other.y;
  }
  return *this;
}
*/

inline bln8 bvec2::operator==(const bvec2& other)
{
  return this->x == other.x & this->y == other.y;
}

inline bln8 bvec2::operator!=(const bvec2& other)
{
  return this->x != other.x & this->y != other.y;
}

inline bvec2 bvec2::Equals(const bvec2& other)
{
  return bvec2(this->x == other.x, this->y == other.y);
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const bvec2& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << " )";

  return os;
}
#endif // DEBUG

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_BVEC2_HPP