#pragma once
#include "../enma.hpp"

// Left-Handed Cartesian Coordinates with Y up for now. Deal with it

#ifdef USE_LH_YU
/**
 * Translates
 * \param position A vec3 position.
 * \return The translation mat4 for the given position
 */
mat4 Translate(const vec3 &position);
mat4 Rotate(flt32 angle, const vec3 &axis);
mat4 Scale(flt32 &scale);
mat4 Scale(const vec3 &scale);

#ifdef ENMA_IMPLEMENTATION
mat4 Translate(const vec3 &position)
{
    return 
    {
        1.0f,       0.0f,       0.0f,       0.0f,
        0.0f,       1.0f,       0.0f,       0.0f,
        0.0f,       0.0f,       1.0f,       0.0f,
        position.x, position.y, position.z, 1.0f
    };
}

mat4 Rotate(flt32 angle)
{
    #ifdef USE_DEG
    const flt32 angles = ToRadians(angle);
    #else
    const flt32 angles = angle;
    #endif

    const flt32 cA = cos(angles);
    const flt32 sA = sin(angles);
    
    const flt32 cA2 = cA * cA;      // cosa2
    const flt32 sA2 = sA * sA;      // sina2

    const flt32 sAcA = sA * cA;     // sina * cosa
    const flt32 sA2cA = sA2 * cA;   // sina2 * cosa

    return
    {
        cA2,                -sAcA,              -sA,        0.0f,
        sA2cA + sAcA,       -sA2 * sA + cA2,    sAcA,       0.0f,
        sAcA * cA + sA2,    -sA2cA + sAcA,      cA2,        0.0f,
        0.0f,               0.0f,               0.0f,       1.0f
    };
}

/*mat4 Rotate(const vec3 &eulerAngles)
{
    #ifdef USE_DEG
    const vec3 angles = ToRadians(eulerAngles);
    #else
    const vec3 angles = eulerAngles;
    #endif

    const flt32 cX = cos(angles.x);   // Cosine of Pitch
    const flt32 cY = cos(angles.y);   // Cosine of Yaw
    const flt32 cZ = cos(angles.z);   // Cosine of Roll

    const flt32 sX = sin(angles.x);   // Sine of Pitch
    const flt32 sY = sin(angles.y);   // Sine of Yaw
    const flt32 sZ = sin(angles.z);   // Sine of Roll

    const flt32 sXZ = sX * sZ;
    const flt32 sYcZ = sX * cZ;

    return
    {
        cY * cZ + sY * sXZ,     sZ * cX,    -sY * cZ + cY * sXZ,    0.0f,
        -cY * sZ + sY * sYcZ,   cZ * cX,    sZ * sY + cY * sYcZ,    0.0f,
        sY * cX,                -sX,        cY * cX,                0.0f,
        0.0f,                   0.0f,       0.0f,                   1.0f
    };
}*/

auto RotationMatrixX = [](flt32 rotationAngle) -> mat4 {
    #ifdef USE_DEG
    rotationAngle = ToRadians(rotationAngle);
    #endif
    return mat4{
        1, 0, 0, 0,
        0, cos(rotationAngle), sin(rotationAngle), 0,
        0, sin(rotationAngle), cos(rotationAngle), 0,
        0, 0, 0, 1
    };
};

auto RotationMatrixY = [](flt32 rotationAngle) -> mat4 {
    #ifdef USE_DEG
    rotationAngle = ToRadians(rotationAngle);
    #endif
    return mat4{
        cos(rotationAngle), 0, -sin(rotationAngle), 0,
        0, 1, 0, 0,
        sin(rotationAngle), 0, cos(rotationAngle), 0,
        0, 0, 0, 1
    };
};

auto RotationMatrixZ = [](flt32 rotationAngle) -> mat4 {
    #ifdef USE_DEG
    rotationAngle = ToRadians(rotationAngle);
    #endif
    return mat4{
        cos(rotationAngle), -sin(rotationAngle), 0, 0,
        sin(rotationAngle), cos(rotationAngle), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
};

mat4 Rotate(const vec3 &eulerAngles)
{
    #ifdef USE_DEG
    const vec3 angles = ToRadians(eulerAngles);
    #else
    const vec3 angles = eulerAngles;
    #endif

    const flt32 cX = cos(angles.x);   // Cosine of Pitch
    const flt32 cY = cos(angles.y);   // Cosine of Yaw
    const flt32 cZ = cos(angles.z);   // Cosine of Roll

    const flt32 sX = sin(angles.x);   // Sine of Pitch
    const flt32 sY = sin(angles.y);   // Sine of Yaw
    const flt32 sZ = sin(angles.z);   // Sine of Roll

    const flt32 sYZ = sY * sZ;
    const flt32 sYcZ = sY * cZ;

    return
    {
        cY * cZ,                -sZ * cY,               -sY,        0.0f,
        sX * sYcZ + cX * sZ,    -sX * sYZ + cX * cZ,    sX * cY,    0.0f,
        cX * sYcZ + sX * sZ,    -sYZ * cX + sX * cZ,    cX * cY,    0.0f,
        0.0f,                   0.0f,                   0.0f,       1.0f
    };
}

mat4 Rotate(flt32 angle, const vec3 &axis)
{
    const vec3 axs = Normalise(axis);

    #ifdef USE_DEG
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

mat4 Scale(flt32 &scale)
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

mat4 Scale(const vec3 &scale)
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
#endif