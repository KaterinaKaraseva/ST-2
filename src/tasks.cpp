// Copyright 2022 UNN-CS
#define _USE_MATH_DEFINES
#include <cmath>
#include "tasks.h"
#include "circle.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculateRopeGap() {
    const double earthRadius = 6378.1 * 1000;
    Circle earth(earthRadius);
    earth.setFerence(earth.getFerence() + 1.0);
    return earth.getRadius() - earthRadius;
}

double calculatePoolCost() {
    const double poolRadius = 3.0;
    const double pathWidth = 1.0;
    const double outerRadius = poolRadius + pathWidth;

    Circle pool(poolRadius);
    Circle outer(outerRadius);

    double concreteArea = outer.getArea() - pool.getArea();
    double fenceLength = outer.getFerence();

    return concreteArea * 1000 + fenceLength * 2000;
}
