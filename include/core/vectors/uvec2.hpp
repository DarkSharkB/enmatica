/* 2 Component Unsigned Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "../../base.hpp"
#include "../../empch.hpp"

struct ALIGN(8) uvec2
{
	union
	{
		struct 
		{
			uin32 x, y;
		};
		uin32 arr[2];
	};

	uvec2(const uvec2& v);
	uvec2(uin32 val = 0U);
	uvec2(uin32 ux, uin32 uy);

	uvec2 operator+(const uvec2& other) const;
	uvec2& operator+=(const uvec2& other);
	uvec2 operator-() const;
	uvec2 operator-(const uvec2& other) const;
	uvec2& operator-=(const uvec2& other);
	uvec2 operator*(const uvec2& other) const;
	uvec2& operator*=(const uvec2& other);
	uvec2 operator*(const uin32 val) const;
	uvec2& operator*=(const uin32 val);
    uvec2 operator/(const uvec2& other) const;
	uvec2& operator/=(const uvec2& other);
	uvec2 operator/(const uin32 val) const;
	uvec2& operator/=(const uin32 val);

    uin32 Dot(const uvec2& other) const;
	uin32 Cross(const uvec2& other) const;
	uin32 Distance(const uvec2& other) const;

	#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& os, const uvec2& vec)
    {
        os << "( X: " << vec.x << "\tY: "<< vec.y << " )";

        return os;
    }
	#endif
};

uin32 Dot(const uvec2& v1, const uvec2& v2);
uin32 Cross(const uvec2& v1, const uvec2& v2);
uin32 Distance(const uvec2& v1, const uvec2& v2);

#ifdef ENMA_IMPLEMENTATION
uvec2::uvec2(const uvec2& v)
{
	*this = v;
}

uvec2::uvec2(uin32 val) : x(val), y(val) {}

uvec2::uvec2(uin32 ux, uin32 uy) : x(ux), y(uy) {}

uvec2 uvec2::operator+(const uvec2& other) const
{
	return uvec2(this->x + other.x, this->y + other.y);
}

uvec2& uvec2::operator+=(const uvec2& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

uvec2 uvec2::operator-() const
{
	return uvec2(-x, -y);
}

uvec2 uvec2::operator-(const uvec2& other) const
{
	return uvec2(this->x - other.x, this->y - other.y);
}

uvec2& uvec2::operator-=(const uvec2& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

uvec2 uvec2::operator*(const uvec2& other) const
{
	return uvec2(this->x * other.x, this->y * other.y);
}

uvec2& uvec2::operator*=(const uvec2& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

uvec2 uvec2::operator*(const uin32 val) const
{
	return uvec2(this->x * val, this->y * val);
}

uvec2& uvec2::operator*=(const uin32 val)
{
	this->x *= val;
	this->y *= val;

	return *this;
}

uvec2 uvec2::operator/(const uvec2& other) const
{

	return uvec2(this->x / other.x, this->y / other.y);
}

uvec2& uvec2::operator/=(const uvec2& other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

uvec2 uvec2::operator/(const uin32 val) const
{

	return uvec2(this->x / val, this->y / val);
}

uvec2& uvec2::operator/=(const uin32 val)
{

	this->x *= val;
	this->y *= val;

	return *this;
}

// Returns the dot product of two vectors
uin32 uvec2::Dot(const uvec2& other) const
{
	return this->x * other.x + this->y * other.y;
}

// Returns the dot product of two vectors
uin32 Dot(const uvec2& v1, const uvec2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// Returns the z-component of 2D cross product of the vector
uin32 uvec2::Cross(const uvec2& other) const
{
	return this->x * other.y - other.x * this->y;
}

// Returns the z-component of 2D cross product of the vector
uin32 Cross(const uvec2& v1, const uvec2& v2)
{
	return v1.x * v2.y - v2.x * v1.y;
}

// Not Tested Yet - Maybe Removed
uin32 uvec2::Distance(const uvec2& other) const
{
	const uin32 xt = this->x - other.x;
	const uin32 yt = this->y - other.y;

	return sqrt(xt * xt + yt * yt);
}

// Not Tested Yet - Maybe Removed
uin32 Distance(const uvec2& v1, const uvec2& v2)
{
	const uin32 xt = v1.x - v2.x;
	const uin32 yt = v1.y - v2.y;

	return sqrt(xt * xt + yt * yt);
}
#endif