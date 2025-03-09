// Copyright 2025 UNN-CS Team
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "tasks.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

TEST(CircleTest, Constructor) {
    Circle c(2.0);
    EXPECT_DOUBLE_EQ(2.0, c.getRadius());
    EXPECT_DOUBLE_EQ(4.0 * M_PI, c.getFerence());
    EXPECT_DOUBLE_EQ(4.0 * M_PI, c.getArea());
}

TEST(CircleTest, SetRadius) {
    Circle c(1.0);
    c.setRadius(3.0);
    EXPECT_DOUBLE_EQ(3.0, c.getRadius());
    EXPECT_DOUBLE_EQ(6.0 * M_PI, c.getFerence());
    EXPECT_DOUBLE_EQ(9.0 * M_PI, c.getArea());
}

TEST(CircleTest, SetFerence) {
    Circle c(1.0);
    c.setFerence(4.0 * M_PI);
    EXPECT_DOUBLE_EQ(2.0, c.getRadius());
    EXPECT_DOUBLE_EQ(4.0 * M_PI, c.getFerence());
    EXPECT_DOUBLE_EQ(4.0 * M_PI, c.getArea());
}

TEST(CircleTest, SetArea) {
    Circle c(1.0);
    c.setArea(16.0 * M_PI);
    EXPECT_DOUBLE_EQ(4.0, c.getRadius());
    EXPECT_DOUBLE_EQ(8.0 * M_PI, c.getFerence());
    EXPECT_DOUBLE_EQ(16.0 * M_PI, c.getArea());
}

TEST(RopeTaskTest, GapCalculation) {
    double gap = calculateRopeGap();
    const double expected = 1.0 / (2 * M_PI);
    EXPECT_NEAR(expected, gap, 1e-15);
}

TEST(PoolTaskTest, CostCalculation) {
    double cost = calculatePoolCost();
    const double expected = (7 * M_PI) * 1000 + (8 * M_PI) * 2000;
    EXPECT_DOUBLE_EQ(expected, cost);
}
