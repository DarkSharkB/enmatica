/* Single Precision Floating-Point 4x2 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../vector.hpp"
#include "../empch.hpp"

struct ALIGN(32) fmat4x2
{
    union
    {
        struct
        {
            flt32 m11, m12;
            flt32 m21, m22;
            flt32 m31, m32;
            flt32 m41, m42;
        };
        flt32 arr[8];
        vec2 rows[4];
    };
    
    fmat4x2(const fmat4x2 &m);
    fmat4x2(const flt32 x0, const flt32 y0, const flt32 x1, const flt32 y1, const flt32 x2, const flt32 y2, const flt32 x3, const flt32 y3);

    #ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, fmat4x2 m)
	{
		os << "{\t\t\t\t\t}\n"
		<< "|\t" << std::setw(8) << m.m11 << "\t" << std::setw(8) << m.m12 << "\t|\n"
		<< "|\t" << std::setw(8) << m.m21 << "\t" << std::setw(8) << m.m22 << "\t|\n"
		<< "|\t" << std::setw(8) << m.m31 << "\t" << std::setw(8) << m.m32 << "\t|\n"
		<< "|\t" << std::setw(8) << m.m41 << "\t" << std::setw(8) << m.m42 << "\t|\n{\t\t\t\t\t}";

		return os;
	}
	#endif
};

#ifdef ENMATICA_IMPL
fmat4x2::fmat4x2(const fmat4x2 &m)
{
    *this= m;
}

fmat4x2::fmat4x2(const flt32 x0, const flt32 y0, const flt32 x1, const flt32 y1, const flt32 x2, const flt32 y2, const flt32 x3, const flt32 y3)
    : m11(x0), m12(y0), m21(x1), m22(y1), m31(x2), m32(y2), m41(x3), m42(y3) {};
#endif