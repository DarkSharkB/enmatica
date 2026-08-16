#include "sfvec.hpp"

#include "log.hpp"
#include <enma.hpp>

#ifdef ENMA_ENABLE_NS
using namespace enma;
#endif

void Vec2Assign()
{
  sfvec2 v1(4, 1);
  sfvec2 v2(2, 20);

  sfvec2 expectResult1(4, 1);
  sfvec2 expectResult2(2, 20);

  sfvec2 actualResult1 = v1;
  sfvec2 actualResult2 = v2;

  EXPECT_VEC2_EQ(actualResult1, expectResult1);
  EXPECT_VEC2_EQ(actualResult2, expectResult2);
  LOG_D("Test Successful: sfvec2 Assignment");
}

void Vec2Add()
{
  sfvec2 v1(4, 1);
  sfvec2 v2(2, 20);
  sfvec2 expectResult1(6, 21);
  sfvec2 expectResult2(14, 11);

  sfvec2 actualResult1 = v1 + v2;
  sfvec2 actualResult2 = v1 + 10;
  v1 += v2;

  EXPECT_VEC2_EQ(actualResult1, expectResult1);
  EXPECT_VEC2_EQ(actualResult2, expectResult2);
  EXPECT_VEC2_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec2 Addition");
}

void Vec2Sub()
{
  sfvec2 v1(4, 1);
  sfvec2 v2(2, 20);
  sfvec2 expectResult1(2, -19);
  sfvec2 expectResult2(0, -3);

  sfvec2 actualResult1 = v1 - v2;
  sfvec2 actualResult2 = v1 - 4;
  v1 -= v2;

  EXPECT_VEC2_EQ(actualResult1, expectResult1);
  EXPECT_VEC2_EQ(actualResult2, expectResult2);
  EXPECT_VEC2_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec2 Subtraction");
}

void Vec2Mul()
{
  sfvec2 v1(4, 2);
  sfvec2 v2(2, 20);
  sfvec2 expectResult1(8, 40);

  sfvec2 actualResult1 = v1 * v2;
  v1 *= v2;

  EXPECT_VEC2_EQ(actualResult1, expectResult1);
  EXPECT_VEC2_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec2 Multiplication");
}

void Vec2Div()
{
  sfvec2 v1(4, 1);
  sfvec2 v2(2, 20);
  sfvec2 expectResult1(2, 0.05);

  sfvec2 actualResult1 = v1 / v2;
  v1 /= v2;

  EXPECT_VEC2_EQ(actualResult1, expectResult1);
  EXPECT_VEC2_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec2 Division");
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
  sfvec2 v(3.0f, 8.0f);

  LOG_D(v.xy);
  LOG_D(v.yx);

  v.yx = sfvec2(9.0f, 2.0f);
  //LOG_D(v.xx);
  //LOG_D(v.xxx);
  LOG_D(v);
  //LOG_D(v.yyy);
  //LOG_D(v.xyyx);
  v.xy = sfvec2(sfvec3(3, 2, 1));

  //v += 2;
  LOG_D(v.rg);
}

void Vec2Tests()
{
  Vec2Assign();
  Vec2ArithmeticTests();
  Vec2SwizzleTests();
}

TEST(sfvec2, Assignment)
{
  Vec2Assign();
}

TEST(sfvec2, Arithmetic_Addition)
{
  Vec2Add();
}

TEST(sfvec2, Arithmetic_Subtraction)
{
  Vec2Sub();
}

TEST(sfvec2, Arithmetic_Multiplication)
{
  Vec2Mul();
}

TEST(sfvec2, Arithmetic_Division)
{
  Vec2Div();
}

void Vec3Assign()
{
  sfvec3 v1(4, 1, 112);
  sfvec3 v2(2, 20, 34);

  sfvec3 expectResult1 = v1;
  sfvec3 expectResult2 = v2;

  EXPECT_VEC3_EQ(v1, expectResult1);
  EXPECT_VEC3_EQ(v2, expectResult2);
  LOG_D("Test Successful: sfvec3 Assignment");
}

void Vec3Add()
{
  sfvec3 v1(4, 1, -4);
  sfvec3 v2(2, 20, -6);
  sfvec3 expectResult1(6, 21, -10);
  sfvec3 expectResult2(14, 11, 6);

  sfvec3 actualResult1 = v1 + v2;
  sfvec3 actualResult2 = v1 + 10;
  v1 += v2;

  EXPECT_VEC3_EQ(actualResult1, expectResult1);
  EXPECT_VEC3_EQ(actualResult2, expectResult2);
  EXPECT_VEC3_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec3 Addition");
}

void Vec3Sub()
{
  sfvec3 v1(4, 1, -4);
  sfvec3 v2(2, 20, -6);
  sfvec3 expectResult1(2, -19, 2);
  sfvec3 expectResult2(0, -3, -8);

  sfvec3 actualResult1 = v1 - v2;
  sfvec3 actualResult2 = v1 - 4;
  v1 -= v2;

  EXPECT_VEC3_EQ(actualResult1, expectResult1);
  EXPECT_VEC3_EQ(actualResult2, expectResult2);
  EXPECT_VEC3_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec3 Subtraction");
}

void Vec3Mul()
{
  sfvec3 v1(4, 2,-9);
  sfvec3 v2(2, 20, 8);
  sfvec3 expectResult1(8, 40, -72);

  sfvec3 actualResult1 = v1 * v2;
  v1 *= v2;

  EXPECT_VEC3_EQ(actualResult1, expectResult1);
  EXPECT_VEC3_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec3 Multiplication");
}

void Vec3Div()
{
  sfvec3 v1(4, 1, -4);
  sfvec3 v2(2, 20, 5);
  sfvec3 expectResult1(2, 0.05, -0.8);

  sfvec3 actualResult1 = v1 / v2;
  v1 /= v2;

  EXPECT_VEC3_EQ(actualResult1, expectResult1);
  EXPECT_VEC3_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec3 Division");
}

void Vec3Lerp()
{
  sfvec3 v1(1, 2, 3);
  sfvec3 v2(2, 6, 4);

  sfvec3 v12mid(1.5, 4, 3.5);

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

TEST(sfvec3, Assignment)
{
  Vec3Assign();
}

TEST(sfvec3, Arithmetic_Addition)
{
  Vec3Add();
}

TEST(sfvec3, Arithmetic_Subtraction)
{
  Vec3Sub();
}

TEST(sfvec3, Arithmetic_Multiplication)
{
  Vec3Mul();
}

TEST(sfvec3, Arithmetic_Division)
{
  Vec3Div();
}

TEST(sfvec3, Linear_Interpolation)
{
  Vec3Lerp();
}

void Vec4Assign()
{
  sfvec4 v1(4.2f, 1.0f, 112.0f);
  sfvec4 v2(2.0, 20.0f, 34.0f, 2.0f);

  sfvec4 expectResult1 = v1;
  sfvec4 expectResult2 = v2;

  EXPECT_VEC4_EQ(v1, expectResult1);
  EXPECT_VEC4_EQ(v2, expectResult2);
  LOG_D("Test Successful: sfvec4 Assignment");
}

void Vec4Add()
{
  sfvec4 v1(4.0f, 1.0f, -4.0f, -14.2f);
  sfvec4 v2(2.0f, 20.0f, -6.0f, 4.5f);
  sfvec4 expectResult1(6.0f, 21.0f, -10.0f, -9.7f);
  sfvec4 expectResult2(14.0f, 11.0f, 6.0f, -4.2f);

  sfvec4 actualResult1 = v1 + v2;
  sfvec4 actualResult2 = v1 + 10.0f;
  v1 += v2;

  EXPECT_VEC4_EQ(actualResult1, expectResult1);
  EXPECT_VEC4_EQ(actualResult2, expectResult2);
  EXPECT_VEC4_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec4 Addition");
}

void Vec4Sub()
{
  sfvec4 v1(4.0f, 1.0f, -4.0f, 2.0f);
  sfvec4 v2(2.0f, 20.0f, -6.0f, 3.0f);
  sfvec4 expectResult1(2.0f, -19.0f, 2.0f, -1.0f);
  sfvec4 expectResult2(0.0f, -3.0f, -8.0f, -2.0f);

  sfvec4 actualResult1 = v1 - v2;
  sfvec4 actualResult2 = v1 - 4.0f;
  v1 -= v2;

  EXPECT_VEC4_EQ(actualResult1, expectResult1);
  EXPECT_VEC4_EQ(actualResult2, expectResult2);
  EXPECT_VEC4_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec4 Subtraction");
}

void Vec4Mul()
{
  sfvec4 v1(4.0f, 2.0f,-9.0f, 1000.0f);
  sfvec4 v2(2.0f, 20.0f, 8.0f, 20.0f);
  sfvec4 expectResult1(8.0f, 40.0f, -72.0f, 20000.0f);

  sfvec4 actualResult1 = v1 * v2;
  v1 *= v2;

  EXPECT_VEC4_EQ(actualResult1, expectResult1);
  EXPECT_VEC4_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec4 Multiplication");
}

void Vec4Div()
{
  sfvec4 v1(4.0f, 1.0f, -4.0f, 0.2f);
  sfvec4 v2(2.0f, 20.0f, 5.0f, 100.0f);
  sfvec4 expectResult1(2.0f, 0.05f, -0.8f, 0.002f);

  sfvec4 actualResult1 = v1 / v2;
  v1 /= v2;

  EXPECT_VEC4_EQ(actualResult1, expectResult1);
  EXPECT_VEC4_EQ(v1, expectResult1);
  LOG_D("Test Successful: sfvec4 Division");
}

void Vec4Normalise()
{
  sfvec4 v(3.0f, 0.0f, 4.0f, 0.0f); // length = 5
  sfvec4 expected(0.6f, 0.0f, 0.8f, 0.0f);

  EXPECT_VEC4_EQ(expected, Normalise(v));

  // also test member function
  sfvec4 v2(3.0f, 0.0f, 4.0f, 0.0f);
  v2.Normalise();
  EXPECT_VEC4_EQ(expected, v2);
}

void Vec4Dot()
{
  sfvec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
  sfvec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

  flt32 expected = 1.0f*5.0f + 2.0f*6.0f + 3.0f*7.0f + 4.0f*8.0f; // 70

  EXPECT_FLOAT_EQ(expected, Dot(v1, v2));
  EXPECT_FLOAT_EQ(expected, v1.Dot(v2));
}

void Vec4Distance()
{
  sfvec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
  sfvec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

  // distance = sqrt((4)^2 + (4)^2 + (4)^2 + (4)^2) = sqrt(64) = 8
  flt32 expected = 8.0f;

  EXPECT_FLOAT_EQ(expected, Distance(v1, v2));
  EXPECT_FLOAT_EQ(expected, v1.Distance(v2));
}

void Vec4Lerp()
{
  sfvec4 v1(1.0f, 2.0f, 3.0f, 5.0f);
  sfvec4 v2(2.0f, 6.0f, 4.0f, 2.0f);

  sfvec4 v12mid(1.5f, 4.0f, 3.5f, 3.5f);

  EXPECT_VEC4_EQ(v1, Lerp(v1, v2, 0.0f));
  EXPECT_VEC4_EQ(v12mid, Lerp(v1, v2, 0.5f));
  EXPECT_VEC4_EQ(v2, Lerp(v1, v2, 1.0f));
}

void Vec4Normalise_Zero()
{
  sfvec4 v(0.0f, 0.0f, 0.0f, 0.0f);

  sfvec4 result = Normalise(v);

  EXPECT_VEC4_EQ(sfvec4(0.0f, 0.0f, 0.0f, 0.0f), result);
}

void Vec4Dot_Negative()
{
  sfvec4 v1(-1.0f, 2.0f, -3.0f, 4.0f);
  sfvec4 v2(5.0f, -6.0f, 7.0f, -8.0f);

  flt32 expected = -1.0f*5.0f + 2.0f*(-6.0f) + -3.0f*7.0f + 4.0f*(-8.0f);

  EXPECT_FLOAT_EQ(expected, Dot(v1, v2));
}

void Vec4Distance_Symmetry()
{
  sfvec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
  sfvec4 v2(5.0f, 6.0f, 7.0f, 8.0f);

  EXPECT_FLOAT_EQ(Distance(v1, v2), Distance(v2, v1));
}

void Vec4Lerp_Extrapolation()
{
  sfvec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
  sfvec4 v2(2.0f, 4.0f, 6.0f, 8.0f);

  // t > 1
  sfvec4 expected1(3.0f, 6.0f, 9.0f, 12.0f);
  EXPECT_VEC4_EQ(expected1, Lerp(v1, v2, 2.0f));

  // t < 0
  sfvec4 expected2(0.0f, 0.0f, 0.0f, 0.0f);
  EXPECT_VEC4_EQ(expected2, Lerp(v1, v2, -1.0f));
}

TEST(sfvec4, Assignment)
{
  Vec4Assign();
}

TEST(sfvec4, Arithmetic_Addition)
{
  Vec4Add();
}

TEST(sfvec4, Arithmetic_Subtraction)
{
  Vec4Sub();
}

TEST(sfvec4, Arithmetic_Multiplication)
{
  Vec4Mul();
}

TEST(sfvec4, Arithmetic_Division)
{
  Vec4Div();
}

TEST(sfvec4, Normalisation)
{
  Vec4Normalise();
}

TEST(sfvec4, Dot_Product)
{
  Vec4Dot();
}

TEST(sfvec4, Distance)
{
  Vec4Distance();
}

TEST(sfvec4, Linear_Interpolation)
{
  Vec4Lerp();
}

TEST(sfvec4, Normalisation_Zero)
{
  Vec4Normalise_Zero();
}

TEST(sfvec4, Dot_Product_Negative)
{
  Vec4Dot_Negative();
}

TEST(sfvec4, Distance_Symmetry)
{
  Vec4Distance_Symmetry();
}

TEST(sfvec4, Linear_Interpolation_Extrapolation)
{
  Vec4Lerp_Extrapolation();
}