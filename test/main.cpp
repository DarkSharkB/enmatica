#include "log.hpp"
#pragma clang diagnostic ignored "-Wmicrosoft-include"

#define ENMA_IMPLEMENTATION
#include "enma.hpp"
#include "vec_test.hpp"

int32 main(int32 argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    Vec2SwizzleTests();

    vec4 v = vec4(0, 0, 4, 1);

    mat4 mx = RotationMatrixX(90);
    mat4 my = RotationMatrixY(90);
    mat4 mz = RotationMatrixZ(90);

    mat4 m = mx * my * mz;

    LOG_D(v);
    LOG_D(m);
    vec4 r = v * m;
    LOG_D(r);

    vec2 a(2, 5.4);
    LOG_D("UV: ", a.u, " ", a.v);

    int32 result = RUN_ALL_TESTS();
    system("pause");
    return result;
}