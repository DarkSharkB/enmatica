#pragma clang diagnostic ignored "-Wmicrosoft-include"

#define ENMA_IMPL
//#include "timemanager.hpp"
#include "enma.hpp"

void Test();
void mm();

int main()
{
    //Test();
    mm();
    system("pause");
}

void Test()
{
    /* How the f* do you write this?? */
    //vec3 v1 = { 0, 2, 1 };
    //vec3 v2 = vec3(12.0f, 24.0f, 12.0f);

   // v1 *= 24;

    //LOG_D(v1);

    //LOG_D(v1/v2);
    vec3 v2 = { 10, 12, 21 };

    vec3 v3 = { 3, 2, -1 };
    //v2 += v3;
    //LOG_D(v2);

    LOG_D("Align: ", alignof(vec3));

    vec3 n = vec3::Normalise(v2);
    LOG_D("Static:", n);
    n = v2.Normalise();
    LOG_D("Interol:", v2.Normalise());
    
    //LOG_D("Interol:", v3.Normalise());
    LOG_D("Static:", vec3::Normalise(v3));
    
    mat4 v = LookAt({}, { 0.0f, 0.0f, 2.0f });
    LOG_D("Look Ma: ", v);
    LOG_D("Look Ma: ", LookAt({}, { 0.0f, 0.0f, 2.0f }));

    vec3 c = vec3::Cross({}, { 0.0f, 0.0f, 2.0f });
    LOG_D("Cross:", c);
    
    flt32 f = vec3::Dot(v3, { 0.0f, 0.0f, 2.0f });
    LOG_D("Dot: ", f);

    
    f = v3.Dot({ 0.0f, 0.0f, 2.0f });
    LOG_D("Dot: ", f);
    LOG_D("Dot: ", v3.Dot({ 0.0f, 0.0f, 2.0f }));
    LOG_D("Dot: ", vec3::Dot(v3, { 0.0f, 0.0f, 2.0f }));
}

void mm()
{
    //flt32 v5 = vec3::Dot(-v1, v2);

    //LOG_D("v1: " << -v1 << " v2: " << v2 << "\nDot: " << v5);

    /*mat4x4 m = LookAt({ 0.0f, 0.0f, -20.0f }, { 0.0f, 0.0f, 40.f });
    //LOG_D(m);

    mat4x4 k = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
    LOG_D(k);
    LOG_D(Transpose(k));
    
    mat3x3 kk = { 4.0f, -5.0f, -2.0f, 5.0f, -6.0f, -2.0f, -8.0f, 9.0f, 3.0f };
    LOG_D(kk);
    //LOG_D("transpose:\n" << Transpose(kk));
    LOG_D("inverse:\n", Inverse(kk));
    LOG_D(kk * Inverse(kk));*/

    LOG_D(quat::ToRotationMatrix(quat::ToQuaternion(vec3(180.0f, 120.0f, 45.0f))));
    LOG_D(quat::ToQuaternion(vec3(89.0f, 120.0f, 45.0f)));

    LOG_D(Rotate(vec3(180.0f, 120.0f, 45.0f)));
    LOG_D(Rotate(45.0f, vec3(0.0f, 0.0f, 1.0f)) * Rotate(180.0f, vec3(1.0f, 0.0f, 0.0f)) * Rotate(120.0f, vec3(0.0f, 1.0f, 0.0f)));

    // OR, convert quaternion to 4x4 roatation matrix
    /*mat4 m = q.getMatrix();
    v2 = m * v;                                     // rotation using matrix instead

    // OR, use matrix rotation directly
    mat4 m
    m.rotate(a, r);                                 // rotate A degree along R axis
    v2 = m * v;                                     // rotation using matrix instead*/

    /*flt32 rad = ToRadians(45.0f);
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
    mat4 mx = Rotate(ang, vec3(1, 0, 0));           // 45 degree about x-axis
    mat4 my = Rotate(ang, vec3(0, 1, 0));           // 45 degree about y-axis
    mat4 mz = Rotate(ang, vec3(0, 0, 1));           // 45 degree about z-axis

    // multiple matrix rotations, order is mz -> my -> mx
    mat4 mmm = mx * my * mz;
    std::cout << "m:\n" << mmm << '\n';         // compare the matrix result with the quaternion*/
}