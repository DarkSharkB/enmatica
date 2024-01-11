/* 3 Component Unsigned Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "uvec2.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"

struct ALIGN(16) uvec3
{
    union
    {
        struct
        {
            uin32 x, y, z;
        };
        uin32 arr[3];
    };
		
public:
    uvec3(const uvec3& v);
    uvec3(const uin32 val = 0U);
    uvec3(const uin32 ux, const uin32 uy, const uin32 uz);
    uvec3(const uin32 x, const uvec2& yz);
	uvec3(const uvec2& xy, const uin32 z);

    uvec3 operator+(const uvec3& other) const;
	uvec3& operator+=(const uvec3& other);
	uvec3 operator-() const;
	uvec3 operator-(const uvec3& other) const;
	uvec3& operator-=(const uvec3& other);
	uvec3 operator*(const uvec3& other) const;
	uvec3& operator*=(const uvec3& other);
	uvec3 operator*(const uin32 val) const;
	uvec3& operator*=(const uin32 val);
	uvec3 operator/(const uvec3& other) const;
	uvec3& operator/=(const uvec3& other);
	uvec3 operator/(const uin32 val) const;
	uvec3& operator/=(const uin32 val);

	uin32 Dot(const uvec3& other) const;
	uvec3 Cross(const uvec3& other) const;
	uin32 Distance(const uvec3& other) const;
	
	#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& os, const uvec3& v)
	{
		os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";

		return os;
	}
	#endif
};

uin32 Dot(const uvec3& v1, const uvec3& v2);
uvec3 Cross(const uvec3& v1, const uvec3& v2);
uin32 Distance(const uvec3& v1, const uvec3& v2);

#ifdef ENMA_IMPLEMENTATION
uvec3::uvec3(const uvec3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

uvec3::uvec3(const uin32 val) : x(val), y(val), z(val) {}

uvec3::uvec3(const uin32 ux, const uin32 uy, const uin32 uz) : x(ux), y(uy), z(uz) {}

uvec3::uvec3(const uin32 x, const uvec2& yz)
{
	this->x = x;
	this->y = yz.x;
	this->z = yz.y;
}

uvec3::uvec3(const uvec2& xy, const uin32 z)
{
	this->x = xy.x;
	this->y = xy.y;
	this->z = z;
}

uvec3 uvec3::operator+(const uvec3& other) const
{
	return uvec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

uvec3& uvec3::operator+=(const uvec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

uvec3 uvec3::operator-() const
{
	return uvec3(-x, -y, -z);
}

uvec3 uvec3::operator-(const uvec3& other) const
{
	return uvec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

uvec3& uvec3::operator-=(const uvec3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	
	return *this;
}

uvec3 uvec3::operator*(const uvec3& other) const
{
	return uvec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

uvec3& uvec3::operator*=(const uvec3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;

	return *this;
}

uvec3 uvec3::operator*(const uin32 val) const
{
	return uvec3(this->x * val, this->y * val, this->z * val);
}

uvec3& uvec3::operator*=(const uin32 val)
{
	this->x *= val;
	this->y *= val;
	this->z *= val;

	return *this;
}

uvec3 uvec3::operator/(const uvec3& other) const
{
	return uvec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

uvec3& uvec3::operator/=(const uvec3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;

	return *this;
}

uvec3 uvec3::operator/(const uin32 val) const
{
	return uvec3(this->x / val, this->y / val, this->z / val);
}

uvec3& uvec3::operator/=(const uin32 val)
{
	this->x /= val;
	this->y /= val;
	this->z /= val;

	return *this;
}

uin32 uvec3::Dot(const uvec3& other) const
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

uin32 Dot(const uvec3& v1, const uvec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}	

uvec3 uvec3::Cross(const uvec3& other) const
{
	return uvec3(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
}

uvec3 Cross(const uvec3& v1, const uvec3& v2)
{
	return uvec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

// Not Tested Yet - Maybe Removed
uin32 uvec3::Distance(const uvec3& other) const
{
	const float xt = this->x - other.x;
	const float yt = this->y - other.y;
	const float zt = this->z - other.z;

	return sqrt(xt * xt + yt * yt + zt * zt);
}

// Not Tested Yet - Maybe Removed
uin32 Distance(const uvec3& v1, const uvec3& v2)
{
	const float xt = v1.x - v2.x;
	const float yt = v1.y - v2.y;
	const float zt = v1.z - v2.z;

	return sqrt(xt * xt + yt * yt + zt * zt);
}
#endif