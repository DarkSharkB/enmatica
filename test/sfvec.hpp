#pragma once

#ifndef ENMA_TEST_SFVEC_HPP
#define ENMA_TEST_SFVEC_HPP

#include <gtest/gtest.h>

#define EXPECT_VEC2_EQ(v1, v2)              \
do                                          \
{                                           \
  EXPECT_FLOAT_EQ(v1.x, v2.x);              \
  EXPECT_FLOAT_EQ(v1.y, v2.y);              \
} while (0)


#define ASSERT_VEC2_EQ(v1, v2)              \
do                                          \
{                                           \
  ASSERT_FLOAT_EQ(v1.x, v2.x);              \
  ASSERT_FLOAT_EQ(v1.y, v2.y);              \
} while (0)

#define EXPECT_VEC3_EQ(v1, v2)              \
do                                          \
{                                           \
  EXPECT_FLOAT_EQ(v1.x, v2.x);              \
  EXPECT_FLOAT_EQ(v1.y, v2.y);              \
  EXPECT_FLOAT_EQ(v1.z, v2.z);              \
} while (0)


#define ASSERT_VEC3_EQ(v1, v2)              \
do                                          \
{                                           \
  ASSERT_FLOAT_EQ(v1.x, v2.x);              \
  ASSERT_FLOAT_EQ(v1.y, v2.y);              \
  ASSERT_FLOAT_EQ(v1.z, v2.z);              \
} while (0)


#define EXPECT_VEC4_EQ(v1, v2)              \
do                                          \
{                                           \
  EXPECT_FLOAT_EQ(v1.x, v2.x);              \
  EXPECT_FLOAT_EQ(v1.y, v2.y);              \
  EXPECT_FLOAT_EQ(v1.z, v2.z);              \
  EXPECT_FLOAT_EQ(v1.w, v2.w);              \
} while (0)

#define ASSERT_VEC4_EQ(v1, v2)              \
do                                          \
{                                           \
  ASSERT_FLOAT_EQ(v1.x, v2.x);              \
  ASSERT_FLOAT_EQ(v1.y, v2.y);              \
  ASSERT_FLOAT_EQ(v1.z, v2.z);              \
  ASSERT_FLOAT_EQ(v1.w, v2.w);              \
} while (0)

#endif // ENMA_TEST_SFVEC_HPP