/** 
 * \brief 4 Component Single Precision Floating-Point Vector
 * 
 * \note This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SFVEC4_HPP
#define ENMA_SFVEC4_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"
#include "sfvec2.hpp"
#include "sfvec3.hpp"
#include "core/simd_helpers.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(16) sfvec4
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

    SFVEC4_SWIZZLE(sfvec4);

    #ifdef USE_SIMD
    __m128 _vals;
    #endif
  };
  
  /**
  * Single value constructor.
  *
  * \param val  Value to initialize x, y, z and w components.
  *			        Defaults to 0.0f if not provided.
  */
  constexpr explicit sfvec4(flt32 val = 0.0f);
  
  /**
  * Constructor with components.
  * 
  * \param x X component.
  * \param y Y component.
  * \param z Z component. Defaults to 0.0f if not provided.
  * \param w W component. Defaults to 0.0f if not provided.
  */
  constexpr explicit sfvec4(flt32 x, flt32 y, flt32 z = 0.0f, flt32 w = 0.0f);

  /**
  * Constructor with two vectors.
  * 
  * \param xy XY sfvec2. Sets the x and y components.
  * \param zw ZW sfvec2. Sets the z and w components.
  */
  constexpr explicit sfvec4(const sfvec2& xy, const sfvec2& zw);
  
  /**
  * Constructor with a value and a vector.
  * 
  * \param x X component.
  * \param yzw YZW sfvec3. Sets the y, z and w components.
  */
  constexpr explicit sfvec4(flt32 x, const sfvec3& yzw);
  
  /**
  * Constructor with a vector and a value.
  * 
  * \param xyz XYZ sfvec3. Sets the x, y and z components.
  * \param w W component.
  */
  constexpr explicit sfvec4(const sfvec3& xyz, flt32 w);

  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of floats of atleast 4 valid flt32.
  */
  constexpr explicit sfvec4(const flt32* arr);
  
  /**
  * Conversion operator to sfvec2.
  * 
  * Implicitly converts the current sfvec3 to a sfvec2 by discarding the z and w components.
  * 
  * \return A sfvec2 with x and y components from the current sfvec4.
  */
  explicit operator sfvec2() const;
  
  /**
  * Conversion operator to sfvec3.
  * 
  * Implicitly converts the current sfvec4 to a sfvec3 by discarding the w component.
  * 
  * \return A sfvec3 with x, y and z components from the current sfvec4.
  */
  explicit operator sfvec3() const;
  
  /**
  * Copy constructor.
  * 
  * \param v Another sfvec4 to copy from.
  */
  //constexpr sfvec4(const sfvec4& v);

    /**
   * \brief Copy Assignment operator.
   * 
   * \param other The other sfvec4
   * \return sfvec4&  Returns the value of other vector 
                      which is copied to left hand side vector.
   */
  //sfvec4& operator=(const sfvec4& other);

  /**
  * Indexing operator.
  * 
  * \param index Index of the component to access (0 for x or r, 1 for y or g, 2 for z or b, 3 for w or a).
  * \return Value of the component at the specified `index`.
  */
  flt32 operator[](uint32 index) const;

  /**
  * Addition operator.
  * 
  * Performs addition between this vector and the `other` vector.
  *
  * \param other The other sfvec4.
  * \return Resultant sfvec4 after addition.
  */
  sfvec4 operator+(const sfvec4& other) const;
  
  /**
  * Addition assignment operator.
  * 
  * Performs addition between this vector and the `other` vector.
  *
  * \param other The other sfvec4.
  * \return Reference to the modified sfvec4 after addition.
  */
  sfvec4& operator+=(const sfvec4& other);
  
  /**
  * Unary minus operator.
  * 
  * Negates the components of the vector.
  *
  * \return Resultant sfvec4 with components negated.
  */
  sfvec4 operator-() const;
  
  /**
  * Subtraction operator.
  * 
  * Performs subtraction between this vector and the `other` vector.
  *
  * \param other The other sfvec4.
  * \return Resultant sfvec4 after subtraction.
  */
  sfvec4 operator-(const sfvec4& other) const;
  
  /**
  * Subtraction assignment operator.
  * 
  * Performs subtraction between this vector and the `other` vector.
  *
  * \param other The other sfvec4.
  * \return Reference to the modified sfvec4 after subtraction.
  */
  sfvec4& operator-=(const sfvec4& other);
  
  /**
  * Multiplication operator (element-wise).
  * 
  * Performs element-wise multiplication between this vector and the `other` vector.
  *
  * \param other The other sfvec4.
  * \return Resultant sfvec4 after multiplication.
  */
  sfvec4 operator*(const sfvec4& other) const;
  
  /**
  * Multiplication assignment operator (element-wise).
  * 
  * Performs element-wise multiplication between this vector and the `other` vector.
  *
  * \param other The other sfvec4.
  * \return Reference to the modified sfvec4 after multiplication.
  */
  sfvec4& operator*=(const sfvec4& other);
  
  /**
  * Multiplication operator (scalar).
  * 
  * Performs scalar multiplication between this vector and the `other` vector.
  * 
  * \param val A scalar value.
  * \return Resultant sfvec4 after multiplication.
  */
  sfvec4 operator*(flt32 val) const;
  
  /**
  * Multiplication assignment operator (scalar).
  * 
  * Performs scalar multiplication between this vector and the `other` vector.
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec4 after multiplication.
  */
  sfvec4& operator*=(flt32 val);
  
  /**
  * Division operator (element-wise).
  * 
  * Performs element-wise division between this vector and the `other` vector.
  * 
  * \param other The other sfvec4.
  * \return Resultant sfvec4 after division.
  */
  sfvec4 operator/(const sfvec4& other) const;
  
  /**
  * Division assignment operator (element-wise).
  *
  * Performs element-wise division between this vector and the `other` vector.
  * 
  * \param other The other sfvec4.
  * \return Reference to the modified sfvec4 after division.
  */
  sfvec4& operator/=(const sfvec4& other);
  
  /**
  * Division assignment operator (scalar).
  * 
  * Performs division between this vector and the scalar `val`.
  * 
  * \param val A scalar value.
  * \return Resultant sfvec4 after division.
  */
  sfvec4 operator/(flt32 val) const;
  
  /**
  * Division assignment operator (scalar).
  * 
  * Performs division between this vector and the scalar `val`.
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec4 after division.
  */
  sfvec4& operator/=(flt32 val);

  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Resultant sfvec4 after addition.
  */
  sfvec4 operator+(flt32 val) const;
  
  /**
  * Assigned addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec4 after addition.
  */
  sfvec4& operator+=(flt32 val);
  
  /**
  * Subtraction operator (scalar).
  * 
  * \param val A scalar value.
  * \return Resultant sfvec4 after subtraction.
  */
  sfvec4 operator-(flt32 val) const;
  
  /**
  * Assigned subtraction operator (scalar).
  * 
  * \param val A scalar value.
  * \return Reference to the modified sfvec4 after subtraction.
  */
  sfvec4& operator-=(flt32 val);

  /**
  * Normalises the vector.
  *
  * \return Reference to the modified sfvec2 after normalisation.
  */
  sfvec4& Normalise();
  
  /**
  * Calculates the dot product of the given vector and the other vector.
  * 
  * \param other The other sfvec4.
  * \return The dot product of the given sfvec4 and the `other` sfvec4.
  */
  flt32 Dot(const sfvec4& other) const;
  
  /**
  * Calculates the distance between given vector and the other vector.
  * 
  * \param other The other sfvec4.
  * \return The distance between the given sfvec4 and the `other` sfvec4.
  */
  flt32 Distance(const sfvec4& other) const;
  
  #ifdef USE_SIMD
  /**
  * Conversion operator to __m128.
  * 
  * Converts the current sfvec4 to a __m128 data type.
  * This conversion allows interoperability with SIMD instructions and operations.
  * 
  * \return  A SIMD __m128 data representing the components of the sfvec4.
  */
  operator __m128() const;
  
  /**
  * Constructor from __m128.
  * 
  * Initializes an sfvec4 object using values from a __m128 SIMD data type.
  * 
  * \param vals A SIMD __m128 data containing values to initialize x, y, z and w components.
  */
  sfvec4(const __m128& vals);

  /**
  * Linear Interpolation
  *
  * Interpolates from the given vector, consider it as `a`, to the other vector `b` based on interpolation parameter `t` using SIMD operations.
  *
  * \param b The sfvec2 to interpolate towards.
  * \param t Interpolation parameter (typically in the range [0, 1]).
  * \return The interpolated sfvec4.
  */
  sfvec4 Lerp(const sfvec4& b, flt32 t) const;
  #endif // USE_SIMD
  
  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sfvec4& v);
  #endif // DEBUG

  /**
  * Shorthand to create a zero vector - sfvec4(0.0f, 0.0f, 0.0f, 0.0f)
  * 
  */
  static const sfvec4 zero;
  
  /**
  * Shorthand to create a unit vector - sfvec4(1.0f, 1.0f, 1.0f, 1.0f)
  * 
  */
  static const sfvec4 one;
  /**
  * Shorthand to create a negative unit vector - sfvec4(-1.0f, -1.0f, -1.0f, -1.0f)
  * 
  */
  static const sfvec4 neg;
};

inline sfvec4 operator+(flt32 val, const sfvec4& vec)
{
  return vec + val;
}

inline sfvec4 operator-(flt32 val, const sfvec4& vec)
{
  return vec - val;
}

inline sfvec4 operator*(flt32 val, const sfvec4& vec)
{
  return vec * val;
}

inline sfvec4 operator/(flt32 val, const sfvec4& vec)
{
  return vec / val;
}
/**
* Normalises the input vector.
*
* \param v The input sfvec4.
* \return The normalized form of the input sfvec4 `v`.
*/
inline sfvec4 Normalise(const sfvec4& v);

/**
* Calculates the dot product between two vectors.
* 
* \param v1 The first sfvec4.
* \param v2 The second sfvec4.
* \return The dot product of the first sfvec4 `v1` and the second sfvec4 `v2`.
*/
inline flt32 Dot(const sfvec4& v1, const sfvec4& v2);

/**
* Calculates the distance between two vectors.
* 
* \param v1 The first sfvec4.
* \param v2 The second sfvec4.
* \return The distance between the first sfvec4 `v1` and the second sfvec4 `v2`.
*/
inline flt32 Distance(const sfvec4& v1, const sfvec4& v2);

#ifdef USE_SIMD
/**
* \brief Linear Interpolation
*
* \details Interpolates from the given vector `a` to the other vector `b` 
*          based on interpolation parameter `t`.
*
* \param a The sfvec4 to interpolate from.
* \param b The sfvec4 to interpolate towards.
* \param t Interpolation parameter (typically in the range [0, 1]).
* \return The interpolated sfvec4.
*/
inline sfvec4 Lerp(const sfvec4& a, const sfvec4& b, flt32 t);
#endif // USE_SIMD

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sfvec4::sfvec4(flt32 val)
: x(val), y(val), z(val), w(val) {}

inline constexpr sfvec4::sfvec4(flt32 x, flt32 y, flt32 z, flt32 w)
: x(x), y(y), z(z), w(w) {}

inline constexpr sfvec4::sfvec4(const sfvec2& xy, const sfvec2& zw)
: x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}

inline constexpr sfvec4::sfvec4(flt32 x, const sfvec3& yzw)
: x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

inline constexpr sfvec4::sfvec4(const sfvec3& xyz, flt32 w)
: x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

inline constexpr sfvec4::sfvec4(const flt32* arr)
: x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]) {}

inline sfvec4::operator sfvec2() const
{
  return sfvec2(this->x, this->y);
}

inline sfvec4::operator sfvec3() const
{
  return sfvec3(this->x, this->y, this->z);
}

/*
inline constexpr sfvec4::sfvec4(const sfvec4& v)
: x(v.x), y(v.y), z(v.z), w(v.w) {}

inline sfvec4& sfvec4::operator=(const sfvec4& other)
{
  if(this != &other)
  {
    this->xyzw = other.xyzw;
  }
  return *this;
}
*/

inline flt32 sfvec4::operator[](uint32 index) const
{
  return _arr[index];
}

inline sfvec4 sfvec4::operator-() const
{
  return sfvec4(-x, -y, -z, -w);
}
#ifdef USE_SIMD
inline sfvec4::operator __m128() const
{
  return this->_vals;
}

inline sfvec4::sfvec4(const __m128& vals)
{
  this->_vals = vals;
}

inline sfvec4 sfvec4::operator+(const sfvec4& other) const
{
  return sfvec4(_mm_add_ps(this->_vals, other._vals));
}

inline sfvec4& sfvec4::operator+=(const sfvec4& other)
{
  this->_vals = _mm_add_ps(this->_vals, other._vals);

  return *this;
}


inline sfvec4 sfvec4::operator-(const sfvec4& other) const
{
  return sfvec4(_mm_sub_ps(this->_vals, other._vals));
}

inline sfvec4& sfvec4::operator-=(const sfvec4& other)
{
  this->_vals = _mm_sub_ps(this->_vals, other._vals);

  return *this;
}

inline sfvec4 sfvec4::operator*(const sfvec4& other) const
{
  return sfvec4(_mm_mul_ps(this->_vals, other._vals));
}

inline sfvec4& sfvec4::operator*=(const sfvec4& other)
{			
  this->_vals = _mm_mul_ps(this->_vals, other._vals);

  return *this;
}

inline sfvec4 sfvec4::operator*(const flt32 val) const
{
  const __m128 v2 = Set1(val);

  return sfvec4(_mm_mul_ps(this->_vals, v2));
}

inline sfvec4& sfvec4::operator*=(const flt32 val)
{
  const __m128 v2 = Set1(val);		

  this->_vals = _mm_mul_ps(this->_vals, v2);

  return *this;
}

inline sfvec4 sfvec4::operator/(const sfvec4& other) const
{
  return sfvec4(_mm_div_ps(this->_vals, other._vals));
}

inline sfvec4& sfvec4::operator/=(const sfvec4& other)
{
  this->_vals = _mm_div_ps(this->_vals, other._vals);

  return *this;
}

inline sfvec4 sfvec4::operator/(const flt32 val) const
{
  const __m128 v2 = Set1(val);

  return sfvec4(_mm_div_ps(this->_vals, v2));
}

inline sfvec4& sfvec4::operator/=(const flt32 val)
{
  const __m128 v2 = Set1(val);

  this->_vals = _mm_div_ps(this->_vals, v2);

  return *this;
}

inline sfvec4 sfvec4::operator+(flt32 val) const
{
  const __m128 v2 = Set1(val);

  return sfvec4(_mm_add_ps(this->_vals, v2));
}

inline sfvec4& sfvec4::operator+=(flt32 val)
{
  const __m128 v2 = Set1(val);

  *this = _mm_add_ps(this->_vals, v2);

  return *this;
}

inline sfvec4 sfvec4::operator-(flt32 val) const
{
  const __m128 v2 = Set1(val);

  return sfvec4(_mm_sub_ps(this->_vals, v2));
}

inline sfvec4& sfvec4::operator-=(flt32 val)
{
  const __m128 v2 = Set1(val);

  *this = _mm_sub_ps(this->_vals, v2);

  return *this;
}

inline sfvec4& sfvec4::Normalise()
{
  const __m128 vals = this->_vals;
  
  __m128 lenSqs = _mm_dp_ps(vals, vals, 0xFF);
  if(lenSqs[0] == 0.0f)
  {
    *this = sfvec4::zero;
  }
  else
  {
    __m128 lens = _mm_sqrt_ps(lenSqs);
    *this = _mm_div_ps(vals, lens);
  }

  return *this;
}

inline sfvec4 Normalise(const sfvec4& v)
{
  const __m128 vals = v._vals;
  
  __m128 lenSqs = _mm_dp_ps(vals, vals, 0xFF);
  if(lenSqs[0] == 0.0f)
  {
    return sfvec4::zero;
  }

  __m128 lens = _mm_sqrt_ps(lenSqs);

  return sfvec4(_mm_div_ps(vals, lens));
}

inline flt32 sfvec4::Dot(const sfvec4& other) const
{
  __m128 dot = _mm_dp_ps(this->_vals, other._vals, 0xFF);

  return dot[0];
}

inline flt32 Dot(const sfvec4& v1, const sfvec4& v2)
{
  __m128 dot = _mm_dp_ps(v1._vals, v2._vals, 0xFF);

  return dot[0];
}

inline flt32 sfvec4::Distance(const sfvec4& other) const
{
  __m128 v1 = this->_vals;
  __m128 v2 = other._vals;

  v1 = _mm_sub_ps(v1, v2);
  v1 = _mm_dp_ps(v1, v1, 0xFF);
  v1 = _mm_sqrt_ps(v1);

  return v1[0];
}

inline flt32 Distance(const sfvec4& v1, const sfvec4& v2)
{
  __m128 m = v1._vals;
  __m128 n = v2._vals;

  m = _mm_sub_ps(m, n);
  m = _mm_dp_ps(m, m, 0xFF);
  m = _mm_sqrt_ps(m);

  return m[0];
}

inline sfvec4 sfvec4::Lerp(const sfvec4& b, flt32 t) const
{
  __m128 lv1 = this->_vals;
  __m128 lv2 = b._vals;

  __m128 lt = Set1(t);

  __m128 bma = _mm_sub_ps(lv2, lv1);

  return sfvec4(_mm_fmadd_ps(lt, bma, lv1));
}

inline sfvec4 Lerp(const sfvec4& a, const sfvec4& b, flt32 t)
{
  __m128 lv1 = a._vals;
  __m128 lv2 = b._vals;

  __m128 lt = Set1(t);

  __m128 bma = _mm_sub_ps(lv2, lv1);

  return sfvec4(_mm_fmadd_ps(lt, bma, lv1));
}

#else // !USE_SIMD

inline sfvec4 sfvec4::operator+(const sfvec4& other) const
{
  return sfvec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

inline sfvec4& sfvec4::operator+=(const sfvec4& other)
{
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  this->w += other.w;

  return *this;
}

inline sfvec4 sfvec4::operator-(const sfvec4& other) const
{
  return sfvec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

inline sfvec4& sfvec4::operator-=(const sfvec4& other)
{
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  this->w -= other.w;

  return *this;
}

inline sfvec4 sfvec4::operator*(const sfvec4& other) const
{
  return sfvec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
}

inline sfvec4& sfvec4::operator*=(const sfvec4& other)
{
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;
  this->w *= other.w;

  return *this;
}

inline sfvec4 sfvec4::operator*(const flt32 val) const
{
  return sfvec4(this->x * val, this->y * val, this->z * val, this->w * val);
}

inline sfvec4& sfvec4::operator*=(const flt32 val)
{
  this->x *= val;
  this->y *= val;
  this->z *= val;
  this->w *= val;

  return *this;
}

inline sfvec4 sfvec4::operator/(const sfvec4& other) const
{

  return sfvec4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
}

inline sfvec4& sfvec4::operator/=(const sfvec4& other)
{
  this->x /= other.x;
  this->y /= other.y;
  this->z /= other.z;
  this->w /= other.w;

  return *this;
}

inline sfvec4 sfvec4::operator/(flt32 val) const
{
  const flt32 rec = 1.0f / val;

  return sfvec4(this->x * rec, this->y * rec, this->z * rec, this->w * rec);
}

inline sfvec4& sfvec4::operator/=(flt32 val)
{
  const flt32 rec = 1.0f / val;

  this->x *= rec;
  this->y *= rec;
  this->z *= rec;
  this->w *= rec;

  return *this;
}

inline sfvec4 sfvec4::operator+(flt32 val) const
{
  return sfvec4(this->x + val, this->y + val, this->z + val, this->w + val);
}

inline sfvec4& sfvec4::operator+=(flt32 val)
{
  this->x += val;
  this->y += val;
  this->z += val;
  this->w += val;

  return *this;
}

inline sfvec4 sfvec4::operator-(flt32 val) const
{
  return sfvec4(this->x - val, this->y - val, this->z - val, this->w - val);
}

inline sfvec4& sfvec4::operator-=(flt32 val)
{
  this->x -= val;
  this->y -= val;
  this->z -= val;
  this->w -= val;

  return *this;
}

/*bvec3 sfvec4::Equals(const sfvec4 &other)
{
  return bvec3(this->x == other.x, this->y == other.y);
}*/

inline sfvec4& sfvec4::Normalise()
{
  flt32 xt = this->x * this->x;
  flt32 yt = this->y * this->y;
  flt32 zt = this->z * this->z;
  flt32 wt = this->w * this->w;

  const flt32 lenSq = xt + yt + zt + wt;
  if(lenSq == 0.0f)
  {
    *this = sfvec4::zero;
  }
  else
  {
    const flt32 mag = 1.0f / sqrt(lenSq);
    *this *= mag;
  }

  return *this;
}

inline sfvec4 Normalise(const sfvec4& v)
{
  sfvec4 res = v;

  flt32 xt = v.x * v.x;
  flt32 yt = v.y * v.y;
  flt32 zt = v.z * v.z;
  flt32 wt = v.w * v.w;

  const flt32 lenSq = xt + yt + zt + wt;
  if(lenSq == 0.0f)
  {
    return sfvec4::zero;
  }

  const flt32 mag = 1.0f / sqrt(lenSq);
  res *= mag;

  return res;
}

inline flt32 sfvec4::Dot(const sfvec4& other) const
{
  return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

inline flt32 Dot(const sfvec4& v1, const sfvec4& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline flt32 sfvec4::Distance(const sfvec4& other) const
{
  flt32 dx = this->x - other.x;
  flt32 dy = this->y - other.y;
  flt32 dz = this->z - other.z;
  flt32 dw = this->w - other.w;

  return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

inline flt32 Distance(const sfvec4& v1, const sfvec4& v2)
{
  flt32 dx = v1.x - v2.x;
  flt32 dy = v1.y - v2.y;
  flt32 dz = v1.z - v2.z;
  flt32 dw = v1.w - v2.w;

  return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

#endif // USE_SIMD & !USE_SIMD

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sfvec4& v)
{
  os << "( X: " << v.x << "\tY: " << v.y << "\tZ: " << v.z << "\tW: " << v.w << " )";
  return os;
}
#endif // DEBUG

inline constexpr sfvec4 sfvec4::zero  = sfvec4(0.0f, 0.0f, 0.0f, 0.0f);
inline constexpr sfvec4 sfvec4::one 	= sfvec4(1.0f, 1.0f, 1.0f, 1.0f);
inline constexpr sfvec4 sfvec4::neg 	= sfvec4(-1.0f, -1.0f, -1.0f, -1.0f);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFVEC4_HPP