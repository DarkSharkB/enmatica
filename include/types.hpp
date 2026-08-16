/** All Data Types Available in the Library
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_TYPES_HPP
#define ENMA_TYPES_HPP

#include "base.hpp"

/* Boolean Types */

using bln8  = bool;
using bln16 = unsigned short;
using bln32 = unsigned int;

/*  Integer Types   */

using sint8  = signed char;
using sint16 = signed short;
using sint32 = signed int;
using sint64 = signed long long;

/*  Unsigned Integer Types   */

using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

/*  Floating-Point Types    */

using flt32 = float;
using flt64 = double;

ENMA_NS_START
//============== All Derived Types =============//
/* Boolean Vector Types */

using  bvec1 = bln8;
//struct bvec2;
//struct bvec3;
//struct bvec4;

/* Integer Vector Types */

using sivec1 = sint32;
//struct sivec2;
//struct sivec3;
//struct sivec4;

/* Unsigned Integer Vector Types */

using uvec1 = uint32;
//struct uvec2;
//struct uvec3;
//struct uvec4;

/* Single-Precision Floating-Point Vector Types */

using sfvec1 = flt32;
//struct sfvec2;
//struct sfvec3;
//struct sfvec4;

/* Double-Precision Floating-Point Vector Types */

using dfvec1 = flt64;
//struct dfvec2;
//struct dfvec3;
//struct dfvec4;

/* Single-Precision Floating-Point Matrix Types */

//struct sfmat2x2;
//struct sfmat2x3;
//struct sfmat2x4;

//using sfmat2 = sfmat2x2;

//struct sfmat3x2;
//struct sfmat3x3;
//struct sfmat3x4;

//using sfmat3   = sfmat3x3;

//struct sfmat4x2;
//struct sfmat4x3;
//struct sfmat4x4;

//using sfmat4   = sfmat4x4;

/* Floating-Point Quaternions */

struct sfquat;
struct dfquat;

//=============================================//
ENMA_NS_END

#endif // ENMA_TYPES_HPP