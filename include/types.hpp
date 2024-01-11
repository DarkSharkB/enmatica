/* Base Types
 * 
 * This header file is part of Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */

#pragma once

/* Boolean Types */
using bln8 = bool;
using bln16 = unsigned short;
using bln32 = unsigned int;

/*  Integer Types   */

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

/*  Unsigned Integer Types   */

using uin8 = unsigned char;
using uin16 = unsigned short;
using uin32 = unsigned int;
using uin64 = unsigned long long;

/*  Floating-Point Types    */

using flt32 = float;    // Single-Precision Floating Point Number
using flt64 = double;   // Double-Precision Floating Point Number

/* Boolean Vector Types */

using bvec1 = bln8;
struct bvec2;
struct bvec3;
struct bvec4;

/* Integer Vector Types */

using ivec1 = int32;
struct ivec2;
struct ivec3;
struct ivec4;

/* Unsigned Integer Vector Types */

using uvec1 = uin32;
struct uvec2;
struct uvec3;
struct uvec4;

/* Single-Precision Floating-Point Vector Types */

using fvec1 = flt32;
struct fvec2;
struct fvec3;
struct fvec4;

using vec1 = fvec1;
using vec2 = fvec2;
using vec3 = fvec3;
using vec4 = fvec4;

/* Double-Precision Floating-Point Vector Types */

using dvec1 = flt64;
struct dvec2;
struct dvec3;
struct dvec4;

/* Single-Precision Floating-Point Matrix Types */

struct fmat2x2;
struct fmat2x3;
struct fmat2x4;

using mat2   = fmat2x2;
using mat2x2 = fmat2x2;
using mat2x3 = fmat2x3;
using mat2x4 = fmat2x4;

struct fmat3x2;
struct fmat3x3;
struct fmat3x4;

using mat3x2 = fmat3x2;
using mat3   = fmat3x3;
using mat3x3 = fmat3x3;
using mat3x4 = fmat3x4;

struct fmat4x2;
struct fmat4x3;
struct fmat4x4;

using mat4x2 = fmat4x2;
using mat4x3 = fmat4x3;
using mat4   = fmat4x4;
using mat4x4 = fmat4x4;


/* Floating-Point Quaternions */

struct fquat;
struct dquat;

using quat = fquat;

/*--------------------------------------------*/