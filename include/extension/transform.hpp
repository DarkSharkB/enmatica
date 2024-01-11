#pragma once
#include "../enma.hpp"

// Only Left-Handed Cartesian Coordinates with Y up for now. Deal with it

mat4x4 Translate(const vec3 &position);
mat4x4 Rotate(const flt32 angle, const vec3 &axis);
mat4x4 Scale(flt32 &scale);
mat4x4 Scale(const vec3 &scale);

#ifdef ENMA_IMPL
mat4x4 Translate(const vec3 &position)
{
    return 
    {
        1.0f,       0.0f,       0.0f,       0.0f,
        0.0f,       1.0f,       0.0f,       0.0f,
        0.0f,       0.0f,       1.0f,       0.0f,
        position.x, position.y, position.z, 1.0f
    };
}

mat4x4 Rotate(const vec3 &eulerAngles)
{
    #ifdef USE_AUTO_DEG
    const vec3 angles = ToRadians(eulerAngles);
    #else
    const vec3 angles = eulerAngles;
    #endif

    const flt32 cX = cos(angles.x);   // Cosine of Pitch
    const flt32 cY = cos(angles.y);   // Cosine of Heading
    const flt32 cZ = cos(angles.z);   // Cosine of Bank

    const flt32 sX = sin(angles.x);   // Sine of Pitch
    const flt32 sY = sin(angles.y);   // Sine of Heading
    const flt32 sZ = sin(angles.z);   // Sine of Bank

    const flt32 sXZ = sX * sZ;
    const flt32 sYcZ = sX * cZ;

    return
    {
        cY * cZ + sY * sXZ,     sZ * cX,    -sY * cZ + cY * sXZ,    0.0f,
        -cY * sZ + sY * sYcZ,   cZ * cX,    sZ * sY + cY * sYcZ,    0.0f,
        sY * cX,                -sX,        cY * cX,                0.0f,
        0.0f,                   0.0f,       0.0f,                   1.0f
    };
}

mat4x4 Rotate(const flt32 angle, const vec3 &axis)
{
    const vec3 axs = vec3::Normalise(axis);

    #ifdef USE_AUTO_DEG
    const flt32 ang = ToRadians(angle);
    #else
    const flt32 ang = angle;
    #endif

    const flt32 cosT = cos(ang);    // Cosine Theta
    const flt32 sinT = sin(ang);    // Sine Theta
    const flt32 omCt = 1.0f - cosT;     // One minus Cosine Theta
    const flt32 xSt = axs.x * sinT;
    const flt32 ySt = axs.y * sinT;
    const flt32 zSt = axs.z * sinT;

    const flt32 x2OmCt = axs.x * axs.x * omCt;
    const flt32 y2OmCt = axs.y * axs.y * omCt;
    const flt32 z2OmCt = axs.z * axs.z * omCt;

    const flt32 xyOmCt = axs.x * axs.y * omCt;
    const flt32 xzOmCt = axs.x * axs.z * omCt;
    const flt32 yzOmCt = axs.y * axs.z * omCt;

    return
    {
        x2OmCt + cosT,  xyOmCt + zSt,   xzOmCt - ySt,   0.0f,
        xyOmCt - zSt,   y2OmCt + cosT,  yzOmCt + xSt,   0.0f,
        xzOmCt + ySt,   yzOmCt - xSt,   z2OmCt + cosT,  0.0f,
        0.0f,           0.0f,           0.0f,           1.0f
    };
}

mat4x4 Scale(flt32 &scale)
{
    if(scale < 0.0f)
    {
        scale = 0.0f;
        return mat4x4();
    }

    return
    {
        scale,  0.0f,   0.0f,   0.0f,
        0.0f,   scale,  0.0f,   0.0f,
        0.0f,   0.0f,   scale,  0.0f,
        0.0f,   0.0f,   0.0f,   1.0f
    };
}

mat4x4 Scale(const vec3 &scale)
{
    return
    {
        scale.x,    0.0f,       0.0f,       0.0f,
        0.0f,       scale.y,    0.0f,       0.0f,
        0.0f,       0.0f,       scale.z,    0.0f,
        0.0f,       0.0f,       0.0f,       1.0f
    };
}
#endif