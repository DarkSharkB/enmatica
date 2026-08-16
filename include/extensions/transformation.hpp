/** Transformation Extension
 * 
 * This header file is an extension to
 * the Enmatica library
 *
 * Copyright (c) 202X Villainous Softworks
 * 
 */
#pragma once

#ifndef ENMA_TRANSFORMATION_HPP
#define ENMA_TRANSFORMATION_HPP

#include "config.hpp"
#include "base.hpp"
#include "types.hpp"
#include "trignometry.hpp"
#include "core/matrices/sfmat4x4.hpp"

//== Note: Currently all functions are implemented only for Left-Handed Y Up Cartesian Coordinates. Deal with it! ==//

ENMA_NS_START
//================= Declaration Starts =================//

/**
* Produces a translation matrix for the given position.
* \param position A position to translate.
* \return The 4x4 transformation matrix translated to position.
*/
inline sfmat4 Translate(const sfvec3& position);

/**
* Produces X-axis rotation matrix for the given rotation angle.
* \param rotationAngle Angle to rotate around the X-axis.
* \return The 4x4 transformation matrix with rotation applied in X-axis.
*/
inline sfmat4 RotateX(flt32 rotationAngle);

/**
* Produces Y-axis rotation matrix for the given rotation angle.
* \param rotationAngle Angle to rotate around the Y-axis.
* \return The 4x4 transformation matrix with rotation applied in Y-axis.
*/
inline sfmat4 RotateY(flt32 rotationAngle);

/**
* Produces Z-axis rotation matrix for the given rotation angle.
* \param rotationAngle Angle to rotate around the Z-axis.
* \return The 4x4 transformation matrix with rotation applied in Z-axis.
*/
inline sfmat4 RotateZ(flt32 rotationAngle);

/**
* Produces a combined X, Y and Z-axis rotation matrix for the given euler angles.
* \param eulerAngles The angles to rotate in each axis.
* \return The 4x4 transformation matrix for the given euler angles.
*/
inline sfmat4 Rotate(const sfvec3& eulerAngles);

/**
* Produces a rotation matrix for the given rotation angle and axis.
* \param rotationAngle The angle to rotate.
* \param axis The axis to rotate.
* \return The 4x4 transformation matrix for the given rotation angle and axis.
*/
inline sfmat4 Rotate(flt32 rotationAngle, const sfvec3& axis);

/**
* Produces a uniform scale matrix.
* \param scale A uniform scale factor applied equally to all axes.
* \return A 4x4 transformation matrix with uniform scaling.
*/
inline sfmat4 Scale(flt32 scale);

/**
* Produces a non-uniform scale matrix.
* \param scale The scale factors to apply along X, Y and Z axes.
* \return A 4x4 transformation matrix with specified scaling.
*/
inline sfmat4 Scale(const sfvec3& scale);

//================== Declaration Ends ==================//
ENMA_NS_END


ENMA_NS_START
//=============== Implementation Starts ===============//

#ifdef USE_LH_YU
inline sfmat4 Translate(const sfvec3& position)
{
  return sfmat4
  {
    1.0f,       0.0f,       0.0f,       0.0f,
    0.0f,       1.0f,       0.0f,       0.0f,
    0.0f,       0.0f,       1.0f,       0.0f,
    position.x, position.y, position.z, 1.0f
  };
}

inline sfmat4 Rotate(flt32 rotationAngle)
{
  #ifdef USE_DEG
  const flt32 angle = ToRadians(rotationAngle);
  #else // !USE_DEG
  const flt32 angle = rotationAngle;
  #endif // USE_DEG && !USE_DEG

  const flt32 c = cos(angle);
  const flt32 s = sin(angle);
  
  const flt32 c2 = c * c;
  const flt32 s2 = s * s;

  const flt32 cs = c * s;
  const flt32 cs2 = c * s2;

  return sfmat4
  {
    c2,           -cs,          -s,   0.0f,
    cs2 + cs,     -s2 * s + c2, cs,   0.0f,
    cs * c - s2,  -cs2 - cs,    c2,   0.0f,
    0.0f,         0.0f,         0.0f, 1.0f
  };
}

inline sfmat4 RotateX(flt32 rotationAngle)
{
  #ifdef USE_DEG
  flt32 angle = ToRadians(rotationAngle);
  #else // !USE_DEG
  flt32 angle = rotationAngle;
  #endif // USE_DEG && !USE_DEG
  
  flt32 c = cos(angle);
  flt32 s = sin(angle);

  return sfmat4
  {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, c,    s,    0.0f,
    0.0f, -s,   c,    0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
};

inline sfmat4 RotateY(flt32 rotationAngle)
{
  #ifdef USE_DEG
  flt32 angle = ToRadians(rotationAngle);
  #else // !USE_DEG
  flt32 angle = rotationAngle;
  #endif // USE_DEG && !USE_DEG
  
  flt32 c = cos(angle);
  flt32 s = sin(angle);

  return sfmat4
  {
    c,    0.0f, -s,   0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    s,    0.0f, c,    0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
};

inline sfmat4 RotateZ(flt32 rotationAngle)
{
  #ifdef USE_DEG
  flt32 angle = ToRadians(rotationAngle);
  #else // !USE_DEG
  flt32 angle = rotationAngle;
  #endif // USE_DEG && !USE_DEG
  
  flt32 c = cos(angle);
  flt32 s = sin(angle);

  return sfmat4
  {
    c,    -s,   0.0f, 0.0f,
    s,    c,    0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
};

inline sfmat4 Rotate(const sfvec3& eulerAngles)
{
  #ifdef USE_DEG
  const sfvec3 angles = ToRadians(eulerAngles);
  #else // !USE_DEG
  const sfvec3 angles = eulerAngles;
  #endif // USE_DEG && !USE_DEG

  const flt32 cX = cos(angles.x);   // Cosine of Pitch
  const flt32 cY = cos(angles.y);   // Cosine of Yaw
  const flt32 cZ = cos(angles.z);   // Cosine of Roll

  const flt32 sX = sin(angles.x);   // Sine of Pitch
  const flt32 sY = sin(angles.y);   // Sine of Yaw
  const flt32 sZ = sin(angles.z);   // Sine of Roll

  const flt32 sYZ = sY * sZ;
  const flt32 sYcZ = sY * cZ;

  return sfmat4
  {
    cY * cZ,              -cY * sZ,             -sY,      0.0f,
    sX * sYcZ + cX * sZ,  -sX * sYZ + cX * cZ,  sX * cY,  0.0f,
    cX * sYcZ - sX * sZ,  -cX * sYZ - sX * cZ,  cX * cY,  0.0f,
    0.0f,                 0.0f,                 0.0f,     1.0f
  };
}

inline sfmat4 Rotate(flt32 rotationAngle, const sfvec3& axis)
{
  #ifdef USE_DEG
  const flt32 angle = ToRadians(rotationAngle);
  #else // !USE_DEG
  const flt32 angle = rotationAngle;
  #endif // USE_DEG && !USE_DEG

  const sfvec3 normAxis = Normalise(axis);

  const flt32 c = cos(angle);
  const flt32 s = sin(angle);
  const flt32 onC = 1.0f - c;                                 // one negate Cosine
  const flt32 xS = normAxis.x * s;
  const flt32 yS = normAxis.y * s;
  const flt32 zS = normAxis.z * s;

  const flt32 x2OnC = normAxis.x * normAxis.x * onC;
  const flt32 y2OnC = normAxis.y * normAxis.y * onC;
  const flt32 z2OnC = normAxis.z * normAxis.z * onC;

  const flt32 xyOnC = normAxis.x * normAxis.y * onC;
  const flt32 xzOnC = normAxis.x * normAxis.z * onC;
  const flt32 yzOnC = normAxis.y * normAxis.z * onC;

  return sfmat4
  {
    x2OnC + c,  xyOnC - zS, xzOnC - yS, 0.0f,
    xyOnC + zS, y2OnC + c,  yzOnC + xS, 0.0f,
    xzOnC + yS, yzOnC - xS, z2OnC + c,  0.0f,
    0.0f,       0.0f,       0.0f,       1.0f
  };
}

inline sfmat4 Scale(flt32 scale)
{
  return sfmat4
  {
    scale,  0.0f,   0.0f,   0.0f,
    0.0f,   scale,  0.0f,   0.0f,
    0.0f,   0.0f,   scale,  0.0f,
    0.0f,   0.0f,   0.0f,   1.0f
  };
}

inline sfmat4 Scale(const sfvec3& scale)
{
  return sfmat4
  {
    scale.x,  0.0f,     0.0f,     0.0f,
    0.0f,     scale.y,  0.0f,     0.0f,
    0.0f,     0.0f,     scale.z,  0.0f,
    0.0f,     0.0f,     0.0f,     1.0f
  };
}
#endif // USE_LH_YU

//================ Implementation Ends ================//
ENMA_NS_END

#endif // ENMA_TRANSFORMATION_HPP