// Copyright 2022 UNN-CS
#define _USE_MATH_DEFINES
#include <cmath>
#include "tasks.h"
#include "circle.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculateRopeGap(double earthRadius) {
    Circle earth(earthRadius);
    earth.setFerence(earth.getFerence() + 1.0);
    return earth.getRadius() - earthRadius;
}

double calculatePoolCost(double poolRadius, double pathWidth) {
    const double outerRadius = poolRadius + pathWidth;
    Circle pool(poolRadius);
    Circle outer(outerRadius);
    double concreteArea = outer.getArea() - pool.getArea();
    double fenceLength = outer.getFerence();
    return concreteArea * 1000 + fenceLength * 2000;
}
