/* 3 Component Unsigned Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "uvec2.hpp"
#include "../empch.hpp"

struct ALIGN(16) uvec3
{
    union
    {
        struct
        {
            uin32 x;
            uin32 y;
            uin32 z;
        };
        uin32 sval[3];
    };
	uin32 x_pad = 0U;	// Padding for alignment. Again, fucking don't use or touch
		
public:
    uvec3(const uvec3 &vec);
    uvec3(uin32 val = 0U);
    uvec3(uin32 ux, uin32 uy, uin32 uz);
    uvec3(const uin32 x, const uvec2 yz);
	uvec3(const uvec2 xy, const uin32 z);

    uvec3 operator+(const uvec3 other);
	uvec3 operator+=(const uvec3 other);
	uvec3 operator-();
	uvec3 operator-(const uvec3 other);
	uvec3 operator-=(const uvec3 other);
	uvec3 operator*(const uvec3 other);
	uvec3 operator*=(const uvec3 other);
	uvec3 operator*(const uin32 val);
	uvec3 operator*=(const uin32 val);
	uvec3 operator/(const uvec3 other);
	uvec3 operator/=(const uvec3 other);
	uvec3 operator/(const uin32 val);
	uvec3 operator/=(const uin32 val);

	uin32 Dot(const uvec3 other);
	static uin32 Dot(const uvec3 v1, const uvec3 v2);
	uvec3 Cross(const uvec3 other);
	static uvec3 Cross(const uvec3 v1, const uvec3 v2);
	uin32 Distance(const uvec3 other);
	static uin32 Distance(const uvec3 v1, const uvec3 v2);
	
	#ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, const uvec3 vec)
	{
		os << "( X: " << vec.x << "\tY: " << vec.y << "\tZ: " << vec.z << " )";

		return os;
	}
	#endif
};

#ifdef ENMATICA_IMPL
uvec3::uvec3(const uvec3 &vec)
{
	*this = vec;
}

uvec3::uvec3(uin32 val) : x(val), y(val), z(val) {}

uvec3::uvec3(uin32 ux, uin32 uy, uin32 uz) : x(ux), y(uy), z(uz) {}

uvec3::uvec3(const uin32 x, const uvec2 yz)
{
	this->x = x;
	this->y = yz.x;
	this->z = yz.y;
}

uvec3::uvec3(const uvec2 xy, const uin32 z)
{
	this->x = xy.x;
	this->y = xy.y;
	this->z = z;
}

uvec3 uvec3::operator+(const uvec3 other)
{
	return uvec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

uvec3 uvec3::operator+=(const uvec3 other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

uvec3 uvec3::operator-()
{
	return uvec3(-x, -y, -z);
}

uvec3 uvec3::operator-(const uvec3 other)
{
	return uvec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

uvec3 uvec3::operator-=(const uvec3 other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	
	return *this;
}

uvec3 uvec3::operator*(const uvec3 other)
{
	return uvec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

uvec3 uvec3::operator*=(const uvec3 other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;

	return *this;
}

uvec3 uvec3::operator*(const uin32 val)
{
	return uvec3(this->x * val, this->y * val, this->z * val);
}

uvec3 uvec3::operator*=(const uin32 val)
{
	this->x *= val;
	this->y *= val;
	this->z *= val;

	return *this;
}

uvec3 uvec3::operator/(const uvec3 other)
{
	return uvec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

uvec3 uvec3::operator/=(const uvec3 other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;

	return *this;
}

uvec3 uvec3::operator/(const uin32 val)
{
	return uvec3(this->x / val, this->y / val, this->z / val);
}

uvec3 uvec3::operator/=(const uin32 val)
{
	this->x /= val;
	this->y /= val;
	this->z /= val;

	return *this;
}

uin32 uvec3::Dot(const uvec3 other)
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

static uin32 Dot(const uvec3 v1, const uvec3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}	

uvec3 uvec3::Cross(const uvec3 other)
{
	return uvec3(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
}

uvec3 uvec3::Cross(const uvec3 v1, const uvec3 v2)
{
	return uvec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

// Not Tested Yet - Maybe Removed
uin32 uvec3::Distance(const uvec3 other)
{
	const float xt = this->x - other.x;
	const float yt = this->y - other.y;
	const float zt = this->z - other.z;

	return sqrt(xt * xt + yt * yt + zt * zt);
}

// Not Tested Yet - Maybe Removed
uin32 uvec3::Distance(const uvec3 v1, const uvec3 v2)
{
	const float xt = v1.x - v2.x;
	const float yt = v1.y - v2.y;
	const float zt = v1.z - v2.z;

	return sqrt(xt * xt + yt * yt + zt * zt);
}
#endif