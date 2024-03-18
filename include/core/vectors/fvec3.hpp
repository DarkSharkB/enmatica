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

struct ALIGN(16) fvec3
{
	union 
    {
        struct
        {
            flt32 x, y, z;
        };
		flt32 arr[3];
    };
	
	fvec3(const fvec3 &vec);
	fvec3(const flt32 val = 0.0f);
	fvec3(const flt32 fx, const flt32 fy, const flt32 fz = 0.0f);
	fvec3(const flt32 *arr);
	fvec3(const flt32 x, const vec2 yz);
	fvec3(const vec2 xy, const flt32 z);

	fvec3 operator+(const fvec3 &other);
	fvec3 operator+=(const fvec3 &other);
	fvec3 operator+(const flt32 val);
	fvec3 operator+=(const flt32 val);
	fvec3 operator-();
	fvec3 operator-(const fvec3 &other);
	fvec3 operator-=(const fvec3 &other);
	fvec3 operator-(const flt32 val);
	fvec3 operator-=(const flt32 val);
	fvec3 operator*(const fvec3 &other);
	fvec3 operator*=(const fvec3 &other);
	fvec3 operator*(const flt32 val);
	fvec3 operator*=(const flt32 val);
	fvec3 operator/(const fvec3 &other);
	fvec3 operator/=(const fvec3 &other);
	fvec3 operator/(const flt32 val);
	fvec3 operator/=(const flt32 val);

	fvec3 Normalise();
	static fvec3 Normalise(const fvec3 &v);
	flt32 Dot(const fvec3 &other);
	static flt32 Dot(const fvec3 &v1, const fvec3 &v2);
	fvec3 Cross(const fvec3 &other);
	static fvec3 Cross(const fvec3 &v1, const fvec3 &v2);
	flt32 Distance(const fvec3 &other);
	static flt32 Distance(const fvec3 &v1, const fvec3 &v2);

	#ifdef USE_SIMD_SPEC
	fvec3(const __m128 &vals);
	#endif

	#ifdef DEBUG
	friend std::ostream &operator<<(std::ostream &os, const fvec3 &vec)
	{
		os << "( X: " << vec.arr[0] << "\tY: " << vec.arr[1] << "\tZ: " << vec.arr[2] << " )";

		return os;
	}
	#endif
};

#ifdef ENMA_IMPL
fvec3::fvec3(const fvec3 &vec)
{
	*this = vec;
}

fvec3::fvec3(const flt32 val) : x(val), y(val), z(val) {}

fvec3::fvec3(const flt32 fx, const flt32 fy, const flt32 fz) : x(fx), y(fy), z(fz) {}

fvec3::fvec3(const flt32 *arr)
{
	this->arr[0] = arr[0];
	this->arr[1] = arr[1];
	this->arr[2] = arr[2];
}

fvec3::fvec3(const flt32 x, const vec2 yz)
{
	this->x = x;
	this->y = yz.x;
	this->z = yz.y;
}

fvec3::fvec3(const vec2 xy, const flt32 z)
{
	this->x = xy.x;
	this->y = xy.y;
	this->z = z;
}

fvec3 fvec3::operator-()
{
	return fvec3(-x, -y, -z);
}

#ifdef USE_SIMD_SPEC
fvec3::fvec3(const __m128 &vals)
{
	this->arr[0] = vals[0];
	this->arr[1] = vals[1];
	this->arr[2] = vals[2];
}

#ifdef USE_MEM_ALIGNED
fvec3 fvec3::operator+(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);
		
	return fvec3(_mm_add_ps(v1, v2));
}
	
fvec3 fvec3::operator+=(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	_mm_store_ps(this->arr, _mm_add_ps(v1, v2));

	return *this;
}

fvec3 fvec3::operator+(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	return fvec3(_mm_add_ps(v1, v2));
}

fvec3 fvec3::operator+=(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	_mm_store_ps(this->arr, _mm_add_ps(v1, v2));

	return *this;
}

fvec3 fvec3::operator-(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);
		
	return fvec3(_mm_sub_ps(v1, v2));
}

fvec3 fvec3::operator-=(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	_mm_store_ps(this->arr, _mm_sub_ps(v1, v2));
		
	return *this;
}

fvec3 fvec3::operator-(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	return fvec3(_mm_sub_ps(v1, v2));
}

fvec3 fvec3::operator-=(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	_mm_store_ps(this->arr, _mm_sub_ps(v1, v2));

	return *this;
}

fvec3 fvec3::operator*(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	return fvec3(_mm_mul_ps(v1, v2));
}

fvec3 fvec3::operator*=(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	_mm_store_ps(this->arr, _mm_mul_ps(v1, v2));

	return *this;
}

fvec3 fvec3::operator*(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	return fvec3(_mm_mul_ps(v1, v2));
}

fvec3 fvec3::operator*=(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	_mm_store_ps(this->arr, _mm_mul_ps(v1, v2));

	return *this;
}

fvec3 fvec3::operator/(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	return fvec3(_mm_div_ps(v1, v2));
}

fvec3 fvec3::operator/=(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);

	_mm_store_ps(this->arr, _mm_div_ps(v1, v2));

	return *this;
}

fvec3 fvec3::operator/(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	return fvec3(_mm_div_ps(v1, v2));
}

fvec3 fvec3::operator/=(const flt32 val)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	_mm_store_ps(this->arr, _mm_div_ps(v1, v2));

	return *this;
}

/**
 * @brief Normalises the vector
 *
 * @return Normalised form of the given vector
 */
fvec3 fvec3::Normalise()
{
	__m128 vl = _mm_load_ps(this->arr);
	__m128 x = _mm_dp_ps(vl, vl, 0x77);

	__m128 mag = _mm_sqrt_ps(x);		// The magnitude of the Vector

	vl = _mm_div_ps(vl, mag);

	*this = vl;							// Normalised vector

	return *this;
}

/**
 * @brief Normalises the vector
 *
 * @return Normalised form of the given vector
 */
fvec3 fvec3::Normalise(const fvec3 &v)
{
	__m128 vl = _mm_load_ps(v.arr);
	__m128 x = _mm_dp_ps(vl, vl, 0x77);

	__m128 mag = _mm_sqrt_ps(x);	// The magnitude of the Vector

	vl = _mm_div_ps(vl, mag);	// Normalised vector

	return fvec3(vl);
}

/**
 * @param other The other vector with which the dot product is calculated
 * @return Dot product between the given vector and the other vector
 */
flt32 fvec3::Dot(const fvec3 &other)
{
	const __m128 v1 = _mm_load_ps(this->arr);
	const __m128 v2 = _mm_load_ps(other.arr);
		
	__m128 dot = _mm_dp_ps(v1, v2, 0x77);

	return dot[0];
	//return this->x * other.x + this->y * other.y + this->z * other.z;
}

flt32 fvec3::Dot(const fvec3 &v1, const fvec3 &v2)
{
	const __m128 lv1 = _mm_load_ps(v1.arr);
	const __m128 lv2 = _mm_load_ps(v2.arr);
		
	__m128 dot = _mm_dp_ps(lv1, lv2, 0x77);

	return dot[0];
	//return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/**
 * @brief Calculates the cross product between this vector and the other vector
 * 
 * @param other The other vector with which the cross product is calculated
 * @return Cross product between the given vector and the other vector
 */
fvec3 fvec3::Cross(const fvec3 &other)
{
	__m128 v1 = _mm_load_ps(this->arr);
	__m128 v2 = _mm_load_ps(other.arr);

	const __m128 i1 = _mm_shuffle_ps(v2, v2, 0x09);
	const __m128 i2 = _mm_shuffle_ps(v1, v1, 0x12);

	v1 = _mm_mul_ps(v1, i1);
	v1 = _mm_shuffle_ps(v1, v1, 0x09);
	v2 = _mm_mul_ps(i1, i2);

	return fvec3(_mm_sub_ps(v1, v2));
}

/**
 * @param v1 The first vector
 * @param v2 The second vector
 * @return fvec3 
 */
fvec3 fvec3::Cross(const fvec3 &v1, const fvec3 &v2)
{
	__m128 lv1 = _mm_load_ps(v1.arr);
	__m128 lv2 = _mm_load_ps(v2.arr);

	const __m128 i1 = _mm_shuffle_ps(lv2, lv2, 0x09);
	const __m128 i2 = _mm_shuffle_ps(lv1, lv1, 0x12);

	lv1 = _mm_mul_ps(lv1, i1);
	lv1 = _mm_shuffle_ps(lv1, lv1, 0x09);
	lv2 = _mm_mul_ps(i1, i2);

	return fvec3(_mm_sub_ps(lv1, lv2));
}

/**
 * @param other The other vector to which the distance is calculated
 * @return Returns the distance between the given vector and the other vector
 */
flt32 fvec3::Distance(const fvec3 &other)
{
	__m128 v1 = _mm_load_ps(this->arr);
	__m128 v2 = _mm_load_ps(other.arr);

	v1 = _mm_sub_ps(v1, v2);

	v1 = _mm_dp_ps(v1, v1, 0xFF);

	v1 = _mm_sqrt_ps(v1);

	return v1[0];
}

/**
 * @param v1 The first vector
 * @param v2 The second vector
 * @return Distance between the first and the second vector
 */
flt32 fvec3::Distance(const fvec3 &v1, const fvec3 &v2)
{
	__m128 lv1 = _mm_load_ps(v1.arr);
	__m128 lv2 = _mm_load_ps(v2.arr);

	lv1 = _mm_sub_ps(lv1, lv2);

	lv1 = _mm_dp_ps(lv1, lv1, 0xFF);

	lv1 = _mm_sqrt_ps(lv1);

	return lv1[0];
}

#else
fvec3 fvec3::operator+(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);
		
	return fvec3(_mm_add_ps(v1, v2));
}
	
fvec3 fvec3::operator+=(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);

	*this = _mm_add_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator+(const flt32 val)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	return fvec3(_mm_add_ps(v1, v2));
}

fvec3 fvec3::operator+=(const flt32 val)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	*this = _mm_add_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator-(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);
		
	return fvec3(_mm_sub_ps(v1, v2));
}

fvec3 fvec3::operator-=(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);

	*this = _mm_sub_ps(v1, v2);
		
	return *this;
}

fvec3 fvec3::operator-(const flt32 val)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	return fvec3(_mm_sub_ps(v1, v2));
}

fvec3 fvec3::operator-=(const flt32 val)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	*this = _mm_sub_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator*(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);

	return fvec3(_mm_mul_ps(v1, v2));
}

fvec3 fvec3::operator*=(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);

	*this = _mm_mul_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator*(const flt32 val)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	return fvec3(_mm_mul_ps(v1, v2));
}

fvec3 fvec3::operator*=(const flt32 val)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	*this = _mm_mul_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator/(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);

	return fvec3(_mm_div_ps(v1, v2));
}

fvec3 fvec3::operator/=(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);

	*this = _mm_div_ps(v1, v2);

	return *this;
}

fvec3 fvec3::operator/(const flt32 val)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	return fvec3(_mm_div_ps(v1, v2));
}

fvec3 fvec3::operator/=(const flt32 val)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_load1_ps(&val);

	*this = _mm_div_ps(v1, v2);

	return *this;
}

/**
 * @brief Normalises the vector
 *
 * @return Normalised form of the given vector
 */
fvec3 fvec3::Normalise()
{
	__m128 vl = _mm_loadu_ps(this->arr);
	__m128 x = _mm_dp_ps(vl, vl, 0x77);

	__m128 mag = _mm_sqrt_ps(x);		// The magnitude of the Vector

	*this = _mm_div_ps(vl, mag);							// Normalised vector
	//LOG_D("INORM: ", _mm_div_ps(vl, mag));

	return *this;
}

/**
 * @brief Normalises the vector
 *
 * @return Normalised form of the given vector
 */
fvec3 fvec3::Normalise(const fvec3 &v)
{
	__m128 vl = _mm_loadu_ps(v.arr);
	__m128 x = _mm_dp_ps(vl, vl, 0x77);

	__m128 mag = _mm_sqrt_ps(x);	// The magnitude of the Vector

	vl = _mm_div_ps(vl, mag);	// Normalised vector

	return fvec3(vl);
}

/**
 * @param other The other vector with which the dot product is calculated
 * @return Dot product between the given vector and the other vector
 */
flt32 fvec3::Dot(const fvec3 &other)
{
	const __m128 v1 = _mm_loadu_ps(this->arr);
	const __m128 v2 = _mm_loadu_ps(other.arr);
		
	__m128 dot = _mm_dp_ps(v1, v2, 0x77);

	return dot[0];
	//return this->x * other.x + this->y * other.y + this->z * other.z;
}

flt32 fvec3::Dot(const fvec3 &v1, const fvec3 &v2)
{
	const __m128 lv1 = _mm_loadu_ps(v1.arr);
	const __m128 lv2 = _mm_loadu_ps(v2.arr);
		
	__m128 dot = _mm_dp_ps(lv1, lv2, 0x77);

	return dot[0];
	//return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/**
 * @brief Calculates the cross product between this vector and the other vector
 * 
 * @param other The other vector with which the cross product is calculated
 * @return Cross product between the given vector and the other vector
 */
fvec3 fvec3::Cross(const fvec3 &other)
{
	__m128 v1 = _mm_loadu_ps(this->arr);
	__m128 v2 = _mm_loadu_ps(other.arr);

	const __m128 i1 = _mm_shuffle_ps(v2, v2, 0x09);
	const __m128 i2 = _mm_shuffle_ps(v1, v1, 0x12);

	v1 = _mm_mul_ps(v1, i1);
	v1 = _mm_shuffle_ps(v1, v1, 0x09);
	v2 = _mm_mul_ps(i1, i2);

	return fvec3(_mm_sub_ps(v1, v2));
}


fvec3 fvec3::Cross(const fvec3 &v1, const fvec3 &v2)
{
	__m128 lv1 = _mm_loadu_ps(v1.arr);
	__m128 lv2 = _mm_loadu_ps(v2.arr);

	const __m128 i1 = _mm_shuffle_ps(lv2, lv2, 0x09);
	const __m128 i2 = _mm_shuffle_ps(lv1, lv1, 0x12);

	lv1 = _mm_mul_ps(lv1, i1);
	lv1 = _mm_shuffle_ps(lv1, lv1, 0x09);
	lv2 = _mm_mul_ps(i1, i2);

	return fvec3(_mm_sub_ps(lv1, lv2));
}

/**
 * @brief Calculates the distance between the given vector and the other vector
 * 
 * @param other The other vector to which the distance is calculated
 * @return Distance between the given vector and the other vector
 */
flt32 fvec3::Distance(const fvec3 &other)
{
	__m128 v1 = _mm_loadu_ps(this->arr);
	__m128 v2 = _mm_loadu_ps(other.arr);

	v1 = _mm_sub_ps(v1, v2);

	v1 = _mm_dp_ps(v1, v1, 0xFF);

	v1 = _mm_sqrt_ps(v1);

	return v1[0];
}

/**
 * @brief Calculates the distance between the first and second vector
 * 
 * @param v1 The first vector from which the distance is calculated
 * @param v2 The second vector to which the distance is calculated
 * @return Distance between the first and second vector
 */
flt32 fvec3::Distance(const fvec3 &v1, const fvec3 &v2)
{
	__m128 lv1 = _mm_loadu_ps(v1.arr);
	__m128 lv2 = _mm_loadu_ps(v2.arr);

	lv1 = _mm_sub_ps(lv1, lv2);

	lv1 = _mm_dp_ps(lv1, lv1, 0xFF);

	lv1 = _mm_sqrt_ps(lv1);

	return lv1[0];
}
#endif
#endif	// USE_SIMD_SPEC
#endif	// ENMA_IMPL

/** 
 * Die, Die, Die
 * Die, Die, Die
 * Die, Die, Die
 * Die, Die, Die
 * The Sick, The Dying and The Dead
 */