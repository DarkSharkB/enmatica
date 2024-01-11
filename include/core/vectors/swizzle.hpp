/* Vector Component Swizzle Helpers
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "../../base.hpp"
#include "../../empch.hpp"

#define CONCATENATE(a, b) a ## b
#define CONCATENATE_3(a, b, c) a ## b ## c
#define CONCATENATE_4(a, b, c, d) a ## b ## c ## d

#define MAKE_XYZW_COMPONENT(a) COMPONENT_XYZW_ ## a
#define MAKE_RGBA_COMPONENT(a) COMPONENT_RGBA_ ## a

#define COMPONENT_XYZW_0 x
#define COMPONENT_XYZW_1 y
#define COMPONENT_XYZW_2 z
#define COMPONENT_XYZW_3 w

#define COMPONENT_RGBA_0 r
#define COMPONENT_RGBA_1 g
#define COMPONENT_RGBA_2 b
#define COMPONENT_RGBA_3 a

#define COMBINE_2(a, b) CONCATENATE(a, b)
#define COMBINE_3(a, b, c) CONCATENATE_3(a, b, c)
#define COMBINE_4(a, b, c, d) CONCATENATE_4(a, b, c, d)

#define CONCATENATE_XYZW_2_COMPONENTS(a, b) COMBINE_2(MAKE_XYZW_COMPONENT(a), MAKE_XYZW_COMPONENT(b))             
#define CONCATENATE_XYZW_3_COMPONENTS(a, b, c) COMBINE_3(MAKE_XYZW_COMPONENT(a), MAKE_XYZW_COMPONENT(b), MAKE_XYZW_COMPONENT(c))
#define CONCATENATE_XYZW_4_COMPONENTS(a, b, c, d) COMBINE_4(MAKE_XYZW_COMPONENT(a), MAKE_XYZW_COMPONENT(b), MAKE_XYZW_COMPONENT(c), MAKE_XYZW_COMPONENT(d))

#define CONCATENATE_RGBA_2_COMPONENTS(a, b) COMBINE_2(MAKE_RGBA_COMPONENT(a), MAKE_RGBA_COMPONENT(b))
#define CONCATENATE_RGBA_3_COMPONENTS(a, b, c) COMBINE_3(MAKE_RGBA_COMPONENT(a), MAKE_RGBA_COMPONENT(b), MAKE_RGBA_COMPONENT(c))
#define CONCATENATE_RGBA_4_COMPONENTS(a, b, c, d) COMBINE_4(MAKE_RGBA_COMPONENT(a), MAKE_RGBA_COMPONENT(b), MAKE_RGBA_COMPONENT(c), MAKE_RGBA_COMPONENT(d))

template<typename OutType, typename Type, uin32 A, uin32 B, uin32 Size>
struct swizzle2
{
    Type arr[Size];

    OutType operator=(const OutType& v)
    {
        static_assert(A != B, "Cannot assign to vector of identical swizzle. Must be different.");
        arr[A] = v.x;
        arr[B] = v.y;

        return *this;
    }

    operator OutType() const
    {
        return OutType(arr[A], arr[B]);
    }

    friend std::ostream& operator<<(std::ostream& os, const swizzle2& v)
    {
        os << "( X: " << v.arr[A] << "\tY: " << v.arr[B] << " )";

        return os;
    }
};

#define VEC2_SWIZZLE2(outType, a, b, primitiveType)                                               \
    swizzle2<outType, primitiveType, a, b, 2> CONCATENATE_XYZW_2_COMPONENTS(a, b);                \
    swizzle2<outType, primitiveType, a, b, 2> CONCATENATE_RGBA_2_COMPONENTS(a, b);

#define VEC3_SWIZZLE2(outType, a, b, primitiveType)                                               \
    swizzle2<outType, primitiveType, a, b, 3> CONCATENATE_XYZW_2_COMPONENTS(a, b);                \
    swizzle2<outType, primitiveType, a, b, 3> CONCATENATE_RGBA_2_COMPONENTS(a, b);

#define VEC4_SWIZZLE2(outType, a, b, primitiveType)                                               \
    swizzle2<outType, primitiveType, a, b, 4> CONCATENATE_XYZW_2_COMPONENTS(a, b);                \
    swizzle2<outType, primitiveType, a, b, 4> CONCATENATE_RGBA_2_COMPONENTS(a, b);

template<typename OutType, typename Type, uin32 A, uin32 B, uin32 C, uin32 Size>
struct swizzle3
{
    Type arr[Size];

    OutType operator=(const OutType& v)
    {
        static_assert(A != B && B != C && C != A, "Cannot assign to vector of identical swizzle. Must be different.");
        arr[A] = v.x;
        arr[B] = v.y;
        arr[C] = v.z;

        return *this;
    }

    operator OutType() const
    {
        return OutType(arr[A], arr[B], arr[C]);
    }

    friend std::ostream& operator<<(std::ostream& os, const swizzle3& v)
    {
        os << "( X: " << v.arr[A] << "\tY: " << v.arr[B] << "\tZ: " << v.arr[C] << " )";

        return os;
    }
};

#define VEC2_SWIZZLE3(outType, a, b, c, primitiveType)                                            \
    swizzle3<outType, primitiveType, a, b, c, 2> CONCATENATE_XYZW_3_COMPONENTS(a, b, c);          \
    swizzle3<outType, primitiveType, a, b, c, 2> CONCATENATE_RGBA_3_COMPONENTS(a, b, c);

#define VEC3_SWIZZLE3(outType, a, b, c, primitiveType)                                            \
    swizzle3<outType, primitiveType, a, b, c, 3> CONCATENATE_XYZW_3_COMPONENTS(a, b, c);          \
    swizzle3<outType, primitiveType, a, b, c, 3> CONCATENATE_RGBA_3_COMPONENTS(a, b, c);

#define VEC4_SWIZZLE3(outType, a, b, c, primitiveType)                                            \
    swizzle3<outType, primitiveType, a, b, c, 4> CONCATENATE_XYZW_3_COMPONENTS(a, b, c);          \
    swizzle3<outType, primitiveType, a, b, c, 4> CONCATENATE_RGBA_3_COMPONENTS(a, b, c);

template<typename OutType, typename Type, uin32 A, uin32 B, uin32 C, uin32 D, uin32 Size>
struct swizzle4
{
    Type arr[Size];

    OutType operator=(const OutType& v)
    {
        static_assert(A != B && B != C && C != D && D != A, "Cannot assign to vector of identical swizzle. Must be different.");
        arr[A] = v.x;
        arr[B] = v.y;
        arr[C] = v.z;
        arr[D] = v.w;

        return *this;
    }

    operator OutType() const
    {
        return OutType(arr[A], arr[B], arr[C], arr[D]);
    }

    friend std::ostream& operator<<(std::ostream& os, const swizzle4& v)
    {
        os << "( X: " << v.arr[A] << "\tY: " << v.arr[B] << "\tZ: " << v.arr[C] << "\tW: " << v.arr[D] << " )";

        return os;
    }
};

#define VEC2_SWIZZLE4(outType, a, b, c, d, primitiveType)                                         \
    swizzle4<outType, primitiveType, a, b, c, d, 2> CONCATENATE_XYZW_4_COMPONENTS(a, b, c, d);    \
    swizzle4<outType, primitiveType, a, b, c, d, 2> CONCATENATE_RGBA_4_COMPONENTS(a, b, c, d);

#define VEC3_SWIZZLE4(outType, a, b, c, d, primitiveType)                                         \
    swizzle4<outType, primitiveType, a, b, c, d, 3> CONCATENATE_XYZW_4_COMPONENTS(a, b, c, d);    \
    swizzle4<outType, primitiveType, a, b, c, d, 3> CONCATENATE_RGBA_4_COMPONENTS(a, b, c, d);

#define VEC4_SWIZZLE4(outType, a, b, c, d, primitiveType)                                         \
    swizzle4<outType, primitiveType, a, b, c, d, 4> CONCATENATE_XYZW_4_COMPONENTS(a, b, c, d);    \
    swizzle4<outType, primitiveType, a, b, c, d, 4> CONCATENATE_RGBA_4_COMPONENTS(a, b, c, d);

#define VEC2_SWIZZLE(outType, primitiveType)              \
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

#define VEC3_SWIZZLE(outType, primitiveType)              \
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

#define VEC4_SWIZZLE(outType, primitiveType)              \
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

#define FVEC2_SWIZZLE(outType) VEC2_SWIZZLE(outType, flt32)
#define IVEC2_SWIZZLE(outType) VEC2_SWIZZLE(outType, uin32)

#define FVEC3_SWIZZLE(outType) VEC3_SWIZZLE(outType, flt32)

#define FVEC4_SWIZZLE(outType) VEC4_SWIZZLE(outType, flt32)