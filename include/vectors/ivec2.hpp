/* 2 Component Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "../empch.hpp"

struct ALIGN(8) ivec2
{
	union
	{
		struct 
		{
			int32 x;
			int32 y;
		};
		int32 sval[2];
	};

	ivec2(const ivec2 &vec);
	ivec2(const int32 val = 0);
	ivec2(const int32 ix, const int32 iy);
	
	ivec2 operator+(const ivec2 other);
	ivec2 operator+=(const ivec2 other);
	ivec2 operator-();
	ivec2 operator-(const ivec2 other);
	ivec2 operator-=(const ivec2 other);
	ivec2 operator*(const ivec2 other);
	ivec2 operator*=(const ivec2 other);
	ivec2 operator*(const int32 val);
	ivec2 operator*=(const int32 val);
    ivec2 operator/(const ivec2 other);
	ivec2 operator/=(const ivec2 other);
	ivec2 operator/(const int32 val);
	ivec2 operator/=(const int32 val);

    int32 Dot(const ivec2 other);
	static int32 Dot(const ivec2 v1, const ivec2 v2);
	int32 Cross(const ivec2 other);
	static int32 Cross(const ivec2 v1, const ivec2 v2);
	flt32 Distance(const ivec2 other);
	static flt32 Distance(const ivec2 v1, const ivec2 v2);

	#ifdef DEBUG
    friend std::ostream &operator<<(std::ostream &os, const ivec2 vec)
    {
        os << "( X: " << vec.x << "\tY: "<< vec.y << " )";

        return os;
    }
	#endif
};

#ifdef ENMATICA_IMPL
ivec2::ivec2(const ivec2 &vec)
{
	*this = vec;
}

ivec2::ivec2(int32 val) : x(val), y(val) {}

ivec2::ivec2(int32 ix, int32 iy) : x(ix), y(iy) {}

ivec2 ivec2::operator+(const ivec2 other)
{
	return ivec2(this->x + other.x, this->y + other.y);
}

ivec2 ivec2::operator+=(const ivec2 other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

ivec2 ivec2::operator-()
{
	return ivec2(-x, -y);
}

ivec2 ivec2::operator-(const ivec2 other)
{
	return ivec2(this->x - other.x, this->y - other.y);
}

ivec2 ivec2::operator-=(const ivec2 other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

ivec2 ivec2::operator*(const ivec2 other)
{
	return ivec2(this->x * other.x, this->y * other.y);
}

ivec2 ivec2::operator*=(const ivec2 other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

ivec2 ivec2::operator*(const int32 val)
{
	return ivec2(this->x * val, this->y * val);
}

ivec2 ivec2::operator*=(const int32 val)
{
	this->x *= val;
	this->y *= val;

	return *this;
}

ivec2 ivec2::operator/(const ivec2 other)
{

	return ivec2(this->x / other.x, this->y / other.y);
}

ivec2 ivec2::operator/=(const ivec2 other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

ivec2 ivec2::operator/(const int32 val)
{

	return ivec2(this->x / val, this->y / val);
}

ivec2 ivec2::operator/=(const int32 val)
{

	this->x *= val;
	this->y *= val;

	return *this;
}

// Returns the dot product of two vectors
int32 ivec2::Dot(const ivec2 other)
{
	return this->x * other.x + this->y * other.y;
}

// Returns the dot product of two vectors
int32 ivec2::Dot(const ivec2 v1, const ivec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// Returns the z-component of 2D cross product of the vector
int32 ivec2::Cross(const ivec2 other)
{
	return this->x * other.y - other.x * this->y;
}

// Returns the z-component of 2D cross product of the vector
int32 ivec2::Cross(const ivec2 v1, const ivec2 v2)
{
	return v1.x * v2.y - v2.x * v1.y;
}

// Not Tested Yet - Maybe Removed
flt32 ivec2::Distance(const ivec2 other)
{
	const int32 xt = this->x - other.x;
	const int32 yt = this->y - other.y;

	return sqrt(xt * xt + yt * yt);
}

// Not Tested Yet - Maybe Removed
flt32 ivec2::Distance(const ivec2 v1, const ivec2 v2)
{
	const int32 xt = v1.x - v2.x;
	const int32 yt = v1.y - v2.y;

	return sqrt(xt * xt + yt * yt);
}
#endif