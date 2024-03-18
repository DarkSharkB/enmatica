#pragma once
#include "../enma.hpp"

#ifdef USE_LH_YU
mat4x4 LookAt(vec3 eye, vec3 target);
mat4x4 FPSCam(vec3 eye, flt32 pitch, flt32 yaw);

mat4x4 Frustum(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 zNear, flt32 zFar);
mat4x4 Perspective(flt32 fovy, flt32 aspect, flt32 zNear, flt32 zFar);
mat4x4 Orthographic(flt32 width, flt32 height, flt32 zNear, flt32 zFar);
mat4x4 Orthographic(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 cNear, flt32 cFar);

#ifdef ENMA_IMPL
mat4x4 LookAt(vec3 eye, vec3 target)
{
    vec3 eyeAt = target - eye;
    vec3 zaxis = vec3::Normalise(eyeAt);
    vec3 xaxis = vec3::Cross({0.0f, 1.0f, 0.0f}, zaxis);
    vec3 yaxis = vec3::Cross(zaxis, xaxis);

    return 
    {
        xaxis.x, yaxis.x, zaxis.x, 0.0f,
        xaxis.y, yaxis.y, zaxis.y, 0.0f,
        xaxis.z, yaxis.z, zaxis.z, 0.0f,
        vec3::Dot(-xaxis, eye), vec3::Dot(-yaxis, eye), vec3::Dot(-zaxis, eye), 1.0f
    };
}

/*mat4x4 FPSCam(vec3 eye, flt32 pitch, flt32 yaw)
{
    flt32 pitchRad = ToRadians(pitch);
    flt32 yawRad = ToRadians(yaw);
    flt32 cosPitch = cos(pitchRad);
    flt32 sinPitch = sin(pitchRad);
    flt32 cosYaw = cos(yawRad);
    flt32 sinYaw = sin(yawRad);

    return mat4x4(1.0f);
}*/

mat4x4 Frustum(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 zNear, flt32 zFar)
{
    return
    {
        (2.0f * zNear) / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, (2.0f * zNear) / (top - bottom), 0.0f, 0.0f,
        -(right + left) / (right - left), -(top + bottom) / (top - bottom), zFar / (zFar - zNear), 1.0f,
        0.0f, 0.0f, -(zFar * zNear) / (zFar - zNear), 0.0f
    };
}

mat4x4 Perspective(flt32 fovy, flt32 aspect, flt32 cNear, flt32 cFar)
{
    const flt32 focal = 1.0f / std::tan(fovy * 0.5f);
    const flt32 nearby = cFar / (cFar - cNear);

    return 
    {    
        focal / aspect, 0.0f, 0.0f, 0.0f, 
        0.0f, -focal, 0.0f, 0.0f,
        0.0f, 0.0f, nearby, 1.0f,
        0.0f, 0.0f, -cNear * nearby, 0.0f
    };
}

mat4x4 Orthographic(flt32 width, flt32 height, flt32 cNear, flt32 cFar)
{
    //const flt32 nearby = zNear / (zNear - zFar);
    //const flt32 nearby = (1.0f - zNear) / (zFar - zNear);
    //const flt32 nearby = (1.0f - zFar) / (zNear - zFar);
    const flt32 asp = width / (flt32)height;
    const flt32 nearby = -cNear / (cFar - cNear);
    //const flt32 nearby = (zFar - zNear) * zNear;

    return 
    {    
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f * asp, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f / (cFar - cNear), 0.0f, 
        0.0f, 0.0f, nearby, 1.0f
    };
}

mat4x4 Orthographic(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 cNear, flt32 cFar) 
{
    return 
    {
        2.0f / (right - left), 0.0f, 0.0f, 0.0f,

        0.0f, -2.0f / (top - bottom), 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f / (cFar - cNear), 0.0f,

        -(right + left) / (right - left), (top + bottom) / (top - bottom), -cNear / (cFar - cNear), 1.0f
    };
}
#endif
#endif