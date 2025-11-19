#pragma once
#include "enma.hpp"

/*          Prevents Windows fuckery      */
#undef near
#undef far
/*                                     */

/**
 * \brief 
 * 
 * \param eye 
 * \param target 
 * \param up
 * \return mat4 
 */
mat4 LookAt(const vec3& eye, const vec3& target, const vec3& up = vec3::up);

/**
 * \brief 
 * 
 * \param fovy 
 * \param aspectRatio 
 * \param near 
 * \param far 
 * \return mat4 
 */
mat4 Perspective(flt32 fovy, flt32 aspectRatio, flt32 near, flt32 far);

/**
 * \brief 
 * 
 * \param width 
 * \param height 
 * \param near 
 * \param far 
 * \return mat4 
 */
mat4 Orthographic(flt32 width, flt32 height, flt32 near, flt32 far);

/**
 * \brief 
 * 
 * \param left 
 * \param right 
 * \param bottom 
 * \param top 
 * \param near 
 * \param far 
 * \return mat4 
 */
mat4 Orthographic(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 near, flt32 far);

#ifdef USE_LH_YU
#ifdef ENMA_IMPLEMENTATION
mat4 LookAt(const vec3& eye, const vec3& target, const vec3& up)
{
    vec3 eyeAt = target - eye;
    vec3 zaxis = Normalise(eyeAt);
    vec3 xaxis = Cross(up, zaxis);
    vec3 yaxis = Cross(zaxis, xaxis);

    return 
    {
        xaxis.x, yaxis.x, zaxis.x, 0.0f,
        xaxis.y, yaxis.y, zaxis.y, 0.0f,
        xaxis.z, yaxis.z, zaxis.z, 0.0f,
        -Dot(xaxis, eye), -Dot(yaxis, eye), -Dot(zaxis, eye), 1.0f
    };
}

mat4 Perspective(flt32 fovy, flt32 aspectRatio, flt32 near, flt32 far)
{
    #ifdef USE_DEG
    const flt32 fovyAngle = ToRadians(fovy);
    #else
    const flt32 fovyAngle = fovy;
    #endif

    const flt32 focal = 1.0f / std::tan(fovyAngle * 0.5f);
    
    #ifdef USE_REV_DEPTH
    const flt32 nearRAhead = near / (far - near);

    return
    {
        focal, 0.0f,   0.0f,               0.0f,
        0.0f,           -focal * aspectRatio, 0.0f,               0.0f,
        0.0f,           0.0f,   -nearRAhead,        1.0f,
        0.0f,           0.0f,   far * nearRAhead,  0.0f
    };
    #else
    const flt32 farRAhead = far / (far - near);

    return
    {
        focal,          0.0f,                   0.0f,               0.0f,
        0.0f,           -focal * aspectRatio,   0.0f,               0.0f,
        0.0f,           0.0f,                   farRAhead,          1.0f,
        0.0f,           0.0f,                   -near * farRAhead,  0.0f
    };
    #endif
}

mat4 Orthographic(flt32 width, flt32 height, flt32 near, flt32 far)
{
    const flt32 aspectRatio = width / (flt32)height;

    
    #ifdef USE_REV_DEPTH
    const flt32 rBehind = 1.0f / (near - far);

    return 
    {    
        1.0f,   0.0f,                 0.0f,               0.0f,
        0.0f,   -1.0f * aspectRatio,  0.0f,               0.0f,
        0.0f,   0.0f,                 rBehind,            0.0f, 
        0.0f,   0.0f,                 -far * rBehind,    1.0f
    };

    #else
    const flt32 rAhead = 1.0f / (far - near);

    return 
    {    
        1.0f,   0.0f,                 0.0f,               0.0f,
        0.0f,   -1.0f * aspectRatio,  0.0f,               0.0f,
        0.0f,   0.0f,                 rAhead,             0.0f, 
        0.0f,   0.0f,                 -near * rAhead,    1.0f
    };
    #endif
}

mat4 Orthographic(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 near, flt32 far) 
{
    const flt32 rHorizontal = 1.0f / (right - left);
    const flt32 rVertical = 1.0f / (top - bottom);

    #ifdef USE_REV_DEPTH
    const flt32 rBehind = 1.0f / (near - far);

    return 
    {
        2.0f * rHorizontal,             0.0f,                           0.0f,               0.0f,

        0.0f,                           -2.0f * rVertical,              0.0f,               0.0f,

        0.0f,                           0.0f,                           rBehind,            0.0f,

        -(right + left) * rHorizontal,  -(top + bottom) * rVertical,    -far * rBehind,    1.0f
    };

    #else
    const flt32 rAhead = 1.0f / (far - near);

    return 
    {
        2.0f * rHorizontal,             0.0f,                           0.0f,               0.0f,

        0.0f,                           -2.0f * rVertical,              0.0f,               0.0f,

        0.0f,                           0.0f,                           rAhead,             0.0f,

        -(right + left) * rHorizontal,  -(top + bottom) * rVertical,    -near * rAhead,    1.0f
    };
    #endif
}
#endif
#endif