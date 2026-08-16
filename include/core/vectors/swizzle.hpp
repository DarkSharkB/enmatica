/* Vector Component Swizzle Helpers
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SWIZZLE_HPP
#define ENMA_SWIZZLE_HPP

#include <iostream>
#include "base.hpp"
#include "types.hpp"

#define CONCATENATE(a, b) a ## b
#define CONCATENATE_3(a, b, c) a ## b ## c
#define CONCATENATE_4(a, b, c, d) a ## b ## c ## d

#define MAKE_XYZW_COMPONENT(a) COMPONENT_XYZW_ ## a
#define MAKE_RGBA_COMPONENT(a) COMPONENT_RGBA_ ## a
#define MAKE_UV_COMPONENT(a) COMPONENT_UV_ ## a

#define COMPONENT_XYZW_0 x
#define COMPONENT_XYZW_1 y
#define COMPONENT_XYZW_2 z
#define COMPONENT_XYZW_3 w

#define COMPONENT_RGBA_0 r
#define COMPONENT_RGBA_1 g
#define COMPONENT_RGBA_2 b
#define COMPONENT_RGBA_3 a

#define COMPONENT_UV_0 u
#define COMPONENT_UV_1 v

#define COMBINE_2(a, b) CONCATENATE(a, b)
#define COMBINE_3(a, b, c) CONCATENATE_3(a, b, c)
#define COMBINE_4(a, b, c, d) CONCATENATE_4(a, b, c, d)

#define CONCATENATE_XYZW_2_COMPONENTS(a, b) COMBINE_2(MAKE_XYZW_COMPONENT(a), MAKE_XYZW_COMPONENT(b))             
#define CONCATENATE_XYZW_3_COMPONENTS(a, b, c) COMBINE_3(MAKE_XYZW_COMPONENT(a), MAKE_XYZW_COMPONENT(b), MAKE_XYZW_COMPONENT(c))
#define CONCATENATE_XYZW_4_COMPONENTS(a, b, c, d) COMBINE_4(MAKE_XYZW_COMPONENT(a), MAKE_XYZW_COMPONENT(b), MAKE_XYZW_COMPONENT(c), MAKE_XYZW_COMPONENT(d))

#define CONCATENATE_RGBA_2_COMPONENTS(a, b) COMBINE_2(MAKE_RGBA_COMPONENT(a), MAKE_RGBA_COMPONENT(b))
#define CONCATENATE_RGBA_3_COMPONENTS(a, b, c) COMBINE_3(MAKE_RGBA_COMPONENT(a), MAKE_RGBA_COMPONENT(b), MAKE_RGBA_COMPONENT(c))
#define CONCATENATE_RGBA_4_COMPONENTS(a, b, c, d) COMBINE_4(MAKE_RGBA_COMPONENT(a), MAKE_RGBA_COMPONENT(b), MAKE_RGBA_COMPONENT(c), MAKE_RGBA_COMPONENT(d))

#define CONCATENATE_UV_2_COMPONENTS(a, b) COMBINE_2(MAKE_UV_COMPONENT(a), MAKE_UV_COMPONENT(b))

ENMA_NS_START
template<typename _OutType, typename _BaseType, uint32 _A, uint32 _B, uint32 _Size>
struct swizzle2
{
  _BaseType arr[_Size];

  _OutType operator=(const _OutType& v)
  {
    static_assert(_A != _B, "Cannot assign to vector of identical swizzle. Must be different.");
    arr[_A] = v.x;
    arr[_B] = v.y;

    return *this;
  }

  operator _OutType() const
  {
    return _OutType(arr[_A], arr[_B]);
  }

  template<typename _CastType>
  operator _CastType() const
  {
    return _CastType(arr[_A], arr[_B]);
  }

  friend std::ostream& operator<<(std::ostream& os, const swizzle2& v)
  {
    os << "( X: " << v.arr[_A] << "\tY: " << v.arr[_B] << " )";
    return os;
  }
};

template<typename _OutType, typename _BaseType, uint32 _A, uint32 _B, uint32 _C, uint32 _Size>
struct swizzle3
{
  _BaseType arr[_Size];

  _OutType operator=(const _OutType& v)
  {
    static_assert(_A != _B && _B != _C && _C != _A, "Cannot assign to vector of identical swizzle. Must be different.");
    arr[_A] = v.x;
    arr[_B] = v.y;
    arr[_C] = v.z;

    return *this;
  }

  operator _OutType() const
  {
    return _OutType(arr[_A], arr[_B], arr[_C]);
  }

  template<typename _CastType>
  operator _CastType() const
  {
    return _CastType(arr[_A], arr[_B], arr[_C]);
  }

  friend std::ostream& operator<<(std::ostream& os, const swizzle3& v)
  {
    os << "( X: " << v.arr[_A] << "\tY: " << v.arr[_B] << "\tZ: " << v.arr[_C] << " )";
    return os;
  }
};

template<typename _OutType, typename _BaseType, uint32 _A, uint32 _B, uint32 _C, uint32 _D, uint32 _Size>
struct swizzle4
{
  _BaseType arr[_Size];

  _OutType operator=(const _OutType& v)
  {
    static_assert(_A != _B && _B != _C && _C != _D && _D != _A, "Cannot assign to vector of identical swizzle. Must be different.");
    arr[_A] = v.x;
    arr[_B] = v.y;
    arr[_C] = v.z;
    arr[_D] = v.w;

    return *this;
  }

  operator _OutType() const
  {
    return _OutType(arr[_A], arr[_B], arr[_C], arr[_D]);
  }

  template<typename _CastType>
  operator _CastType() const
  {
    return _CastType(arr[_A], arr[_B], arr[_C], arr[_D]);
  }

  friend std::ostream& operator<<(std::ostream& os, const swizzle4& v)
  {
    os << "( X: " << v.arr[_A] << "\tY: " << v.arr[_B] << "\tZ: " << v.arr[_C] << "\tW: " << v.arr[_D] << " )";
    return os;
  }
};
ENMA_NS_END

#define VEC2_SWIZZLE2(outType, a, b, primitiveType)                                             \
  swizzle2<outType, primitiveType, a, b, 2> CONCATENATE_XYZW_2_COMPONENTS(a, b);                \
  swizzle2<outType, primitiveType, a, b, 2> CONCATENATE_RGBA_2_COMPONENTS(a, b);

#define VEC3_SWIZZLE2(outType, a, b, primitiveType)                                             \
  swizzle2<outType, primitiveType, a, b, 3> CONCATENATE_XYZW_2_COMPONENTS(a, b);                \
  swizzle2<outType, primitiveType, a, b, 3> CONCATENATE_RGBA_2_COMPONENTS(a, b);

#define VEC4_SWIZZLE2(outType, a, b, primitiveType)                                             \
  swizzle2<outType, primitiveType, a, b, 4> CONCATENATE_XYZW_2_COMPONENTS(a, b);                \
  swizzle2<outType, primitiveType, a, b, 4> CONCATENATE_RGBA_2_COMPONENTS(a, b);

#define VEC2_SWIZZLE3(outType, a, b, c, primitiveType)                                          \
  swizzle3<outType, primitiveType, a, b, c, 2> CONCATENATE_XYZW_3_COMPONENTS(a, b, c);          \
  swizzle3<outType, primitiveType, a, b, c, 2> CONCATENATE_RGBA_3_COMPONENTS(a, b, c);

#define VEC3_SWIZZLE3(outType, a, b, c, primitiveType)                                          \
  swizzle3<outType, primitiveType, a, b, c, 3> CONCATENATE_XYZW_3_COMPONENTS(a, b, c);          \
  swizzle3<outType, primitiveType, a, b, c, 3> CONCATENATE_RGBA_3_COMPONENTS(a, b, c);

#define VEC4_SWIZZLE3(outType, a, b, c, primitiveType)                                          \
  swizzle3<outType, primitiveType, a, b, c, 4> CONCATENATE_XYZW_3_COMPONENTS(a, b, c);          \
  swizzle3<outType, primitiveType, a, b, c, 4> CONCATENATE_RGBA_3_COMPONENTS(a, b, c);

#define VEC2_SWIZZLE4(outType, a, b, c, d, primitiveType)                                       \
  swizzle4<outType, primitiveType, a, b, c, d, 2> CONCATENATE_XYZW_4_COMPONENTS(a, b, c, d);    \
  swizzle4<outType, primitiveType, a, b, c, d, 2> CONCATENATE_RGBA_4_COMPONENTS(a, b, c, d);

#define VEC3_SWIZZLE4(outType, a, b, c, d, primitiveType)                                       \
  swizzle4<outType, primitiveType, a, b, c, d, 3> CONCATENATE_XYZW_4_COMPONENTS(a, b, c, d);    \
  swizzle4<outType, primitiveType, a, b, c, d, 3> CONCATENATE_RGBA_4_COMPONENTS(a, b, c, d);

#define VEC4_SWIZZLE4(outType, a, b, c, d, primitiveType)                                       \
  swizzle4<outType, primitiveType, a, b, c, d, 4> CONCATENATE_XYZW_4_COMPONENTS(a, b, c, d);    \
  swizzle4<outType, primitiveType, a, b, c, d, 4> CONCATENATE_RGBA_4_COMPONENTS(a, b, c, d);

#define VEC2_SWIZZLE(outType, primitiveType)            \
  VEC2_SWIZZLE2(outType, 0, 0, primitiveType)           \
  VEC2_SWIZZLE2(outType, 0, 1, primitiveType)           \
  VEC2_SWIZZLE2(outType, 1, 0, primitiveType)           \
  VEC2_SWIZZLE2(outType, 1, 1, primitiveType)           \
                                                        \
  VEC2_SWIZZLE3(outType, 0, 0, 0, primitiveType)        \
  VEC2_SWIZZLE3(outType, 0, 0, 1, primitiveType)        \
  VEC2_SWIZZLE3(outType, 0, 1, 0, primitiveType)        \
  VEC2_SWIZZLE3(outType, 0, 1, 1, primitiveType)        \
  VEC2_SWIZZLE3(outType, 1, 0, 0, primitiveType)        \
  VEC2_SWIZZLE3(outType, 1, 0, 1, primitiveType)        \
  VEC2_SWIZZLE3(outType, 1, 1, 0, primitiveType)        \
  VEC2_SWIZZLE3(outType, 1, 1, 1, primitiveType)        \
                                                        \
  VEC2_SWIZZLE4(outType, 0, 0, 0, 0, primitiveType)     \
  VEC2_SWIZZLE4(outType, 0, 0, 0, 1, primitiveType)     \
  VEC2_SWIZZLE4(outType, 0, 0, 1, 0, primitiveType)     \
  VEC2_SWIZZLE4(outType, 0, 0, 1, 1, primitiveType)     \
  VEC2_SWIZZLE4(outType, 0, 1, 0, 0, primitiveType)     \
  VEC2_SWIZZLE4(outType, 0, 1, 0, 1, primitiveType)     \
  VEC2_SWIZZLE4(outType, 0, 1, 1, 0, primitiveType)     \
  VEC2_SWIZZLE4(outType, 0, 1, 1, 1, primitiveType)     \
  VEC2_SWIZZLE4(outType, 1, 0, 0, 0, primitiveType)     \
  VEC2_SWIZZLE4(outType, 1, 0, 0, 1, primitiveType)     \
  VEC2_SWIZZLE4(outType, 1, 0, 1, 0, primitiveType)     \
  VEC2_SWIZZLE4(outType, 1, 0, 1, 1, primitiveType)     \
  VEC2_SWIZZLE4(outType, 1, 1, 0, 0, primitiveType)     \
  VEC2_SWIZZLE4(outType, 1, 1, 0, 1, primitiveType)     \
  VEC2_SWIZZLE4(outType, 1, 1, 1, 0, primitiveType)     \
  VEC2_SWIZZLE4(outType, 1, 1, 1, 1, primitiveType)

#define VEC3_SWIZZLE(outType, primitiveType)            \
  VEC3_SWIZZLE2(outType, 0, 0, primitiveType)           \
  VEC3_SWIZZLE2(outType, 0, 1, primitiveType)           \
  VEC3_SWIZZLE2(outType, 0, 2, primitiveType)           \
  VEC3_SWIZZLE2(outType, 1, 0, primitiveType)           \
  VEC3_SWIZZLE2(outType, 1, 1, primitiveType)           \
  VEC3_SWIZZLE2(outType, 1, 2, primitiveType)           \
  VEC3_SWIZZLE2(outType, 2, 0, primitiveType)           \
  VEC3_SWIZZLE2(outType, 2, 1, primitiveType)           \
  VEC3_SWIZZLE2(outType, 2, 2, primitiveType)           \
                                                        \
  VEC3_SWIZZLE3(outType, 0, 0, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 0, 0, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 0, 0, 2, primitiveType)        \
  VEC3_SWIZZLE3(outType, 0, 1, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 0, 1, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 0, 1, 2, primitiveType)        \
  VEC3_SWIZZLE3(outType, 0, 2, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 0, 2, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 0, 2, 2, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 0, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 0, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 0, 2, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 1, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 1, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 1, 2, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 2, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 2, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 1, 2, 2, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 0, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 0, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 0, 2, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 1, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 1, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 1, 2, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 2, 0, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 2, 1, primitiveType)        \
  VEC3_SWIZZLE3(outType, 2, 2, 2, primitiveType)        \
                                                        \
  VEC3_SWIZZLE4(outType, 0, 0, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 0, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 0, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 0, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 0, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 0, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 0, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 0, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 0, 2, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 1, 2, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 0, 2, 2, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 0, 2, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 1, 2, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 1, 2, 2, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 0, 2, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 1, 2, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 0, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 0, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 0, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 1, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 1, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 1, 2, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 2, 0, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 2, 1, primitiveType)     \
  VEC3_SWIZZLE4(outType, 2, 2, 2, 2, primitiveType)

#define VEC4_SWIZZLE(outType, primitiveType)            \
  VEC4_SWIZZLE2(outType, 0, 0, primitiveType)           \
  VEC4_SWIZZLE2(outType, 0, 1, primitiveType)           \
  VEC4_SWIZZLE2(outType, 0, 2, primitiveType)           \
  VEC4_SWIZZLE2(outType, 0, 3, primitiveType)           \
  VEC4_SWIZZLE2(outType, 1, 0, primitiveType)           \
  VEC4_SWIZZLE2(outType, 1, 1, primitiveType)           \
  VEC4_SWIZZLE2(outType, 1, 2, primitiveType)           \
  VEC4_SWIZZLE2(outType, 1, 3, primitiveType)           \
  VEC4_SWIZZLE2(outType, 2, 0, primitiveType)           \
  VEC4_SWIZZLE2(outType, 2, 1, primitiveType)           \
  VEC4_SWIZZLE2(outType, 2, 2, primitiveType)           \
  VEC4_SWIZZLE2(outType, 2, 3, primitiveType)           \
  VEC4_SWIZZLE2(outType, 3, 0, primitiveType)           \
  VEC4_SWIZZLE2(outType, 3, 1, primitiveType)           \
  VEC4_SWIZZLE2(outType, 3, 2, primitiveType)           \
  VEC4_SWIZZLE2(outType, 3, 3, primitiveType)           \
                                                        \
  VEC4_SWIZZLE3(outType, 0, 0, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 0, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 0, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 0, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 1, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 1, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 1, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 1, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 2, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 2, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 2, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 2, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 3, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 3, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 3, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 0, 3, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 0, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 0, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 0, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 0, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 1, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 1, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 1, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 1, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 2, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 2, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 2, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 2, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 3, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 3, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 3, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 1, 3, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 0, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 0, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 0, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 0, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 1, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 1, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 1, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 1, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 2, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 2, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 2, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 2, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 3, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 3, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 3, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 2, 3, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 0, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 0, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 0, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 0, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 1, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 1, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 1, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 1, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 2, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 2, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 2, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 2, 3, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 3, 0, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 3, 1, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 3, 2, primitiveType)        \
  VEC4_SWIZZLE3(outType, 3, 3, 3, primitiveType)        \
                                                        \
  VEC4_SWIZZLE4(outType, 0, 0, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 0, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 1, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 2, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 0, 3, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 0, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 1, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 2, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 1, 3, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 0, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 1, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 2, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 2, 3, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 0, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 1, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 2, 3, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 0, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 0, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 0, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 0, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 1, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 1, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 1, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 1, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 2, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 2, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 2, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 2, 3, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 3, 0, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 3, 1, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 3, 2, primitiveType)     \
  VEC4_SWIZZLE4(outType, 3, 3, 3, 3, primitiveType)

#define UIVEC2_SWIZZLE(outType) VEC2_SWIZZLE(outType, uint32)
#define SIVEC2_SWIZZLE(outType) VEC2_SWIZZLE(outType, sint32)
#define SFVEC2_SWIZZLE(outType) VEC2_SWIZZLE(outType, flt32)
#define DFVEC2_SWIZZLE(outType) VEC2_SWIZZLE(outType, flt64)

#define UIVEC3_SWIZZLE(outType) VEC3_SWIZZLE(outType, uint32)
#define SIVEC3_SWIZZLE(outType) VEC3_SWIZZLE(outType, sint32)
#define SFVEC3_SWIZZLE(outType) VEC3_SWIZZLE(outType, flt32)
#define DFVEC3_SWIZZLE(outType) VEC3_SWIZZLE(outType, flt64)

#define UIVEC4_SWIZZLE(outType) VEC4_SWIZZLE(outType, uint32)
#define SIVEC4_SWIZZLE(outType) VEC4_SWIZZLE(outType, sint32)
#define SFVEC4_SWIZZLE(outType) VEC4_SWIZZLE(outType, flt32)
#define DFVEC4_SWIZZLE(outType) VEC4_SWIZZLE(outType, flt64)

#endif // ENMA_SWIZZLE_HPP