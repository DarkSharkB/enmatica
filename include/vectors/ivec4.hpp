/* 4 Component Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "ivec2.hpp"
#include "ivec3.hpp"
#include "../empch.hpp"

struct ALIGN(16) ivec4
{
    union 
    {
        struct
        {
            int32 x;
            int32 y;
            int32 z;
            int32 w;
        };
        int32 sval[4];
        __m128i vval;
    };

    ivec4(const ivec4 &vec);
	ivec4(const int32 val = 0);
    ivec4(const int32 ix, const int32 iy, const int32 iz, const int32 iw);
    ivec4(const int32 *arr);
	ivec4(const __m128i &vals);
	ivec4(const ivec2 v1, const ivec2 v2);
	ivec4(const int32 x, const ivec3 yzw);
	ivec4(const ivec3 xyz, const int32 w);

    ivec4 operator+(const ivec4 other);
	ivec4 operator+=(const ivec4 other);
	ivec4 operator-();
	ivec4 operator-(const ivec4 other);
	ivec4 operator-=(const ivec4 other);
    ivec4 operator*(const ivec4 other);
	ivec4 operator*=(const ivec4 other);
	ivec4 operator*(const int32 val);
	ivec4 operator*=(const int32 val);
    ivec4 operator/(const ivec4 other);
	ivec4 operator/=(const ivec4 other);
	ivec4 operator/(const int32 val);
	ivec4 operator/=(const int32 val);

	int32 Dot(const ivec4 other);
	static int32 Dot(const ivec4 v1, const ivec4 v2);
	int32 Distance(const ivec4 other);
	static int32 Distance(const ivec4 v1, const ivec4 v2);

	#ifdef DEBUG
    friend std::ostream &operator<<(std::ostream &os, const ivec4 vec)
    {
        os << "( X: " << vec.x << "\tY: "<< vec.y << "\tZ: " << vec.z << "\tW: " << vec.w << " )";

        return os;
    }
	#endif
};

#ifdef ENMATICA_IMPL
ivec4::ivec4(const ivec4 &vec)
{
	*this = vec;
}

ivec4::ivec4(const int32 val) : x(val), y(val), z(val), w(val) {}

ivec4::ivec4(const int32 ix, const int32 iy, const int32 iz, const int32 iw) : x(ix), y(iy), z(iz), w(iw) {}

ivec4::ivec4(const int32 *arr)
{
	this->vval[0] = arr[0];
	this->vval[1] = arr[1];
	this->vval[2] = arr[2];
	this->vval[3] = arr[3];
}

ivec4::ivec4(const __m128i &vals)
{
	this->vval = vals;
}

ivec4::ivec4(const ivec2 v1, const ivec2 v2)
{
	this->x = v1.x;
	this->y = v1.y;
	this->z = v2.x;
	this->w = v2.y;
}

ivec4::ivec4(const int32 x, const ivec3 yzw)
{
	this->x = x;
	this->y = yzw.x;
	this->z = yzw.y;
	this->w = yzw.z;
}

ivec4::ivec4(const ivec3 xyz, const int32 w)
{
	this->x = xyz.x;
	this->y = xyz.y;
	this->z = xyz.z;
	this->w = w;
}

ivec4 ivec4::operator+(const ivec4 other)
{
	return _mm_add_epi32(this->vval, other.vval);
}

ivec4 ivec4::operator+=(const ivec4 other)
{
	this->vval = _mm_add_epi32(this->vval, other.vval);

	return *this;
}

ivec4 ivec4::operator-()
{
	return ivec4(-x, -y, -z, -w);
}

ivec4 ivec4::operator-(const ivec4 other)
{
	return _mm_sub_epi32(this->vval, other.vval);
}

ivec4 ivec4::operator-=(const ivec4 other)
{
	this->vval = _mm_sub_epi32(this->vval, other.vval);

	return *this;
}

ivec4 ivec4::operator*(const ivec4 other)
{
	return _mm_mul_epi32(this->vval, other.vval);
}

ivec4 ivec4::operator*=(const ivec4 other)
{
	this->vval = _mm_mul_epi32(this->vval, other.vval);
	
	return *this;
}

ivec4 ivec4::operator*(const int32 val)
{
	return ivec4(this->x * val, this->y * val, this->z * val, this->w * val);
}

ivec4 ivec4::operator*=(const int32 val)
{
	this->x *= val;
	this->y *= val;
	this->z *= val;
	this->w *= val;

	return *this;
}

ivec4 ivec4::operator/(const ivec4 other)
{
	return ivec4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
}

ivec4 ivec4::operator/=(const ivec4 other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	this->w /= other.w;

	return *this;
}

ivec4 ivec4::operator/(const int32 val)
{

	return ivec4(this->x / val, this->y / val, this->z / val, this->w / val);
}

ivec4 ivec4::operator/=(const int32 val)
{
	this->x /= val;
	this->y /= val;
	this->z /= val;
	this->w /= val;

	return *this;
}

int32 ivec4::Dot(const ivec4 other)
{
	return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

int32 ivec4::Dot(const ivec4 v1, const ivec4 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// Not Tested Yet - Maybe Removed
int32 ivec4::Distance(const ivec4 other)
{
	const flt32 xt = this->x - other.x;
	const flt32 yt = this->y - other.y;
	const flt32 zt = this->z - other.z;
	const flt32 wt = this->w - other.w;

	return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}

// Not Tested Yet - Maybe Removed
int32 ivec4::Distance(const ivec4 v1, const ivec4 v2)
{
	const flt32 xt = v1.x - v2.x;
	const flt32 yt = v1.y - v2.y;
	const flt32 zt = v1.z - v2.z;
	const flt32 wt = v1.w - v2.w;

	return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}
#endif