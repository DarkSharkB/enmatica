/* Single Precision Floating-Point 4x4 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../vector.hpp"
#include "../empch.hpp"

struct ALIGN(64) fmat4x4
{
public:
	union
	{
		struct
		{
			flt32 m11, m12, m13, m14;
			flt32 m21, m22, m23, m24;
			flt32 m31, m32, m33, m34;
			flt32 m41, m42, m43, m44;
		};
		flt32 arr[16];
		vec4 rows[4];
	};

public:	
	fmat4x4(const fmat4x4 &mat);
	fmat4x4(const flt32 val = 0.0f);
	fmat4x4(const flt32 x0, const flt32 y0, const flt32 z0, const flt32 w0, const flt32 x1, const flt32 y1 = 0.0f, const flt32 z1 = 0.0f, const flt32 w1 = 0.0f, const flt32 x2 = 0.0f, const flt32 y2 = 0.0f, const flt32 z2 = 0.0f, const flt32 w2 = 0.0f, const flt32 x3 = 0.0f, const flt32 y3 = 0.0f, const flt32 z3 = 0.0f, const flt32 w3 = 0.0f);
	fmat4x4(const __m128 r1, const __m128 r2, const __m128 r3, const __m128 r4);
	fmat4x4(const __m256 r12, const __m256 r34);
	fmat4x4(const vec4 row1, const vec4 row2, const vec4 row3, const vec4 row4);

	fmat4x4 operator+(const fmat4x4 other);
	fmat4x4 operator+=(const fmat4x4 other);
	fmat4x4 operator+(const flt32 val);
	fmat4x4 operator-();
	fmat4x4 operator-(const fmat4x4 other);
	fmat4x4 operator-=(const fmat4x4 other);
	fmat4x4 operator*(const fmat4x4 other);
	fmat4x4 operator*=(const fmat4x4 other);
	fmat4x4 operator*(const flt32 val);
	fmat4x4 operator/(const flt32 val);

	#ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, fmat4x4 mat)
	{
		os 
		<< "\n{\t\t\t\t\t\t\t\t\t}\n"
		<< "|\t" << std::setw(8) << mat.m11 << "\t" << std::setw(8) << mat.m12 << "\t" << std::setw(8) << mat.m13 << "\t" << std::setw(8) << mat.m14 << "\t|\n"
		<< "|\t" << std::setw(8) << mat.m21 << "\t" << std::setw(8) << mat.m22 << "\t" << std::setw(8) << mat.m23 << "\t" << std::setw(8) << mat.m24 << "\t|\n"
		<< "|\t" << std::setw(8) << mat.m31 << "\t" << std::setw(8) << mat.m32 << "\t" << std::setw(8) << mat.m33 << "\t" << std::setw(8) << mat.m34 << "\t|\n"
		<< "|\t" << std::setw(8) << mat.m41 << "\t" << std::setw(8) << mat.m42 << "\t" << std::setw(8) << mat.m43 << "\t" << std::setw(8) << mat.m44 << "\t|\n{\t\t\t\t\t\t\t\t\t}";

		return os;
	}
	#endif
};

fmat4x4 Transpose(fmat4x4);

#ifdef ENMATICA_IMPL
fmat4x4::fmat4x4(const fmat4x4 &mat)
{
	*this = mat;
}

fmat4x4::fmat4x4(const flt32 val)
{
	arr[0] = arr[5] = arr[10] = arr[15] = val;
	arr[1] = arr[2] = arr[3] = arr[4] = arr[6] = arr[7] = arr[8] = arr[9] = arr[11] = arr[12] = arr[13] = arr[14] = 0.0f;
}

fmat4x4::fmat4x4(const flt32 x0, const flt32 y0, const flt32 z0, const flt32 w0, const flt32 x1, const flt32 y1, const flt32 z1, const flt32 w1, const flt32 x2, const flt32 y2, const flt32 z2, const flt32 w2, const flt32 x3, const flt32 y3, const flt32 z3, const flt32 w3)
	: m11(x0), m12(y0), m13(z0), m14(w0), m21(x1), m22(y1), m23(z1), m24(w1), m31(x2), m32(y2), m33(z2), m34(w2), m41(x3), m42(y3), m43(z3), m44(w3) {}

fmat4x4::fmat4x4(const __m128 r1, const __m128 r2, const __m128 r3, const __m128 r4)
{
	this->arr[0] = r1[0];
	this->arr[1] = r1[1];
	this->arr[2] = r1[2];
	this->arr[3] = r1[3];
	this->arr[4] = r2[0];
	this->arr[5] = r2[1];
	this->arr[6] = r2[2];
	this->arr[7] = r2[3];
	this->arr[8] = r3[0];
	this->arr[9] = r3[1];
	this->arr[10] = r3[2];
	this->arr[11] = r3[3];
	this->arr[12] = r4[0];
	this->arr[13] = r4[1];
	this->arr[14] = r4[2];
	this->arr[15] = r4[3];
}

fmat4x4::fmat4x4(const __m256 r12, const __m256 r34)
{
	this->arr[0] = r12[0];
	this->arr[1] = r12[1];
	this->arr[2] = r12[2];
	this->arr[3] = r12[3];
	this->arr[4] = r12[4];
	this->arr[5] = r12[5];
	this->arr[6] = r12[6];
	this->arr[7] = r12[7];
	this->arr[8] = r34[0];
	this->arr[9] = r34[1];
	this->arr[10] = r34[2];
	this->arr[11] = r34[3];
	this->arr[12] = r34[4];
	this->arr[13] = r34[5];
	this->arr[14] = r34[6];
	this->arr[15] = r34[7];
}

fmat4x4::fmat4x4(const vec4 row1, const vec4 row2, const vec4 row3, const vec4 row4)
{
	this->rows[0] = row1;
	this->rows[1] = row2;
	this->rows[2] = row3;
	this->rows[3] = row4;
}

fmat4x4 fmat4x4::operator+(const fmat4x4 other)
{
	__m256 r11 = _mm256_load_ps(this->arr);
	__m256 r12 = _mm256_load_ps(&this->arr[8]);

	__m256 r21 = _mm256_load_ps(other.arr);
	__m256 r22 = _mm256_load_ps(&other.arr[8]);


	r11 = _mm256_add_ps(r11, r21);
	r12 = _mm256_add_ps(r12, r22);

	return fmat4x4(r11, r12);
}
	
fmat4x4 fmat4x4::operator+=(const fmat4x4 other)
{
	__m256 r11 = _mm256_load_ps(&this->arr[0]);
	__m256 r12 = _mm256_load_ps(&this->arr[8]);

	__m256 r21 = _mm256_load_ps(&other.arr[0]);
	__m256 r22 = _mm256_load_ps(&other.arr[8]);


	r11 = _mm256_add_ps(r11, r21);
	r12 = _mm256_add_ps(r12, r22);

	*this = fmat4x4(r11, r12);
	/*this->rows[0] += other.rows[0];
	this->rows[1] += other.rows[1];
	this->rows[2] += other.rows[2];
	this->rows[3] += other.rows[3];*/

	return *this;
}

fmat4x4 fmat4x4::operator+(const flt32 val)
{
	__m256 addv = _mm256_set1_ps(val);

	__m256 r1 = _mm256_load_ps(&this->arr[0]);
	__m256 r2 = _mm256_load_ps(&this->arr[8]);


	r1 = _mm256_add_ps(r1, addv);
	r2 = _mm256_add_ps(r2, addv);

	return fmat4x4(r1, r2);
}

fmat4x4 fmat4x4::operator-()
{
	return mat4x4(
		-m11, -m12, -m13, -m14, 
		-m21, -m22, -m23, -m24, 
		-m31, -m32, -m33, -m34, 
		-m41, -m42, -m43, -m44
	);
}

fmat4x4 fmat4x4::operator-(const fmat4x4 other)
{
	__m256 r11 = _mm256_load_ps(&this->arr[0]);
	__m256 r12 = _mm256_load_ps(&this->arr[8]);

	__m256 r21 = _mm256_load_ps(&other.arr[0]);
	__m256 r22 = _mm256_load_ps(&other.arr[8]);

	r11 = _mm256_sub_ps(r11, r21);
	r12 = _mm256_sub_ps(r12, r22);

	return fmat4x4(r11, r12);
}
	
fmat4x4 fmat4x4::operator-=(const fmat4x4 other)
{
	__m256 r11 = _mm256_load_ps(&this->arr[0]);
	__m256 r12 = _mm256_load_ps(&this->arr[8]);

	__m256 r21 = _mm256_load_ps(&other.arr[0]);
	__m256 r22 = _mm256_load_ps(&other.arr[8]);

	r11 = _mm256_sub_ps(r11, r21);
	r12 = _mm256_sub_ps(r12, r22);

	*this = fmat4x4(r11, r12);

	return *this;
}

fmat4x4 fmat4x4::operator*(const fmat4x4 other)
{
	flt32 	a[4] = { 0, 0, 0, 0 }, 
			b[4] = { 0, 0, 0, 0 }, 
			c[4] = { 0, 0, 0, 0 }, 
			d[4] = { 0, 0, 0, 0 }; 

	__m128 r00, r01, r02, r03;
	__m128 r10, r11, r12, r13;
	__m128 i1, i2, i3, i4;

	r00 = _mm_load_ps(this->rows[0].arr);
	r01 = _mm_load_ps(this->rows[1].arr);
	r02 = _mm_load_ps(this->rows[2].arr);
	r03 = _mm_load_ps(this->rows[3].arr);

	r10 = _mm_load_ps(other.rows[0].arr);
	r11 = _mm_load_ps(other.rows[1].arr);
	r12 = _mm_load_ps(other.rows[2].arr);
	r13 = _mm_load_ps(other.rows[3].arr);

	_MM_TRANSPOSE4_PS(r10, r11, r12, r13);
	
	i1 = _mm_dp_ps(r00, r10, 0xFF);
	i2 = _mm_dp_ps(r00, r11, 0xFF);
	i3 = _mm_dp_ps(r00, r12, 0xFF);
	i4 = _mm_dp_ps(r00, r13, 0xFF);

	a[0] = i1[0];
	a[1] = i2[0];
	a[2] = i3[0];
	a[3] = i4[0];


	i1 = _mm_dp_ps(r01, r10, 0xFF);
	i2 = _mm_dp_ps(r01, r11, 0xFF);
	i3 = _mm_dp_ps(r01, r12, 0xFF);
	i4 = _mm_dp_ps(r01, r13, 0xFF);

	b[0] = i1[0];
	b[1] = i2[0];
	b[2] = i3[0];
	b[3] = i4[0];


	i1 = _mm_dp_ps(r02, r10, 0xFF);
	i2 = _mm_dp_ps(r02, r11, 0xFF);
	i3 = _mm_dp_ps(r02, r12, 0xFF);
	i4 = _mm_dp_ps(r02, r13, 0xFF);

	c[0] = i1[0];
	c[1] = i2[0];
	c[2] = i3[0];
	c[3] = i4[0];


	i1 = _mm_dp_ps(r03, r10, 0xFF);
	i2 = _mm_dp_ps(r03, r11, 0xFF);
	i3 = _mm_dp_ps(r03, r12, 0xFF);
	i4 = _mm_dp_ps(r03, r13, 0xFF);

	d[0] = i1[0];
	d[1] = i2[0];
	d[2] = i3[0];
	d[3] = i4[0];


	return fmat4x4(vec4(a), vec4(b), vec4(c), vec4(d));
}

fmat4x4 fmat4x4::operator*=(const fmat4x4 other)
{
	flt32 	a[4] = { 0, 0, 0, 0 }, 
			b[4] = { 0, 0, 0, 0 }, 
			c[4] = { 0, 0, 0, 0 }, 
			d[4] = { 0, 0, 0, 0 }; 

	__m128 r00, r01, r02, r03;
	__m128 r10, r11, r12, r13;
	__m128 i1, i2, i3, i4;

	r00 = _mm_load_ps(this->rows[0].arr);
	r01 = _mm_load_ps(this->rows[1].arr);
	r02 = _mm_load_ps(this->rows[2].arr);
	r03 = _mm_load_ps(this->rows[3].arr);

	r10 = _mm_load_ps(other.rows[0].arr);
	r11 = _mm_load_ps(other.rows[1].arr);
	r12 = _mm_load_ps(other.rows[2].arr);
	r13 = _mm_load_ps(other.rows[3].arr);

	_MM_TRANSPOSE4_PS(r10, r11, r12, r13);
	
	i1 = _mm_dp_ps(r00, r10, 0xFF);
	i2 = _mm_dp_ps(r00, r11, 0xFF);
	i3 = _mm_dp_ps(r00, r12, 0xFF);
	i4 = _mm_dp_ps(r00, r13, 0xFF);

	this->arr[0] = i1[0];
	this->arr[1] = i2[0];
	this->arr[2] = i3[0];
	this->arr[3] = i4[0];

	i1 = _mm_dp_ps(r01, r10, 0xFF);
	i2 = _mm_dp_ps(r01, r11, 0xFF);
	i3 = _mm_dp_ps(r01, r12, 0xFF);
	i4 = _mm_dp_ps(r01, r13, 0xFF);

	this->arr[4] = i1[0];
	this->arr[5] = i2[0];
	this->arr[6] = i3[0];
	this->arr[7] = i4[0];

	i1 = _mm_dp_ps(r02, r10, 0xFF);
	i2 = _mm_dp_ps(r02, r11, 0xFF);
	i3 = _mm_dp_ps(r02, r12, 0xFF);
	i4 = _mm_dp_ps(r02, r13, 0xFF);

	/*c[0] = i1[0];
	c[1] = i2[0];
	c[2] = i3[0];
	c[3] = i4[0];*/

	this->arr[8] = i1[0];
	this->arr[9] = i2[0];
	this->arr[10] = i3[0];
	this->arr[11] = i4[0];


	i1 = _mm_dp_ps(r03, r10, 0xFF);
	i2 = _mm_dp_ps(r03, r11, 0xFF);
	i3 = _mm_dp_ps(r03, r12, 0xFF);
	i4 = _mm_dp_ps(r03, r13, 0xFF);

	this->arr[12] = i1[0];
	this->arr[13] = i2[0];
	this->arr[14] = i3[0];
	this->arr[15] = i4[0];


	//*this = fmat4x4(vec4(a), vec4(b), vec4(c), vec4(d));

	return *this;
}

fmat4x4 fmat4x4::operator*(const flt32 val)
{
	__m256 rfl = _mm256_set1_ps(val);

	__m256 r12 = _mm256_load_ps(&this->arr[0]);
	__m256 r34 = _mm256_load_ps(&this->arr[8]);

	return fmat4x4(_mm256_mul_ps(r12, rfl), _mm256_mul_ps(r34, rfl));
}

fmat4x4 fmat4x4::operator/(const flt32 val)
{
	__m256 rfl = _mm256_div_ps(_mm256_set1_ps(1.0f), _mm256_set1_ps(val));

	__m256 r12 = _mm256_load_ps(&this->arr[0]);
	__m256 r34 = _mm256_load_ps(&this->arr[8]);

	return fmat4x4(_mm256_mul_ps(r12, rfl), _mm256_mul_ps(r34, rfl));
}

fmat4x4 Transpose(fmat4x4 mat)
{
    __m128 r1 = _mm_load_ps(&mat.arr[0]);
    __m128 r2 = _mm_load_ps(&mat.arr[4]);
    __m128 r3 = _mm_load_ps(&mat.arr[8]);
    __m128 r4 = _mm_load_ps(&mat.arr[12]);

    _MM_TRANSPOSE4_PS(r1, r2, r3, r4);

    return fmat4x4(r1, r2, r3, r4);
}

fmat4x4 Inverse(fmat4x4 mat)
{
	return mat;
}
#endif