// Copyright 2025 UNN-CS
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include "circle.h"
#include "tasks.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

TEST(CircleTest, ConstructorInitialization) {
    Circle c(5.0);
    EXPECT_DOUBLE_EQ(5.0, c.getRadius());
    EXPECT_DOUBLE_EQ(10.0 * M_PI, c.getFerence());
    EXPECT_DOUBLE_EQ(25.0 * M_PI, c.getArea());
}

TEST(CircleTest, SetRadiusToZero) {
    Circle c(1.0);
    c.setRadius(0.0);
    EXPECT_DOUBLE_EQ(0.0, c.getRadius());
    EXPECT_DOUBLE_EQ(0.0, c.getFerence());
    EXPECT_DOUBLE_EQ(0.0, c.getArea());
}

TEST(CircleTest, SetNegativeRadius) {
    Circle c(2.0);
    c.setRadius(-3.0);
    EXPECT_DOUBLE_EQ(3.0, c.getRadius());
    EXPECT_DOUBLE_EQ(6.0 * M_PI, c.getFerence());
    EXPECT_DOUBLE_EQ(9.0 * M_PI, c.getArea());
}

TEST(CircleTest, SetFerenceToZero) {
    Circle c(5.0);
    c.setFerence(0.0);
    EXPECT_DOUBLE_EQ(0.0, c.getRadius());
    EXPECT_DOUBLE_EQ(0.0, c.getFerence());
    EXPECT_DOUBLE_EQ(0.0, c.getArea());
}

TEST(CircleTest, SetAreaToLargeValue) {
    Circle c(1.0);
    c.setArea(10000.0);
    EXPECT_DOUBLE_EQ(sqrt(10000.0 / M_PI), c.getRadius());
    EXPECT_DOUBLE_EQ(2 * M_PI * sqrt(10000.0 / M_PI), c.getFerence());
}

TEST(CircleTest, MultipleRadiusChanges) {
    Circle c(2.0);
    c.setRadius(4.0);
    c.setRadius(1.0);
    EXPECT_DOUBLE_EQ(1.0, c.getRadius());
    EXPECT_DOUBLE_EQ(2.0 * M_PI, c.getFerence());
}

TEST(CircleTest, PrecisionForSmallRadius) {
    Circle c(1e-10);
    EXPECT_NEAR(2 * M_PI * 1e-10, c.getFerence(), 1e-25);
}

TEST(CircleTest, PrecisionForLargeRadius) {
    Circle c(1e10);
    EXPECT_NEAR(2 * M_PI * 1e10, c.getFerence(), 1e-5);
}

TEST(CircleTest, SetFerenceAndBackToRadius) {
    Circle c(3.0);
    double initialFerence = c.getFerence();
    c.setFerence(100.0);
    c.setRadius(c.getRadius());
    EXPECT_DOUBLE_EQ(100.0, c.getFerence());
}

TEST(CircleTest, ChainSetters) {
    Circle c(2.0);
    c.setArea(c.getArea())
     .setFerence(c.getFerence())
     .setRadius(c.getRadius());
    EXPECT_DOUBLE_EQ(2.0, c.getRadius());
}

TEST(RopeTaskTest, ZeroLengthAdded) {
    const double earthRadius = 6378.1 * 1000;
    Circle earth(earthRadius);
    earth.setFerence(earth.getFerence() + 0.0);
    EXPECT_DOUBLE_EQ(0.0, earth.getRadius() - earthRadius);
}

TEST(RopeTaskTest, NegativeLengthAdded) {
    const double earthRadius = 10.0;
    Circle earth(earthRadius);
    earth.setFerence(earth.getFerence() - 1.0);
    EXPECT_NEAR(-1.0 / (2 * M_PI), earth.getRadius() - earthRadius, 1e-10);
}

TEST(RopeTaskTest, EarthRadiusAsZero) {
    Circle earth(0.0);
    earth.setFerence(1.0);
    EXPECT_DOUBLE_EQ(1.0 / (2 * M_PI), earth.getRadius());
}

TEST(RopeTaskTest, HugeEarthRadius) {
    const double earthRadius = 1e15;
    Circle earth(earthRadius);
    earth.setFerence(earth.getFerence() + 1.0);
    EXPECT_NEAR(1.0 / (2 * M_PI), earth.getRadius() - earthRadius, 1e-5);
}

TEST(RopeTaskTest, MultipleIncrements) {
    const double earthRadius = 10.0;
    Circle earth(earthRadius);
    earth.setFerence(earth.getFerence() + 1.0);
    earth.setFerence(earth.getFerence() + 1.0);
    EXPECT_NEAR(2.0 / (2 * M_PI), earth.getRadius() - earthRadius, 1e-10);
}

TEST(PoolTaskTest, ZeroPathWidth) {
    const double poolRadius = 3.0;
    Circle pool(poolRadius);
    Circle outer(poolRadius + 0.0);
    double cost = (outer.getArea() - pool.getArea()) * 1000 +
                   outer.getFerence() * 2000;
    EXPECT_DOUBLE_EQ(0.0 * 1000 + 6 * M_PI * 2000, cost);
}

TEST(PoolTaskTest, NegativePathWidth) {
    const double poolRadius = 3.0;
    Circle pool(poolRadius);
    Circle outer(poolRadius - 1.0);
    double concreteArea = outer.getArea() - pool.getArea();
    double cost = concreteArea * 1000 + outer.getFerence() * 2000;
    EXPECT_LT(cost, 0);
}

TEST(PoolTaskTest, DifferentPoolRadius) {
    const double poolRadius = 5.0;
    const double pathWidth = 1.0;
    Circle pool(poolRadius);
    Circle outer(poolRadius + pathWidth);
    double expected = (M_PI * 36 - M_PI * 25) * 1000 + (12 * M_PI) * 2000;
    EXPECT_DOUBLE_EQ(expected, (outer.getArea() - pool.getArea()) * 1000
                                + outer.getFerence() * 2000);
}

TEST(PoolTaskTest, LargePathWidth) {
    const double poolRadius = 3.0;
    const double pathWidth = 100.0;
    Circle outer(poolRadius + pathWidth);
    double expectedConcrete = (M_PI * pow(103, 2) - M_PI * 9) * 1000;
    double expectedFence = 2 * M_PI * 103 * 2000;
    EXPECT_NEAR(expectedConcrete + expectedFence, calculatePoolCost(), 1e-5);
}

TEST(PoolTaskTest, CostWithPrecision) {
    double cost = calculatePoolCost();
    double expectedConcrete = M_PI*(16 - 9)*1000;
    double expectedFence = 8*M_PI*2000;
    EXPECT_DOUBLE_EQ(expectedConcrete + expectedFence, cost);
}

TEST(EdgeCaseTest, MaxDoubleValues) {
    Circle c(std::numeric_limits<double>::max());
    EXPECT_DOUBLE_EQ(2 * M_PI * std::numeric_limits<double>::max(),
                     c.getFerence());
}

TEST(EdgeCaseTest, MinPositiveRadius) {
    Circle c(std::numeric_limits<double>::min());
    EXPECT_DOUBLE_EQ(2 * M_PI * std::numeric_limits<double>::min(),
                     c.getFerence());
}

TEST(ConsistencyTest, AllSetters) {
    Circle c(2.0);
    c.setRadius(3.0);
    c.setFerence(c.getFerence());
    c.setArea(c.getArea());
    EXPECT_DOUBLE_EQ(3.0, c.getRadius());
}
