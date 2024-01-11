/* Single Precision Floating-Point 2x2 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../vector.hpp"
#include "../empch.hpp"

struct ALIGN(16) fmat2x2
{
    union
    {
        struct
        {
            flt32 m11, m12;
            flt32 m21, m22;
        };
        flt32 arr[4];
        vec2 rows[2];
    };

    fmat2x2(const fmat2x2 &mat);
    fmat2x2(const flt32 val = 0.0f);
    fmat2x2(const flt32 x0, const flt32 y0, const flt32 x1, const flt32 y1);
    fmat2x2(const __m128 vals);
    fmat2x2(const vec2 row1, const vec2 row2);

    fmat2x2 operator+(const fmat2x2 other);
    fmat2x2 operator+=(const fmat2x2 other);
    fmat2x2 operator-(const fmat2x2 other);
    fmat2x2 operator-=(const fmat2x2 other);
    fmat2x2 operator*(const fmat2x2 other);
    fmat2x2 operator*=(const fmat2x2 other);
    fmat2x2 operator*(const flt32 val);
    fmat2x2 operator*=(const flt32 val);
    fmat2x2 operator/(const flt32 val);
    fmat2x2 operator/=(const flt32 val);

    flt32 Determinant();

    #ifdef DEBUG
    // Just here for console debugging
	friend std::ostream &operator<<(std::ostream &os, fmat2x2 mat)
	{
		os 
        << "{\t\t\t       }\n"
        << "|\t\t\t       |\n"
		<< "|  " << std::setw(12) << mat.m11 << "  " << std::setw(12) << mat.m12 <<  "  |\n"
		<< "|  " << std::setw(12) << mat.m21 << "  " << std::setw(12) << mat.m22 <<  "  |\n"
        << "|\t\t\t       |\n"
        << "{\t\t\t       }";

		return os;
	}
	#endif
};

fmat2x2 Transpose(const fmat2x2 m);

fmat2x2 operator*(const fmat2x3 m1, const mat3x2 m2);
fmat2x2 operator*(const fmat2x4 m1, const mat4x2 m2);

#ifdef ENMATICA_IMPL
fmat2x2::fmat2x2(const fmat2x2 &mat)
{
    *this = mat;
}
        
fmat2x2::fmat2x2(const flt32 val)
{
    this->arr[0] = val;
    this->arr[1] = 0.0f;
    this->arr[2] = 0.0f;
    this->arr[3] = val;
}
        
fmat2x2::fmat2x2(const flt32 x0, const flt32 y0, const flt32 x1, const flt32 y1) : m11(x0), m12(y0), m21(x1), m22(y1) {}

fmat2x2::fmat2x2(const __m128 vals)
{
    this->arr[0] = vals[0];
    this->arr[1] = vals[1];
    this->arr[2] = vals[2];
    this->arr[3] = vals[3];
}

fmat2x2::fmat2x2(const vec2 row1, const vec2 row2)
{
    this->m11 = row1.x;
    this->m12 = row1.y;
    this->m21 = row2.x;
    this->m22 = row2.y;
}

fmat2x2 fmat2x2::operator+(const fmat2x2 other)
{
    __m128 m1 = _mm_load_ps(this->arr);
    __m128 m2 = _mm_load_ps(other.arr);

    return _mm_add_ps(m1, m2);
}

fmat2x2 fmat2x2::operator+=(const fmat2x2 other)
{
    __m128 m1 = _mm_load_ps(this->arr);
    __m128 m2 = _mm_load_ps(other.arr);

    _mm_store_ps(this->arr, _mm_add_ps(m1, m2));

    return *this;
}

fmat2x2 fmat2x2::operator-(const fmat2x2 other)
{
    __m128 m1 = _mm_load_ps(this->arr);
    __m128 m2 = _mm_load_ps(other.arr);

    return _mm_sub_ps(m1, m2);
}

fmat2x2 fmat2x2::operator-=(const fmat2x2 other)
{
    __m128 m1 = _mm_load_ps(this->arr);
    __m128 m2 = _mm_load_ps(other.arr);

    _mm_store_ps(this->arr, _mm_sub_ps(m1, m2));

    return *this;
}

fmat2x2 fmat2x2::operator*(const fmat2x2 other)
{
    // Need a better way
    __m128 r1 = _mm_load_ps(this->arr);     // First Matrix
    __m128 r3 = _mm_load_ps(other.arr);     // Second Matrix

    __m128 r2 = _mm_shuffle_ps(r1, r1, 0xEE);
    r1 = _mm_shuffle_ps(r1, r1, 0x44);
    r3 = _mm_shuffle_ps(r3, r3, 0xD8);

    r1 = _mm_dp_ps(r1, r3, 0xFF);
    r2 = _mm_dp_ps(r2, r3, 0xFF);

    /*r1 = _mm_hadd_ps(r1, r1);
    r2 = _mm_hadd_ps(r2, r2);*/

    r2 = _mm_shuffle_ps(r1, r2, 0xE4);

    return fmat2x2(r2);
}

fmat2x2 fmat2x2::operator*=(const fmat2x2 other)
{
    // Same as above, right?
    __m128 r1 = _mm_load_ps(this->arr);   // First Matrix
    __m128 r3 = _mm_load_ps(other.arr);       // Second Matrix

    __m128 r2 = _mm_shuffle_ps(r1, r1, 0xEE);
    r1 = _mm_shuffle_ps(r1, r1, 0x44);
    r3 = _mm_shuffle_ps(r3, r3, 0xD8);

    r1 = _mm_dp_ps(r1, r3, 0XFF);
    r2 = _mm_dp_ps(r2, r3, 0xFF);

    /*r1 = _mm_hadd_ps(r1, r1);
    r2 = _mm_hadd_ps(r2, r2);*/

    r2 = _mm_shuffle_ps(r1, r2, 0xE4);

    *this = r2;

    return *this;
}

fmat2x2 fmat2x2::operator*(const flt32 val)
{
    __m128 m = _mm_load_ps(this->arr);
    __m128 fl = _mm_load1_ps(&val);

    return fmat2x2(_mm_mul_ps(m, fl));
}

fmat2x2 fmat2x2::operator*=(const flt32 val)
{
    __m128 m = _mm_load_ps(this->arr);
    __m128 fl = _mm_load1_ps(&val);

    _mm_store_ps(this->arr, _mm_mul_ps(m, fl));

    return *this;
}

fmat2x2 fmat2x2::operator/(const flt32 val)
{
    __m128 m = _mm_load_ps(this->arr);
    __m128 fl = _mm_load1_ps(&val);

    return fmat2x2(_mm_div_ps(m, fl));
}

fmat2x2 fmat2x2::operator/=(const flt32 val)
{
    __m128 m = _mm_load_ps(this->arr);
    __m128 fl = _mm_load1_ps(&val);

    _mm_store_ps(this->arr, _mm_div_ps(m, fl));
        
    return *this;
}

flt32 fmat2x2::Determinant()
{
    __m128 m = _mm_load_ps(this->arr);
    __m128 n = _mm_shuffle_ps(m, m, 0xBB);

    m = _mm_mul_ps(m, n);

    return m[0] - m[1];
}

fmat2x2 Transpose(const fmat2x2 m)
{
    __m128 r = _mm_load_ps(m.arr);

    r = _mm_shuffle_ps(r, r, _MM_SHUFFLE(3, 1, 2, 0));

    return fmat2x2(r);
}

#include "fmat2x3.hpp"
#include "fmat3x2.hpp"
fmat2x2 operator*(const fmat2x3 m1, const fmat3x2 m2)
{
    return fmat2x2(2.0f);
}

#include "fmat2x4.hpp"
#include "fmat4x2.hpp"
fmat2x2 operator*(const fmat2x4 m1, const fmat4x2 m2)
{
    fmat2x2 m;

    m.arr[0] = m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31 + m1.m14 * m2.m41;
    m.arr[1] = m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32 + m1.m14 * m2.m42;
    m.arr[2] = m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31 + m1.m24 * m2.m41;
    m.arr[3] = m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32 + m1.m24 * m2.m42;

    return m;
}
#endif

