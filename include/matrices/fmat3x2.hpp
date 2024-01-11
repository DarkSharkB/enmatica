/* Single Precision Floating-Point 3x2 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../vector.hpp"
#include "../empch.hpp"

struct ALIGN(32) fmat3x2
{
    union
    {
        struct
        {
            flt32 m11, m12;
            flt32 m21, m22;
            flt32 m31, m32;
        };
        flt32 arr[6];
        vec2 rows[3];
    };
private:
    flt32 x_pad[2] = { 0.0f, 0.0f };

public:
    fmat3x2(const fmat3x2 &mat);
    fmat3x2(const flt32 val = 0.0f);
    fmat3x2(const flt32 x0, const flt32 y0, const flt32 x1, const flt32 y1, const flt32 x2, const flt32 y2);
    fmat3x2(const flt32 *arr);
    fmat3x2(const __m128 hr1, const __m128 hr2);
    fmat3x2(const vec2 v1, const vec2 v2, const vec2 v3);

    #ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, fmat3x2 mat)
	{
		os 
        << "{\t\t\t       }\n"
        << "|\t\t\t       |\n"
		<< "|  " << std::setw(12) << mat.m11 << "  " << std::setw(12) << mat.m12 << "  |\n"
		<< "|  " << std::setw(12) << mat.m21 << "  " << std::setw(12) << mat.m22 << "  |\n"
        << "|  " << std::setw(12) << mat.m31 << "  " << std::setw(12) << mat.m32 << "  |\n"
        << "|\t\t\t       |\n"
        << "{\t\t\t       }";

		return os;
	}
	#endif
};

fmat3x2 Transpose(const fmat2x3 mat);

#ifdef ENMATICA_IMPL
fmat3x2::fmat3x2(const fmat3x2 &mat)
{
    *this = mat;
}

fmat3x2::fmat3x2(const flt32 val)
{
    this->arr[0] = val;
    this->arr[1] = 0.0f;
    this->arr[2] = 0.0f;
    this->arr[3] = val;
    this->arr[4] = 0.0f;
    this->arr[5] = 0.0f;
}

fmat3x2::fmat3x2(const flt32 x0, const flt32 y0, const flt32 x1, const flt32 y1, const flt32 x2, const flt32 y2) : m11(x0), m12(y0), m21(x1), m22(y1), m31(x2), m32(y2) {}

fmat3x2::fmat3x2(const flt32 *arr)
{
    this->arr[0] = arr[0];
    this->arr[1] = arr[1];
    this->arr[2] = arr[2];
    this->arr[3] = arr[3];
    this->arr[4] = arr[4];
    this->arr[5] = arr[5];
}

fmat3x2::fmat3x2(const __m128 hr1, const __m128 hr2)
{
    this->arr[0] = hr1[0];
    this->arr[1] = hr1[1];
    this->arr[2] = hr1[2];
    this->arr[3] = hr2[0];
    this->arr[4] = hr2[1];
    this->arr[5] = hr2[2];
}

fmat3x2::fmat3x2(const vec2 v1, const vec2 v2, const vec2 v3)
{
    this->rows[0] = v1;
    this->rows[1] = v2;
    this->rows[2] = v3;
}

#include "fmat2x3.hpp"
fmat3x2 Transpose(const fmat2x3 mat)
{
    const __m128 r1 = _mm_loadu_ps(&mat.arr[0]);
    const __m128 r2 = _mm_loadu_ps(&mat.arr[2]);

    __m128 s1 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(0, 1, 3, 0));
    __m128 s2 = _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(2, 3, 0, 2));

    return fmat3x2(s1, s2);
}
#endif