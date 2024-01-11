/* 4 Component Unsigned Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "uvec2.hpp"
#include "uvec3.hpp"
#include "../empch.hpp"

struct ALIGN(16) uvec4
{
    union
    {
        struct
        {
            uin32 x;
            uin32 y;
            uin32 z;
            uin32 w;
        };
        uin32 sval[4];
        //__m128i vval;
    };

    uvec4(const uvec4 &vec);
    uvec4(uin32 val = 0U);
    uvec4(uin32 ux, uin32 uy, uin32 uz, uin32 uw);
	uvec4(const uvec2 xy, const uvec2 zw);
	uvec4(const uin32 x, const uvec3 yzw);
	uvec4(const uvec3 xyz, const uin32 w);

    uvec4 operator+(const uvec4 other);
	uvec4 operator+=(const uvec4 other);
	uvec4 operator-();
	uvec4 operator-(const uvec4 other);
	uvec4 operator-=(const uvec4 other);
    uvec4 operator*(const uvec4 other);
	uvec4 operator*=(const uvec4 other);
	uvec4 operator*(const uin32 val);
	uvec4 operator*=(const uin32 val);
    uvec4 operator/(const uvec4 other);
	uvec4 operator/=(const uvec4 other);
	uvec4 operator/(const uin32 val);
	uvec4 operator/=(const uin32 val);

	uin32 Dot(const uvec4 other);
	static uin32 Dot(const uvec4 v1, const uvec4 v2);
	uin32 Distance(const uvec4 other);
	static uin32 Distance(const uvec4 v1, const uvec4 v2);

	#ifdef DEBUG
    friend std::ostream &operator<<(std::ostream &os, const uvec4 vec)
    {
        os << "( X: " << vec.x << "\tY: "<< vec.y << "\tZ: " << vec.z << "\tW: " << vec.w << " )";

        return os;
    }
	#endif
};

#ifdef ENMATICA_IMPL
uvec4::uvec4(const uvec4 &vec)
{
    *this = vec;
}

uvec4::uvec4(uin32 val) : x(val), y(val), z(val), w(val) {}

uvec4::uvec4(uin32 ux, uin32 uy, uin32 uz, uin32 uw) : x(ux), y(uy), z(uz), w(uw) {}

uvec4::uvec4(const uvec2 xy, const uvec2 zw)
{
    this->x = xy.x;
    this->y = xy.y;
    this->z = zw.x;
    this->w = zw.y;
}

uvec4::uvec4(const uin32 x, const uvec3 yzw)
{
    this->x = x;
    this->y = yzw.x;
    this->z = yzw.y;
    this->w = yzw.z;
}

uvec4::uvec4(const uvec3 xyz, const uin32 w)
{
    this->x = xyz.x;
    this->y = xyz.y;
    this->z = xyz.z;
    this->w = w;
}

uvec4 uvec4::operator+(const uvec4 other)
{
    return uvec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

uvec4 uvec4::operator+=(const uvec4 other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;

    return *this;
}

uvec4 uvec4::operator-()
{
	return uvec4(-x, -y, -z, -w);
}

uvec4 uvec4::operator-(const uvec4 other)
{
    return uvec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

uvec4 uvec4::operator-=(const uvec4 other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;

    return *this;
}

uvec4 uvec4::operator*(const uvec4 other)
{
    return uvec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
}

uvec4 uvec4::operator*=(const uvec4 other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->w *= other.w;

    return *this;
}

uvec4 uvec4::operator*(const uin32 val)
{
    return uvec4(this->x * val, this->y * val, this->z * val, this->w * val);
}

uvec4 uvec4::operator*=(const uin32 val)
{
    this->x *= val;
    this->y *= val;
    this->z *= val;
    this->w *= val;

    return *this;
}

uvec4 uvec4::operator/(const uvec4 other)
{
    return uvec4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
}

uvec4 uvec4::operator/=(const uvec4 other)
{
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    this->w /= other.w;

    return *this;
}

uvec4 uvec4::operator/(const uin32 val)
{

    return uvec4(this->x / val, this->y / val, this->z / val, this->w / val);
}

uvec4 uvec4::operator/=(const uin32 val)
{
    this->x /= val;
    this->y /= val;
    this->z /= val;
    this->w /= val;

    return *this;
}

uin32 uvec4::Dot(const uvec4 other)
{
    return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

uin32 uvec4::Dot(const uvec4 v1, const uvec4 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// Not Tested Yet - Maybe Removed
uin32 uvec4::Distance(const uvec4 other)
{
	const float xt = this->x - other.x;
	const float yt = this->y - other.y;
	const float zt = this->z - other.z;
	const float wt = this->w - other.w;

	return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}

// Not Tested Yet - Maybe Removed
uin32 uvec4::Distance(const uvec4 v1, const uvec4 v2)
{
	const float xt = v1.x - v2.x;
	const float yt = v1.y - v2.y;
	const float zt = v1.z - v2.z;
	const float wt = v1.w - v2.w;

	return sqrt(xt * xt + yt * yt + zt * zt + wt * wt);
}
#endif