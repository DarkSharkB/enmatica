/* Single Precision Floating-Point 2x3 Matrix
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

struct ALIGN(32) fmat2x3
{
    union
    {
        struct
        {
            flt32 m11, m12, m13;
            flt32 m21, m22, m23;
        };
        flt32 arr[6];
        vec3 rows[2];
    };

private:
    flt32 x_pad[2] = { 0.0f, 0.0f };    // Just the padding, don't mess it up. Leave it be

public:
    fmat2x3(const fmat2x3 &mat);
    fmat2x3(const flt32 val = 0.0f);
    fmat2x3(const flt32 x0, const flt32 y0, const flt32 z0, const flt32 x1, const flt32 y1, const flt32 z1);
    fmat2x3(const flt32 *arr);
    fmat2x3(const __m128 v1, const __m128 v2);
    fmat2x3(const vec3 row1, const vec3 row2);

    fmat2x3 operator+(const fmat2x3 other);
    fmat2x3 operator+=(const fmat2x3 other);
    fmat2x3 operator-(const fmat2x3 other);
    fmat2x3 operator-=(const fmat2x3 other);
    fmat2x3 operator*(const flt32 val);
    fmat2x3 operator*=(const flt32 val);
    fmat2x3 operator/(const flt32 val);
    fmat2x3 operator/=(const flt32 val);
    /*

    fmat2x3 operator*(const fmat2x3 other)
    {
        __m128 r1 = _mm_load_ps(this->arr);   // First Matrix
        __m128 r3 = _mm_load_ps(other.arr);       // Second Matrix

        __m128 r2 = _mm_shuffle_ps(r1, r1, 0xEE);
        r1 = _mm_shuffle_ps(r1, r1, 0x44);
        r3 = _mm_shuffle_ps(r3, r3, 0xD8);

        r1 = _mm_mul_ps(r1, r3);
        r2 = _mm_mul_ps(r2, r3);

        r1 = _mm_hadd_ps(r1, r1);
        r2 = _mm_hadd_ps(r2, r2);

        r2 = _mm_shuffle_ps(r1, r2, 0xE4);

        return fmat2x3(r2);
    }

    fmat2x3 operator*=(const fmat2x3 other)
    {
        __m128 r1 = _mm_load_ps(this->arr);   // First Matrix
        __m128 r3 = _mm_load_ps(other.arr);       // Second Matrix

        __m128 r2 = _mm_shuffle_ps(r1, r1, 0xEE);
        r1 = _mm_shuffle_ps(r1, r1, 0x44);
        r3 = _mm_shuffle_ps(r3, r3, 0xD8);

        r1 = _mm_mul_ps(r1, r3);
        r2 = _mm_mul_ps(r2, r3);

        r1 = _mm_hadd_ps(r1, r1);
        r2 = _mm_hadd_ps(r2, r2);

        r2 = _mm_shuffle_ps(r1, r2, 0xE4);

        _mm_store_ps(this->arr, r2);

        return *this;
    }

    fmat2x3 operator*(const flt32 f)
    {
        __m128 m = _mm_load_ps(this->arr);
        __m128 fl = _mm_load1_ps(&f);

        return fmat2x3(_mm_mul_ps(m, fl));
    }

    fmat2x3 operator*=(const flt32 f)
    {
        __m128 m = _mm_load_ps(this->arr);
        __m128 fl = _mm_load1_ps(&f);

        _mm_store_ps(this->arr, _mm_mul_ps(m, fl));

        return *this;
    }

    fmat2x3 operator/(const flt32 f)
    {
        __m128 m = _mm_load_ps(this->arr);
        __m128 fl = _mm_load1_ps(&f);

        return fmat2x3(_mm_div_ps(m, fl));
    }

    fmat2x3 operator/=(const flt32 f)
    {
        __m128 m = _mm_load_ps(this->arr);
        __m128 fl = _mm_load1_ps(&f);

        _mm_store_ps(this->arr, _mm_div_ps(m, fl));
        
        return *this;
    }*/

    flt32 Determinant();
    
    #ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, fmat2x3 mat)
	{
		os 
        << "{\t\t\t\t\t     }\n"
        << "|\t\t\t\t\t     |\n"
		<< "|  " << std::setw(12) << mat.m11 << "  " << std::setw(12) << mat.m12 << "  " << std::setw(12) << mat.m13 << "  |\n"
		<< "|  " << std::setw(12) << mat.m21 << "  " << std::setw(12) << mat.m22 << "  " << std::setw(12) << mat.m23 << "  |\n"
        << "|\t\t\t\t\t     |\n"
        << "{\t\t\t\t\t     }";

		return os;
	}
	#endif
};

fmat2x3 Transpose(const fmat3x2 mat);

#ifdef ENMA_IMPLEMENTATION
fmat2x3::fmat2x3(const fmat2x3 &mat)
{
    *this = mat;
}
    
fmat2x3::fmat2x3(const flt32 val)
{
    this->arr[0] = val;
    this->arr[1] = 0.0f;
    this->arr[2] = 0.0f;
    this->arr[3] = 0.0f;
    this->arr[4] = val;
    this->arr[5] = 0.0f;
}
    
fmat2x3::fmat2x3(const flt32 x0, const flt32 y0, const flt32 z0, const flt32 x1, const flt32 y1, const flt32 z1) : m11(x0), m12(y0), m13(z0), m21(x1), m22(y1), m23(z1) {}

fmat2x3::fmat2x3(const __m128 v1, const __m128 v2)
{
    this->arr[0] = v1[0];
    this->arr[1] = v1[1];
    this->arr[2] = v1[2];
    this->arr[3] = v2[0];
    this->arr[4] = v2[1];
    this->arr[5] = v2[2];
}

fmat2x3::fmat2x3(const vec3 row1, const vec3 row2)
{
    this->rows[0] = row1;
    this->rows[1] = row2;
}

fmat2x3 fmat2x3::operator+(const fmat2x3 other)
{
    vec3 r11 = this->rows[0];
    vec3 r12 = this->rows[1];

    vec3 r21 = other.rows[0];
    vec3 r22 = other.rows[1];


    return fmat2x3(r11 + r12, r21 + r22);
}

fmat2x3 fmat2x3::operator+=(const fmat2x3 other)
{
    __m128 m1 = _mm_loadu_ps(this->arr);
    __m128 m2 = _mm_loadu_ps(other.arr);

    _mm_store_ps(this->arr, _mm_add_ps(m1, m2));

    return *this;
}

fmat2x3 fmat2x3::operator-(const fmat2x3 other)
{
    vec3 r11 = this->rows[0];
    vec3 r12 = this->rows[1];

    vec3 r21 = other.rows[0];
    vec3 r22 = other.rows[1];


    return fmat2x3(r11 - r12, r21 - r22);
}

fmat2x3 fmat2x3::operator-=(const fmat2x3 other)
{
    __m128 m1 = _mm_loadu_ps(this->arr);
    __m128 m2 = _mm_loadu_ps(other.arr);

    _mm_store_ps(this->arr, _mm_sub_ps(m1, m2));

    return *this;
}

flt32 fmat2x3::Determinant()
{
    __m128 m = _mm_load_ps(this->arr);
    __m128 n = _mm_shuffle_ps(m, m, 0xBB);

    m = _mm_mul_ps(m, n);

    return m[0] - m[1];
}

#include "fmat3x2.hpp"
fmat2x3 Transpose(const fmat3x2 mat)
{
    __m128 r1 = _mm_loadu_ps(&mat.arr[0]);
    __m128 r2 = _mm_loadu_ps(&mat.arr[2]);

    __m128 s1 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 2, 2, 0));
    __m128 s2 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 3, 3, 1));

    return fmat2x3(s1, s2);
}
#endif