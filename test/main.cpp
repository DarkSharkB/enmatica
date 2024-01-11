#pragma clang diagnostic ignored "-Wmicrosoft-include"

#define ENMATICA_IMPL
//#include "timemanager.hpp"
#include "camera.hpp"
#include "log.hpp"
#include "enma.hpp"

void Test();

int main()
{
    Test();

    system("pause");
}

void Test()
{
    //vec3 v1 = { 0, 0, 1 };
    //vec3 v2 = { 0, 0, -20 };


    //flt32 v5 = vec3::Dot(-v1, v2);

    //LOG_D("v1: " << -v1 << " v2: " << v2 << "\nDot: " << v5);

    mat4x4 m = se::LookAt({ 0.0f, 0.0f, -20.0f }, { 0.0f, 0.0f, 40.f });
    //LOG_D(m);

    mat4x4 k = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
    LOG_D(k);
    LOG_D(Transpose(k));
    
    mat3x3 kk = { 4.0f, -5.0f, -2.0f, 5.0f, -6.0f, -2.0f, -8.0f, 9.0f, 3.0f };
    LOG_D(kk);
    //LOG_D("transpose:\n" << Transpose(kk));
    LOG_D("inverse:\n" << Inverse(kk));
    LOG_D(kk * Inverse(kk));

    quat quin;
    LOG_D(quin);
    LOG_D(quat::ToQuaternion(ToRadians(vec3(90.0f, 0.0f, 0.0f))));
    LOG_D(ToDegrees(quat::ToEulerAngles(quat::ToQuaternion(ToRadians(vec3(90.0f, 0.0f, 0.0f))))));

    /*vec3 v(1, 2, 3);                             // 3D vertex to rotate
    vec3 r(0.57735f, 0.57735f, 0.57735f);        // rotation axis (unit vector)
    flt32 a = 45.0f;                                // rotation angle in degree

    // convert to quaternions
    quat p = quat(0, v.x, v.y, v.z);    // quaternion form of v
    quat q = quat(ToRadians(a * 0.5f), r);   // rotation quaternion with half-angle
    quat c = quat::Conjugate(q);                    // q* (conjugate of q)

    // rotate p by multiplying qpq*
    quat p2 = q * p * c;

    // vector part of p2 contains the rotated 3D vertex
    vec3 v2(p2.x, p2.y, p2.z);                   // quaternion to vector
    std::cout << "v2: " << ToDegrees(v2) << std::endl;         // print the result*/

    // OR, convert quaternion to 4x4 roatation matrix
    /*mat4 m = q.getMatrix();
    v2 = m * v;                                     // rotation using matrix instead

    // OR, use matrix rotation directly
    mat4 m
    m.rotate(a, r);                                 // rotate A degree along R axis
    v2 = m * v;                                     // rotation using matrix instead*/

    flt32 rad = ToRadians(45.0f);
    quat qx = quat::Rotate(rad, vec3(1, 0, 0)); // 45 degree about x-axis
    quat qy = quat::Rotate(rad, vec3(0, 1, 0)); // 45 degree about y-axis
    quat qz = quat::Rotate(rad, vec3(0, 0, 1)); // 45 degree about z-axis

    // compose multiple rotations, order is qz -> qy -> qx
    quat q = qx * qy * qz;
    std::cout << "q: " << q << '\n';          // print the result
    std::cout << "q: " << quat::Inverse(q) * q << '\n';          // print the result
    std::cout << quat::ToRotationMatrix(q) << '\n';       // compare the result with matrix form below

    quat qq = quat::ToQuaternion(vec3(rad));

    flt32 ang = 45.0f;
    // 3 rotations in matrix form
    mat4 mx = se::Rotate(ang, vec3(1, 0, 0));           // 45 degree about x-axis
    mat4 my = se::Rotate(ang, vec3(0, 1, 0));           // 45 degree about y-axis
    mat4 mz = se::Rotate(ang, vec3(0, 0, 1));           // 45 degree about z-axis

    // multiple matrix rotations, order is mz -> my -> mx
    mat4 mmm = mx * my * mz;
    std::cout << "m:\n" << mmm << '\n';         // compare the matrix result with the quaternion
}