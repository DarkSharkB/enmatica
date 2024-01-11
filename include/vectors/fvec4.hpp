/* 4 Component Single Precision Floating-Point Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "fvec2.hpp"
#include "fvec3.hpp"
#include "../empch.hpp"

struct ALIGN(16) fvec4
{
    union
    {
        struct
        {
            flt32 x, y, z, w;
        };
        flt32 arr[4];
    };

	fvec4(const fvec4 &vec);
	fvec4(const flt32 val = 0.0f);
    fvec4(const flt32 fx, const flt32 fy, const flt32 fz = 0.0f, const flt32 fw = 0.0f);
    fvec4(const flt32 *arr);
	fvec4(const __m128 vals);
	fvec4(const fvec2 xy, const fvec2 zw);
	fvec4(const flt32 x, const fvec3 yzw);
	fvec4(const fvec3 xyz, const flt32 w);
    
    fvec4 operator+(const fvec4 other);
	fvec4 operator+=(const fvec4 other);
	fvec4 operator+(const flt32 val);
	fvec4 operator+=(const flt32 val);
	fvec4 operator-();
	fvec4 operator-(const fvec4 other);
	fvec4 operator-=(const fvec4 other);
	fvec4 operator-(const flt32 val);
	fvec4 operator-=(const flt32 val);
    fvec4 operator*(const fvec4 other);
	fvec4 operator*=(const fvec4 other);
	fvec4 operator*(const flt32 val);
	fvec4 operator*=(const flt32 val);
    fvec4 operator/(const fvec4 other);
	fvec4 operator/=(const fvec4 other);
	fvec4 operator/(const flt32 val);
	fvec4 operator/=(const flt32 val);

	fvec4 Normalize();
	flt32 Dot(const fvec4 other);
	flt32 Distance(const fvec4 other);
	
	
	#ifdef DEBUG
    friend std::ostream &operator<<(std::ostream &os, const fvec4 vec)
    {
        os << "( X: " << vec.arr[0] << "\tY: " << vec.arr[1] << "\tZ: " << vec.arr[2] << "\tW: " << vec.arr[3] << " )";

        return os;
    }
	#endif
};


#ifdef ENMATICA_IMPL
fvec4::fvec4(const fvec4 &vec)
{
    *this = vec;
}

fvec4::fvec4(const flt32 val) : x(val), y(val), z(val), w(val) {}

fvec4::fvec4(const flt32 fx, const flt32 fy, const flt32 fz, const flt32 fw) : x(fx), y(fy), z(fz), w(fw) {}

fvec4::fvec4(const flt32 *arr)
{
	this->arr[0] = arr[0];
	this->arr[1] = arr[1];
	this->arr[2] = arr[2];
	this->arr[3] = arr[3];
}

fvec4::fvec4(const __m128 vals)
{
	this->arr[0] = vals[0];
	this->arr[1] = vals[1];
	this->arr[2] = vals[2];
	this->arr[3] = vals[3];
}

fvec4::fvec4(const fvec2 xy, const fvec2 zw)
{
	this->x = xy.x;
	this->y = xy.y;
	this->z = zw.x;
	this->w = zw.y;
}

fvec4::fvec4(const flt32 x, const fvec3 yzw)
{
    this->x = x;
	this->y = yzw.x;
	this->z = yzw.y;
	this->w = yzw.z;
}

fvec4::fvec4(const fvec3 xyz, const flt32 w)
{
    this->x = xyz.x;
	this->y = xyz.y;
	this->z = xyz.z;
	this->w = w;
}

fvec4 fvec4::operator+(const fvec4 other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	return fvec4(_mm_add_ps(v1, v2));
}

fvec4 fvec4::operator+=(const fvec4 other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	_mm_store_ps(this->arr, _mm_add_ps(v1, v2));

	return *this;
}

fvec4 fvec4::operator+(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 a = _mm_load_ps1(&val);

	return fvec4(_mm_add_ps(v1, a));
}

fvec4 fvec4::operator+=(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 a = _mm_load_ps1(&val);

	_mm_store_ps(this->arr, _mm_add_ps(v1, a));

	return *this;
}

fvec4 fvec4::operator-()
{
	return fvec4(-x, -y, -z, -w);
}

fvec4 fvec4::operator-(const fvec4 other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	return fvec4(_mm_sub_ps(v1, v2));
}

fvec4 fvec4::operator-=(const fvec4 other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	_mm_store_ps(this->arr, _mm_sub_ps(v1, v2));

	return *this;
}

fvec4 fvec4::operator-(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 s = _mm_load_ps1(&val);

	return fvec4(_mm_sub_ps(v1, s));
}

fvec4 fvec4::operator-=(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 s = _mm_load_ps1(&val);

	_mm_store_ps(this->arr, _mm_sub_ps(v1, s));

	return *this;
}

fvec4 fvec4::operator*(const fvec4 other)
{
    const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	return fvec4(_mm_mul_ps(v1, v2));
}

fvec4 fvec4::operator*=(const fvec4 other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);			

	_mm_store_ps(this->arr, _mm_mul_ps(v1, v2));

	return *this;
}

fvec4 fvec4::operator*(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);		// Load up the first Vector using the array block into the XMM register
	const __m128 v2 = _mm_load_ps1(&val);			// Load up the flt32 into another XMM register

	return fvec4(_mm_mul_ps(v1, v2));				// Return the result of the multiplication of the two values
}

fvec4 fvec4::operator*=(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);		// Same as above
	const __m128 v2 = _mm_load_ps1(&val);			

	_mm_store_ps(this->arr, _mm_mul_ps(v1, v2));

	return *this;
}

fvec4 fvec4::operator/(const fvec4 other)
{
    const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	return fvec4(_mm_div_ps(v1, v2));
}

fvec4 fvec4::operator/=(const fvec4 other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	_mm_store_ps(this->arr, _mm_div_ps(v1, v2));

    return *this;
}

fvec4 fvec4::operator/(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 d = _mm_load_ps1(&val);

	return fvec4(_mm_div_ps(v1, d));
}

fvec4 fvec4::operator/=(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 d = _mm_load_ps1(&val);

	_mm_store_ps(this->arr, _mm_div_ps(v1, d));

	return *this;
}

/**
 * @return Normalized form of the given vector
 */
fvec4 fvec4::Normalize()
{
	const __m128 ld = _mm_load_ps(this->arr);
	__m128 dp = _mm_dp_ps(ld, ld, 0xFF);
	__m128 dpsqrt = _mm_sqrt_ps(dp);
	__m128 norm = _mm_div_ps(ld, dp);

	return fvec4(norm);
}

/**
 * @param other The second vector with which the dot product is calculated
 * @return Returns the dot product between the given vector and the second vector
 */
flt32 fvec4::Dot(const fvec4 other)
{
	__m128 m = _mm_load_ps(this->arr);
	__m128 n =  _mm_load_ps(other.arr);
	__m128 dot = _mm_dp_ps(m, n, 0xFF);

	return dot[0];
}

/*
 * @param other The other vector to which the distance is calculated
 * @return Returns the distance between the given vector and the other vector
 */
flt32 fvec4::Distance(const fvec4 other)
{
	__m128 v1 = _mm_load_ps(this->arr);
	__m128 v2 = _mm_load_ps(other.arr);

	v1 = _mm_sub_ps(v1, v2);
	v1 = _mm_dp_ps(v1, v1, 0xFF);
	v1 = _mm_sqrt_ps(v1);

	return v1[0];
}
#endif