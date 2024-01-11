/* 2 Component Single Precision Floating-Point Vector
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
#include "bvec2.hpp"

using namespace std;

struct ALIGN(8) fvec2
{
    union 
    {
        flt32 _arr[2];
        struct
        {
			flt32 x, y;
        };
        struct
        {
			flt32 r, g;
        };

		FVEC2_SWIZZLE(fvec2);
    };

	/**
	 * Copy constructor.
	 * 
	 * \param v Another fvec2 to copy from.
	 */
	fvec2(const fvec2& v);
	/**
	 * Constructor with components.
	 * 
	 * \param x X component.
	 * \param y Y component.
	 */
    fvec2(flt32 x, flt32 y);
	/**
	 * Single value constructor.
	 *
	 * \param val Value to initialize x and y components. 
	 *			  Defaults to 0.0f if not provided.
	 */
	explicit fvec2(flt32 val = 0.0f);
	/**
	 * Array constructor.
	 * 
	 * \param arr Pointer to an array of at least 2 flt32 elements.
	 */
	explicit fvec2(const flt32* arr);
	
	/**
	 * Indexing operator.
	 * 
	 * \param index Index of the component to access (0 for x or r, 1 for y or g).
	 * \return Value of the component at the specified `index`.
	 */
	flt32 operator[](uin32 index) const;

	/**
	 * Addition operator.
	 * 
	 * Performs addition between this vector and the `other` vector.
	 *
	 * \param other The other fvec2.
	 * \return Resultant fvec2 after addition.
	 */
	fvec2 operator+(const fvec2& other) const;
	/**
	 * Addition assignment operator.
	 * 
	 * Performs addition between this vector and the `other` vector.
	 *
	 * \param other The other fvec2.
	 * \return Reference to the modified fvec2 after addition.
	 */
	fvec2& operator+=(const fvec2& other);
	/**
	 * Unary minus operator.
	 * 
	 * Negates the components of the vector.
	 *
	 * \return Resultant fvec2 with components negated.
	 */
	fvec2 operator-() const;
	/**
	 * Subtraction operator.
	 * 
	 * Performs subtraction between this vector and the `other` vector.
	 *
	 * \param other The other fvec2.
	 * \return Resultant fvec2 after subtraction.
	 */
	fvec2 operator-(const fvec2& other) const;
	/**
	 * Subtraction assignment operator.
	 * 
	 * Performs subtraction between this vector and the `other` vector.
	 *
	 * \param other The other fvec2.
	 * \return Reference to the modified fvec2 after subtraction.
	 */
	fvec2& operator-=(const fvec2& other);
	/**
	 * Multiplication operator (element-wise).
	 * 
	 * Performs element-wise multiplication between this vector and the `other` vector.
	 *
	 * \param other The other fvec2.
	 * \return Resultant fvec2 after multiplication.
	 */
	fvec2 operator*(const fvec2& other) const;
	/**
	 * Multiplication assignment operator (element-wise).
	 * 
	 * Performs element-wise multiplication between this vector and the `other` vector.
	 *
	 * \param other The other fvec2.
	 * \return Reference to the modified fvec2 after multiplication.
	 */
	fvec2& operator*=(const fvec2& other);
	/**
	 * Multiplication operator (scalar).
	 * 
	 * Performs scalar multiplication between this vector and the `other` vector.
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec2 after multiplication.
	 */
	fvec2 operator*(flt32 val) const;
	/**
	 * Multiplication assignment operator (scalar).
	 * 
	 * Performs scalar multiplication between this vector and the `other` vector.
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec2 after multiplication.
	 */
	fvec2& operator*=(flt32 val);
	/**
	 * Division operator (element-wise).
	 * 
	 * Performs element-wise division between this vector and the `other` vector.
	 * 
	 * \param other The other fvec2.
	 * \return Resultant fvec2 after division.
	 */
    fvec2 operator/(const fvec2& other) const;
	/**
	 * Division assignment operator (element-wise).
	 *
	 * Performs element-wise division between this vector and the `other` vector.
	 * 
	 * \param other The other fvec2.
	 * \return Reference to the modified fvec2 after division.
	 */
	fvec2& operator/=(const fvec2& other);
	/**
	 * Division assignment operator (scalar).
	 * 
	 * Performs division between this vector and the scalar `val`.
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec2 after division.
	 */
	fvec2 operator/(flt32 val) const;
	/**
	 * Division assignment operator (scalar).
	 * 
	 * Performs division between this vector and the scalar `val`.
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec2 after division.
	 */
	fvec2& operator/=(flt32 val);

	//			Extension Functions for Ease of Use 		//
	
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec2 after addition.
	 */
	fvec2 operator+(flt32 val) const;
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec2 after addition.
	 */
	fvec2& operator+=(flt32 val);
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec2 after subtraction.
	 */
	fvec2 operator-(flt32 val) const;
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec2 after subtraction.
	 */
	fvec2& operator-=(flt32 val);

	/**
	 * Normalises the vector.
	 *
	 * \return Reference to the modified fvec2 after normalisation.
	 */
	fvec2& Normalise();
	/**
	 * Calculates the dot product of the given vector and the other vector.
	 * 
	 * \param other The other fvec2.
	 * \return The dot product of the given fvec2 and the `other` fvec2.
	 */
    flt32 Dot(const fvec2& other);
	/**
	 * Calculates the cross product between given vector and the other vector.
	 * 
	 * \param other The other fvec2.
	 * \return The z-component of the cross product between the given fvec2 and the `other` fvec2.
	 */
	flt32 Cross(const fvec2& other);

	/**
	 * Calculates the distance between given vector and the other vector.
	 * 
	 * \param other The other fvec2.
	 * \return The distance between the given fvec2 and the `other` fvec2.
	 */
	flt32 Distance(const fvec2& other);

	#ifdef USE_SIMD
	/**
	 * Constructor from __m128.
	 * 
	 * Initializes an fvec2 using values from a __m128 SIMD data type.
	 * 
	 * \param vals __m128 SIMD data type containing values to initialize x and y components.
	 */
	fvec2(const __m128& vals);

	/**
	 * Linear Interpolation
	 *
	 * Interpolates from the given vector, consider it as `a`, to the other vector `b` based on interpolation parameter `t` using SIMD operations.
	 *
	 * \param b The fvec2 to interpolate towards.
	 * \param t Interpolation parameter (typically in the range [0, 1]).
	 * \return The interpolated fvec2.
	 */
	fvec2 Lerp(const fvec2& b, flt32 t);
	#endif
	
	#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& os, const fvec2& v)
    {
        os << "( X: " << v.x << "\tY: " << v.y << " )";

        return os;
    }
	#endif

	/**
	 * Shorthand to create a zero vector - fvec2(0.0f, 0.0f)
	 * 
	 */
	const static fvec2 zero;
	/**
	 * Shorthand to create a unit vector - fvec2(1.0f, 1.0f)
	 * 
	 */
	const static fvec2 one;
	/**
	 * Shorthand to create a negative unit vector - fvec2(-1.0f, -1.0f)
	 * 
	 */
	const static fvec2 neg;

	/**
	 * Shorthand to create up vector - fvec2(0.0f, 1.0f)
	 * 
	 */
	const static fvec2 up;
	/**
	 * Shorthand to create down vector - fvec2(0.0f, -1.0f)
	 * 
	 */
	const static fvec2 down;
	/**
	 * Shorthand to create right vector - fvec2(1.0f, 0.0f)
	 * 
	 */
	const static fvec2 right;
	/**
	 * Shorthand to create left vector - fvec2(-1.0f, 0.0f)
	 * 
	 */
	const static fvec2 left;
};

/**
 * Normalises the input vector.
 *
 * \param v The input fvec2.
 * \return The normalized form of the input fvec2 `v`.
 */
fvec2 Normalise(const fvec2& v);
/**
 * Calculates the dot product between two vectors.
 * 
 * \param v1 The first fvec2.
 * \param v2 The second fvec2.
 * \return The dot product of the first fvec2 `v1` and the second fvec2 `v2`.
 */
flt32 Dot(const fvec2& v1, const fvec2& v2);
/**
 * Calculates the cross product between two vectors.
 * 
 * \param v1 The first fvec2.
 * \param v2 The second fvec2.
 * \return The z-component of the cross product between the first fvec2 `v1` and the second fvec2 `v2`.
 */
flt32 Cross(const fvec2& v1, const fvec2& v2);
/**
 * Calculates the distance between two vectors.
 * 
 * \param v1 The first fvec2.
 * \param v2 The second fvec2.
 * \return The distance between the first fvec2 `v1` and the second fvec2 `v2`.
 */
flt32 Distance(const fvec2& v1, const fvec2& v2);

#ifdef USE_SIMD
/**
 * Linear Interpolation
 *
 * Interpolates from the given vector `a` to the other vector `b` based on interpolation parameter `t`.
 *
 * \param a The fvec2 to interpolate from.
 * \param b The fvec2 to interpolate towards.
 * \param t Interpolation parameter (typically in the range [0, 1]).
 * \return The interpolated fvec2.
 */
fvec2 Lerp(const fvec2& a, const fvec2& b, flt32 t);
#endif

#ifdef ENMA_IMPLEMENTATION
fvec2::fvec2(const fvec2& v) : x(v.x), y(v.y) {}

fvec2::fvec2(flt32 x, flt32 y) : x(x), y(y) {}

fvec2::fvec2(flt32 val) : x(val), y(val) {}

fvec2::fvec2(const flt32* arr)
{
	this->_arr[0] = arr[0];
	this->_arr[1] = arr[1];
}

flt32 fvec2::operator[](uin32 index) const
{
	return _arr[index];
}

flt32 fvec2::Cross(const fvec2& other)
{
	return this->x * other.y - other.x * this->y;
}

flt32 Cross(const fvec2& v1, const fvec2& v2)
{
	return v1.x * v2.y - v2.x * v1.y;
}

#ifdef USE_SIMD

fvec2::fvec2(const __m128& vals)
{
	this->_arr[0] = vals[0];
	this->_arr[1] = vals[1];
}

inline __m128 set(const fvec2& v)
{
	return _mm_set_ps(0.0f, 0.0f, v.y, v.x);
}
    
inline fvec2 fvec2::operator+(const fvec2& other) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	return fvec2(_mm_add_ps(v1, v2));
}

fvec2& fvec2::operator+=(const fvec2& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	*this = _mm_add_ps(v1, v2);

	return *this;
}

fvec2 fvec2::operator-() const
{
	return fvec2(-x, -y);
}

fvec2 fvec2::operator-(const fvec2& other) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	return fvec2(_mm_sub_ps(v1, v2));
}

fvec2& fvec2::operator-=(const fvec2& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	*this = _mm_sub_ps(v1, v2);

	return *this;
}

fvec2 fvec2::operator*(const fvec2& other) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	return fvec2(_mm_mul_ps(v1, v2));
}

fvec2& fvec2::operator*=(const fvec2& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	*this = _mm_mul_ps(v1, v2);

	return *this;
}

fvec2 fvec2::operator*(flt32 val) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	return fvec2(_mm_mul_ps(v1, v2));
}

fvec2& fvec2::operator*=(flt32 val)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	*this = _mm_mul_ps(v1, v2);

	return *this;
}

fvec2 fvec2::operator/(const fvec2& other) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	return fvec2(_mm_div_ps(v1, v2));
}

fvec2& fvec2::operator/=(const fvec2& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	*this = _mm_div_ps(v1, v2);

	return *this;
}

fvec2 fvec2::operator/(flt32 val) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	return fvec2(_mm_div_ps(v1, v2));
}

fvec2& fvec2::operator/=(flt32 val)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	*this = _mm_div_ps(v1, v2);

	return *this;
}

fvec2 fvec2::operator+(flt32 val) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	return fvec2(_mm_add_ps(v1, v2));
}

fvec2& fvec2::operator+=(flt32 val)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	*this = _mm_add_ps(v1, v2);

	return *this;
}

fvec2 fvec2::operator-(flt32 val) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	return fvec2(_mm_sub_ps(v1, v2));
}

fvec2& fvec2::operator-=(flt32 val)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	*this = _mm_sub_ps(v1, v2);

	return *this;
}

fvec2& fvec2::Normalise()
{
	const __m128 vl = set(*this);
	const __m128 x = _mm_dp_ps(vl, vl, 0x77);

	const __m128 mag = _mm_sqrt_ps(x);		// The magnitude of the Vector

	*this = _mm_div_ps(vl, mag);			// Normalised vector

	return *this;
}

fvec2 Normalise(const fvec2& v)
{
	__m128 vl = set(v);
	const __m128 x = _mm_dp_ps(vl, vl, 0x77);

	const __m128 mag = _mm_sqrt_ps(x);	// The magnitude of the Vector

	vl = _mm_div_ps(vl, mag);	// Normalised vector

	return fvec2(vl);
}

flt32 fvec2::Dot(const fvec2& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);
		
	const __m128 dot = _mm_dp_ps(v1, v2, 0x77);

	return dot[0];
}

flt32 Dot(const fvec2& v1, const fvec2& v2)
{
	const __m128 lv1 = set(v1);
	const __m128 lv2 = set(v2);
		
	const __m128 dot = _mm_dp_ps(lv1, lv2, 0x77);

	return dot[0];
}

flt32 fvec2::Distance(const fvec2& other)
{
	__m128 v1 = set(*this);
	__m128 v2 = set(other);

	v1 = _mm_sub_ps(v1, v2);

	v1 = _mm_dp_ps(v1, v1, 0xFF);

	v1 = _mm_sqrt_ps(v1);

	return v1[0];
}

flt32 Distance(const fvec2& v1, const fvec2& v2)
{
	__m128 lv1 = set(v1);
	__m128 lv2 = set(v2);

	lv1 = _mm_sub_ps(lv1, lv2);

	lv1 = _mm_dp_ps(lv1, lv1, 0xFF);

	lv1 = _mm_sqrt_ps(lv1);

	return lv1[0];
}

fvec2 fvec2::Lerp(const fvec2& b, flt32 t)
{
	__m128 lv1 = set(*this);
	__m128 lv2 = set(b);

	__m128 lt = set1(t);

	__m128 bma = _mm_sub_ps(lv2, lv1);

	return fvec2(_mm_fmadd_ps(lt, bma, lv1));
}

fvec2 Lerp(const fvec2& a, const fvec2& b, flt32 t)
{
	__m128 lv1 = set(a);
	__m128 lv2 = set(b);

	__m128 lt = set1(t);

	__m128 bma = _mm_sub_ps(lv2, lv1);

	return fvec2(_mm_fmadd_ps(lt, bma, lv1));
}

#else

fvec2 fvec2::operator+(const fvec2& other) const
{
	return fvec2(this->x + other.x, this->y + other.y);
}

fvec2& fvec2::operator+=(const fvec2& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

fvec2 fvec2::operator-() const
{
	return fvec2(-x, -y);
}

fvec2 fvec2::operator-(const fvec2& other) const
{
	return fvec2(this->x - other.x, this->y - other.y);
}

fvec2& fvec2::operator-=(const fvec2& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

fvec2 fvec2::operator*(const fvec2& other) const
{
	return fvec2(this->x * other.x, this->y * other.y);
}

fvec2& fvec2::operator*=(const fvec2& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

fvec2 fvec2::operator*(flt32 val) const
{
	return fvec2(this->x * val, this->y * val);
}

fvec2& fvec2::operator*=(flt32 val)
{
	this->x *= val;
	this->y *= val;

	return *this;
}

fvec2 fvec2::operator/(const fvec2& other) const
{

	return fvec2(this->x / other.x, this->y / other.y);
}

fvec2& fvec2::operator/=(const fvec2& other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

fvec2 fvec2::operator/(flt32 val) const
{
	const flt32 rec = 1.0f / val;

	return fvec2(this->x * rec, this->y * rec);
}

fvec2& fvec2::operator/=(flt32 val)
{
	const flt32 rec = 1.0f / val;

	this->x *= rec;
	this->y *= rec;

	return *this;
}

fvec2 fvec2::operator+(flt32 val) const
{
	return fvec2(this->x + val, this->y + val);
}

fvec2& fvec2::operator+=(flt32 val)
{
	this->x += val;
	this->y += val;

	return *this;
}

fvec2 fvec2::operator-(flt32 val) const
{
	return fvec2(this->x - val, this->y - val);
}

fvec2& fvec2::operator-=(flt32 val)
{
	this->x -= val;
	this->y -= val;

	return *this;
}

/**
 * @return Normalised form of the given vector
 */
fvec2& fvec2::Normalise()
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
flt32 fvec2::Dot(const fvec2& other)
{
    return this->x * other.x + this->y * other.y;
}

/**
 * @brief Calculates the Euclidean distance between this vector and another vector.
 *
 * @param other The other vector to which the distance is calculated.
 * @return Distance between this vector and the other vector.
 */
flt32 fvec2::Distance(const fvec2& other)
{
	flt32 dx = this->x - other.x;
	flt32 dy = this->y - other.y;

	return sqrt(dx * dx + dy * dy);
}

#endif

const fvec2 fvec2::zero 	= fvec2();
const fvec2 fvec2::one 		= fvec2(1.0f);
const fvec2 fvec2::neg		= fvec2(-1.0f);

const fvec2 fvec2::up 		= fvec2(0.0f, 1.0f);
const fvec2 fvec2::down 	= fvec2(0.0f, -1.0f);
const fvec2 fvec2::right 	= fvec2(1.0f, 0.0f);
const fvec2 fvec2::left 	= fvec2(-1.0f, 0.0f);

#endif	// ENMA_IMPLEMENTATION
