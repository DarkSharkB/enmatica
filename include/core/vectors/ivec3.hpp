/* 3 Component Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "ivec2.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"

struct ALIGN(16) ivec3
{
    union
    {
        struct
        {
            int32 x, y, z;
        };
        int32 arr[3];
    };
    
public:
    ivec3(const ivec3 &v);
    ivec3(const int32 val = 0);
    ivec3(const int32 ix, const int32 iy, const int32 iz);
    ivec3(const int32 x, const ivec2& yz);
	ivec3(const ivec2& xy, const int32 z);

    ivec3 operator+(const ivec3& other) const;
	ivec3& operator+=(const ivec3& other);
	ivec3 operator-() const;
	ivec3 operator-(const ivec3& other) const;
	ivec3& operator-=(const ivec3& other);
	ivec3 operator*(const ivec3& other) const;
	ivec3& operator*=(const ivec3& other);
	ivec3 operator*(const int32 val) const;
	ivec3& operator*=(const int32 val);
	ivec3 operator/(const ivec3& other) const;
	ivec3& operator/=(const ivec3& other);
	ivec3 operator/(const int32 val) const;
	ivec3& operator/=(const int32 val);

	flt32 Dot(const ivec3& other) const;
	ivec3 Cross(const ivec3& other) const;
	int32 Distance(const ivec3& other) const;
	
	#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& os, const ivec3& v)
	{
		os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";

		return os;
	}
	#endif
};

flt32 Dot(const ivec3& v1, const ivec3& v2);
ivec3 Cross(const ivec3& v1, const ivec3& v2);
int32 Distance(const ivec3& v1, const ivec3& v2);

#ifdef ENMA_IMPLEMENTATION
ivec3::ivec3(const ivec3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

ivec3::ivec3(int32 val) : x(val), y(val), z(val) {}

ivec3::ivec3(int32 ix, int32 iy, int32 iz) : x(ix), y(iy), z(iz) {}

ivec3::ivec3(const int32 x, const ivec2& yz)
{
	this->x = x;
	this->y = yz.x;
	this->z = yz.y;
}

ivec3::ivec3(const ivec2& xy, const int32 z)
{
	this->x = xy.x;
	this->y = xy.y;
	this->z = z;
}

ivec3 ivec3::operator+(const ivec3& other) const
{
	return ivec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

ivec3& ivec3::operator+=(const ivec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

ivec3 ivec3::operator-() const
{
	return ivec3(-x, -y, -z);
}

ivec3 ivec3::operator-(const ivec3& other) const
{
	return ivec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

ivec3& ivec3::operator-=(const ivec3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	
	return *this;
}

ivec3 ivec3::operator*(const ivec3& other) const
{
	return ivec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

ivec3& ivec3::operator*=(const ivec3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;

	return *this;
}

ivec3 ivec3::operator*(const int32 val) const
{
	return ivec3(this->x * val, this->y * val, this->z * val);
}

ivec3& ivec3::operator*=(const int32 val)
{
	this->x *= val;
	this->y *= val;
	this->z *= val;

	return *this;
}

ivec3 ivec3::operator/(const ivec3& other) const
{
	return ivec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

ivec3& ivec3::operator/=(const ivec3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;

	return *this;
}

ivec3 ivec3::operator/(const int32 val) const
{
	return ivec3(this->x / val, this->y / val, this->z / val);
}

ivec3& ivec3::operator/=(const int32 val)
{
	this->x /= val;
	this->y /= val;
	this->z /= val;

	return *this;
}

flt32 ivec3::Dot(const ivec3& other) const
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

flt32 Dot(const ivec3& v1, const ivec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}	

ivec3 ivec3::Cross(const ivec3& other) const
{
	return ivec3(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
}

ivec3 Cross(const ivec3& v1, const ivec3& v2)
{
	return ivec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

// Not Tested Yet - Maybe Removed
int32 ivec3::Distance(const ivec3& other) const
{
	const flt32 xt = this->x - other.x;
	const flt32 yt = this->y - other.y;
	const flt32 zt = this->z - other.z;

	return sqrt(xt * xt + yt * yt + zt * zt);
}

// Not Tested Yet - Maybe Removed or the type be changed
int32 Distance(const ivec3& v1, const ivec3& v2)
{
	const flt32 xt = v1.x - v2.x;
	const flt32 yt = v1.y - v2.y;
	const flt32 zt = v1.z - v2.z;

	return sqrt(xt * xt + yt * yt + zt * zt);
}
#endif