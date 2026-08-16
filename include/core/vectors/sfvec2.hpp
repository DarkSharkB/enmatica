/**
 * \brief 2 Component Single Precision Floating-Point Vector
 * 
 * \note This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFVEC2_HPP
#define ENMA_SFVEC2_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"
#include "core/simd_helpers.hpp"

#define DOT_XY_STO_XY 0x33
#define DOT_XY_STO_MEM0 0x31

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(8) sfvec2
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
    struct
    {
      flt32 u, v;
    };

    SFVEC2_SWIZZLE(sfvec2);
  };

  /**
  * Single value constructor.
  *
  * \param val Value to initialise the x and y components. 
  *			       Defaults to 0.0f when value is not provided.
  */
  constexpr explicit sfvec2(flt32 val = 0.0f);

  /**
  * Constructor with components.
  * 
  * \param x X component.
  * \param y Y component.
  */
  constexpr explicit sfvec2(flt32 x, flt32 y);

  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of floats of atleast 2 valid flt32.
  */
  constexpr explicit sfvec2(const flt32* arr);
  
  /**
  * Copy constructor.
  * 
  * \param v Another sfvec2 to copy from.
  */
  //constexpr sfvec2(const sfvec2& v);

  /**
   * \brief Copy Assignment operator.
   * 
   * \param other The other sfvec2
   * \return sfvec2&  Returns the value of other vector 
                      which is copied to left hand side vector.
   */
  //sfvec2& operator=(const sfvec2& other);

  /**
  * Indexing operator.
  * 
  * \param index Index of the component to access (0 for x or r, 1 for y or g).
  * \return Value of the component at the specified `index`.
  */
  flt32 operator[](uint32 index) const;

  /**
  * Addition operator.
  * 
  * Performs addition between this vector and the `other` vector.
  *
  * \param other The other sfvec2.
  * \return Resultant sfvec2 after addition.
  */
  sfvec2 operator+(const sfvec2& other) const;

  /**
  * Addition assignment operator.
  * 
  * Performs addition between this vector and the `other` vector.
  *
  * \param other The other sfvec2.
  * \return Reference to the modified sfvec2 after addition.
  */
  sfvec2& operator+=(const sfvec2& other);

  /**
  * Unary minus operator.
  * 
  * Negates the components of the vector.
  *
  * \return Resultant sfvec2 with components negated.
  */
  sfvec2 operator-() const;

  /**
  * Subtraction operator.
  * 
  * Performs subtraction between this vector and the `other` vector.
  *
  * \param other The other sfvec2.
  * \return Resultant sfvec2 after subtraction.
  */
  sfvec2 operator-(const sfvec2& other) const;

  /**
  * Subtraction assignment operator.
  * 
  * Performs subtraction between this vector and the `other` vector.
  *
  * \param other The other sfvec2.
  * \return Reference to the modified sfvec2 after subtraction.
  */
  sfvec2& operator-=(const sfvec2& other);

  /**
  * Multiplication operator (element-wise).
  * 
  * Performs element-wise multiplication between this vector and the `other` vector.
  *
  * \param other The other sfvec2.
  * \return Resultant sfvec2 after multiplication.
  */
  sfvec2 operator*(const sfvec2& other) const;

  /**
  * Multiplication assignment operator (element-wise).
  * 
  * Performs element-wise multiplication between this vector and the `other` vector.
  *
  * \param other The other sfvec2.
  * \return Reference to the modified sfvec2 after multiplication.
  */
  sfvec2& operator*=(const sfvec2& other);

  /**
  * Multiplication operator (scalar).
  * 
  * Performs scalar multiplication between this vector and the `other` vector.
  * 
  * \param val A scalar value.
  * \return Resultant sfvec2 after multiplication.
  */
  sfvec2 operator*(flt32 val) const;

  /**
  * Multiplication assignment operator (scalar).
  * 
  * Performs scalar multiplication between this vector and the `other` vector.
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec2 after multiplication.
  */
  sfvec2& operator*=(flt32 val);

  /**
  * Division operator (element-wise).
  * 
  * Performs element-wise division between this vector and the `other` vector.
  * 
  * \param other The other sfvec2.
  * \return Resultant sfvec2 after division.
  */
  sfvec2 operator/(const sfvec2& other) const;

  /**
  * Division assignment operator (element-wise).
  *
  * Performs element-wise division between this vector and the `other` vector.
  * 
  * \param other The other sfvec2.
  * \return Reference to the modified sfvec2 after division.
  */
  sfvec2& operator/=(const sfvec2& other);

  /**
  * Division assignment operator (scalar).
  * 
  * Performs division between this vector and the scalar `val`.
  * 
  * \param val A scalar value.
  * \return Resultant sfvec2 after division.
  */
  sfvec2 operator/(flt32 val) const;

  /**
  * Division assignment operator (scalar).
  * 
  * Performs division between this vector and the scalar `val`.
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec2 after division.
  */
  sfvec2& operator/=(flt32 val);

  //			Extension Functions for Ease of Use 		//
  
  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Resultant sfvec2 after addition.
  */
  sfvec2 operator+(flt32 val) const;

  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec2 after addition.
  */
  sfvec2& operator+=(flt32 val);

  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Resultant sfvec2 after subtraction.
  */
  sfvec2 operator-(flt32 val) const;

  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec2 after subtraction.
  */
  sfvec2& operator-=(flt32 val);

  /**
  * Normalises the vector.
  *
  * \return Reference to the modified sfvec2 after normalisation.
  */
  sfvec2& Normalise();
  /**
  * Calculates the dot product of the given vector and the other vector.
  * 
  * \param other The other sfvec2.
  * \return The dot product of the given sfvec2 and the `other` sfvec2.
  */
    flt32 Dot(const sfvec2& other);
  /**
  * Calculates the cross product between given vector and the other vector.
  * 
  * \param other The other sfvec2.
  * \return The z-component of the cross product between the given sfvec2 and the `other` sfvec2.
  */
  flt32 Cross(const sfvec2& other);

  /**
  * Calculates the distance between given vector and the other vector.
  * 
  * \param other The other sfvec2.
  * \return The distance between the given sfvec2 and the `other` sfvec2.
  */
  flt32 Distance(const sfvec2& other);

  #ifdef USE_SIMD
  /**
  * Constructor from __m128.
  * 
  * Initializes an sfvec2 using values from a __m128 SIMD data type.
  * 
  * \param vals __m128 SIMD data type containing values to initialize x and y components.
  */
  sfvec2(const __m128& vals);

  /**
  * Linear Interpolation
  *
  * Interpolates from the given vector `a` to the other vector `b` 
  * based on interpolation parameter `t` using SIMD operations.
  *
  * \param b The sfvec2 to interpolate towards.
  * \param t Interpolation parameter (typically in the range [0, 1]).
  * \return The interpolated sfvec2.
  */
  sfvec2 Lerp(const sfvec2& b, flt32 t);
  #endif
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfvec2& v);
  #endif // DEBUG

  /**
  * Shorthand to create a zero vector - sfvec2(0.0f, 0.0f)
  * 
  */
  static const sfvec2 zero;
  /**
  * Shorthand to create a unit vector - sfvec2(1.0f, 1.0f)
  * 
  */
  static const sfvec2 one;
  /**
  * Shorthand to create a negative unit vector - sfvec2(-1.0f, -1.0f)
  * 
  */
  static const sfvec2 neg;

  /**
  * Shorthand to create up vector - sfvec2(0.0f, 1.0f)
  * 
  */
  static const sfvec2 up;
  /**
  * Shorthand to create down vector - sfvec2(0.0f, -1.0f)
  * 
  */
  static const sfvec2 down;
  /**
  * Shorthand to create right vector - sfvec2(1.0f, 0.0f)
  * 
  */
  static const sfvec2 right;
  /**
  * Shorthand to create left vector - sfvec2(-1.0f, 0.0f)
  * 
  */
  static const sfvec2 left;
};

/**
* Normalises the input vector.
*
* \param v The input sfvec2.
* \return The normalized form of the input sfvec2 `v`.
*/
inline sfvec2 Normalise(const sfvec2& v);

/**
* Calculates the dot product between two vectors.
* 
* \param v1 The first sfvec2.
* \param v2 The second sfvec2.
* \return The dot product of the first sfvec2 `v1` and the second sfvec2 `v2`.
*/
inline flt32 Dot(const sfvec2& v1, const sfvec2& v2);

/**
* Calculates the cross product between two vectors.
* 
* \param v1 The first sfvec2.
* \param v2 The second sfvec2.
* \return The z-component of the cross product between the first sfvec2 `v1` and the second sfvec2 `v2`.
*/
inline flt32 Cross(const sfvec2& v1, const sfvec2& v2);

/**
* Calculates the distance between two vectors.
* 
* \param v1 The first sfvec2.
* \param v2 The second sfvec2.
* \return The distance between the first sfvec2 `v1` and the second sfvec2 `v2`.
*/
inline flt32 Distance(const sfvec2& v1, const sfvec2& v2);

#ifdef USE_SIMD
inline __m128 Set(const sfvec2& v)
{
  return _mm_set_ps(0.0f, 0.0f, v.y, v.x);
}

/**
* Linear Interpolation
*
* Interpolates from the given vector `a` to the other vector `b` based on interpolation parameter `t`.
*
* \param a The sfvec2 to interpolate from.
* \param b The sfvec2 to interpolate towards.
* \param t Interpolation parameter (typically in the range [0, 1]).
* \return The interpolated sfvec2.
*/
inline sfvec2 Lerp(const sfvec2& a, const sfvec2& b, flt32 t);
#endif // USE_SIMD

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfvec2::sfvec2(flt32 val)
: x(val), y(val) {}

inline constexpr sfvec2::sfvec2(flt32 x, flt32 y)
: x(x), y(y) {}

inline constexpr sfvec2::sfvec2(const flt32* arr)
: x(arr[0]), y(arr[1]) {}

inline flt32 sfvec2::operator[](uint32 index) const
{
  return _arr[index];
}

/*
inline constexpr sfvec2::sfvec2(const sfvec2& v)
: x(v.x), y(v.y) {}

inline sfvec2& sfvec2::operator=(const sfvec2& other)
{
  if(this != &other)
  {
    this->xy = other.xy;
  }
  return *this;
}
*/

#ifdef USE_SIMD
inline sfvec2::sfvec2(const __m128& vals)
{
  this->x = vals[0];
  this->y = vals[1];
}
    
inline sfvec2 sfvec2::operator+(const sfvec2& other) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  return sfvec2(_mm_add_ps(v1, v2));
}

inline sfvec2& sfvec2::operator+=(const sfvec2& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  *this = _mm_add_ps(v1, v2);

  return *this;
}

inline sfvec2 sfvec2::operator-() const
{
  return sfvec2(-x, -y);
}

inline sfvec2 sfvec2::operator-(const sfvec2& other) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  return sfvec2(_mm_sub_ps(v1, v2));
}

inline sfvec2& sfvec2::operator-=(const sfvec2& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  *this = _mm_sub_ps(v1, v2);

  return *this;
}

inline sfvec2 sfvec2::operator*(const sfvec2& other) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  return sfvec2(_mm_mul_ps(v1, v2));
}

inline sfvec2& sfvec2::operator*=(const sfvec2& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  *this = _mm_mul_ps(v1, v2);

  return *this;
}

inline sfvec2 sfvec2::operator*(flt32 val) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  return sfvec2(_mm_mul_ps(v1, v2));
}

inline sfvec2& sfvec2::operator*=(flt32 val)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  *this = _mm_mul_ps(v1, v2);

  return *this;
}

inline sfvec2 sfvec2::operator/(const sfvec2& other) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  return sfvec2(_mm_div_ps(v1, v2));
}

inline sfvec2& sfvec2::operator/=(const sfvec2& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);

  *this = _mm_div_ps(v1, v2);

  return *this;
}

inline sfvec2 sfvec2::operator/(flt32 val) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  return sfvec2(_mm_div_ps(v1, v2));
}

inline sfvec2& sfvec2::operator/=(flt32 val)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  *this = _mm_div_ps(v1, v2);

  return *this;
}

inline sfvec2 sfvec2::operator+(flt32 val) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  return sfvec2(_mm_add_ps(v1, v2));
}

inline sfvec2& sfvec2::operator+=(flt32 val)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  *this = _mm_add_ps(v1, v2);

  return *this;
}

inline sfvec2 sfvec2::operator-(flt32 val) const
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  return sfvec2(_mm_sub_ps(v1, v2));
}

inline sfvec2& sfvec2::operator-=(flt32 val)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set1(val);

  *this = _mm_sub_ps(v1, v2);

  return *this;
}

inline sfvec2& sfvec2::Normalise()
{
  const __m128 vl = Set(*this);
  const __m128 x = _mm_dp_ps(vl, vl, DOT_XY_STO_XY);

  const __m128 mag = _mm_sqrt_ps(x);		// The magnitude of the Vector

  *this = _mm_div_ps(vl, mag);			// Normalised vector

  return *this;
}

inline sfvec2 Normalise(const sfvec2& v)
{
  __m128 vl = Set(v);
  const __m128 x = _mm_dp_ps(vl, vl, DOT_XY_STO_XY);

  const __m128 mag = _mm_sqrt_ps(x);		// The magnitude of the Vector

  vl = _mm_div_ps(vl, mag);				// Normalised vector

  return sfvec2(vl);
}

inline flt32 sfvec2::Dot(const sfvec2& other)
{
  const __m128 v1 = Set(*this);
  const __m128 v2 = Set(other);
    
  const __m128 dot = _mm_dp_ps(v1, v2, DOT_XY_STO_MEM0);

  return dot[0];
}

inline flt32 Dot(const sfvec2& v1, const sfvec2& v2)
{
  const __m128 lv1 = Set(v1);
  const __m128 lv2 = Set(v2);
    
  const __m128 dot = _mm_dp_ps(lv1, lv2, DOT_XY_STO_MEM0);

  return dot[0];
}

inline flt32 sfvec2::Distance(const sfvec2& other)
{
  __m128 v1 = Set(*this);
  __m128 v2 = Set(other);

  v1 = _mm_sub_ps(v1, v2);

  v1 = _mm_dp_ps(v1, v1, 0xFF);

  v1 = _mm_sqrt_ps(v1);

  return v1[0];
}

inline flt32 Distance(const sfvec2& v1, const sfvec2& v2)
{
  __m128 lv1 = Set(v1);
  __m128 lv2 = Set(v2);

  lv1 = _mm_sub_ps(lv1, lv2);

  lv1 = _mm_dp_ps(lv1, lv1, 0xFF);

  lv1 = _mm_sqrt_ps(lv1);

  return lv1[0];
}

inline sfvec2 sfvec2::Lerp(const sfvec2& b, flt32 t)
{
  __m128 lv1 = Set(*this);
  __m128 lv2 = Set(b);

  __m128 lt = Set1(t);

  __m128 bma = _mm_sub_ps(lv2, lv1);

  return sfvec2(_mm_fmadd_ps(lt, bma, lv1));
}

inline sfvec2 Lerp(const sfvec2& a, const sfvec2& b, flt32 t)
{
  __m128 lv1 = Set(a);
  __m128 lv2 = Set(b);

  __m128 lt = Set1(t);

  __m128 bma = _mm_sub_ps(lv2, lv1);

  return sfvec2(_mm_fmadd_ps(lt, bma, lv1));
}

#else // !USE_SIMD

inline sfvec2 sfvec2::operator+(const sfvec2& other) const
{
  return sfvec2(this->x + other.x, this->y + other.y);
}

inline sfvec2& sfvec2::operator+=(const sfvec2& other)
{
  this->x += other.x;
  this->y += other.y;

  return *this;
}

inline sfvec2 sfvec2::operator-() const
{
  return sfvec2(-x, -y);
}

inline sfvec2 sfvec2::operator-(const sfvec2& other) const
{
  return sfvec2(this->x - other.x, this->y - other.y);
}

inline sfvec2& sfvec2::operator-=(const sfvec2& other)
{
  this->x -= other.x;
  this->y -= other.y;

  return *this;
}

inline sfvec2 sfvec2::operator*(const sfvec2& other) const
{
  return sfvec2(this->x * other.x, this->y * other.y);
}

inline sfvec2& sfvec2::operator*=(const sfvec2& other)
{
  this->x *= other.x;
  this->y *= other.y;

  return *this;
}

inline sfvec2 sfvec2::operator*(flt32 val) const
{
  return sfvec2(this->x * val, this->y * val);
}

inline sfvec2& sfvec2::operator*=(flt32 val)
{
  this->x *= val;
  this->y *= val;

  return *this;
}

inline sfvec2 sfvec2::operator/(const sfvec2& other) const
{

  return sfvec2(this->x / other.x, this->y / other.y);
}

inline sfvec2& sfvec2::operator/=(const sfvec2& other)
{
  this->x /= other.x;
  this->y /= other.y;

  return *this;
}

inline sfvec2 sfvec2::operator/(flt32 val) const
{
  const flt32 rec = 1.0f / val;

  return sfvec2(this->x * rec, this->y * rec);
}

inline sfvec2& sfvec2::operator/=(flt32 val)
{
  const flt32 rec = 1.0f / val;

  this->x *= rec;
  this->y *= rec;

  return *this;
}

inline sfvec2 sfvec2::operator+(flt32 val) const
{
  return sfvec2(this->x + val, this->y + val);
}

inline sfvec2& sfvec2::operator+=(flt32 val)
{
  this->x += val;
  this->y += val;

  return *this;
}

inline sfvec2 sfvec2::operator-(flt32 val) const
{
  return sfvec2(this->x - val, this->y - val);
}

inline sfvec2& sfvec2::operator-=(flt32 val)
{
  this->x -= val;
  this->y -= val;

  return *this;
}

inline sfvec2& sfvec2::Normalise()
{
  flt32 xt = this->x * this->x;
  flt32 yt = this->y * this->y;

  const flt32 mag = 1.0f / sqrt(xt + yt);
  *this *= mag;

  return *this;
}

inline flt32 sfvec2::Dot(const sfvec2& other)
{
  return this->x * other.x + this->y * other.y;
}

inline flt32 sfvec2::Distance(const sfvec2& other)
{
  flt32 dx = this->x - other.x;
  flt32 dy = this->y - other.y;

  return sqrt(dx * dx + dy * dy);
}
#endif // USE_SIMD && !USE_SIMD

inline flt32 sfvec2::Cross(const sfvec2& other)
{
  return this->x * other.y - other.x * this->y;
}

inline flt32 Cross(const sfvec2& v1, const sfvec2& v2)
{
  return v1.x * v2.y - v2.x * v1.y;
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfvec2& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << " )";
  return os;
}
#endif // DEBUG

inline constexpr sfvec2 sfvec2::zero 	= sfvec2(0.0f, 0.0f);
inline constexpr sfvec2 sfvec2::one 	= sfvec2(1.0f, 1.0f);
inline constexpr sfvec2 sfvec2::neg	  = sfvec2(-1.0f, -1.0f);

inline constexpr sfvec2 sfvec2::up 	  = sfvec2(0.0f, 1.0f);
inline constexpr sfvec2 sfvec2::down 	= sfvec2(0.0f, -1.0f);
inline constexpr sfvec2 sfvec2::right = sfvec2(1.0f, 0.0f);
inline constexpr sfvec2 sfvec2::left 	= sfvec2(-1.0f, 0.0f);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFVEC2_HPP