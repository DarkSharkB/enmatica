/* 3 Component Single Precision Floating-Point Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "fvec2.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"
#include "../simd_helpers.hpp"
#include "swizzle.hpp"

struct ALIGN(16) fvec3
{
	union 
    {
		flt32 _arr[3];
        struct
        {
			flt32 x, y, z;
		};
		struct
        {
			flt32 r, g, b;
		};

		FVEC3_SWIZZLE(fvec3);

		#ifdef USE_MEM_ALIGNED
		__m128 _vals;
		#endif
    };
	
	/**
	 * Copy constructor.
	 * 
	 * \param v Another fvec3 to copy from.
	 */
	fvec3(const fvec3& v);
	/**
	 * Constructor with components.
	 * 
	 * \param x X component.
	 * \param y Y component.
	 * \param z Z component. Defaults to 0.0f if not provided.
	 */
	fvec3(flt32 x, flt32 y, flt32 z = 0.0f);
	/**
	 * Single value constructor.
	 *
	 * \param val Value to initialize x, y and z components.
	 *			  Defaults to 0.0f if not provided.
	 */
	explicit fvec3(flt32 val = 0.0f);
	/**
	 * Array constructor.
	 * 
	 * \param arr Pointer to an array of at least 3 flt32 elements.
	 */
	explicit fvec3(const flt32* arr);
	
	/**
	 * Constructor with a value and a vector.
	 * 
	 * \param x X component.
	 * \param yz YZ fvec2. Sets the y and z components.
	 */
	fvec3(flt32 x, const vec2& yz);
	/**
	 * Constructor with a vector and a value.
	 * 
	 * \param xy XY fvec2. Sets the x and y components.
	 * \param z Z component.
	 */
	fvec3(const vec2& xy, flt32 z);

	/**
	 * Conversion operator to fvec2.
	 * 
	 * Implicitly converts the current fvec3 to a fvec2 by discarding the z component.
	 * 
	 * \return A fvec2 with x and y components from the current fvec3.
	 */
	operator fvec2() const;
	/**
	 * Indexing operator.
	 * 
	 * \param index Index of the component to access (0 for x or r, 1 for y or g, 2 for z or b).
	 * \return Value of the component at the specified `index`.
	 */
	flt32 operator[](uin32 index) const;

	/**
	 * Addition operator.
	 * 
	 * Performs addition between this vector and the `other` vector.
	 *
	 * \param other The other fvec3.
	 * \return Resultant fvec3 after addition.
	 */
	fvec3 operator+(const fvec3& other) const;
	/**
	 * Addition assignment operator.
	 * 
	 * Performs addition between this vector and the `other` vector.
	 *
	 * \param other The other fvec3.
	 * \return Reference to the modified fvec3 after addition.
	 */
	fvec3& operator+=(const fvec3& other);
	/**
	 * Unary minus operator.
	 * 
	 * Negates the components of the vector.
	 *
	 * \return Resultant fvec3 with components negated.
	 */
	fvec3 operator-() const;
	/**
	 * Subtraction operator.
	 * 
	 * Performs subtraction between this vector and the `other` vector.
	 *
	 * \param other The other fvec3.
	 * \return Resultant fvec3 after subtraction.
	 */
	fvec3 operator-(const fvec3& other) const;
	/**
	 * Subtraction assignment operator.
	 * 
	 * Performs subtraction between this vector and the `other` vector.
	 *
	 * \param other The other fvec3.
	 * \return Reference to the modified fvec3 after subtraction.
	 */
	fvec3& operator-=(const fvec3& other);
	/**
	 * Multiplication operator (element-wise).
	 * 
	 * Performs element-wise multiplication between this vector and the `other` vector.
	 *
	 * \param other The other fvec3.
	 * \return Resultant fvec3 after multiplication.
	 */
	fvec3 operator*(const fvec3& other) const;
	/**
	 * Multiplication assignment operator (element-wise).
	 * 
	 * Performs element-wise multiplication between this vector and the `other` vector.
	 *
	 * \param other The other fvec3.
	 * \return Reference to the modified fvec3 after multiplication.
	 */
	fvec3& operator*=(const fvec3& other);
	/**
	 * Multiplication operator (scalar).
	 * 
	 * Performs scalar multiplication between this vector and the `other` vector.
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec3 after multiplication.
	 */
	fvec3 operator*(flt32 val) const;
	/**
	 * Multiplication assignment operator (scalar).
	 * 
	 * Performs scalar multiplication between this vector and the `other` vector.
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec3 after multiplication.
	 */
	fvec3& operator*=(flt32 val);
	/**
	 * Division operator (element-wise).
	 * 
	 * Performs element-wise division between this vector and the `other` vector.
	 * 
	 * \param other The other fvec3.
	 * \return Resultant fvec3 after division.
	 */
	fvec3 operator/(const fvec3& other) const;
	/**
	 * Division assignment operator (element-wise).
	 *
	 * Performs element-wise division between this vector and the `other` vector.
	 * 
	 * \param other The other fvec3.
	 * \return Reference to the modified fvec3 after division.
	 */
	fvec3& operator/=(const fvec3& other);
	/**
	 * Division assignment operator (scalar).
	 * 
	 * Performs division between this vector and the scalar `val`.
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec3 after division.
	 */
	fvec3 operator/(flt32 val) const;
	/**
	 * Division assignment operator (scalar).
	 * 
	 * Performs division between this vector and the scalar `val`.
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec3 after division.
	 */
	fvec3& operator/=(flt32 val);

	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec3 after addition.
	 */
	fvec3 operator+(flt32 val) const;
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec3 after addition.
	 */
	fvec3& operator+=(flt32 val);
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec3 after subtraction.
	 */
	fvec3 operator-(flt32 val) const;
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec3 after subtraction.
	 */
	fvec3& operator-=(flt32 val);

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	friend fvec3 operator*(T val, const fvec3& vec)
	{
        return vec * val;
    }

	/**
	 * Normalises the vector.
	 *
	 * \return Reference to the modified fvec3 after normalisation.
	 */
	fvec3& Normalise();
	/**
	 * Calculates the dot product of the given vector and the other vector.
	 * 
	 * \param other The other fvec3.
	 * \return The dot product of the given fvec3 and the `other` fvec3.
	 */
	flt32 Dot(const fvec3& other);
	/**
	 * Calculates the cross product between given vector and the other vector.
	 * 
	 * \param other The other fvec3.
	 * \return The cross product between the given fvec3 and the `other` fvec3.
	 */
	fvec3& Cross(const fvec3& other);
	/**
	 * Calculates the distance between given vector and the other vector.
	 * 
	 * \param other The other fvec3.
	 * \return The distance between the given fvec3 and the `other` fvec3.
	 */
	flt32 Distance(const fvec3& other);

	#ifdef USE_SIMD
	/**
	 * Constructor from __m128.
	 * 
	 * Initializes an fvec3 using values from a __m128 SIMD data type.
	 * 
	 * \param vals A SIMD __m128 data containing values to initialize x, y and z components.
	 */
	fvec3(const __m128& vals);

	/**
	 * Linear Interpolation
	 *
	 * Interpolates from the given vector, consider it as `a`, to the other vector `b` based on interpolation parameter `t` using SIMD operations.
	 *
	 * \param b The fvec3 to interpolate towards.
	 * \param t Interpolation parameter (typically in the range [0, 1]).
	 * \return The interpolated fvec3.
	 */
	fvec3 Lerp(const fvec3& b, flt32 t);
	#endif

	#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& os, const fvec3& v)
	{
		os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";

		return os;
	}
	#endif
	/**
	 * Shorthand to create a zero vector - fvec3(0.0f, 0.0f, 0.0f)
	 * 
	 */
	const static fvec3 zero;
	/**
	 * Shorthand to create a unit vector - fvec3(1.0f, 1.0f, 1.0f)
	 * 
	 */
	const static fvec3 one;
	/**
	 * Shorthand to create a negative unit vector - fvec3(-1.0f, -1.0f, -1.0f)
	 * 
	 */
	const static fvec3 neg;

	/**
	 * Shorthand to create up vector - fvec3(0.0f, 1.0f, 0.0f)
	 * 
	 */
	const static fvec3 up;
	/**
	 * Shorthand to create down vector - fvec3(0.0f, -1.0f, 0.0f)
	 * 
	 */
	const static fvec3 down;
	/**
	 * Shorthand to create right vector - fvec3(1.0f, 0.0f, 0.0f)
	 * 
	 */
	const static fvec3 right;
	/**
	 * Shorthand to create left vector - fvec3(-1.0f, 0.0f, 0.0f)
	 * 
	 */
	const static fvec3 left;
	/**
	 * Shorthand to create forward vector - fvec3(0.0f, 0.0f, 1.0f)
	 * 
	 */
	const static fvec3 forward;
	/**
	 * Shorthand to create back vector - fvec3(0.0f, 0.0f, -1.0f)
	 * 
	 */
	const static fvec3 back;
};

/**
 * @brief Normalises the input vector.
 * 
 * This function takes a three dimensional vector as input and returns
 * a normalised (unit length) version of the vector.
 * 
 * @param v The input fvec3.
 * @return The normalised form of the input fvec3 `v`.
 */
fvec3 Normalise(const fvec3& v);
/**
 * Calculates the dot product between two vectors.
 * 
 * \param v1 The first fvec3.
 * \param v2 The second fvec3.
 * \return The dot product of the first fvec3 `v1` and the second fvec3 `v2`.
 */
flt32 Dot(const fvec3& v1, const fvec3& v2);
/**
 * Calculates the cross product between two vectors.
 * 
 * \param v1 The first fvec3.
 * \param v2 The second fvec3.
 * \return The cross product between the first fvec3 `v1` and the second fvec3 `v2`.
 */
fvec3 Cross(const fvec3& v1, const fvec3& v2);
/**
 * Calculates the distance between two vectors.
 * 
 * \param v1 The first fvec3.
 * \param v2 The second fvec3.
 * \return The distance between the first fvec3 `v1` and the second fvec3 `v2`.
 */
flt32 Distance(const fvec3& v1, const fvec3& v2);

#ifdef USE_SIMD
fvec3 Lerp(const fvec3& a, const fvec3& b, flt32 t);
#endif

#ifdef ENMA_IMPLEMENTATION
fvec3::fvec3(const fvec3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

fvec3::fvec3(flt32 x, flt32 y, flt32 z) : x(x), y(y), z(z) {}

fvec3::fvec3(flt32 val) : x(val), y(val), z(val) {}

fvec3::fvec3(const flt32* arr)
{
	this->_arr[0] = arr[0];
	this->_arr[1] = arr[1];
	this->_arr[2] = arr[2];
}

fvec3::fvec3(flt32 x, const vec2& yz) : x(x), y(yz.x), z(yz.y) {}

fvec3::fvec3(const vec2& xy, flt32 z) : x(xy.x), y(xy.y), z(z) {}

fvec3::operator vec2() const
{
	return vec2(this->x, this->y);
}

flt32 fvec3::operator[](uin32 index) const
{
	return _arr[index];
}

fvec3 fvec3::operator-() const
{
	return fvec3(-x, -y, -z);
}

#ifdef USE_SIMD

__m128 set(const fvec3& v)
{
	return _mm_set_ps(0.0f, v.z, v.y, v.x);
}

#ifdef USE_MEM_ALIGNED
fvec3::fvec3(const __m128& vals)
{
	this->_vals = vals;
}

fvec3 fvec3::operator+(const fvec3& other) const
{
	return fvec3(_mm_add_ps(this->_vals, other._vals));
}
	
fvec3& fvec3::operator+=(const fvec3& other)
{
	this->_vals = _mm_add_ps(this->_vals, other._vals);

	return *this;
}

fvec3 fvec3::operator-(const fvec3& other) const
{
	return fvec3(_mm_sub_ps(this->_vals, other._vals));
}

fvec3& fvec3::operator-=(const fvec3& other)
{
	this->_vals = _mm_sub_ps(this->_vals, other._vals);
		
	return *this;
}

fvec3 fvec3::operator*(const fvec3& other) const
{
	return fvec3(_mm_mul_ps(this->_vals, other._vals));
}

fvec3& fvec3::operator*=(const fvec3& other)
{
	this->_vals = _mm_mul_ps(this->_vals, other._vals);

	return *this;
}

fvec3 fvec3::operator*(flt32 val) const
{
	const __m128 v2 = set1(val);

	return fvec3(_mm_mul_ps(this->_vals, v2));
}

fvec3& fvec3::operator*=(flt32 val)
{
	const __m128 v2 = set1(val);

	this->_vals = _mm_mul_ps(this->_vals, v2);

	return *this;
}

fvec3 fvec3::operator/(const fvec3& other) const
{
	return fvec3(_mm_div_ps(this->_vals, other._vals));
}

fvec3& fvec3::operator/=(const fvec3& other)
{
	this->_vals =_mm_div_ps(this->_vals, other._vals);

	return *this;
}

fvec3 fvec3::operator/(flt32 val) const
{
	const __m128 v2 = set1(val);

	return fvec3(_mm_div_ps(this->_vals, v2));
}

fvec3& fvec3::operator/=(flt32 val)
{
	const __m128 v2 = set1(val);

	this->_vals = _mm_div_ps(this->_vals, v2);

	return *this;
}

fvec3 fvec3::operator+(flt32 val) const
{
	const __m128 v2 = set1(val);

	return fvec3(_mm_add_ps(this->_vals, v2));
}

fvec3& fvec3::operator+=(flt32 val)
{
	const __m128 v2 = set1(val);

	this->_vals = _mm_add_ps(this->_vals, v2);

	return *this;
}

fvec3 fvec3::operator-(flt32 val) const
{
	const __m128 v2 = set1(val);

	return fvec3(_mm_sub_ps(this->_vals, v2));
}

fvec3& fvec3::operator-=(flt32 val)
{
	const __m128 v2 = set1(val);

	this->_vals = _mm_sub_ps(this->_vals, v2);

	return *this;
}
fvec3& fvec3::Normalise()
{
	__m128 vl = this->_vals;
	__m128 x = _mm_dp_ps(vl, vl, 0x77);

	__m128 mag = _mm_sqrt_ps(x);		// The magnitude of the Vector

	*this = _mm_div_ps(vl, mag);		// Normalised vector

	return *this;
}

fvec3 Normalise(const fvec3& v)
{
	__m128 vl = v._vals;
	__m128 x = _mm_dp_ps(vl, vl, 0x77);

	__m128 mag = _mm_sqrt_ps(x);	// The magnitude of the Vector

	vl = _mm_div_ps(vl, mag);	// Normalised vector

	return fvec3(vl);
}

flt32 fvec3::Dot(const fvec3& other)
{
	__m128 dot = _mm_dp_ps(this->_vals, other._vals, 0x77);

	return dot[0];
}

flt32 Dot(const fvec3& v1, const fvec3& v2)
{
	__m128 dot = _mm_dp_ps(v1._vals, v2._vals, 0x77);

	return dot[0];
}

fvec3& fvec3::Cross(const fvec3& other)
{
	__m128 v1 = this->_vals;
	__m128 v2 = other._vals;

	const __m128 i1 = _mm_shuffle_ps(v2, v2, 0x09);
	const __m128 i2 = _mm_shuffle_ps(v1, v1, 0x12);

	v1 = _mm_mul_ps(v1, i1);
	v1 = _mm_shuffle_ps(v1, v1, 0x09);
	v2 = _mm_mul_ps(i1, i2);

	*this = _mm_sub_ps(v1, v2);

	return *this;
}

fvec3 Cross(const fvec3& v1, const fvec3& v2)
{
	__m128 lv1 = v1._vals;
	__m128 lv2 = v2._vals;

	const __m128 i1 = _mm_shuffle_ps(lv2, lv2, 0x09);
	const __m128 i2 = _mm_shuffle_ps(lv1, lv1, 0x12);

	lv1 = _mm_mul_ps(lv1, i1);
	lv1 = _mm_shuffle_ps(lv1, lv1, 0x09);
	lv2 = _mm_mul_ps(i1, i2);

	return fvec3(_mm_sub_ps(lv1, lv2));
}

flt32 fvec3::Distance(const fvec3& other)
{
	__m128 v1 = this->_vals;
	__m128 v2 = other._vals;

	v1 = _mm_sub_ps(v1, v2);

	v1 = _mm_dp_ps(v1, v1, 0xFF);

	v1 = _mm_sqrt_ps(v1);

	return v1[0];
}

flt32 Distance(const fvec3& v1, const fvec3& v2)
{
	__m128 lv1 = _mm_sub_ps(v1._vals, v2._vals);

	lv1 = _mm_dp_ps(lv1, lv1, 0xFF);

	lv1 = _mm_sqrt_ps(lv1);

	return lv1[0];
}

fvec3 fvec3::Lerp(const fvec3& b, flt32 t)
{
	__m128 lv1 = this->_vals;
	__m128 lv2 = b._vals;

	__m128 lt = set1(t);

	__m128 bma = _mm_sub_ps(lv2, lv1);

	return fvec3(_mm_fmadd_ps(lt, bma, lv1));
}

fvec3 Lerp(const fvec3& a, const fvec3& b, flt32 t)
{
	__m128 lv1 = a._vals;
	__m128 lv2 = b._vals;

	__m128 lt = set1(t);

	__m128 bma = _mm_sub_ps(lv2, lv1);

	return fvec3(_mm_fmadd_ps(lt, bma, lv1));
}

#else // USE_MEM_ALIGNED

fvec3::fvec3(const __m128& vals)
{
	this->_arr[0] = vals[0];
	this->_arr[1] = vals[1];
	this->_arr[2] = vals[2];
}

fvec3 fvec3::operator+(const fvec3& other) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);
		
	return fvec3(_mm_add_ps(v1, v2));
}

fvec3& fvec3::operator+=(const fvec3& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	*this = _mm_add_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator-(const fvec3& other) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);
		
	return fvec3(_mm_sub_ps(v1, v2));
}

fvec3& fvec3::operator-=(const fvec3& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	*this = _mm_sub_ps(v1, v2);
		
	return *this;
}

fvec3 fvec3::operator*(const fvec3& other) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	return fvec3(_mm_mul_ps(v1, v2));
}

fvec3& fvec3::operator*=(const fvec3& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	*this = _mm_mul_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator*(flt32 val) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	return fvec3(_mm_mul_ps(v1, v2));
}

fvec3& fvec3::operator*=(flt32 val)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	*this = _mm_mul_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator/(const fvec3& other) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	return fvec3(_mm_div_ps(v1, v2));
}

fvec3& fvec3::operator/=(const fvec3& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);

	*this = _mm_div_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator/(flt32 val) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	return fvec3(_mm_div_ps(v1, v2));
}

fvec3& fvec3::operator/=(flt32 val)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	*this = _mm_div_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator+(flt32 val) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	return fvec3(_mm_add_ps(v1, v2));
}

fvec3& fvec3::operator+=(flt32 val)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	*this = _mm_add_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator-(flt32 val) const
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	return fvec3(_mm_sub_ps(v1, v2));
}

fvec3& fvec3::operator-=(flt32 val)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set1(val);

	*this = _mm_sub_ps(v1, v2);

	return *this;
}

fvec3& fvec3::Normalise()
{
	const __m128 vl = set(*this);
	const __m128 x = _mm_dp_ps(vl, vl, 0x77);

	const __m128 mag = _mm_sqrt_ps(x);		// The magnitude of the Vector

	*this = _mm_div_ps(vl, mag);			// Normalised vector

	return *this;
}

fvec3 Normalise(const fvec3& v)
{
	__m128 vl = set(v);
	const __m128 x = _mm_dp_ps(vl, vl, 0x77);

	const __m128 mag = _mm_sqrt_ps(x);	// The magnitude of the Vector

	vl = _mm_div_ps(vl, mag);	// Normalised vector

	return fvec3(vl);
}

flt32 fvec3::Dot(const fvec3& other)
{
	const __m128 v1 = set(*this);
	const __m128 v2 = set(other);
		
	const __m128 dot = _mm_dp_ps(v1, v2, 0x77);

	return dot[0];
}

flt32 Dot(const fvec3& v1, const fvec3& v2)
{
	const __m128 lv1 = set(v1);
	const __m128 lv2 = set(v2);
		
	const __m128 dot = _mm_dp_ps(lv1, lv2, 0x77);

	return dot[0];
}

fvec3& fvec3::Cross(const fvec3& other)
{
	__m128 v1 = set(*this);
	__m128 v2 = set(other);

	const __m128 i1 = _mm_shuffle_ps(v2, v2, 0x09);
	const __m128 i2 = _mm_shuffle_ps(v1, v1, 0x12);

	v1 = _mm_mul_ps(v1, i1);
	v1 = _mm_shuffle_ps(v1, v1, 0x09);
	v2 = _mm_mul_ps(i1, i2);

	*this = _mm_sub_ps(v1, v2);

	return *this;
}

fvec3 Cross(const fvec3& v1, const fvec3& v2)
{
	__m128 lv1 = set(v1);
	__m128 lv2 = set(v2);

	const __m128 i1 = _mm_shuffle_ps(lv2, lv2, 0x09);
	const __m128 i2 = _mm_shuffle_ps(lv1, lv1, 0x12);

	lv1 = _mm_mul_ps(lv1, i1);
	lv1 = _mm_shuffle_ps(lv1, lv1, 0x09);
	lv2 = _mm_mul_ps(i1, i2);

	return fvec3(_mm_sub_ps(lv1, lv2));
}

flt32 fvec3::Distance(const fvec3& other)
{
	__m128 v1 = set(*this);
	__m128 v2 = set(other);

	v1 = _mm_sub_ps(v1, v2);

	v1 = _mm_dp_ps(v1, v1, 0xFF);

	v1 = _mm_sqrt_ps(v1);

	return v1[0];
}

flt32 Distance(const fvec3& v1, const fvec3& v2)
{
	__m128 lv1 = set(v1);
	__m128 lv2 = set(v2);

	lv1 = _mm_sub_ps(lv1, lv2);

	lv1 = _mm_dp_ps(lv1, lv1, 0xFF);

	lv1 = _mm_sqrt_ps(lv1);

	return lv1[0];
}

fvec3 fvec3::Lerp(const fvec3& b, flt32 t)
{
	__m128 lv1 = set(*this);
	__m128 lv2 = set(b);

	__m128 lt = set1(t);

	__m128 bma = _mm_sub_ps(lv2, lv1);

	return fvec3(_mm_fmadd_ps(lt, bma, lv1));
}

fvec3 Lerp(const fvec3& a, const fvec3& b, flt32 t)
{
	__m128 lv1 = set(a);
	__m128 lv2 = set(b);

	__m128 lt = set1(t);
	
	__m128 bma = _mm_sub_ps(lv2, lv1);

	return fvec3(_mm_fmadd_ps(lt, bma, lv1));
}

#endif // USE_SIMD && ! USE_MEM_ALIGNED

#else // ! USE_SIMD

fvec3 fvec3::operator+(const fvec3& other) const
{
	return fvec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

fvec3& fvec3::operator+=(const fvec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

fvec3 fvec3::operator-(const fvec3& other) const
{
	return fvec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

fvec3& fvec3::operator-=(const fvec3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}

fvec3 fvec3::operator*(const fvec3& other) const
{
	return fvec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

fvec3& fvec3::operator*=(const fvec3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;

	return *this;
}

fvec3 fvec3::operator*(flt32 val) const
{
	return fvec3(this->x * val, this->y * val, this->z * val);
}

fvec3& fvec3::operator*=(flt32 val)
{
	this->x *= val;
	this->y *= val;
	this->z *= val;

	return *this;
}

fvec3 fvec3::operator/(const fvec3& other) const
{

	return fvec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

fvec3& fvec3::operator/=(const fvec3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;

	return *this;
}

fvec3 fvec3::operator/(flt32 val) const
{
	const flt32 rec = 1.0f / val;

	return fvec3(this->x * rec, this->y * rec, this->z * rec);
}

fvec3& fvec3::operator/=(flt32 val)
{
	const flt32 rec = 1.0f / val;

	this->x *= rec;
	this->y *= rec;
	this->z *= rec;

	return *this;
}

fvec3 fvec3::operator+(flt32 val) const
{

	return fvec3(this->x + val, this->y + val, this->z + val);
}

fvec3& fvec3::operator+=(flt32 val)
{
	this->x += val;
	this->y += val;
	this->z += val;

	return *this;
}

fvec3 fvec3::operator-(flt32 val) const
{

	return fvec3(this->x - val, this->y - val, this->z - val);
}

fvec3& fvec3::operator-=(flt32 val)
{
	this->x -= val;
	this->y -= val;
	this->z -= val;

	return *this;
}

/*bvec3 fvec3::Equals(const fvec3 &other)
{
	return bvec3(this->x == other.x, this->y == other.y);
}*/

fvec3& fvec3::Normalise()
{
	flt32 xt = this->x * this->x;
	flt32 yt = this->y * this->y;
	flt32 zt = this->z * this->z;

	const flt32 mag = 1.0f / sqrt(xt + yt + zt);
	*this *= mag;

	return *this;
}

fvec3 Normalise(const fvec3& v)
{
	fvec3 res = v;
	flt32 xt = v.x * v.x;
	flt32 yt = v.y * v.y;
	flt32 zt = v.z * v.z;

	const flt32 mag = 1.0f / sqrt(xt + yt + zt);
	res *= mag;

	return res;
}

flt32 fvec3::Dot(const fvec3& other)
{
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

flt32 Dot(const fvec3& v1, const fvec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

fvec3& fvec3::Cross(const fvec3& other)
{
	*this = fvec3(this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y - this->y * other.x);
	return *this;
}

fvec3 Cross(const fvec3& v1, const fvec3& v2)
{
	return fvec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

flt32 fvec3::Distance(const fvec3& other)
{
	flt32 dx = this->x - other.x;
	flt32 dy = this->y - other.y;
	flt32 dz = this->z - other.z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

flt32 Distance(const fvec3& v1, const fvec3& v2)
{
	flt32 dx = v1.x - v2.x;
	flt32 dy = v1.y - v2.y;
	flt32 dz = v1.z - v2.z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

#endif

const fvec3 fvec3::zero 	= vec3();
const fvec3 fvec3::one 		= vec3(1.0f);
const fvec3 fvec3::neg 		= vec3(-1.0f);

const fvec3 fvec3::up 		= vec3(0.0f, 1.0f, 0.0f);
const fvec3 fvec3::down 	= vec3(0.0f, -1.0f, 0.0f);
const fvec3 fvec3::right 	= vec3(1.0f, 0.0f, 0.0f);
const fvec3 fvec3::left 	= vec3(-1.0f, 0.0f, 0.0f);
const fvec3 fvec3::forward 	= vec3(0.0f, 0.0f, 1.0f);
const fvec3 fvec3::back 	= vec3(0.0f, 0.0f, -1.0f);

#endif	// ENMA_IMPLEMENTATION

//////////////////////////////////////////////////////
// 					Die, Die, Die					//
// 					Die, Die, Die					//
// 					Die, Die, Die					//
// 					Die, Die, Die					//
// 			The Sick, The Dying and The Dead		//
//////////////////////////////////////////////////////
