/* Single Precision Floating-Point 2x4 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../../vector.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"

struct ALIGN(32) fmat2x4
{
    union
    {
        struct
        {
            flt32 m11, m12, m13, m14;
            flt32 m21, m22, m23, m24;
        };
        flt32 arr[8];
        vec4 rows[2];
    };

    fmat2x4(const fmat2x4 &mat);
    fmat2x4(const flt32 val = 0.0f);
    fmat2x4(const flt32 x0, const flt32 y0, const flt32 z0, const flt32 w0, const flt32 x1, const flt32 y1, const flt32 z1, const flt32 w1);
    fmat2x4(const flt32 *arr);
    fmat2x4(const __m256 mat);
    fmat2x4(const vec2 hrow11, const vec2 hrow12, const vec2 hrow21, const vec2 hrow22);
    fmat2x4(const vec4 row1, const vec4 row2);

    fmat2x4 operator+(const fmat2x4 other);
    fmat2x4 operator+=(const fmat2x4 other);
    fmat2x4 operator-(const fmat2x4 other);
    fmat2x4 operator-=(const fmat2x4 other);
    fmat2x4 operator*(const flt32 val);
    fmat2x4 operator*=(const flt32 val);
    fmat2x4 operator/(const flt32 val);
    fmat2x4 operator/=(const flt32 val);

    #ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, fmat2x4 mat)
	{
		os
        << "{\t\t\t\t\t\t\t   }\n"
        << "|\t\t\t\t\t\t\t   |\n"
		<< "|  " << std::setw(12) << mat.m11 << "  " << std::setw(12) << mat.m12 << "  " << std::setw(12) << mat.m13 << "  " << std::setw(12) << mat.m14 << "  |\n"
		<< "|  " << std::setw(12) << mat.m21 << "  " << std::setw(12) << mat.m22 << "  " << std::setw(12) << mat.m23 << "  " << std::setw(12) << mat.m24 << "  |\n"
        << "|\t\t\t\t\t\t\t   |\n"
        << "{\t\t\t\t\t\t\t   }";

		return os;
	}
	#endif
};

fmat2x4 Transpose(const fmat4x2 mat);

#ifdef ENMA_IMPLEMENTATION
fmat2x4::fmat2x4(const fmat2x4 &mat)
{
    *this = mat;
}

fmat2x4::fmat2x4(const flt32 val)
{
    this->arr[0] = this->arr[5] = val;
    this->arr[1] = this->arr[2] = this->arr[3] = this->arr[4] = this->arr[6] = this->arr[7] = 0.0f;
}
    
fmat2x4::fmat2x4(const flt32 x0, const flt32 y0, const flt32 z0, const flt32 w0, const flt32 x1, const flt32 y1, const flt32 z1, const flt32 w1) 
    : m11(x0), m12(y0), m13(z0), m14(w0), m21(x1), m22(y1), m23(z1), m24(w1) {}

fmat2x4::fmat2x4(const vec4 row1, const vec4 row2)
{
    this->rows[0] = row1;
    this->rows[1] = row2;
}

#ifdef USE_SIMD
fmat2x4::fmat2x4(const __m256 mat)
{
    this->arr[0] = mat[0];
    this->arr[1] = mat[1];
    this->arr[2] = mat[2];
    this->arr[3] = mat[3];
    this->arr[4] = mat[4];
    this->arr[5] = mat[5];
    this->arr[6] = mat[6];
    this->arr[7] = mat[7];
}

fmat2x4 fmat2x4::operator+(const fmat2x4 other)
{
    __m256 m1 = _mm256_load_ps(this->arr);
    __m256 m2 = _mm256_load_ps(other.arr);

    return fmat2x4(_mm256_add_ps(m1, m2));
}

fmat2x4 fmat2x4::operator+=(const fmat2x4 other)
{
    __m256 m1 = _mm256_load_ps(this->arr);
    __m256 m2 = _mm256_load_ps(other.arr);

    *this = _mm256_add_ps(m1, m2);

	return *this;
}

fmat2x4 fmat2x4::operator-(const fmat2x4 other)
{
    __m256 m1 = _mm256_load_ps(this->arr);
    __m256 m2 = _mm256_load_ps(other.arr);

    m1 = _mm256_sub_ps(m1, m2);

    return fmat2x4(m1);
}

fmat2x4 fmat2x4::operator-=(const fmat2x4 other)
{
	__m256 m1 = _mm256_load_ps(this->arr);
    __m256 m2 = _mm256_load_ps(other.arr);

    *this = _mm256_sub_ps(m1, m2);

	return *this;
}


fmat2x4 fmat2x4::operator*(const flt32 val)
{
    __m256 fl = _mm256_set1_ps(val);
    __m256 m1 = _mm256_load_ps(this->arr);

    return _mm256_mul_ps(m1, fl);
}

fmat2x4 fmat2x4::operator*=(const flt32 val)
{
    __m256 fl = _mm256_set1_ps(val);
    __m256 m1 = _mm256_load_ps(this->arr);

    *this = _mm256_mul_ps(m1, fl);

    return *this;
}

fmat2x4 fmat2x4::operator/(const flt32 val)
{
    __m256 fl = _mm256_set1_ps(val);
    __m256 m1 = _mm256_load_ps(this->arr);

    return _mm256_div_ps(m1, fl);
}

fmat2x4 fmat2x4::operator/=(const flt32 val)
{
    __m256 fl = _mm256_set1_ps(val);
    __m256 m1 = _mm256_load_ps(this->arr);

    *this = _mm256_div_ps(m1, fl);
    
    return *this;
}
#endif // USE_SIMD
#endif