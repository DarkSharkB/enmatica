/* Single Precision Floating-Point 4x3 Matrix
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once
#include "../vector.hpp"
#include "../empch.hpp"

struct ALIGN(64) fmat4x3
{
private:
	union
	{
		struct
		{
			flt32 m11, m12, m13;
			flt32 m21, m22, m23;
			flt32 m31, m32, m33;
			flt32 m41, m42, m43;
		};
		flt32 arr[12];
		vec3 rows[4];
	};

private:
    flt32 x_pad[4];

public:	
	fmat4x3(const fmat4x3 &m)
	{
			*this = m;
	}

	fmat4x3(const flt32 x0 = 0.0f, const flt32 y0 = 0.0f, const flt32 z0 = 0.0f, const flt32 x1 = 0.0f, const flt32 y1 = 0.0f, const flt32 z1 = 0.0f, const flt32 x2 = 0.0f, const flt32 y2 = 0.0f, const flt32 z2 = 0.0f, const flt32 x3 = 0.0f, const flt32 y3 = 0.0f, const flt32 z3 = 0.0f)
			: m11(x0), m12(y0), m13(z0), m21(x1), m22(y1), m23(z1), m31(x2), m32(y2), m33(z2), m41(x3), m42(y3), m43(z3) {}

	fmat4x3(const __m128 &r0, const __m128 &r1, const __m128 &r2, const __m128 &r3)
	{
			this->rows[0] = r0;
			this->rows[1] = r1;
			this->rows[2] = r2;
			this->rows[3] = r3;
	}

	fmat4x3(const vec3 &v0, const vec3 &v1, const vec3 &v2)
	{
			this->rows[0] = v0;
			this->rows[1] = v1;
			this->rows[2] = v2;
	}

	fmat4x3 operator+(const fmat4x3 m)
	{
		return fmat4x3(this->rows[0] + m.rows[0], this->rows[1] + m.rows[1], this->rows[2] + m.rows[2]);
	}
	
	fmat4x3 operator+=(const fmat4x3 m)
	{
		this->rows[0] = this->rows[0] + m.rows[0];
		this->rows[1] = this->rows[1] + m.rows[1];
		this->rows[2] = this->rows[2] + m.rows[2];
		this->rows[3] = this->rows[3] + m.rows[3];

		return *this;
	}

	fmat4x3 operator-(const fmat4x3 m)
	{
		return fmat4x3(this->rows[0] - m.rows[0], this->rows[1] - m.rows[1], this->rows[2] - m.rows[2]);
	}
	
	fmat4x3 operator-=(const fmat4x3 m)
	{
		this->rows[0] = this->rows[0] - m.rows[0];
		this->rows[1] = this->rows[1] - m.rows[1];
		this->rows[2] = this->rows[2] - m.rows[2];
		this->rows[3] = this->rows[3] - m.rows[3];

		return *this;
	}

	fmat4x3 operator*(const fmat4x3 m)
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

		r10 = _mm_load_ps(m.rows[0].arr);
		r11 = _mm_load_ps(m.rows[1].arr);
		r12 = _mm_load_ps(m.rows[2].arr);
		r13 = _mm_load_ps(m.rows[3].arr);

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


		return fmat4x3(vec3(a), vec3(b), vec3(c));
	}

	#ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, fmat4x3 m)
	{
		os << "{\t\t\t\t\t\t\t\t\t}\n"
		<< "|\t" << std::setw(8) << m.m11 << "\t" << std::setw(8) << m.m12 << "\t" << std::setw(8) << m.m13 << "\t" << "\t|\n"
		<< "|\t" << std::setw(8) << m.m21 << "\t" << std::setw(8) << m.m22 << "\t" << std::setw(8) << m.m23 << "\t" << "\t|\n"
		<< "|\t" << std::setw(8) << m.m31 << "\t" << std::setw(8) << m.m32 << "\t" << std::setw(8) << m.m33 << "\t" << "\t|\n"
		<< "|\t" << std::setw(8) << m.m41 << "\t" << std::setw(8) << m.m42 << "\t" << std::setw(8) << m.m43 << "\t" << "\t|\n{\t\t\t\t\t\t\t\t\t}";

		return os;
	}
	#endif
};

#ifdef ENMATICA_IMPL

#endif