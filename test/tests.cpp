#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "tasks.h"

TEST(CircleTest, Constructor) {
  Circle c(5.0);
  EXPECT_DOUBLE_EQ(5.0, c.getRadius());
  EXPECT_DOUBLE_EQ(2 * M_PI * 5.0, c.getFerence());
  EXPECT_DOUBLE_EQ(M_PI * 25.0, c.getArea());
}

TEST(CircleTest, SetRadius) {
  Circle c(0);
  c.setRadius(10);
  EXPECT_DOUBLE_EQ(10, c.getRadius());
  EXPECT_DOUBLE_EQ(2 * M_PI * 10, c.getFerence());
  EXPECT_DOUBLE_EQ(M_PI * 100, c.getArea());
}

TEST(CircleTest, SetFerence) {
  Circle c(0);
  c.setFerence(20 * M_PI);
  EXPECT_DOUBLE_EQ(10, c.getRadius());
  EXPECT_DOUBLE_EQ(20 * M_PI, c.getFerence());
  EXPECT_DOUBLE_EQ(M_PI * 100, c.getArea());
}

TEST(CircleTest, SetArea) {
  Circle c(0);
  c.setArea(100 * M_PI);
  EXPECT_DOUBLE_EQ(10, c.getRadius());
  EXPECT_DOUBLE_EQ(20 * M_PI, c.getFerence());
  EXPECT_DOUBLE_EQ(100 * M_PI, c.getArea());
}

TEST(RopeTaskTest, Gap) {
  double gap = calculateRopeGap();
  EXPECT_NEAR(1.0 / (2 * M_PI), gap, 1e-5);
}

TEST(PoolTaskTest, Costs) {
  PoolCost cost = calculatePoolCost();
  double expectedConcrete = (M_PI * (16 - 9)) * 1000;
  double expectedFence = (2 * M_PI * 4) * 2000;
  EXPECT_DOUBLE_EQ(expectedConcrete, cost.concreteCost);
  EXPECT_DOUBLE_EQ(expectedFence, cost.fenceCost);
}

TEST(CircleTest, ZeroRadius) {
  Circle c(0);
  EXPECT_DOUBLE_EQ(0, c.getRadius());
  EXPECT_DOUBLE_EQ(0, c.getFerence());
  EXPECT_DOUBLE_EQ(0, c.getArea());
}

TEST(CircleTest, NegativeRadius) {
  Circle c(-5);
  EXPECT_DOUBLE_EQ(-5, c.getRadius());
  EXPECT_DOUBLE_EQ(2 * M_PI * -5, c.getFerence());
  EXPECT_DOUBLE_EQ(M_PI * 25, c.getArea());
}

TEST(CircleTest, UpdateFromArea) {
  Circle c(0);
  c.setArea(M_PI * 25);
  EXPECT_DOUBLE_EQ(5, c.getRadius());
  EXPECT_DOUBLE_EQ(10 * M_PI, c.getFerence());
  EXPECT_DOUBLE_EQ(25 * M_PI, c.getArea());
}
