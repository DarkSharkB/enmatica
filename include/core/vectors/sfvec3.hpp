/** 
 * \brief 3 Component Single Precision Floating-Point Vector
 * 
 * \note This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFVEC3_HPP
#define ENMA_SFVEC3_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"
#include "sfvec2.hpp"
#include "core/simd_helpers.hpp"

ENMA_NS_START
struct ALIGN(16) sfvec3
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

    SFVEC3_SWIZZLE(sfvec3);

    #ifdef USE_SIMD_ALIGNED
    __m128 _vals;
    #endif // USE_SIMD_ALIGNED
  };
  
  /**
  * \brief Single value constructor.
  *
  * \param val Value to initialize x, y and z components.
  *			       Defaults to 0.0f if not provided.
  */
  constexpr explicit sfvec3(flt32 val = 0.0f);
  
  /**
  * \brief Constructor with components.
  * 
  * \param x X component.
  * \param y Y component.
  * \param z Z component. Defaults to 0.0f if not provided.
  */
  constexpr explicit sfvec3(flt32 x, flt32 y, flt32 z = 0.0f);

  /**
  * \brief Constructor with a value and a vector.
  * 
  * \param x  X component.
  * \param yz YZ sfvec2. Sets the y and z components.
  */
  constexpr explicit sfvec3(flt32 x, const sfvec2& yz);

  /**
  * \brief Constructor with a vector and a value.
  * 
  * \param xy XY sfvec2. Sets the x and y components.
  * \param z Z component.
  */
  constexpr explicit sfvec3(const sfvec2& xy, flt32 z);
  
  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of floats of atleast 3 valid flt32.
  */
  constexpr explicit sfvec3(const flt32* arr);

  /**
  * \brief Conversion operator to sfvec2.
  * 
  * Implicitly converts the current sfvec3 to a sfvec2 by discarding the z component.
  * 
  * \return A sfvec2 with x and y components from the current sfvec3.
  */
  explicit operator sfvec2() const;
  
  /**
  * \brief Copy constructor.
  * 
  * \param v Another sfvec3 to copy from.
  */
  //constexpr sfvec3(const sfvec3& v);

  /**
   * \brief Copy Assignment operator.
   * 
   * \param other The other sfvec3
   * \return sfvec3&  Returns the value of other vector 
                      which is copied to left hand side vector.
   */
  //sfvec3& operator=(const sfvec3& other);

  /**
  * \brief Indexing operator.
  * 
  * \param index Index of the component to access (0 for x or r, 1 for y or g, 2 for z or b).
  * \return Value of the component at the specified `index`.
  */
  flt32 operator[](uint32 index) const;

  /**
  * \brief Addition operator.
  * 
  * Performs addition between this vector and the `other` vector.
  *
  * \param other The other sfvec3.
  * \return Resultant sfvec3 after addition.
  */
  sfvec3 operator+(const sfvec3& other) const;
  
  /**
  * \brief Addition assignment operator.
  * 
  * Performs addition between this vector and the `other` vector.
  *
  * \param other The other sfvec3.
  * \return Reference to the modified sfvec3 after addition.
  */
  sfvec3& operator+=(const sfvec3& other);
  
  /**
  * \brief Unary minus operator.
  * 
  * Negates the components of the vector.
  *
  * \return Resultant sfvec3 with components negated.
  */
  sfvec3 operator-() const;
  
  /**
  * \brief Subtraction operator.
  * 
  * Performs subtraction between this vector and the `other` vector.
  *
  * \param other The other sfvec3.
  * \return Resultant sfvec3 after subtraction.
  */
  sfvec3 operator-(const sfvec3& other) const;
  
  /**
  * \brief Subtraction assignment operator.
  * 
  * Performs subtraction between this vector and the `other` vector.
  *
  * \param other The other sfvec3.
  * \return Reference to the modified sfvec3 after subtraction.
  */
  sfvec3& operator-=(const sfvec3& other);
  
  /**
  * \brief Multiplication operator (element-wise).
  * 
  * Performs element-wise multiplication between this vector and the `other` vector.
  *
  * \param other The other sfvec3.
  * \return Resultant sfvec3 after multiplication.
  */
  sfvec3 operator*(const sfvec3& other) const;
  
  /**
  * \brief Multiplication assignment operator (element-wise).
  * 
  * Performs element-wise multiplication between this vector and the `other` vector.
  *
  * \param other The other sfvec3.
  * \return Reference to the modified sfvec3 after multiplication.
  */
  sfvec3& operator*=(const sfvec3& other);
  
  /**
  * \brief Multiplication operator (scalar).
  * 
  * Performs scalar multiplication between this vector and the `other` vector.
  * 
  * \param val A scalar value.
  * \return Resultant sfvec3 after multiplication.
  */
  sfvec3 operator*(flt32 val) const;
  
  /**
  * \brief Multiplication assignment operator (scalar).
  * 
  * Performs scalar multiplication between this vector and the `other` vector.
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec3 after multiplication.
  */
  sfvec3& operator*=(flt32 val);
  
  /**
  * \brief Division operator (element-wise).
  * 
  * Performs element-wise division between this vector and the `other` vector.
  * 
  * \param other The other sfvec3.
  * \return Resultant sfvec3 after division.
  */
  sfvec3 operator/(const sfvec3& other) const;
  
  /**
  * \brief Division assignment operator (element-wise).
  *
  * Performs element-wise division between this vector and the `other` vector.
  * 
  * \param other The other sfvec3.
  * \return Reference to the modified sfvec3 after division.
  */
  sfvec3& operator/=(const sfvec3& other);
  
  /**
  * \brief Division assignment operator (scalar).
  * 
  * Performs division between this vector and the scalar `val`.
  * 
  * \param val A scalar value.
  * \return Resultant sfvec3 after division.
  */
  sfvec3 operator/(flt32 val) const;
  
  /**
  * \brief Division assignment operator (scalar).
  * 
  * Performs division between this vector and the scalar `val`.
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec3 after division.
  */
  sfvec3& operator/=(flt32 val);

  /**
  * \brief Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Resultant sfvec3 after addition.
  */
  sfvec3 operator+(flt32 val) const;
  
  /**
  * \brief Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec3 after addition.
  */
  sfvec3& operator+=(flt32 val);
  
  /**
  * \brief Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Resultant sfvec3 after subtraction.
  */
  sfvec3 operator-(flt32 val) const;
  
  /**
  * \brief Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec3 after subtraction.
  */
  sfvec3& operator-=(flt32 val);

  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
  friend sfvec3 operator*(T val, const sfvec3& vec)
  {
    return vec * val;
  }

  /**
  * \brief Calculates the length of the given vector
  * 
  * \return The length of the vector
  */
  flt32 Length();
  
  /**
  * Normalises the vector.
  *
  * \return Reference to the modified sfvec3 after normalisation.
  */
  sfvec3& Normalise();
  
  /**
  * Calculates the dot product of the given vector and the other vector.
  * 
  * \param other The other sfvec3.
  * \return The dot product of the given sfvec3 and the `other` sfvec3.
  */
  flt32 Dot(const sfvec3& other);
  
  /**
  * Calculates the cross product between given vector and the other vector.
  * 
  * \param other The other sfvec3.
  * \return The cross product between the given sfvec3 and the `other` sfvec3.
  */
  sfvec3& Cross(const sfvec3& other);
  
  /**
  * Calculates the distance between given vector and the other vector.
  * 
  * \param other The other sfvec3.
  * \return The distance between the given sfvec3 and the `other` sfvec3.
  */
  flt32 Distance(const sfvec3& other);

  #ifdef USE_SIMD
  /**
  * Constructor from __m128.
  * 
  * Initializes an sfvec3 using values from a __m128 SIMD data type.
  * 
  * \param vals A SIMD __m128 data containing values to initialize x, y and z components.
  */
  sfvec3(const __m128& vals);

  /**
  * Linear Interpolation
  *
  * Interpolates from the given vector `a`, to the other vector `b` 
  * based on interpolation parameter `t` using SIMD operations.
  *
  * \param b The sfvec3 to interpolate towards.
  * \param t Interpolation parameter (typically in the range [0, 1]).
  * \return The interpolated sfvec3.
  */
  sfvec3 Lerp(const sfvec3& b, flt32 t);
  #endif // USE_SIMD

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfvec3& v);
  #endif // DEBUG

  /**
   * \brief Shorthand to create a zero vector - sfvec3(0.0f, 0.0f, 0.0f)
   * 
   */
  static const sfvec3 zero;

  /**
  * \brief Shorthand to create a unit vector - sfvec3(1.0f, 1.0f, 1.0f)
  * 
  */
  static const sfvec3 one;

  /**
  * \brief Shorthand to create a negative unit vector - sfvec3(-1.0f, -1.0f, -1.0f)
  * 
  */
  static const sfvec3 neg;

  /**
  * \brief Shorthand to create up vector - sfvec3(0.0f, 1.0f, 0.0f)
  * 
  */
  static const sfvec3 up;

  /**
  * \brief Shorthand to create down vector - sfvec3(0.0f, -1.0f, 0.0f)
  * 
  */
  static const sfvec3 down;

  /**
  * \brief Shorthand to create right vector - sfvec3(1.0f, 0.0f, 0.0f)
  * 
  */
  static const sfvec3 right;

  /**
  * \brief Shorthand to create left vector - sfvec3(-1.0f, 0.0f, 0.0f)
  * 
  */
  static const sfvec3 left;

  /**
  * \brief Shorthand to create forward vector - sfvec3(0.0f, 0.0f, 1.0f)
  * 
  */
  static const sfvec3 forward;

  /**
  * \brief Shorthand to create back vector - sfvec3(0.0f, 0.0f, -1.0f)
  * 
  */
  static const sfvec3 back;
};

/**
* \brief Normalises the input vector.
* 
* \details This function takes a three dimensional vector as input and returns
*          a normalised (unit length) version of the vector.
* 
* \param v The input sfvec3.
* \return The normalised form of the input sfvec3 `v`.
*/
inline sfvec3 Normalise(const sfvec3& v);

/**
* \brief Calculates the dot product between two vectors.
* 
* \param v1 The first sfvec3.
* \param v2 The second sfvec3.
* \return The dot product of the first sfvec3 `v1` and the second sfvec3 `v2`.
*/
inline flt32 Dot(const sfvec3& v1, const sfvec3& v2);

/**
* \brief Calculates the cross product between two vectors.
* 
* \param v1 The first sfvec3.
* \param v2 The second sfvec3.
* \return The cross product between the first sfvec3 `v1` and the second sfvec3 `v2`.
*/
inline sfvec3 Cross(const sfvec3& v1, const sfvec3& v2);

/**
* \brief Calculates the distance between two vectors.
* 
* \param v1 The first sfvec3.
* \param v2 The second sfvec3.
* \return The distance between the first sfvec3 `v1` and the second sfvec3 `v2`.
*/
inline flt32 Distance(const sfvec3& v1, const sfvec3& v2);

/**
 * \brief 
 * 
 * \param v 
 * \return flt32 
 */
inline flt32 Length(const sfvec3& v);

#ifdef USE_SIMD
__m128 Set(const sfvec3& v);
sfvec3 Lerp(const sfvec3& a, const sfvec3& b, flt32 t);
#endif
ENMA_NS_END


ENMA_NS_START
//-----------------------------------------------------//
//               Implementation Starts                 //
//-----------------------------------------------------//

inline constexpr sfvec3::sfvec3(flt32 val)
: x(val), y(val), z(val) {}

inline constexpr sfvec3::sfvec3(flt32 x, flt32 y, flt32 z)
: x(x), y(y), z(z) {}

inline constexpr sfvec3::sfvec3(flt32 x, const sfvec2& yz)
: x(x), y(yz.x), z(yz.y) {}

inline constexpr sfvec3::sfvec3(const sfvec2& xy, flt32 z)
: x(xy.x), y(xy.y), z(z) {}

inline constexpr sfvec3::sfvec3(const flt32* arr)
: x(arr[0]), y(arr[1]), z(arr[2]) {}

inline sfvec3::operator sfvec2() const
{
  return sfvec2(this->x, this->y);
}

/*
inline constexpr sfvec3::sfvec3(const sfvec3& v)
: x(v.x), y(v.y), z(v.z) {}

inline sfvec3& sfvec3::operator=(const sfvec3& other)
{
  if(this != &other)
  {
    this->xyz = other.xyz;
  }
  return *this;
}
*/

inline flt32 sfvec3::operator[](uint32 index) const
{
  return _arr[index];
}

inline sfvec3 sfvec3::operator-() const
{
  return sfvec3(-x, -y, -z);
}

#ifdef USE_SIMD
inline __m128 Set(const sfvec3& v)
{
  return _mm_set_ps(0.0f, v.z, v.y, v.x);
}

#ifdef USE_SIMD_ALIGNED
inline sfvec3::sfvec3(const __m128& vals)
{
  this->_vals = vals;
}

inline sfvec3 sfvec3::operator+(const sfvec3& other) const
{
  return sfvec3(_mm_add_ps(this->_vals, other._vals));
}
  
inline sfvec3& sfvec3::operator+=(const sfvec3& other)
{
  this->_vals = _mm_add_ps(this->_vals, other._vals);

  return *this;
}

inline sfvec3 sfvec3::operator-(const sfvec3& other) const
{
  return sfvec3(_mm_sub_ps(this->_vals, other._vals));
}

inline sfvec3& sfvec3::operator-=(const sfvec3& other)
{
  this->_vals = _mm_sub_ps(this->_vals, other._vals);
    
  return *this;
}

inline sfvec3 sfvec3::operator*(const sfvec3& other) const
{
  return sfvec3(_mm_mul_ps(this->_vals, other._vals));
}

inline sfvec3& sfvec3::operator*=(const sfvec3& other)
{
  this->_vals = _mm_mul_ps(this->_vals, other._vals);

  return *this;
}

inline sfvec3 sfvec3::operator*(flt32 val) const
{
  const __m128 v2 = Set1(val);

  return sfvec3(_mm_mul_ps(this->_vals, v2));
}

inline sfvec3& sfvec3::operator*=(flt32 val)
{
  const __m128 v2 = Set1(val);

  this->_vals = _mm_mul_ps(this->_vals, v2);

  return *this;
}

inline sfvec3 sfvec3::operator/(const sfvec3& other) const
{
  return sfvec3(_mm_div_ps(this->_vals, other._vals));
}

inline sfvec3& sfvec3::operator/=(const sfvec3& other)
{
  this->_vals =_mm_div_ps(this->_vals, other._vals);

  return *this;
}

inline sfvec3 sfvec3::operator/(flt32 val) const
{
  const __m128 v2 = Set1(val);

  return sfvec3(_mm_div_ps(this->_vals, v2));
}

inline sfvec3& sfvec3::operator/=(flt32 val)
{
  const __m128 v2 = Set1(val);

  this->_vals = _mm_div_ps(this->_vals, v2);

  return *this;
}

inline sfvec3 sfvec3::operator+(flt32 val) const
{
  const __m128 v2 = Set1(val);

  return sfvec3(_mm_add_ps(this->_vals, v2));
}

inline sfvec3& sfvec3::operator+=(flt32 val)
{
  const __m128 v2 = Set1(val);

  this->_vals = _mm_add_ps(this->_vals, v2);

  return *this;
}

inline sfvec3 sfvec3::operator-(flt32 val) const
{
  const __m128 v2 = Set1(val);

  return sfvec3(_mm_sub_ps(this->_vals, v2));
}

inline sfvec3& sfvec3::operator-=(flt32 val)
{
  const __m128 v2 = Set1(val);

  this->_vals = _mm_sub_ps(this->_vals, v2);

  return *this;
}

inline sfvec3& sfvec3::Normalise()
{
  __m128 vl = this->_vals;
  __m128 x = _mm_dp_ps(vl, vl, 0x77);

  __m128 mag = _mm_sqrt_ps(x);		  // The magnitude of the Vector

  *this = _mm_div_ps(vl, mag);	// Normalised vector

  return *this;
}

inline sfvec3 Normalise(const sfvec3& v)
{
  __m128 vl = v._vals;
  __m128 x = _mm_dp_ps(vl, vl, 0x77);

  __m128 mag = _mm_sqrt_ps(x);	// The magnitude of the Vector

  vl = _mm_div_ps(vl, mag);	// Normalised vector

  return sfvec3(vl);
}

inline flt32 sfvec3::Dot(const sfvec3& other)
{
  __m128 dot = _mm_dp_ps(this->_vals, other._vals, 0x77);

  return dot[0];
}

inline flt32 Dot(const sfvec3& v1, const sfvec3& v2)
{
  __m128 dot = _mm_dp_ps(v1._vals, v2._vals, 0x77);

  return dot[0];
}

inline sfvec3& sfvec3::Cross(const sfvec3& other)
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

inline sfvec3 Cross(const sfvec3& v1, const sfvec3& v2)
{
  __m128 lv1 = v1._vals;
  __m128 lv2 = v2._vals;

  const __m128 i1 = _mm_shuffle_ps(lv2, lv2, 0x09);
  const __m128 i2 = _mm_shuffle_ps(lv1, lv1, 0x12);

  lv1 = _mm_mul_ps(lv1, i1);
  lv1 = _mm_shuffle_ps(lv1, lv1, 0x09);
  lv2 = _mm_mul_ps(i1, i2);

  return sfvec3(_mm_sub_ps(lv1, lv2));
}

inline flt32 sfvec3::Distance(const sfvec3& other)
{
  __m128 v1 = this->_vals;
  __m128 v2 = other._vals;

  v1 = _mm_sub_ps(v1, v2);

  v1 = _mm_dp_ps(v1, v1, 0xFF);

  v1 = _mm_sqrt_ps(v1);

  return v1[0];
}

inline flt32 Distance(const sfvec3& v1, const sfvec3& v2)
{
  __m128 lv1 = _mm_sub_ps(v1._vals, v2._vals);

  lv1 = _mm_dp_ps(lv1, lv1, 0x77);

  lv1 = _mm_sqrt_ps(lv1);

  return lv1[0];
}

inline flt32 sfvec3::Length()
{
  __m128 v = this->_vals;

  __m128 vv = _mm_mul_ps(v, v);

  v = _mm_dp_ps(vv, vv, 0x77);

  v = _mm_sqrt_ps(v);

  return v[0];
}

inline flt32 Length(const sfvec3& v)
{
  __m128 vl = v._vals;

  __m128 vlvl = _mm_mul_ps(vl, vl);

  vl = _mm_dp_ps(vlvl, vlvl, 0x77);

  vl = _mm_sqrt_ps(vl);

  return vl[0];
}

inline sfvec3 sfvec3::Lerp(const sfvec3& b, flt32 t)
{
  __m128 lv1 = this->_vals;
  __m128 lv2 = b._vals;

  __m128 lt = Set1(t);

  __m128 bma = _mm_sub_ps(lv2, lv1);

  return sfvec3(_mm_fmadd_ps(lt, bma, lv1));
}

inline sfvec3 Lerp(const sfvec3& a, const sfvec3& b, flt32 t)
{
  __m128 lv1 = a._vals;
  __m128 lv2 = b._vals;

  __m128 lt = Set1(t);

  __m128 bma = _mm_sub_ps(lv2, lv1);

  return sfvec3(_mm_fmadd_ps(lt, bma, lv1));
}

#else // !USE_SIMD_ALIGNED
inline sfvec3::sfvec3(const __m128& vals)
{
  this->_arr[0] = vals[0];
  this->_arr[1] = vals[1];
  this->_arr[2] = vals[2];
}

inline sfvec3 sfvec3::operator+(const sfvec3& other) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);
    
  return sfvec3(_mm_add_ps(v1, v2));
}

inline sfvec3& sfvec3::operator+=(const sfvec3& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  *this = _mm_add_ps(v1, v2);

  return *this;
}

inline sfvec3 sfvec3::operator-(const sfvec3& other) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);
    
  return sfvec3(_mm_sub_ps(v1, v2));
}

inline sfvec3& sfvec3::operator-=(const sfvec3& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  *this = _mm_sub_ps(v1, v2);
    
  return *this;
}

inline sfvec3 sfvec3::operator*(const sfvec3& other) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  return sfvec3(_mm_mul_ps(v1, v2));
}

inline sfvec3& sfvec3::operator*=(const sfvec3& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  *this = _mm_mul_ps(v1, v2);

  return *this;
}

inline sfvec3 sfvec3::operator*(flt32 val) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  return sfvec3(_mm_mul_ps(v1, v2));
}

inline sfvec3& sfvec3::operator*=(flt32 val)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  *this = _mm_mul_ps(v1, v2);

  return *this;
}

inline sfvec3 sfvec3::operator/(const sfvec3& other) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  return sfvec3(_mm_div_ps(v1, v2));
}

inline sfvec3& sfvec3::operator/=(const sfvec3& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  *this = _mm_div_ps(v1, v2);

  return *this;
}

inline sfvec3 sfvec3::operator/(flt32 val) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  return sfvec3(_mm_div_ps(v1, v2));
}

inline sfvec3& sfvec3::operator/=(flt32 val)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  *this = _mm_div_ps(v1, v2);

  return *this;
}

inline sfvec3 sfvec3::operator+(flt32 val) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  return sfvec3(_mm_add_ps(v1, v2));
}

inline sfvec3& sfvec3::operator+=(flt32 val)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  *this = _mm_add_ps(v1, v2);

  return *this;
}

inline sfvec3 sfvec3::operator-(flt32 val) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  return sfvec3(_mm_sub_ps(v1, v2));
}

inline sfvec3& sfvec3::operator-=(flt32 val)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  *this = _mm_sub_ps(v1, v2);

  return *this;
}

inline sfvec3& sfvec3::Normalise()
{
  const __m128 vl = Set(*this);
  const __m128 x = _mm_dp_ps(vl, vl, 0x7F);

  const __m128 mag = _mm_rsqrt_ps(x);

  *this = _mm_mul_ps(vl, mag);

  return *this;
}

inline sfvec3 Normalise(const sfvec3& v)
{
  const __m128 half  = _mm_set1_ps(0.5f);
  const __m128 three = _mm_set1_ps(3.0f);

  __m128 vl = Set(v);
  __m128 dot = _mm_dp_ps(vl, vl, 0x7F);

  __m128 inv = _mm_rsqrt_ps(dot);

  // return sfvec3(_mm_mul_ps(vl, inv));
  // Newton–Raphson (NR) refinement step: inv * 0.5 * (3 - dot * inv²)
  
  __m128 inv2 = _mm_mul_ps(inv, inv);
  __m128 t = _mm_fnmadd_ps(dot, inv2, three);

  __m128 nr = _mm_mul_ps(inv, _mm_mul_ps(half, t));

  return sfvec3(nr);
}

inline flt32 sfvec3::Dot(const sfvec3& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);
    
  const __m128 dot = _mm_dp_ps(v1, v2, 0x77);

  return dot[0];
}

inline flt32 Dot(const sfvec3& v1, const sfvec3& v2)
{
  const __m128 lv1 = Set(v1);
  const __m128 lv2 = Set(v2);
    
  const __m128 dot = _mm_dp_ps(lv1, lv2, 0x77);

  return dot[0];
}

inline sfvec3& sfvec3::Cross(const sfvec3& other)
{
  __m128 v1 = Set(*this);
  __m128 v2 = Set(other);

  const __m128 i1 = _mm_shuffle_ps(v2, v2, 0x09);
  const __m128 i2 = _mm_shuffle_ps(v1, v1, 0x12);

  v1 = _mm_mul_ps(v1, i1);
  v1 = _mm_shuffle_ps(v1, v1, 0x09);

  v2 = _mm_mul_ps(i1, i2);

  *this = _mm_sub_ps(v1, v2);

  return *this;
}

inline sfvec3 Cross(const sfvec3& v1, const sfvec3& v2)
{
  __m128 lv1 = Set(v1);
  __m128 lv2 = Set(v2);

  const __m128 i1 = _mm_shuffle_ps(lv2, lv2, 0x09);
  const __m128 i2 = _mm_shuffle_ps(lv1, lv1, 0x12);

  lv1 = _mm_mul_ps(lv1, i1);
  lv1 = _mm_shuffle_ps(lv1, lv1, 0x09);
  lv2 = _mm_mul_ps(i1, i2);

  return sfvec3(_mm_sub_ps(lv1, lv2));
}

inline flt32 sfvec3::Distance(const sfvec3& other)
{
  __m128 v1 = Set(*this);
  __m128 v2 = Set(other);

  v1 = _mm_sub_ps(v1, v2);

  v1 = _mm_dp_ps(v1, v1, 0xFF);

  v1 = _mm_sqrt_ps(v1);

  return v1[0];
}

inline flt32 Distance(const sfvec3& v1, const sfvec3& v2)
{
  __m128 lv1 = Set(v1);
  __m128 lv2 = Set(v2);

  lv1 = _mm_sub_ps(lv1, lv2);

  lv1 = _mm_dp_ps(lv1, lv1, 0xFF);

  lv1 = _mm_sqrt_ps(lv1);

  return lv1[0];
}

inline sfvec3 sfvec3::Lerp(const sfvec3& b, flt32 t)
{
  __m128 lv1 = Set(*this);
  __m128 lv2 = Set(b);

  __m128 lt = Set1(t);

  __m128 bma = _mm_sub_ps(lv2, lv1);

  return sfvec3(_mm_fmadd_ps(lt, bma, lv1));
}

inline sfvec3 Lerp(const sfvec3& a, const sfvec3& b, flt32 t)
{
  __m128 lv1 = Set(a);
  __m128 lv2 = Set(b);

  __m128 lt = Set1(t);
  
  __m128 bma = _mm_sub_ps(lv2, lv1);

  return sfvec3(_mm_fmadd_ps(lt, bma, lv1));
}
#endif // USE_SIMD_ALIGNED

#else // !USE_SIMD
inline sfvec3 sfvec3::operator+(const sfvec3& other) const
{
  return sfvec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

inline sfvec3& sfvec3::operator+=(const sfvec3& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;

  return *this;
}

inline sfvec3 sfvec3::operator-(const sfvec3& other) const
{
  return sfvec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

inline sfvec3& sfvec3::operator-=(const sfvec3& other)
{
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;

  return *this;
}

inline sfvec3 sfvec3::operator*(const sfvec3& other) const
{
  return sfvec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

inline sfvec3& sfvec3::operator*=(const sfvec3& other)
{
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;

  return *this;
}

inline sfvec3 sfvec3::operator*(flt32 val) const
{
  return sfvec3(this->x * val, this->y * val, this->z * val);
}

inline sfvec3& sfvec3::operator*=(flt32 val)
{
  this->x *= val;
  this->y *= val;
  this->z *= val;

  return *this;
}

inline sfvec3 sfvec3::operator/(const sfvec3& other) const
{

  return sfvec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

inline sfvec3& sfvec3::operator/=(const sfvec3& other)
{
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;

  return *this;
}

inline sfvec3 sfvec3::operator/(flt32 val) const
{
  const flt32 rec = 1.0f / val;

  return sfvec3(this->x * rec, this->y * rec, this->z * rec);
}

inline sfvec3& sfvec3::operator/=(flt32 val)
{
  const flt32 rec = 1.0f / val;

  this->x *= rec;
  this->y *= rec;
  this->z *= rec;

  return *this;
}

inline sfvec3 sfvec3::operator+(flt32 val) const
{
  return sfvec3(this->x + val, this->y + val, this->z + val);
}

inline sfvec3& sfvec3::operator+=(flt32 val)
{
  this->x += val;
  this->y += val;
  this->z += val;

  return *this;
}

inline sfvec3 sfvec3::operator-(flt32 val) const
{

  return sfvec3(this->x - val, this->y - val, this->z - val);
}

inline sfvec3& sfvec3::operator-=(flt32 val)
{
  this->x -= val;
  this->y -= val;
  this->z -= val;

  return *this;
}

/*bvec3 sfvec3::Equals(const sfvec3 &other)
{
  return bvec3(this->x == other.x, this->y == other.y);
}*/

inline sfvec3& sfvec3::Normalise()
{
  flt32 xt = this->x * this->x;
  flt32 yt = this->y * this->y;
  flt32 zt = this->z * this->z;

  const flt32 mag = 1.0f / sqrt(xt + yt + zt);
  *this *= mag;

  return *this;
}

inline sfvec3 Normalise(const sfvec3& v)
{
  sfvec3 res = v;
  flt32 xt = v.x * v.x;
  flt32 yt = v.y * v.y;
  flt32 zt = v.z * v.z;

  const flt32 mag = 1.0f / sqrt(xt + yt + zt);
  res *= mag;

  return res;
}

inline flt32 sfvec3::Dot(const sfvec3& other)
{
  return this->x * other.x + this->y * other.y + this->z * other.z;
}

inline flt32 Dot(const sfvec3& v1, const sfvec3& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline sfvec3& sfvec3::Cross(const sfvec3& other)
{
  this->x = this->y * other.z - this->z * other.y;
  this->y = this->z * other.x - this->x * other.z;
  this->z = this->x * other.y - this->y * other.x;

  return *this;
}

inline sfvec3 Cross(const sfvec3& v1, const sfvec3& v2)
{
  return sfvec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

inline flt32 sfvec3::Distance(const sfvec3& other)
{
  flt32 dx = this->x - other.x;
  flt32 dy = this->y - other.y;
  flt32 dz = this->z - other.z;

  return sqrt(dx * dx + dy * dy + dz * dz);
}

inline flt32 Distance(const sfvec3& v1, const sfvec3& v2)
{
  flt32 dx = v1.x - v2.x;
  flt32 dy = v1.y - v2.y;
  flt32 dz = v1.z - v2.z;

  return sqrt(dx * dx + dy * dy + dz * dz);
}
#endif // USE_SIMD

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfvec3& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << " )";
  return os;
}
#endif // DEBUG

inline constexpr sfvec3 sfvec3::zero 		= sfvec3(0.0f, 0.0f, 0.0f);
inline constexpr sfvec3 sfvec3::one 	  = sfvec3(1.0f, 1.0f, 1.0f);
inline constexpr sfvec3 sfvec3::neg 	  = sfvec3(-1.0f, -1.0f, -1.0f);

inline constexpr sfvec3 sfvec3::up 		  = sfvec3(0.0f, 1.0f, 0.0f);
inline constexpr sfvec3 sfvec3::down 		= sfvec3(0.0f, -1.0f, 0.0f);
inline constexpr sfvec3 sfvec3::right   = sfvec3(1.0f, 0.0f, 0.0f);
inline constexpr sfvec3 sfvec3::left 		= sfvec3(-1.0f, 0.0f, 0.0f);
inline constexpr sfvec3 sfvec3::forward	= sfvec3(0.0f, 0.0f, 1.0f);
inline constexpr sfvec3 sfvec3::back 		= sfvec3(0.0f, 0.0f, -1.0f);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFVEC3_HPP

//////////////////////////////////////////////////////
//////////////////// Die, Die, Die ////////////////////
//////////////////// Die, Die, Die ////////////////////
//////////////////// Die, Die, Die ////////////////////
//////////////////// Die, Die, Die ////////////////////
/////////// The Sick, The Dying and The Dead //////////
//////////////////////// MEGADETH /////////////////////