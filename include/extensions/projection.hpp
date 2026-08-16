/** Projection Extension
 * 
 * This header file is an extension to
 * the Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_PROJECTION_HPP
#define ENMA_PROJECTION_HPP

#include "config.hpp"
#include "base.hpp"
#include "types.hpp"
#include "trignometry.hpp"
#include "core/vectors/sfvec3.hpp"
#include "core/matrices/sfmat4x4.hpp"

ENMA_NS_START
//================= Declaration Starts =================//

/**
* \brief 
* 
* \param eye 
* \param target 
* \param up
* \return sfmat4 
*/
inline sfmat4 LookAt(const sfvec3& eye, const sfvec3& target, const sfvec3& up = sfvec3::up);

/**
* \brief 
* 
* \param fovy 
* \param aspectRatio 
* \param near 
* \param far 
* \return sfmat4 
*/
inline sfmat4 Perspective(flt32 fovy, flt32 aspectRatio, flt32 near, flt32 far);

/**
* \brief 
* 
* \param width 
* \param height 
* \param near 
* \param far 
* \return sfmat4 
*/
inline sfmat4 Orthographic(flt32 width, flt32 height, flt32 near, flt32 far);

/**
* \brief 
* 
* \param left 
* \param right 
* \param bottom 
* \param top 
* \param near 
* \param far 
* \return sfmat4 
*/
inline sfmat4 Orthographic(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 near, flt32 far);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

#ifdef USE_LH_YU
inline sfmat4 LookAt(const sfvec3& eye, const sfvec3& target, const sfvec3& up)
{
  sfvec3 eyeAt = target - eye;
  sfvec3 zAxis = Normalise(eyeAt);
  sfvec3 xAxis = Cross(up, zAxis);
  sfvec3 yAxis = Cross(zAxis, xAxis);

  return sfmat4
  {
    xAxis.x, yAxis.x, zAxis.x, 0.0f,
    xAxis.y, yAxis.y, zAxis.y, 0.0f,
    xAxis.z, yAxis.z, zAxis.z, 0.0f,
    -Dot(xAxis, eye), -Dot(yAxis, eye), -Dot(zAxis, eye), 1.0f
  };
}

inline sfmat4 Perspective(flt32 fovy, flt32 aspectRatio, flt32 near, flt32 far)
{
  #ifdef USE_DEG
  const flt32 fovyAngle = ToRadians(fovy);
  #else // !USE_DEG
  const flt32 fovyAngle = fovy;
  #endif // USE_DEG && !USE_DEG

  const flt32 focal = 1.0f / std::tan(fovyAngle * 0.5f);
  
  #ifdef USE_REV_DEPTH
  const flt32 nearRecpAhead = near / (far - near);

  return sfmat4
  {
    focal,  0.0f,                 0.0f,                 0.0f,
    0.0f,   -focal * aspectRatio, 0.0f,                 0.0f,
    0.0f,   0.0f,                 -nearRecpAhead,       1.0f,
    0.0f,   0.0f,                 far * nearRecpAhead,  0.0f
  };
  #else // !USE_REV_DEPTH
  const flt32 farRecpAhead = far / (far - near);

  return sfmat4
  {
    focal,  0.0f,                 0.0f,                 0.0f,
    0.0f,   -focal * aspectRatio, 0.0f,                 0.0f,
    0.0f,   0.0f,                 farRecpAhead,         1.0f,
    0.0f,   0.0f,                 -near * farRecpAhead, 0.0f
  };
  #endif // USE_REV_DEPTH && !USE_REV_DEPTH
}

inline sfmat4 Orthographic(flt32 width, flt32 height, flt32 near, flt32 far)
{
  const flt32 aspectRatio = width / height;
  
  #ifdef USE_REV_DEPTH
  const flt32 recpBehind = 1.0f / (near - far);

  return sfmat4
  {    
    1.0f,   0.0f,                 0.0f,               0.0f,
    0.0f,   -1.0f * aspectRatio,  0.0f,               0.0f,
    0.0f,   0.0f,                 recpBehind,         0.0f, 
    0.0f,   0.0f,                 -far * recpBehind,  1.0f
  };

  #else // !USE_REV_DEPTH
  const flt32 recpAhead = 1.0f / (far - near);

  return sfmat4
  {    
    1.0f,   0.0f,                 0.0f,               0.0f,
    0.0f,   -1.0f * aspectRatio,  0.0f,               0.0f,
    0.0f,   0.0f,                 recpAhead,          0.0f, 
    0.0f,   0.0f,                 -near * recpAhead,  1.0f
  };
  #endif // USE_REV_DEPTH && !USE_REV_DEPTH
}

inline sfmat4 Orthographic(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 near, flt32 far) 
{
  const flt32 recpHorizontal = 1.0f / (right - left);
  const flt32 recpVertical = 1.0f / (top - bottom);

  #ifdef USE_REV_DEPTH
  const flt32 recpBehind = 1.0f / (near - far);

  return sfmat4
  {
    2.0f * recpHorizontal,            0.0f,                           0.0f,               0.0f,

    0.0f,                             -2.0f * recpVertical,           0.0f,               0.0f,

    0.0f,                             0.0f,                           recpBehind,         0.0f,

    -(right + left) * recpHorizontal, -(top + bottom) * recpVertical, -far * recpBehind,  1.0f
  };

  #else // !USE_REV_DEPTH
  const flt32 recpAhead = 1.0f / (far - near);

  return sfmat4
  {
    2.0f * recpHorizontal,            0.0f,                           0.0f,               0.0f,

    0.0f,                             -2.0f * recpVertical,           0.0f,               0.0f,

    0.0f,                             0.0f,                           recpAhead,          0.0f,

    -(right + left) * recpHorizontal, -(top + bottom) * recpVertical, -near * recpAhead,  1.0f
  };
  #endif // USE_REV_DEPTH && !USE_REV_DEPTH
}
#endif // USE_LH_YU

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_PROJECTION_HPP