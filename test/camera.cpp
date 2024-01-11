#include "camera.hpp"

namespace SE_NAMESPACE
{
    Camera::Camera(ProjectionType type)
    {
    }
        
    mat4x4 Camera::CamMatrix()
    {
        return view * proj;
    }

    mat4x4 Translate(vec3 position)
    {
        mat4x4 m = mat4x4(1.0f);

        m.rows[3] = { position.x, position.y, position.z, 1.0f };

        return mat4x4(m.rows[0], m.rows[1], m.rows[2], m.rows[3]);
    }

    mat4x4 Rotate(flt32 angle, vec3 axis)
    {
        axis.Normalize();

        const flt32 rad = ToRadians(angle);
        const flt32 cosT = cos(rad);
        const flt32 sinT = sin(rad);
        const flt32 omCt = 1.0f - cosT;
        const flt32 xSt = axis.x * sinT;
        const flt32 ySt = axis.y * sinT;
        const flt32 zSt = axis.z * sinT;

        mat4x4 rotationMatrix = mat4x4(1.0f);

        rotationMatrix.m11 = axis.x * axis.x * omCt + cosT;
        rotationMatrix.m12 = axis.x * axis.y * omCt - zSt;
        rotationMatrix.m13 = axis.x * axis.z * omCt + ySt;

        rotationMatrix.m21 = axis.x * axis.y * omCt + zSt;
        rotationMatrix.m22 = axis.y * axis.y * omCt + cosT;
        rotationMatrix.m23 = axis.y * axis.z * omCt - xSt;

        rotationMatrix.m31 = axis.x * axis.z * omCt - ySt;
        rotationMatrix.m32 = axis.y * axis.z * omCt + xSt;
        rotationMatrix.m33 = axis.z * axis.z * omCt + cosT;

        return rotationMatrix;
    }

    mat4x4 Scale(flt32 scale)
    {
        if(scale <= 0.0f)
        {
            scale = 0.0f;
            return mat4x4();
        }
        return mat4x4(vec4(scale, 0.0f), vec4(0.0f, scale), vec4(0.0f, 0.0f, scale), vec4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    mat4x4 LookAt(vec3 eye, vec3 target, vec3 up)
    {
        vec3 eyeAt = target - eye;
        vec3 zaxis = eyeAt.Normalize();
        vec3 xaxis = vec3::Cross(up.Normalize(), zaxis);
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
} // namespace SE_NAMESPACE
