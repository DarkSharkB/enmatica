#pragma once
#include "../include/enma.hpp"

#define SE_NAMESPACE se

namespace SE_NAMESPACE
{
    enum ProjectionType
    {
        CAM_PERSPECTIVE = 0,
        CAM_ORTHOGRAPHIC = 1,
        CAM_2D = 2
    };

    class Camera
    {
    public:
        mat4x4 view;
        mat4x4 proj;

        Camera(ProjectionType type = ProjectionType::CAM_PERSPECTIVE);
        ~Camera() = default;
        mat4x4 CamMatrix();
    };

    mat4x4 Translate(vec3 position);
    mat4x4 Rotate(flt32 angle, vec3 axis);
    mat4x4 Scale(flt32 scale);

    mat4x4 LookAt(vec3 eye, vec3 target, vec3 up = {0.0f, 1.0f, 0.0f});
    mat4x4 FPSCam(vec3 eye, flt32 pitch, flt32 yaw);

    mat4x4 Perspective(flt32 fovy, flt32 aspect, flt32 zNear, flt32 zFar);
    mat4x4 Orthographic(flt32 width, flt32 height, flt32 zNear, flt32 zFar);
    mat4x4 Orthographic(flt32 left, flt32 right, flt32 bottom, flt32 top, flt32 cNear, flt32 cFar);
    
} // namespace SE_NAMESPACE
