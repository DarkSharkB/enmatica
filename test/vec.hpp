#include "enma.hpp"
#include "gtest/gtest.h"
#include <cmath>

#define EXPECT_VEC2_EQ(v1, v2)              \
do                                          \
{                                           \
    EXPECT_FLOAT_EQ(v1.x, v2.x);            \
    EXPECT_FLOAT_EQ(v1.y, v2.y);            \
} while (0)


#define ASSERT_VEC2_EQ(v1, v2)              \
do                                          \
{                                           \
    ASSERT_FLOAT_EQ(v1.x, v2.x);            \
    ASSERT_FLOAT_EQ(v1.y, v2.y);            \
} while (0)

#define EXPECT_VEC3_EQ(v1, v2)              \
do                                          \
{                                           \
    EXPECT_FLOAT_EQ(v1.x, v2.x);            \
    EXPECT_FLOAT_EQ(v1.y, v2.y);            \
    EXPECT_FLOAT_EQ(v1.z, v2.z);            \
} while (0)


#define ASSERT_VEC3_EQ(v1, v2)              \
do                                          \
{                                           \
    ASSERT_FLOAT_EQ(v1.x, v2.x);            \
    ASSERT_FLOAT_EQ(v1.y, v2.y);            \
    ASSERT_FLOAT_EQ(v1.z, v2.z);            \
} while (0)


#define EXPECT_VEC4_EQ(v1, v2)              \
do                                          \
{                                           \
    EXPECT_FLOAT_EQ(v1.x, v2.x);            \
    EXPECT_FLOAT_EQ(v1.y, v2.y);            \
    EXPECT_FLOAT_EQ(v1.z, v2.z);            \
    EXPECT_FLOAT_EQ(v1.w, v2.w);            \
} while (0)

#define ASSERT_VEC4_EQ(v1, v2)              \
do                                          \
{                                           \
    ASSERT_FLOAT_EQ(v1.x, v2.x);            \
    ASSERT_FLOAT_EQ(v1.y, v2.y);            \
    ASSERT_FLOAT_EQ(v1.z, v2.z);            \
    ASSERT_FLOAT_EQ(v1.w, v2.w);            \
} while (0)

void Vec2Assign()
{
    vec2 v1(4, 1);
    vec2 v2(2, 20);

    vec2 expectResult1(4, 1);
    vec2 expectResult2(2, 20);

    vec2 actualResult1 = v1;
    vec2 actualResult2 = v2;

    EXPECT_VEC2_EQ(actualResult1, expectResult1);
    EXPECT_VEC2_EQ(actualResult2, expectResult2);
    LOG_D("Test Successful: vec2 Assignment");
}

void Vec2Add()
{
    vec2 v1(4, 1);
    vec2 v2(2, 20);
    vec2 expectResult1(6, 21);
    vec2 expectResult2(14, 11);

    vec2 actualResult1 = v1 + v2;
    vec2 actualResult2 = v1 + 10;
    v1 += v2;

    EXPECT_VEC2_EQ(actualResult1, expectResult1);
    EXPECT_VEC2_EQ(actualResult2, expectResult2);
    EXPECT_VEC2_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec2 Addition");
}

void Vec2Sub()
{
    vec2 v1(4, 1);
    vec2 v2(2, 20);
    vec2 expectResult1(2, -19);
    vec2 expectResult2(0, -3);

    vec2 actualResult1 = v1 - v2;
    vec2 actualResult2 = v1 - 4;
    v1 -= v2;

    EXPECT_VEC2_EQ(actualResult1, expectResult1);
    EXPECT_VEC2_EQ(actualResult2, expectResult2);
    EXPECT_VEC2_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec2 Subtraction");
}

void Vec2Mul()
{
    vec2 v1(4, 2);
    vec2 v2(2, 20);
    vec2 expectResult1(8, 40);

    vec2 actualResult1 = v1 * v2;
    v1 *= v2;

    EXPECT_VEC2_EQ(actualResult1, expectResult1);
    EXPECT_VEC2_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec2 Multiplication");
}

void Vec2Div()
{
    vec2 v1(4, 1);
    vec2 v2(2, 20);
    vec2 expectResult1(2, 0.05);

    vec2 actualResult1 = v1 / v2;
    v1 /= v2;

    EXPECT_VEC2_EQ(actualResult1, expectResult1);
    EXPECT_VEC2_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec2 Division");
}

void Vec2ArithmeticTests()
{
    Vec2Add();
    Vec2Sub();
    Vec2Mul();
    Vec2Div();
}

void Vec2SwizzleTests()
{
    vec2 v(3.0f, 8.0f);

    LOG_D(v.xy);
    LOG_D(v.yx);

    v.yx = vec2(9.0f, 2.0f);
    //LOG_D(v.xx);
    //LOG_D(v.xxx);
    LOG_D(v);
    //LOG_D(v.yyy);
    //LOG_D(v.xyyx);
    v.xy = vec3(3, 2, 1);

    //v += 2;
    LOG_D(v.rg);
}

void Vec2Tests()
{
    Vec2Assign();
    Vec2ArithmeticTests();
    Vec2SwizzleTests();
}

TEST(vec2, Assignment)
{
    Vec2Assign();
}

TEST(vec2, Arithmetic_Addition)
{
    Vec2Add();
}

TEST(vec2, Arithmetic_Subtraction)
{
    Vec2Sub();
}

TEST(vec2, Arithmetic_Multiplication)
{
    Vec2Mul();
}

TEST(vec2, Arithmetic_Division)
{
    Vec2Div();
}

void Vec3Assign()
{
    vec3 v1(4, 1, 112);
    vec3 v2(2, 20, 34);

    vec3 expectResult1 = v1;
    vec3 expectResult2 = v2;

    EXPECT_VEC3_EQ(v1, expectResult1);
    EXPECT_VEC3_EQ(v2, expectResult2);
    LOG_D("Test Successful: vec3 Assignment");
}

void Vec3Add()
{
    vec3 v1(4, 1, -4);
    vec3 v2(2, 20, -6);
    vec3 expectResult1(6, 21, -10);
    vec3 expectResult2(14, 11, 6);

    vec3 actualResult1 = v1 + v2;
    vec3 actualResult2 = v1 + 10;
    v1 += v2;

    EXPECT_VEC3_EQ(actualResult1, expectResult1);
    EXPECT_VEC3_EQ(actualResult2, expectResult2);
    EXPECT_VEC3_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec3 Addition");
}

void Vec3Sub()
{
    vec3 v1(4, 1, -4);
    vec3 v2(2, 20, -6);
    vec3 expectResult1(2, -19, 2);
    vec3 expectResult2(0, -3, -8);

    vec3 actualResult1 = v1 - v2;
    vec3 actualResult2 = v1 - 4;
    v1 -= v2;

    EXPECT_VEC3_EQ(actualResult1, expectResult1);
    EXPECT_VEC3_EQ(actualResult2, expectResult2);
    EXPECT_VEC3_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec3 Subtraction");
}

void Vec3Mul()
{
    vec3 v1(4, 2,-9);
    vec3 v2(2, 20, 8);
    vec3 expectResult1(8, 40, -72);

    vec3 actualResult1 = v1 * v2;
    v1 *= v2;

    EXPECT_VEC3_EQ(actualResult1, expectResult1);
    EXPECT_VEC3_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec3 Multiplication");
}

void Vec3Div()
{
    vec3 v1(4, 1, -4);
    vec3 v2(2, 20, 5);
    vec3 expectResult1(2, 0.05, -0.8);

    vec3 actualResult1 = v1 / v2;
    v1 /= v2;

    EXPECT_VEC3_EQ(actualResult1, expectResult1);
    EXPECT_VEC3_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec3 Division");
}

void Vec3Lerp()
{
    vec3 v1(1, 2, 3);
    vec3 v2(2, 6, 4);

    vec3 v12mid(1.5, 4, 3.5);

    EXPECT_VEC3_EQ(v1, Lerp(v1, v2, 0.0f));
    EXPECT_VEC3_EQ(v12mid, Lerp(v1, v2, 0.5f));
    EXPECT_VEC3_EQ(v2, Lerp(v1, v2, 1.0f));
}

void Vec3ArithmeticTests()
{
    Vec3Add();
    Vec3Sub();
    Vec3Mul();
    Vec3Div();
}

void Vec3Tests()
{
    Vec3Assign();
    Vec3ArithmeticTests();
}

TEST(vec3, Assignment)
{
    Vec3Assign();
}

TEST(vec3, Arithmetic_Addition)
{
    Vec3Add();
}

TEST(vec3, Arithmetic_Subtraction)
{
    Vec3Sub();
}

TEST(vec3, Arithmetic_Multiplication)
{
    Vec3Mul();
}

TEST(vec3, Arithmetic_Division)
{
    Vec3Div();
}

TEST(vec3, Linear_Interpolation)
{
    Vec3Lerp();
}

void Vec4Assign()
{
    vec4 v1(4, 1, 112);
    vec4 v2(2, 20, 34);

    vec4 expectResult1 = v1;
    vec4 expectResult2 = v2;

    EXPECT_VEC4_EQ(v1, expectResult1);
    EXPECT_VEC4_EQ(v2, expectResult2);
    LOG_D("Test Successful: vec4 Assignment");
}

void Vec4Add()
{
    vec4 v1(4, 1, -4, -14.2);
    vec4 v2(2, 20, -6, 4.5);
    vec4 expectResult1(6, 21, -10, -9.7);
    vec4 expectResult2(14, 11, 6, -4.2);

    vec4 actualResult1 = v1 + v2;
    vec4 actualResult2 = v1 + 10;
    v1 += v2;

    EXPECT_VEC4_EQ(actualResult1, expectResult1);
    EXPECT_VEC4_EQ(actualResult2, expectResult2);
    EXPECT_VEC4_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec4 Addition");
}

void Vec4Sub()
{
    vec4 v1(4, 1, -4, 2);
    vec4 v2(2, 20, -6, 3);
    vec4 expectResult1(2, -19, 2, -1);
    vec4 expectResult2(0, -3, -8, -2);

    vec4 actualResult1 = v1 - v2;
    vec4 actualResult2 = v1 - 4;
    v1 -= v2;

    EXPECT_VEC4_EQ(actualResult1, expectResult1);
    EXPECT_VEC4_EQ(actualResult2, expectResult2);
    EXPECT_VEC4_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec4 Subtraction");
}

void Vec4Mul()
{
    vec4 v1(4, 2,-9, 1000);
    vec4 v2(2, 20, 8, 20);
    vec4 expectResult1(8, 40, -72, 20000);

    vec4 actualResult1 = v1 * v2;
    v1 *= v2;

    EXPECT_VEC4_EQ(actualResult1, expectResult1);
    EXPECT_VEC4_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec4 Multiplication");
}

void Vec4Div()
{
    vec4 v1(4, 1, -4, 0.2);
    vec4 v2(2, 20, 5, 100);
    vec4 expectResult1(2, 0.05, -0.8, 0.002);

    vec4 actualResult1 = v1 / v2;
    v1 /= v2;

    EXPECT_VEC4_EQ(actualResult1, expectResult1);
    EXPECT_VEC4_EQ(v1, expectResult1);
    LOG_D("Test Successful: vec4 Division");
}

void Vec4Lerp()
{
    vec4 v1(1, 2, 3, 5);
    vec4 v2(2, 6, 4, 2);

    vec4 v12mid(1.5, 4, 3.5, 3.5);

    EXPECT_VEC4_EQ(v1, Lerp(v1, v2, 0.0f));
    EXPECT_VEC4_EQ(v12mid, Lerp(v1, v2, 0.5f));
    EXPECT_VEC4_EQ(v2, Lerp(v1, v2, 1.0f));
}

void Vec4ArithmeticTests()
{
    Vec4Add();
    Vec4Sub();
    Vec4Mul();
    Vec4Div();
}

void Vec4Tests()
{
    Vec4Assign();
    Vec4ArithmeticTests();
}

TEST(vec4, Assignment)
{
    Vec4Assign();
}

TEST(vec4, Arithmetic_Addition)
{
    Vec4Add();
}

TEST(vec4, Arithmetic_Subtraction)
{
    Vec4Sub();
}

TEST(vec4, Arithmetic_Multiplication)
{
    Vec4Mul();
}

TEST(vec4, Arithmetic_Division)
{
    Vec4Div();
}

TEST(vec4, Linear_Interpolation)
{
    Vec4Lerp();
}

void AllTests()
{
    Vec2Tests();
    Vec3Tests();
    Vec4Tests();
}