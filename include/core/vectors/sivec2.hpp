/** 
 * \brief 2 Component Signed Integer Vector
 * 
 * This header file is part of Enmatica library
 *
 * \copyright Copyright (c) 202X by Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_SIVEC2_HPP
#define ENMA_SIVEC2_HPP

#include "base.hpp"
#include "types.hpp"
#include "swizzle.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

struct ALIGN(8) sivec2
{
  union
  {
    sint32 _arr[2];
    struct 
    {
      sint32 x, y;
    };
    struct
    {
      sint32 r, g;
    };

    SIVEC2_SWIZZLE(sivec2);
  };

  /**
  * Single value constructor.
  *
  * \param val Value to initialize x and y components. 
  *			       Defaults to 0 if not provided.
  */
  constexpr explicit sivec2(sint32 val = 0);

  /**
  * Constructor with components.
  * 
  * \param x X component.
  * \param y Y component.
  */
  constexpr explicit sivec2(sint32 x, sint32 y);

  /**
  * \brief Constructor with an array.
  * 
  * \param arr A constant pointer to an array of atleast 2 sint32.
  */
  constexpr explicit sivec2(const sint32* arr);

  
  /**
  * Copy constructor.
  * 
  * \param v Another sivec2 to copy from.
  */
  //constexpr sivec2(const sivec2& v);

  /**
  * Indexing operator.
  * 
  * \param index Index of the component to access (0 for x or r, 1 for y or g).
  * \return Value of the component at the specified `index`.
  */
  sint32 operator[](uint32 index) const;
  
  /**
  * Addition operator.
  * 
  * Performs addition between this vector and the `other` vector.
  *
  * \param other The other sivec2.
  * \return Resultant sivec2 after addition.
  */
  sivec2 operator+(const sivec2& other) const;
  sivec2& operator+=(const sivec2& other);
  sivec2 operator-() const;
  sivec2 operator-(const sivec2& other) const;
  sivec2& operator-=(const sivec2& other);
  sivec2 operator*(const sivec2& other) const;
  sivec2& operator*=(const sivec2& other);
  sivec2 operator*(sint32 val) const;
  sivec2& operator*=(sint32 val);
  sivec2 operator/(const sivec2& other) const;
  sivec2& operator/=(const sivec2& other);
  sivec2 operator/(sint32 val) const;
  sivec2& operator/=(sint32 val);
  
  //======== Extension Functions for Ease of Use ========//
  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Resultant fvec2 after addition.
  */
  sivec2 operator+(sint32 val) const;
  
  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Reference to the modified fvec2 after addition.
  */
  sivec2& operator+=(sint32 val);

  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Resultant fvec2 after subtraction.
  */
  sivec2 operator-(sint32 val) const;

  /**
  * Addition operator (scalar).
  * 
  * \param val A scalar value.
  * \return Reference to the modified fvec2 after subtraction.
  */
  sivec2& operator-=(sint32 val);

  /**
  * Normalises the vector.
  *
  * \return Reference to the modified sivec2 after normalisation.
  */
  sivec2& Normalise();

  /**
  * Calculates the dot product of the given vector and the other vector.
  * 
  * \param other The other sivec2.
  * \return The dot product of the given sivec2 and the `other` sivec2.
  */
  sint32 Dot(const sivec2& other) const;

  /**
  * Calculates the cross product between given vector and the other vector.
  * 
  * \param other The other sivec2.
  * \return The z-component of the cross product between the given sivec2 and the `other` sivec2.
  */
  sint32 Cross(const sivec2& other) const;

  /**
  * Calculates the distance between given vector and the other vector.
  * 
  * \param other The other sivec2.
  * \return The distance between the given sivec2 and the `other` sivec2.
  */
  flt32 Distance(const sivec2& other) const;

  #ifdef DEBUG
  friend std::ostream& operator<<(std::ostream& os, const sivec2& v);
  #endif // DEBUG
  // Extension functions end here! //
  
  /**
  * Shorthand to create a zero vector - sivec2(0, 0)
  * 
  */
  static const sivec2 zero;

  /**
  * Shorthand to create a unit vector - sivec2(1, 1)
  * 
  */
  static const sivec2 one;

  /**
  * Shorthand to create a negative unit vector - sivec2(-1, -1)
  * 
  */
  static const sivec2 neg;


  /**
  * Shorthand to create up vector - sivec2(0, 1)
  * 
  */
  static const sivec2 up;

  /**
  * Shorthand to create down vector - sivec2(0, -1)
  * 
  */
  static const sivec2 down;

  /**
  * Shorthand to create right vector - sivec2(1, 0)
  * 
  */
  static const sivec2 right;
  
  /**
  * Shorthand to create left vector - sivec2(-1, 0)
  * 
  */
  static const sivec2 left;
};

inline sint32 Dot(const sivec2& v1, const sivec2& v2);
inline sint32 Cross(const sivec2& v1, const sivec2& v2);
inline flt32 Distance(const sivec2& v1, const sivec2& v2);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

inline constexpr sivec2::sivec2(sint32 val)
: x(val), y(val) {}

inline constexpr sivec2::sivec2(sint32 x, sint32 y)
: x(x), y(y) {}

inline constexpr sivec2::sivec2(const sint32* arr)
: x(arr[0]), y(arr[1]) {}

/*
inline constexpr sivec2::sivec2(const sivec2& v)
: x(v.x), y(v.y) {}
*/

inline sint32 sivec2::operator[](uint32 index) const
{
  return _arr[index];
}

inline sivec2 sivec2::operator+(const sivec2& other) const
{
  return sivec2(this->x + other.x, this->y + other.y);
}

inline sivec2& sivec2::operator+=(const sivec2& other)
{
  this->x += other.x;
  this->y += other.y;

  return *this;
}

inline sivec2 sivec2::operator-() const
{
  return sivec2(-x, -y);
}

inline sivec2 sivec2::operator-(const sivec2& other) const
{
  return sivec2(this->x - other.x, this->y - other.y);
}

inline sivec2& sivec2::operator-=(const sivec2& other)
{
  this->x -= other.x;
  this->y -= other.y;

  return *this;
}

inline sivec2 sivec2::operator*(const sivec2& other) const
{
  return sivec2(this->x * other.x, this->y * other.y);
}

inline sivec2& sivec2::operator*=(const sivec2& other)
{
  this->x *= other.x;
  this->y *= other.y;

  return *this;
}

inline sivec2 sivec2::operator*(sint32 val) const
{
  return sivec2(this->x * val, this->y * val);
}

inline sivec2& sivec2::operator*=(sint32 val)
{
  this->x *= val;
  this->y *= val;

  return *this;
}

inline sivec2 sivec2::operator/(const sivec2& other) const
{

  return sivec2(this->x / other.x, this->y / other.y);
}

inline sivec2& sivec2::operator/=(const sivec2& other)
{
  this->x /= other.x;
  this->y /= other.y;

  return *this;
}

inline sivec2 sivec2::operator/(sint32 val) const
{

  return sivec2(this->x / val, this->y / val);
}

inline sivec2& sivec2::operator/=(sint32 val)
{

  this->x *= val;
  this->y *= val;

  return *this;
}

inline sint32 sivec2::Dot(const sivec2& other) const
{
  return this->x * other.x + this->y * other.y;
}

inline sint32 Dot(const sivec2& v1, const sivec2& v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

inline sint32 sivec2::Cross(const sivec2& other) const
{
  return this->x * other.y - other.x * this->y;
}

inline sint32 Cross(const sivec2& v1, const sivec2& v2)
{
  return v1.x * v2.y - v2.x * v1.y;
}

inline flt32 sivec2::Distance(const sivec2& other) const
{
  const sint32 xt = this->x - other.x;
  const sint32 yt = this->y - other.y;

  return sqrt(xt * xt + yt * yt);
}

inline flt32 Distance(const sivec2& v1, const sivec2& v2)
{
  const sint32 xt = v1.x - v2.x;
  const sint32 yt = v1.y - v2.y;

  return sqrt(xt * xt + yt * yt);
}

#ifdef DEBUG
inline std::ostream& operator<<(std::ostream& os, const sivec2& v)
{
  os << "( X: " << v.x << "\tY: "<< v.y << " )";
  return os;
}
#endif // DEBUG

inline constexpr sivec2 sivec2::zero 	= sivec2(0, 0);
inline constexpr sivec2 sivec2::one   = sivec2(1, 1);
inline constexpr sivec2 sivec2::neg   = sivec2(-1, -1);

inline constexpr sivec2 sivec2::up 	  = sivec2(0, 1);
inline constexpr sivec2 sivec2::down 	= sivec2(0, -1);
inline constexpr sivec2 sivec2::right = sivec2(1, 0);
inline constexpr sivec2 sivec2::left 	= sivec2(-1, 0);

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_SFVEC2_HPP