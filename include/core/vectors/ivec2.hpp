/* 2 Component Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "../../base.hpp"
#include "../../empch.hpp"
#include "../simd_helpers.hpp"
#include "swizzle.hpp"

struct ALIGN(8) ivec2
{
	union
	{
		int32 _arr[2];
		struct 
		{
			int32 x, y;
		};
        struct
        {
			int32 r, g;
        };

		IVEC2_SWIZZLE(ivec2);
	};

	/**
	 * Copy constructor.
	 * 
	 * \param v Another ivec2 to copy from.
	 */
	ivec2(const ivec2 &v);
	/**
	 * Constructor with components.
	 * 
	 * \param x X component.
	 * \param y Y component.
	 */
	ivec2(int32 x, int32 y);
	/**
	 * Single value constructor.
	 *
	 * \param val Value to initialize x and y components. 
	 *			  Defaults to 0 if not provided.
	 */
	explicit ivec2(int32 val = 0);
	/**
	 * Array constructor.
	 * 
	 * \param arr Pointer to an array of at least 2 int32 elements.
	 */
	explicit ivec2(const int32* arr);

	/**
	 * Indexing operator.
	 * 
	 * \param index Index of the component to access (0 for x or r, 1 for y or g).
	 * \return Value of the component at the specified `index`.
	 */
	int32 operator[](uin32 index) const;
	
	/**
	 * Addition operator.
	 * 
	 * Performs addition between this vector and the `other` vector.
	 *
	 * \param other The other ivec2.
	 * \return Resultant ivec2 after addition.
	 */
	ivec2 operator+(const ivec2& other) const;
	ivec2& operator+=(const ivec2& other);
	ivec2 operator-() const;
	ivec2 operator-(const ivec2& other) const;
	ivec2& operator-=(const ivec2& other);
	ivec2 operator*(const ivec2& other) const;
	ivec2& operator*=(const ivec2& other);
	ivec2 operator*(const int32 val) const;
	ivec2& operator*=(const int32 val);
    ivec2 operator/(const ivec2& other) const;
	ivec2& operator/=(const ivec2& other);
	ivec2 operator/(const int32 val) const;
	ivec2& operator/=(const int32 val);
	
	//			Extension Functions for Ease of Use 		//

	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec2 after addition.
	 */
	ivec2 operator+(int32 val) const;
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec2 after addition.
	 */
	ivec2& operator+=(int32 val);
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec2 after subtraction.
	 */
	ivec2 operator-(int32 val) const;
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec2 after subtraction.
	 */
	ivec2& operator-=(int32 val);

	/**
	 * Normalises the vector.
	 *
	 * \return Reference to the modified ivec2 after normalisation.
	 */
	ivec2& Normalise();
	/**
	 * Calculates the dot product of the given vector and the other vector.
	 * 
	 * \param other The other ivec2.
	 * \return The dot product of the given ivec2 and the `other` ivec2.
	 */
    int32 Dot(const ivec2& other) const;
	/**
	 * Calculates the cross product between given vector and the other vector.
	 * 
	 * \param other The other ivec2.
	 * \return The z-component of the cross product between the given ivec2 and the `other` ivec2.
	 */
	int32 Cross(const ivec2& other) const;
	/**
	 * Calculates the distance between given vector and the other vector.
	 * 
	 * \param other The other ivec2.
	 * \return The distance between the given ivec2 and the `other` ivec2.
	 */
	flt32 Distance(const ivec2& other) const;

	#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& os, const ivec2& v)
    {
        os << "( X: " << v.x << "\tY: "<< v.y << " )";

        return os;
    }
	#endif

	
	/**
	 * Shorthand to create a zero vector - ivec2(0, 0)
	 * 
	 */
	const static ivec2 zero;
	/**
	 * Shorthand to create a unit vector - ivec2(1, 1)
	 * 
	 */
	const static ivec2 one;
	/**
	 * Shorthand to create a negative unit vector - ivec2(-1, -1)
	 * 
	 */
	const static ivec2 neg;

	/**
	 * Shorthand to create up vector - ivec2(0, 1)
	 * 
	 */
	const static ivec2 up;
	/**
	 * Shorthand to create down vector - ivec2(0, -1)
	 * 
	 */
	const static ivec2 down;
	/**
	 * Shorthand to create right vector - ivec2(1, 0)
	 * 
	 */
	const static ivec2 right;
	/**
	 * Shorthand to create left vector - ivec2(-1, 0)
	 * 
	 */
	const static ivec2 left;
};

int32 Dot(const ivec2& v1, const ivec2& v2);
int32 Cross(const ivec2& v1, const ivec2& v2);
flt32 Distance(const ivec2& v1, const ivec2& v2);

#ifdef ENMA_IMPLEMENTATION
ivec2::ivec2(const ivec2& v)
{
	this->x = v.x;
	this->y = v.y;
}

ivec2::ivec2(int32 x, int32 y) : x(x), y(y) {}

ivec2::ivec2(int32 val) : x(val), y(val) {}

ivec2::ivec2(const int32* arr)
{
	this->_arr[0] = arr[0];
	this->_arr[1] = arr[1];
}

int32 ivec2::operator[](uin32 index) const
{
	return _arr[index];
}

ivec2 ivec2::operator+(const ivec2& other) const
{
	return ivec2(this->x + other.x, this->y + other.y);
}

ivec2& ivec2::operator+=(const ivec2& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

ivec2 ivec2::operator-() const
{
	return ivec2(-x, -y);
}

ivec2 ivec2::operator-(const ivec2& other) const
{
	return ivec2(this->x - other.x, this->y - other.y);
}

ivec2& ivec2::operator-=(const ivec2& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

ivec2 ivec2::operator*(const ivec2& other) const
{
	return ivec2(this->x * other.x, this->y * other.y);
}

ivec2& ivec2::operator*=(const ivec2& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

ivec2 ivec2::operator*(const int32 val) const
{
	return ivec2(this->x * val, this->y * val);
}

ivec2& ivec2::operator*=(const int32 val)
{
	this->x *= val;
	this->y *= val;

	return *this;
}

ivec2 ivec2::operator/(const ivec2& other) const
{

	return ivec2(this->x / other.x, this->y / other.y);
}

ivec2& ivec2::operator/=(const ivec2& other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

ivec2 ivec2::operator/(const int32 val) const
{

	return ivec2(this->x / val, this->y / val);
}

ivec2& ivec2::operator/=(const int32 val)
{

	this->x *= val;
	this->y *= val;

	return *this;
}

int32 ivec2::Dot(const ivec2& other) const
{
	return this->x * other.x + this->y * other.y;
}

int32 Dot(const ivec2& v1, const ivec2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

int32 ivec2::Cross(const ivec2& other) const
{
	return this->x * other.y - other.x * this->y;
}

int32 Cross(const ivec2& v1, const ivec2& v2)
{
	return v1.x * v2.y - v2.x * v1.y;
}

flt32 ivec2::Distance(const ivec2& other) const
{
	const int32 xt = this->x - other.x;
	const int32 yt = this->y - other.y;

	return sqrt(xt * xt + yt * yt);
}

flt32 Distance(const ivec2& v1, const ivec2& v2)
{
	const int32 xt = v1.x - v2.x;
	const int32 yt = v1.y - v2.y;

	return sqrt(xt * xt + yt * yt);
}

const ivec2 ivec2::zero 	= ivec2(0);
const ivec2 ivec2::one 		= ivec2(1);
const ivec2 ivec2::neg 		= ivec2(-1);

const ivec2 ivec2::up 		= ivec2(0, 1);
const ivec2 ivec2::down 	= ivec2(0, -1);
const ivec2 ivec2::right 	= ivec2(1, 0);
const ivec2 ivec2::left 	= ivec2(-1, 0);

#endif	// ENMA_IMPLEMENTATION
