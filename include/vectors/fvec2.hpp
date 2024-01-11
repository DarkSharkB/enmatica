/* 2 Component Single Precision Floating-Point Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "../empch.hpp"

struct ALIGN(8) fvec2
{
    union 
    {
        struct
        {
            flt32 x, y;
        };
        flt32 arr[2];
    };

	fvec2(const fvec2 &vec);
	fvec2(const flt32 val = 0.0f);
    fvec2(const flt32 fx, const flt32 fy);
	fvec2(const flt32 *arr);
	fvec2(const __m128 vals);

    fvec2 operator+(const fvec2 other);
	fvec2 operator+=(const fvec2 other);
	fvec2 operator+(const flt32 val);
	fvec2 operator+=(const flt32 val);
	fvec2 operator-();
	fvec2 operator-(const fvec2 other);
	fvec2 operator-=(const fvec2 other);
	fvec2 operator-(const flt32 val);
	fvec2 operator-=(const flt32 val);
	fvec2 operator*(const fvec2 other);
	fvec2 operator*=(const fvec2 other);
	fvec2 operator*(const flt32 val);
	fvec2 operator*=(const flt32 val);
    fvec2 operator/(const fvec2 other);
	fvec2 operator/=(const fvec2 other);
	fvec2 operator/(const flt32 val);
	fvec2 operator/=(const flt32 val);

	fvec2 Normalize();
    flt32 Dot(const fvec2 other);
	flt32 Cross(const fvec2 other);
	flt32 Distance(const fvec2 other);
	
	#ifdef DEBUG
    friend std::ostream &operator<<(std::ostream &os, const fvec2 vec)
    {
        os << "( X: " << vec.arr[0] << "\tY: " << vec.arr[1] << " )";

        return os;
    }
	#endif
};

#ifdef ENMATICA_IMPL
fvec2::fvec2(const fvec2 &vec)
{
    *this = vec;
}

fvec2::fvec2(const flt32 val) : x(val), y(val) {}

fvec2::fvec2(const flt32 fx, const flt32 fy) : x(fx), y(fy) {}

fvec2::fvec2(const flt32 *arr)
{
	this->arr[0] = arr[0];
	this->arr[1] = arr[1];
}

fvec2::fvec2(const __m128 vals)
{
		this->arr[0] = vals[0];
		this->arr[1] = vals[1];
}
    
fvec2 fvec2::operator+(const fvec2 other)
{
	__m128 v1 = _mm_set_ps(0.0f, 0.0f, this->y, this->x);
	__m128 v2 = _mm_set_ps(0.0f, 0.0f, other.y, other.x);

	return fvec2(_mm_add_ps(v1, v2));
}

fvec2 fvec2::operator+=(const fvec2 other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

fvec2 fvec2::operator+(const flt32 val)
{
	return fvec2(this->x + val, this->y + val);
}

fvec2 fvec2::operator+=(const flt32 val)
{
	this->x += val;
	this->y += val;

	return *this;
}

fvec2 fvec2::operator-()
{
	return fvec2(-x, -y);
}

fvec2 fvec2::operator-(const fvec2 other)
{
	return fvec2(this->x - other.x, this->y - other.y);
}

fvec2 fvec2::operator-=(const fvec2 other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

fvec2 fvec2::operator-(const flt32 val)
{
	return fvec2(this->x - val, this->y - val);
}

fvec2 fvec2::operator-=(const flt32 val)
{
	this->x -= val;
	this->y -= val;

	return *this;
}

fvec2 fvec2::operator*(const fvec2 other)
{
	return fvec2(this->x * other.x, this->y * other.y);
}

fvec2 fvec2::operator*=(const fvec2 other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

fvec2 fvec2::operator*(const flt32 val)
{
	return fvec2(this->x * val, this->y * val);
}

fvec2 fvec2::operator*=(const flt32 val)
{
	this->x *= val;
	this->y *= val;

	return *this;
}

fvec2 fvec2::operator/(const fvec2 other)
{

	return fvec2(this->x / other.x, this->y / other.y);
}

fvec2 fvec2::operator/=(const fvec2 other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

fvec2 fvec2::operator/(const flt32 val)
{
	const flt32 rec = 1.0f / val;

	return fvec2(this->x * rec, this->y * rec);
}

fvec2 fvec2::operator/=(const flt32 val)
{
	const flt32 rec = 1.0f / val;

	this->x *= rec;
	this->y *= rec;

	return *this;
}

/**
 * @return Normalized form of the given vector
 */
fvec2 fvec2::Normalize()
{
	flt32 xt = this->x * this->x;
	flt32 yt = this->y * this->y;

	const flt32 mag = 1.0f / sqrt(xt + yt);
	*this *= mag;

	return *this;
}

/**
 * @param other The other vector with which the dot product is calculated
 * @return Returns the dot product between the given vector and the other vector
 */
flt32 fvec2::Dot(const fvec2 other)
{
    return this->x * other.x + this->y * other.y;
}

/**
 * @brief Calculates the cross product between this vector and the other vector
 * 
 * @param other The other vector with which the cross product is calculated
 * @return Returns the z-component of the cross product between the given vector and the other vector
 */
flt32 fvec2::Cross(const fvec2 other)
{
	return this->x * other.y - other.x * this->y;
}

/*
 * @param other The other vector to which the distance is calculated
 * @return Returns the distance between the given vector and the other vector
 */
flt32 fvec2::Distance(const fvec2 other)
{
	flt32 d = 0.0f;
	flt32 xt = this->x - other.x;
	flt32 yt = this->y - other.y;
	xt *= xt;
	yt *= yt;

	d = xt + yt;

	return sqrt(d);
}
#endif