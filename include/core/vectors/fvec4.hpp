/* 4 Component Single Precision Floating-Point Vector
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X by Villainous Softworks
 * 
 */

#pragma once
#include "fvec2.hpp"
#include "fvec3.hpp"
#include "../../base.hpp"
#include "../../empch.hpp"
#include "../simd_helpers.hpp"
#include "swizzle.hpp"

struct ALIGN(16) fvec4
{
    union
    {
        flt32 _arr[4];
        struct
        {
			flt32 x, y, z, w;
        };
		struct
        {
			flt32 r, g, b, a;
		};

		FVEC4_SWIZZLE(fvec4);

		#ifdef USE_SIMD
		__m128 _vals;
		#endif
    };

	/**
	 * Copy constructor.
	 * 
	 * \param v Another fvec4 to copy from.
	 */
	fvec4(const fvec4& v);
	/**
	 * Constructor with components.
	 * 
	 * \param x X component.
	 * \param y Y component.
	 * \param z Z component. Defaults to 0.0f if not provided.
	 * \param w W component. Defaults to 0.0f if not provided.
	 */
    fvec4(flt32 fx, flt32 y, flt32 z = 0.0f, flt32 w = 0.0f);
	/**
	 * Single value constructor.
	 *
	 * \param val Value to initialize x, y, z and w components.
	 *			  Defaults to 0.0f if not provided.
	 */
	explicit fvec4(flt32 val = 0.0f);
	/**
	 * Array constructor.
	 * 
	 * \param arr Pointer to an array of at least 4 flt32 elements.
	 */
    explicit fvec4(const flt32* arr);

	/**
	 * Constructor with two vectors.
	 * 
	 * \param xy XY fvec2. Sets the x and y components.
	 * \param zw ZW fvec2. Sets the z and w components.
	 */
	fvec4(const fvec2& xy, const fvec2& zw);
	/**
	 * Constructor with a value and a vector.
	 * 
	 * \param x X component.
	 * \param yzw YZW fvec3. Sets the y, z and w components.
	 */
	fvec4(flt32 x, const fvec3& yzw);
	/**
	 * Constructor with a vector and a value.
	 * 
	 * \param xyz XYZ fvec3. Sets the x, y and z components.
	 * \param w W component.
	 */
	fvec4(const fvec3& xyz, flt32 w);
	
	/**
	 * Conversion operator to fvec2.
	 * 
	 * Implicitly converts the current fvec3 to a fvec2 by discarding the z and w components.
	 * 
	 * \return A fvec2 with x and y components from the current fvec4.
	 */
	operator fvec2() const;
	/**
	 * Conversion operator to fvec3.
	 * 
	 * Implicitly converts the current fvec4 to a fvec3 by discarding the w component.
	 * 
	 * \return A fvec3 with x, y and z components from the current fvec4.
	 */
	operator fvec3() const;
	/**
	 * Indexing operator.
	 * 
	 * \param index Index of the component to access (0 for x or r, 1 for y or g, 2 for z or b, 3 for w or a).
	 * \return Value of the component at the specified `index`.
	 */
	flt32 operator[](uin32 index) const;
    
	/**
	 * Addition operator.
	 * 
	 * Performs addition between this vector and the `other` vector.
	 *
	 * \param other The other fvec4.
	 * \return Resultant fvec4 after addition.
	 */
    fvec4 operator+(const fvec4& other) const;
	/**
	 * Addition assignment operator.
	 * 
	 * Performs addition between this vector and the `other` vector.
	 *
	 * \param other The other fvec4.
	 * \return Reference to the modified fvec4 after addition.
	 */
	fvec4& operator+=(const fvec4& other);
	/**
	 * Unary minus operator.
	 * 
	 * Negates the components of the vector.
	 *
	 * \return Resultant fvec4 with components negated.
	 */
	fvec4 operator-() const;
	/**
	 * Subtraction operator.
	 * 
	 * Performs subtraction between this vector and the `other` vector.
	 *
	 * \param other The other fvec4.
	 * \return Resultant fvec4 after subtraction.
	 */
	fvec4 operator-(const fvec4& other) const;
	/**
	 * Subtraction assignment operator.
	 * 
	 * Performs subtraction between this vector and the `other` vector.
	 *
	 * \param other The other fvec4.
	 * \return Reference to the modified fvec4 after subtraction.
	 */
	fvec4& operator-=(const fvec4& other);
	/**
	 * Multiplication operator (element-wise).
	 * 
	 * Performs element-wise multiplication between this vector and the `other` vector.
	 *
	 * \param other The other fvec4.
	 * \return Resultant fvec4 after multiplication.
	 */
    fvec4 operator*(const fvec4& other) const;
	/**
	 * Multiplication assignment operator (element-wise).
	 * 
	 * Performs element-wise multiplication between this vector and the `other` vector.
	 *
	 * \param other The other fvec4.
	 * \return Reference to the modified fvec4 after multiplication.
	 */
	fvec4& operator*=(const fvec4& other);
	/**
	 * Multiplication operator (scalar).
	 * 
	 * Performs scalar multiplication between this vector and the `other` vector.
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec4 after multiplication.
	 */
	fvec4 operator*(flt32 val) const;
	/**
	 * Multiplication assignment operator (scalar).
	 * 
	 * Performs scalar multiplication between this vector and the `other` vector.
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec4 after multiplication.
	 */
	fvec4& operator*=(flt32 val);
	/**
	 * Division operator (element-wise).
	 * 
	 * Performs element-wise division between this vector and the `other` vector.
	 * 
	 * \param other The other fvec4.
	 * \return Resultant fvec4 after division.
	 */
    fvec4 operator/(const fvec4& other) const;
	/**
	 * Division assignment operator (element-wise).
	 *
	 * Performs element-wise division between this vector and the `other` vector.
	 * 
	 * \param other The other fvec4.
	 * \return Reference to the modified fvec4 after division.
	 */
	fvec4& operator/=(const fvec4& other);
	/**
	 * Division assignment operator (scalar).
	 * 
	 * Performs division between this vector and the scalar `val`.
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec4 after division.
	 */
	fvec4 operator/(flt32 val) const;
	/**
	 * Division assignment operator (scalar).
	 * 
	 * Performs division between this vector and the scalar `val`.
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec4 after division.
	 */
	fvec4& operator/=(flt32 val);
	

	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec4 after addition.
	 */
	fvec4 operator+(flt32 val) const;
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec4 after addition.
	 */
	fvec4& operator+=(flt32 val);
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Resultant fvec4 after subtraction.
	 */
	fvec4 operator-(flt32 val) const;
	/**
	 * Addition operator (scalar).
	 * 
	 * \param val A scalar value.
	 * \return Reference to the modified fvec4 after subtraction.
	 */
	fvec4& operator-=(flt32 val);
	/**
	 * 
	 * \param other 
	 * \return fvec4 
	 */
	fvec4 operator*(const fmat4x4& other);

	/**
	 * Normalises the vector.
	 *
	 * \return Reference to the modified fvec2 after normalisation.
	 */
	fvec4& Normalise();
	/**
	 * Calculates the dot product of the given vector and the other vector.
	 * 
	 * \param other The other fvec4.
	 * \return The dot product of the given fvec4 and the `other` fvec4.
	 */
	flt32 Dot(const fvec4& other) const;
	/**
	 * Calculates the distance between given vector and the other vector.
	 * 
	 * \param other The other fvec4.
	 * \return The distance between the given fvec4 and the `other` fvec4.
	 */
	flt32 Distance(const fvec4& other) const;
	
	#ifdef USE_SIMD
	/**
	 * Conversion operator to __m128.
	 * 
	 * Converts the current fvec4 to a __m128 data type.
	 * This conversion allows interoperability with SIMD instructions and operations.
	 * 
	 * \return  A SIMD __m128 data representing the components of the fvec4.
	 */
	operator __m128() const;
	/**
	 * Constructor from __m128.
	 * 
	 * Initializes an fvec4 object using values from a __m128 SIMD data type.
	 * 
	 * \param vals A SIMD __m128 data containing values to initialize x, y, z and w components.
	 */
	fvec4(const __m128& vals);

	/**
	 * Linear Interpolation
	 *
	 * Interpolates from the given vector, consider it as `a`, to the other vector `b` based on interpolation parameter `t` using SIMD operations.
	 *
	 * \param b The fvec2 to interpolate towards.
	 * \param t Interpolation parameter (typically in the range [0, 1]).
	 * \return The interpolated fvec4.
	 */
	fvec4 Lerp(const fvec4& b, flt32 t) const;
	#endif
	
	#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& os, const fvec4& v)
    {
        os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << "\tW: " << v.w << " )";

        return os;
    }
	#endif

	/**
	 * Shorthand to create a zero vector - fvec4(0.0f, 0.0f, 0.0f, 0.0f)
	 * 
	 */
	const static fvec4 zero;
	
	/**
	 * Shorthand to create a unit vector - fvec4(1.0f, 1.0f, 1.0f, 1.0f)
	 * 
	 */
	const static fvec4 one;
	/**
	 * Shorthand to create a negative unit vector - fvec4(-1.0f, -1.0f, -1.0f, -1.0f)
	 * 
	 */
	const static fvec4 neg;
};

/**
 * Normalises the input vector.
 *
 * \param v The input fvec4.
 * \return The normalized form of the input fvec4 `v`.
 */
fvec4 Normalise(const fvec4& v);
/**
 * Calculates the dot product between two vectors.
 * 
 * \param v1 The first fvec4.
 * \param v2 The second fvec4.
 * \return The dot product of the first fvec4 `v1` and the second fvec4 `v2`.
 */
flt32 Dot(const fvec4& v1, const fvec4& v2);
/**
 * Calculates the distance between two vectors.
 * 
 * \param v1 The first fvec4.
 * \param v2 The second fvec4.
 * \return The distance between the first fvec4 `v1` and the second fvec4 `v2`.
 */
flt32 Distance(const fvec4& v1, const fvec4& v2);

#ifdef USE_SIMD
/**
 * Linear Interpolation
 *
 * Interpolates from the given vector `a` to the other vector `b` based on interpolation parameter `t`.
 *
 * \param a The fvec4 to interpolate from.
 * \param b The fvec4 to interpolate towards.
 * \param t Interpolation parameter (typically in the range [0, 1]).
 * \return The interpolated fvec4.
 */
fvec4 Lerp(const fvec4& a, const fvec4& b, flt32 t);
#endif

#ifdef ENMA_IMPLEMENTATION
fvec4::fvec4(const fvec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

fvec4::fvec4(flt32 x, flt32 y, flt32 z, flt32 w) : x(x), y(y), z(z), w(w) {}

fvec4::fvec4(flt32 val) : x(val), y(val), z(val), w(val) {}

fvec4::fvec4(const flt32* arr)
{
	this->_arr[0] = arr[0];
	this->_arr[1] = arr[1];
	this->_arr[2] = arr[2];
	this->_arr[3] = arr[3];
}

fvec4::fvec4(const fvec2& xy, const fvec2& zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}

fvec4::fvec4(const flt32 x, const fvec3& yzw) : x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

fvec4::fvec4(const fvec3& xyz, const flt32 w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

fvec4::operator vec2() const
{
	return vec2(this->x, this->y);
}

fvec4::operator vec3() const
{
	return vec3(this->x, this->y, this->z);
}

flt32 fvec4::operator[](uin32 index) const
{
	return _arr[index];
}

#ifdef USE_SIMD
fvec4::operator __m128() const
{
	return this->_vals;
}

fvec4::fvec4(const __m128& vals)
{
	this->_vals = vals;
}

fvec4 fvec4::operator+(const fvec4& other) const
{
	return fvec4(_mm_add_ps(this->_vals, other._vals));
}

fvec4& fvec4::operator+=(const fvec4& other)
{
	this->_vals = _mm_add_ps(this->_vals, other._vals);

	return *this;
}

fvec4 fvec4::operator-() const
{
	return fvec4(-x, -y, -z, -w);
}

fvec4 fvec4::operator-(const fvec4& other) const
{
	return fvec4(_mm_sub_ps(this->_vals, other._vals));
}

fvec4& fvec4::operator-=(const fvec4& other)
{
	this->_vals = _mm_sub_ps(this->_vals, other._vals);

	return *this;
}

fvec4 fvec4::operator*(const fvec4& other) const
{
	return fvec4(_mm_mul_ps(this->_vals, other._vals));
}

fvec4& fvec4::operator*=(const fvec4& other)
{			
	this->_vals = _mm_mul_ps(this->_vals, other._vals);

	return *this;
}

fvec4 fvec4::operator*(const flt32 val) const
{
	const __m128 v2 = set1(val);

	return fvec4(_mm_mul_ps(this->_vals, v2));				// Return the result of the multiplication of the two values
}

fvec4& fvec4::operator*=(const flt32 val)
{
	const __m128 v2 = set1(val);		

	this->_vals = _mm_mul_ps(this->_vals, v2);

	return *this;
}

fvec4 fvec4::operator/(const fvec4& other) const
{
	return fvec4(_mm_div_ps(this->_vals, other._vals));
}

fvec4& fvec4::operator/=(const fvec4& other)
{
	this->_vals = _mm_div_ps(this->_vals, other._vals);

    return *this;
}

fvec4 fvec4::operator/(const flt32 val) const
{
	const __m128 v2 = set1(val);

	return fvec4(_mm_div_ps(this->_vals, v2));
}

fvec4& fvec4::operator/=(const flt32 val)
{
	const __m128 v2 = set1(val);

	this->_vals = _mm_div_ps(this->_vals, v2);

	return *this;
}

fvec4 fvec4::operator+(flt32 val) const
{
	const __m128 v2 = set1(val);

	return fvec4(_mm_add_ps(this->_vals, v2));
}

fvec4& fvec4::operator+=(flt32 val)
{
	const __m128 v2 = set1(val);

	*this = _mm_add_ps(this->_vals, v2);

	return *this;
}

fvec4 fvec4::operator-(flt32 val) const
{
	const __m128 v2 = set1(val);

	return fvec4(_mm_sub_ps(this->_vals, v2));
}

fvec4& fvec4::operator-=(flt32 val)
{
	const __m128 v2 = set1(val);

	*this = _mm_sub_ps(this->_vals, v2);

	return *this;
}

fvec4& fvec4::Normalise()
{
	const __m128 ld = this->_vals;
	__m128 dp = _mm_dp_ps(ld, ld, 0xFF);
	__m128 dpsqrt = _mm_sqrt_ps(dp);

	*this = _mm_div_ps(ld, dp);

	return *this;
}

fvec4 Normalise(const fvec4& v)
{
	const __m128 ld = v._vals;
	__m128 dp = _mm_dp_ps(ld, ld, 0xFF);
	__m128 dpsqrt = _mm_sqrt_ps(dp);

	return fvec4(_mm_div_ps(ld, dp));
}

flt32 fvec4::Dot(const fvec4& other) const
{
	__m128 dot = _mm_dp_ps(this->_vals, other._vals, 0xFF);

	return dot[0];
}

flt32 Dot(const fvec4& v1, const fvec4& v2)
{
	__m128 dot = _mm_dp_ps(v1._vals, v2._vals, 0xFF);

	return dot[0];
}

flt32 fvec4::Distance(const fvec4& other) const
{
	__m128 v1 = this->_vals;
	__m128 v2 = other._vals;

	v1 = _mm_sub_ps(v1, v2);
	v1 = _mm_dp_ps(v1, v1, 0xFF);
	v1 = _mm_sqrt_ps(v1);

	return v1[0];
}

flt32 Distance(const fvec4& v1, const fvec4& v2)
{
	__m128 m = v1._vals;
	__m128 n = v2._vals;

	m = _mm_sub_ps(m, n);
	m = _mm_dp_ps(m, m, 0xFF);
	m = _mm_sqrt_ps(m);

	return m[0];
}

fvec4 fvec4::Lerp(const fvec4& b, flt32 t) const
{
	__m128 lv1 = this->_vals;
	__m128 lv2 = b._vals;

	__m128 lt = set1(t);

	__m128 bma = _mm_sub_ps(lv2, lv1);

	return fvec4(_mm_fmadd_ps(lt, bma, lv1));
}

fvec4 Lerp(const fvec4& a, const fvec4& b, flt32 t)
{
	__m128 lv1 = a._vals;
	__m128 lv2 = b._vals;

	__m128 lt = set1(t);

	__m128 bma = _mm_sub_ps(lv2, lv1);

	return fvec4(_mm_fmadd_ps(lt, bma, lv1));
}

#else // ! USE_SIMD

fvec4 fvec4::operator+(const fvec4& other) const
{
	return fvec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

fvec4& fvec4::operator+=(const fvec4& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;

	return *this;
}

fvec4 fvec4::operator-(const fvec4& other) const
{
	return fvec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

fvec4& fvec4::operator-=(const fvec4& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;

	return *this;
}

fvec4 fvec4::operator*(const fvec4& other) const
{
	return fvec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
}

fvec4& fvec4::operator*=(const fvec4& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	this->w *= other.w;

	return *this;
}

fvec4 fvec4::operator*(const flt32 val) const
{
	return fvec4(this->x * val, this->y * val, this->z * val, this->w * val);
}

fvec4& fvec4::operator*=(const flt32 val)
{
	this->x *= val;
	this->y *= val;
	this->z *= val;
	this->w *= val;

	return *this;
}

fvec4 fvec4::operator/(const fvec4& other) const
{

	return fvec4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
}

fvec4& fvec4::operator/=(const fvec4& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	this->w /= other.w;

	return *this;
}

fvec4 fvec4::operator/(flt32 val) const
{
	const flt32 rec = 1.0f / val;

	return fvec4(this->x * rec, this->y * rec, this->z * rec, this->w * rec);
}

fvec4& fvec4::operator/=(flt32 val)
{
	const flt32 rec = 1.0f / val;

	this->x *= rec;
	this->y *= rec;
	this->z *= rec;
	this->w *= rec;

	return *this;
}

fvec4 fvec4::operator+(flt32 val) const
{
	return fvec4(this->x + val, this->y + val, this->z + val, this->w + val);
}

fvec4& fvec4::operator+=(flt32 val)
{
	this->x += val;
	this->y += val;
	this->z += val;
	this->w += val;

	return *this;
}

fvec4 fvec4::operator-(flt32 val) const
{
	return fvec4(this->x - val, this->y - val, this->z - val, this->w - val);
}

fvec4& fvec4::operator-=(flt32 val)
{
	this->x -= val;
	this->y -= val;
	this->z -= val;
	this->w -= val;

	return *this;
}

/*bvec3 fvec4::Equals(const fvec4 &other)
{
	return bvec3(this->x == other.x, this->y == other.y);
}*/

fvec4& fvec4::Normalise()
{
	flt32 xt = this->x * this->x;
	flt32 yt = this->y * this->y;
	flt32 zt = this->z * this->z;
	flt32 wt = this->w * this->w;

	const flt32 mag = 1.0f / sqrt(xt + yt + zt + wt);
	*this *= mag;

	return *this;
}

fvec4 Normalise(const fvec4& v)
{
	fvec4 res = v;

	flt32 xt = v.x * v.x;
	flt32 yt = v.y * v.y;
	flt32 zt = v.z * v.z;
	flt32 wt = v.w * v.w;

	const flt32 mag = 1.0f / sqrt(xt + yt + zt + wt);
	res *= mag;

	return res;
}

flt32 fvec4::Dot(const fvec4& other) const
{
    return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

flt32 Dot(const fvec4& v1, const fvec4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

flt32 fvec4::Distance(const fvec4& other) const
{
	flt32 dx = this->x - other.x;
	flt32 dy = this->y - other.y;
	flt32 dz = this->z - other.z;
	flt32 dw = this->w - other.w;

	return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

flt32 Distance(const fvec4& v1, const fvec4& v2)
{
	flt32 dx = v1.x - v2.x;
	flt32 dy = v1.y - v2.y;
	flt32 dz = v1.z - v2.z;
	flt32 dw = v1.w - v2.w;

	return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

#endif

const fvec4 fvec4::zero = vec4();
const fvec4 fvec4::one 	= vec4(1.0f);
const fvec4 fvec4::neg 	= vec4(-1.0f);

#endif // ENMA_IMPLEMENTATION
