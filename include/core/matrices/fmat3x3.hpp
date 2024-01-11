/* Single Precision Floating-Point 3x3 Matrix
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

struct fmat3x3
{
    union
    {
        struct
        {
            flt32 m11, m12, m13;
            flt32 m21, m22, m23;
            flt32 m31, m32, m33;
        };
        flt32 arr[9];
    };
    flt32 x_pad[3] = { 0.0f, 0.0f, 0.0f };

    fmat3x3(const fmat3x3 &mat);
    fmat3x3(const flt32 val = 0.0f);
    fmat3x3(const flt32 x0, const flt32 y0, const flt32 z0, const flt32 x1, const flt32 y1, const flt32 z1, const flt32 x2, const flt32 y2, const flt32 z2);
    fmat3x3(const __m128 &r1, const __m128 &r2, const __m128 &r3);
    fmat3x3(const __m256 &t1, const flt32 &f);
    fmat3x3(const vec3 &row1, const vec3 &row2, const vec3 &row3);
    
    fmat3x3 operator+(const fmat3x3 other);
    fmat3x3 operator+=(const fmat3x3 other);
    fmat3x3 operator-(const fmat3x3 other);
    fmat3x3 operator-=(const fmat3x3 other);
    fmat3x3 operator*(const fmat3x3 other);
    fmat3x3 operator*=(const fmat3x3 other);
    fmat3x3 operator*(const flt32 val);
    fmat3x3 operator*=(const flt32 val);
    fmat3x3 operator/(const flt32 val);
    fmat3x3 operator/=(const flt32 val);

    #ifdef DEBUG
    friend std::ostream &operator<<(std::ostream &os, const fmat3x3 mat)
    {
        os 
        << "\n{\t\t\t\t\t\t\t}\n"
		<< "|\t" << std::setw(12) << mat.m11 << "  " << std::setw(12) << mat.m12 << "  " << std::setw(12) << mat.m13 <<  "\t|\n"
		<< "|\t" << std::setw(12) << mat.m21 << "  " << std::setw(12) << mat.m22 << "  " << std::setw(12) << mat.m23 <<  "\t|\n"
        << "|\t" << std::setw(12) << mat.m31 << "  " << std::setw(12) << mat.m32 << "  " << std::setw(12) << mat.m33 <<  "\t|\n"
        << "{\t\t\t\t\t\t\t}";

        return os;
    }
    #endif
};

fmat3x3 Transpose(fmat3x3 mat);
fmat3x3 Inverse(fmat3x3 mat);

#ifdef ENMA_IMPLEMENTATION
fmat3x3::fmat3x3(const fmat3x3 &mat)
{
    *this = mat;
}

fmat3x3::fmat3x3(const flt32 val)
{
    this->arr[0] = this->arr[4] = this->arr[8] = val;
    this->arr[1] = this->arr[2] = this->arr[3] = this->arr[5] = this->arr[6] = this->arr[7] = 0.0f;
}

fmat3x3::fmat3x3(const flt32 x0, const flt32 y0, const flt32 z0, const flt32 x1, const flt32 y1, const flt32 z1, const flt32 x2, const flt32 y2, const flt32 z2)
	: m11(x0), m12(y0), m13(z0), m21(x1), m22(y1), m23(z1), m31(x2), m32(y2), m33(z2) {}

fmat3x3::fmat3x3(const __m128 &r1, const __m128 &r2, const __m128 &r3)
{
    this->arr[0] = r1[0];
    this->arr[1] = r1[1];
    this->arr[2] = r1[2];
    this->arr[3] = r2[0];
    this->arr[4] = r2[1];
    this->arr[5] = r2[2];
    this->arr[6] = r3[0];
    this->arr[7] = r3[1];
    this->arr[8] = r3[2];
}

fmat3x3::fmat3x3(const __m256 &f8vals, const flt32 &val)
{
    this->arr[0] = f8vals[0];
    this->arr[1] = f8vals[1];
    this->arr[2] = f8vals[2];
    this->arr[3] = f8vals[3];
    this->arr[4] = f8vals[4];
    this->arr[5] = f8vals[5];
    this->arr[6] = f8vals[6];
    this->arr[7] = f8vals[7];
    this->arr[8] = val;
}

fmat3x3::fmat3x3(const vec3 &row1, const vec3 &row2, const vec3 &row3)
{
    this->arr[0] = row1.x;
    this->arr[1] = row1.y;
    this->arr[2] = row1.z;
    this->arr[3] = row2.x;
    this->arr[4] = row2.y;
    this->arr[5] = row2.z;
    this->arr[6] = row3.x;
    this->arr[7] = row3.y;
    this->arr[8] = row3.z;
}

fmat3x3 fmat3x3::operator+(const fmat3x3 m)
{
    __m256 t1 = _mm256_loadu_ps(this->arr);
    __m256 t2 = _mm256_loadu_ps(m.arr);
    flt32 l = this->m33 + m.m33;

    t1 = _mm256_add_ps(t1, t2);
    
    return fmat3x3(t1, l);
}

fmat3x3 fmat3x3::operator+=(const fmat3x3 m)
{
    __m256 t1 = _mm256_loadu_ps(this->arr);
    __m256 t2 = _mm256_loadu_ps(m.arr);
    this->m33 += m.m33;

    t1 = _mm256_add_ps(t1, t2);

    _mm256_storeu_ps(this->arr, t1);

    return *this;
}

fmat3x3 fmat3x3::operator-(const fmat3x3 m)
{
    __m256 t1 = _mm256_loadu_ps(this->arr);
    __m256 t2 = _mm256_loadu_ps(m.arr);
    flt32 l = this->m33 - m.m33;

    t1 = _mm256_sub_ps(t1, t2);
    
    return fmat3x3(t1, l);
}

fmat3x3 fmat3x3::operator-=(const fmat3x3 m)
{
    __m256 t1 = _mm256_loadu_ps(this->arr);
    __m256 t2 = _mm256_loadu_ps(m.arr);
    this->m33 -= m.m33;

    t1 = _mm256_sub_ps(t1, t2);

    _mm256_storeu_ps(this->arr, t1);

    return *this;
}

fmat3x3 fmat3x3::operator*(const fmat3x3 other)
{
    flt32 m1 = m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
    flt32 m2 = m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
    flt32 m3 = m11 * other.m13 + m12 * other.m23 + m13 * other.m33;

    flt32 m4 = m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
    flt32 m5 = m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
    flt32 m6 = m21 * other.m13 + m22 * other.m23 + m23 * other.m33;

    flt32 m7 = m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
    flt32 m8 = m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
    flt32 m9 = m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

    return fmat3x3(m1, m2, m3, m4, m5, m6, m7, m8, m9);
}

fmat3x3 fmat3x3::operator*=(const fmat3x3 other)
{
    flt32 m1 = m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
    flt32 m2 = m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
    flt32 m3 = m11 * other.m13 + m12 * other.m23 + m13 * other.m33;

    flt32 m4 = m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
    flt32 m5 = m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
    flt32 m6 = m21 * other.m13 + m22 * other.m23 + m23 * other.m33;

    flt32 m7 = m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
    flt32 m8 = m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
    flt32 m9 = m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

    *this = fmat3x3(m1, m2, m3, m4, m5, m6, m7, m8, m9);

    return *this;
}

fmat3x3 fmat3x3::operator*(const flt32 val)
{
    __m256 t1 = _mm256_loadu_ps(this->arr);
    __m256 t2 = _mm256_set1_ps(val);
    flt32 l = this->m33 * val;

    t1 = _mm256_mul_ps(t1, t2);
    
    return fmat3x3(t1, l);
}

fmat3x3 fmat3x3::operator*=(const flt32 val)
{
    __m256 t1 = _mm256_loadu_ps(this->arr);
    __m256 t2 = _mm256_set1_ps(val);
    this->m33 *= val;

    t1 = _mm256_mul_ps(t1, t2);

    _mm256_storeu_ps(this->arr, t1);

    return *this;
}

fmat3x3 fmat3x3::operator/(const flt32 f)
{
    const flt32 rec = 1.0f / f;

    __m256 t1 = _mm256_loadu_ps(this->arr);
    __m256 t2 = _mm256_set1_ps(rec);

    flt32 l = this->m33 * rec;

    t1 = _mm256_mul_ps(t1, t2);
    
    return fmat3x3(t1, l);
}

fmat3x3 fmat3x3::operator/=(const flt32 f)
{
    const flt32 rec = 1.0f / f;

    __m256 t1 = _mm256_loadu_ps(this->arr);
    __m256 t2 = _mm256_set1_ps(rec);
    this->m33 *= rec;

    t1 = _mm256_mul_ps(t1, t2);

    _mm256_storeu_ps(this->arr, t1);

    return *this;
}

fmat3x3 Transpose(fmat3x3 mat)
{
    flt32 m12 = mat.m21;
    flt32 m13 = mat.m31;
    flt32 m23 = mat.m32;

    return fmat3x3(mat.m11, m12, m13, mat.m12, mat.m22, m23, mat.m13, mat.m23, mat.m33);
}

flt32 Determinant(fmat3x3 mat)
{
    flt32 d1 = mat.m11 * (mat.m22 * mat.m33 - mat.m23 * mat.m32);
    flt32 d2 = mat.m12 * (mat.m23 * mat.m31 - mat.m21 * mat.m33);
    flt32 d3 = mat.m13 * (mat.m21 * mat.m32 - mat.m22 * mat.m31);

    return d1 + d2 + d3;
}

fmat3x3 Inverse(fmat3x3 mat)
{
    flt32 m1 = mat.m22 * mat.m33 - mat.m23 * mat.m32;
    flt32 m2 = mat.m23 * mat.m31 - mat.m21 * mat.m33;
    flt32 m3 = mat.m21 * mat.m32 - mat.m22 * mat.m31;
    
    flt32 m4 = mat.m13 * mat.m32 - mat.m12 * mat.m33;
    flt32 m5 = mat.m11 * mat.m33 - mat.m13 * mat.m31;
    flt32 m6 = mat.m31 * mat.m12 - mat.m11 * mat.m32;
    
    flt32 m7 = mat.m12 * mat.m23 - mat.m22 * mat.m13;
    flt32 m8 = mat.m21 * mat.m13 - mat.m11 * mat.m23;
    flt32 m9 = mat.m11 * mat.m22 - mat.m12 * mat.m21;

    flt32 det = mat.m11 * m1 + mat.m12 * m2 + mat.m13 * m3;

    return mat3x3(m1, m4, m7, m2, m5, m8, m3, m6, m9) / det;
}
#endif