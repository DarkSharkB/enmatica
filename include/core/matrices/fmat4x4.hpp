/* Single Precision Floating-Point 4x4 Matrix
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
#include <smmintrin.h>

struct ALIGN(64) fmat4x4
{
	union
	{
		flt32 _arr[16];
		struct
		{
			flt32 m11, m12, m13, m14;
			flt32 m21, m22, m23, m24;
			flt32 m31, m32, m33, m34;
			flt32 m41, m42, m43, m44;
		};
		#ifdef USE_SIMD
		__m128 _vals[4];
		__m256 _vals2[2];
		#endif
	};

	fmat4x4(const fmat4x4& m);
	fmat4x4(flt32 val = 0.0f);
	fmat4x4(flt32 x0, flt32 y0, flt32 z0, flt32 w0, flt32 x1, flt32 y1 = 0.0f, flt32 z1 = 0.0f, flt32 w1 = 0.0f, flt32 x2 = 0.0f, flt32 y2 = 0.0f, flt32 z2 = 0.0f, flt32 w2 = 0.0f, flt32 x3 = 0.0f, flt32 y3 = 0.0f, flt32 z3 = 0.0f, flt32 w3 = 0.0f);
	fmat4x4(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4);

	fvec4 operator[](uin32 rowIndex) const;

	fmat4x4 operator+(const fmat4x4& other) const;
	fmat4x4& operator+=(const fmat4x4& other);
	fmat4x4 operator+(flt32 val) const;
	fmat4x4 operator-() const;
	fmat4x4 operator-(const fmat4x4& other) const;
	fmat4x4& operator-=(const fmat4x4& other);
	fmat4x4 operator*(const fmat4x4& other) const;
	fmat4x4& operator*=(const fmat4x4& other);
	fmat4x4 operator*(flt32 val) const;
	fmat4x4 operator/(flt32 val) const;

	fvec4 operator*(const fvec4 &other) const;

	#ifdef USE_SIMD
	fmat4x4(const __m128& r1, const __m128& r2, const __m128& r3, const __m128& r4);
	fmat4x4(const __m256& r12, const __m256& r34);
	#endif

	#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& os, const fmat4x4& m)
	{
		os 
		<< "\n{\t\t\t\t\t\t\t\t\t}\n"
		<< "|\t" << std::setw(8) << m.m11 << "\t" << std::setw(8) << m.m12 << "\t" << std::setw(8) << m.m13 << "\t" << std::setw(8) << m.m14 << "\t|\n"
		<< "|\t" << std::setw(8) << m.m21 << "\t" << std::setw(8) << m.m22 << "\t" << std::setw(8) << m.m23 << "\t" << std::setw(8) << m.m24 << "\t|\n"
		<< "|\t" << std::setw(8) << m.m31 << "\t" << std::setw(8) << m.m32 << "\t" << std::setw(8) << m.m33 << "\t" << std::setw(8) << m.m34 << "\t|\n"
		<< "|\t" << std::setw(8) << m.m41 << "\t" << std::setw(8) << m.m42 << "\t" << std::setw(8) << m.m43 << "\t" << std::setw(8) << m.m44 << "\t|\n{\t\t\t\t\t\t\t\t\t}";

		return os;
	}
	#endif

	const static fmat4x4 zero;
	const static fmat4x4 identity;
};

fmat4x4 Transpose(const fmat4x4& m);
fmat4x4 AffineInverse(const fmat4x4& m);

#ifdef ENMA_IMPLEMENTATION
fmat4x4::fmat4x4(const fmat4x4& m) 
	: m11(m.m11), m12(m.m12), m13(m.m13), m14(m.m14), m21(m.m21), m22(m.m22), m23(m.m23), m24(m.m24), 
	  m31(m.m31), m32(m.m32), m33(m.m33), m34(m.m34), m41(m.m41), m42(m.m42), m43(m.m43), m44(m.m44) {}

fmat4x4::fmat4x4(flt32 val)
{
	_arr[0] = _arr[5] = _arr[10] = _arr[15] = val;
	_arr[1] = _arr[2] = _arr[3] = _arr[4] = _arr[6] = _arr[7] = _arr[8] = _arr[9] = _arr[11] = _arr[12] = _arr[13] = _arr[14] = 0.0f;
}

fmat4x4::fmat4x4(flt32 x0, flt32 y0, flt32 z0, flt32 w0, flt32 x1, flt32 y1, flt32 z1, flt32 w1, flt32 x2, flt32 y2, flt32 z2, flt32 w2, flt32 x3, flt32 y3, flt32 z3, flt32 w3) : m11(x0), m12(y0), m13(z0), m14(w0), m21(x1), m22(y1), m23(z1), m24(w1), m31(x2), m32(y2), m33(z2), m34(w2), m41(x3), m42(y3), m43(z3), m44(w3) {}

fmat4x4::fmat4x4(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4)
{
	this->_vals[0] = row1;
	this->_vals[1] = row2;
	this->_vals[2] = row3;
	this->_vals[3] = row4;
}

fmat4x4 fmat4x4::operator-() const
{
	return mat4x4(
		-m11, -m12, -m13, -m14, 
		-m21, -m22, -m23, -m24, 
		-m31, -m32, -m33, -m34, 
		-m41, -m42, -m43, -m44
	);
}

#ifdef USE_SIMD
fmat4x4::fmat4x4(const __m128& r1, const __m128& r2, const __m128& r3, const __m128& r4)
{
	this->_vals[0] = r1;
	this->_vals[1] = r2;
	this->_vals[2] = r3;
	this->_vals[3] = r4;
}

fmat4x4::fmat4x4(const __m256& r12, const __m256& r34)
{
	this->_vals2[0] = r12;
	this->_vals2[1] = r34;
}

fvec4 fmat4x4::operator[](uin32 rowIndex) const
{
	//assert(rowIndex > 0 && rowIndex < 4);
	return fvec4(this->_arr + (4 * rowIndex));
}

fmat4x4 fmat4x4::operator+(const fmat4x4& other) const
{
	__m256 r11 = this->_vals2[0];
	__m256 r12 = this->_vals2[1];

	__m256 r21 = other._vals2[0];
	__m256 r22 = other._vals2[1];


	r11 = _mm256_add_ps(r11, r21);
	r12 = _mm256_add_ps(r12, r22);

	return fmat4x4(r11, r12);
}

fmat4x4& fmat4x4::operator+=(const fmat4x4& other)
{
	__m256 r11 = this->_vals2[0];
	__m256 r12 = this->_vals2[1];

	__m256 r21 = other._vals2[0];
	__m256 r22 = other._vals2[1];

	r11 = _mm256_add_ps(r11, r21);
	r12 = _mm256_add_ps(r12, r22);

	*this = fmat4x4(r11, r12);

	return *this;
}

fmat4x4 fmat4x4::operator+(flt32 val) const
{
	__m256 addv = _mm256_set1_ps(val);

	__m256 r1 = this->_vals2[0];
	__m256 r2 = this->_vals2[1];

	r1 = _mm256_add_ps(r1, addv);
	r2 = _mm256_add_ps(r2, addv);

	return fmat4x4(r1, r2);
}


fmat4x4 fmat4x4::operator-(const fmat4x4& other) const
{
	__m256 r11 = this->_vals2[0];
	__m256 r12 = this->_vals2[1];

	__m256 r21 = other._vals2[0];
	__m256 r22 = other._vals2[1];

	r11 = _mm256_sub_ps(r11, r21);
	r12 = _mm256_sub_ps(r12, r22);

	return fmat4x4(r11, r12);
}
	
fmat4x4& fmat4x4::operator-=(const fmat4x4& other)
{
	__m256 r11 = this->_vals2[0];
	__m256 r12 = this->_vals2[1];

	__m256 r21 = other._vals2[0];
	__m256 r22 = other._vals2[1];

	r11 = _mm256_sub_ps(r11, r21);
	r12 = _mm256_sub_ps(r12, r22);

	*this = fmat4x4(r11, r12);

	return *this;
}

fmat4x4 fmat4x4::operator*(const fmat4x4& other) const
{
	flt32 	a[4] = { 0, 0, 0, 0 }, 
			b[4] = { 0, 0, 0, 0 }, 
			c[4] = { 0, 0, 0, 0 }, 
			d[4] = { 0, 0, 0, 0 }; 

	__m128 r00, r01, r02, r03;
	__m128 r10, r11, r12, r13;
	__m128 i1, i2, i3, i4;

	r00 = this->_vals[0];
	r01 = this->_vals[1];
	r02 = this->_vals[2];
	r03 = this->_vals[3];

	r10 = other._vals[0];
	r11 = other._vals[1];
	r12 = other._vals[2];
	r13 = other._vals[3];

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

fvec4 fmat4x4::operator*(const fvec4& other) const
{
	__m128 r00, r01, r02, r03;
	__m128 v41;

	r00 = this->_vals[0];
	r01 = this->_vals[1];
	r02 = this->_vals[2];
	r03 = this->_vals[3];

	v41 = other;

	r00 = _mm_dp_ps(r00, v41, 0xFF);
	r01 = _mm_dp_ps(r01, v41, 0xFF);
	r02 = _mm_dp_ps(r02, v41, 0xFF);
	r03 = _mm_dp_ps(r03, v41, 0xFF);

	return { r00[0], r01[0], r02[0], r03[0] };
}

fmat4x4& fmat4x4::operator*=(const fmat4x4& other)
{
	flt32 	a[4] = { 0, 0, 0, 0 }, 
			b[4] = { 0, 0, 0, 0 }, 
			c[4] = { 0, 0, 0, 0 }, 
			d[4] = { 0, 0, 0, 0 }; 

	__m128 r00, r01, r02, r03;
	__m128 r10, r11, r12, r13;
	__m128 i1, i2, i3, i4;

	r00 = this->_vals[0];
	r01 = this->_vals[1];
	r02 = this->_vals[2];
	r03 = this->_vals[3];

	r10 = other._vals[0];
	r11 = other._vals[1];
	r12 = other._vals[2];
	r13 = other._vals[3];

	_MM_TRANSPOSE4_PS(r10, r11, r12, r13);
	
	i1 = _mm_dp_ps(r00, r10, 0xFF);
	i2 = _mm_dp_ps(r00, r11, 0xFF);
	i3 = _mm_dp_ps(r00, r12, 0xFF);
	i4 = _mm_dp_ps(r00, r13, 0xFF);

	this->_arr[0] = i1[0];
	this->_arr[1] = i2[0];
	this->_arr[2] = i3[0];
	this->_arr[3] = i4[0];

	i1 = _mm_dp_ps(r01, r10, 0xFF);
	i2 = _mm_dp_ps(r01, r11, 0xFF);
	i3 = _mm_dp_ps(r01, r12, 0xFF);
	i4 = _mm_dp_ps(r01, r13, 0xFF);

	this->_arr[4] = i1[0];
	this->_arr[5] = i2[0];
	this->_arr[6] = i3[0];
	this->_arr[7] = i4[0];

	i1 = _mm_dp_ps(r02, r10, 0xFF);
	i2 = _mm_dp_ps(r02, r11, 0xFF);
	i3 = _mm_dp_ps(r02, r12, 0xFF);
	i4 = _mm_dp_ps(r02, r13, 0xFF);

	/*c[0] = i1[0];
	c[1] = i2[0];
	c[2] = i3[0];
	c[3] = i4[0];*/

	this->_arr[8] = i1[0];
	this->_arr[9] = i2[0];
	this->_arr[10] = i3[0];
	this->_arr[11] = i4[0];


	i1 = _mm_dp_ps(r03, r10, 0xFF);
	i2 = _mm_dp_ps(r03, r11, 0xFF);
	i3 = _mm_dp_ps(r03, r12, 0xFF);
	i4 = _mm_dp_ps(r03, r13, 0xFF);

	this->_arr[12] = i1[0];
	this->_arr[13] = i2[0];
	this->_arr[14] = i3[0];
	this->_arr[15] = i4[0];


	//*this = fmat4x4(vec4(a), vec4(b), vec4(c), vec4(d));

	return *this;
}

fmat4x4 fmat4x4::operator*(flt32 val) const
{
	__m256 rfl = _mm256_set1_ps(val);

	__m256 r12 = this->_vals2[0];
	__m256 r34 = this->_vals2[1];

	return fmat4x4(_mm256_mul_ps(r12, rfl), _mm256_mul_ps(r34, rfl));
}

fmat4x4 fmat4x4::operator/(flt32 val) const
{
	__m256 rfl = _mm256_div_ps(_mm256_set1_ps(1.0f), _mm256_set1_ps(val));

	__m256 r12 = this->_vals2[0];
	__m256 r34 = this->_vals2[1];

	return fmat4x4(_mm256_mul_ps(r12, rfl), _mm256_mul_ps(r34, rfl));
}

fmat4x4 Transpose(const fmat4x4& m)
{
    __m128 r1 = m._vals[0];
    __m128 r2 = m._vals[1];
    __m128 r3 = m._vals[2];
    __m128 r4 = m._vals[3];

    _MM_TRANSPOSE4_PS(r1, r2, r3, r4);

    return fmat4x4(r1, r2, r3, r4);
}
#endif

fmat4x4 Inverse(const fmat4x4& m)
{
	// TODO: Implementation
	return m;
}

fmat4x4 AffineInverse(const fmat4x4& m)
{
    flt32 m12 = m.m21;
    flt32 m13 = m.m31;
    flt32 m23 = m.m32;

	return fmat4x4
	{
		m.m11, m12, m13, 0.0f,
		m.m12, m.m22, m23, 0.0f,
		m.m13, m.m23, m.m33, 0.0f,
		-m.m41, -m.m42, -m.m43, 1.0f
	};
}

fvec4 fvec4::operator*(const fmat4x4& other)
{
	vec4 v = this->_vals;
	mat4 m = Transpose(other);

	flt32 x = _mm_dp_ps(v, m._vals[0], 0xFF)[0];
	flt32 y = _mm_dp_ps(v, m._vals[1], 0xFF)[0];
	flt32 z = _mm_dp_ps(v, m._vals[2], 0xFF)[0];
	flt32 w = _mm_dp_ps(v, m._vals[3], 0xFF)[0];

	return fvec4(x, y, z, w);
}

const fmat4x4 fmat4x4::zero = mat4();
const fmat4x4 fmat4x4::identity = mat4(1.0f);
#endif