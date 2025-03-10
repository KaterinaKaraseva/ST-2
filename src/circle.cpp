// Copyright 2022 UNN-CS
#define _USE_MATH_DEFINES
#include <cmath>
#include "circle.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Circle::Circle(double r) {
    setRadius(r);
}

Circle& Circle::setRadius(double r) {
    radius = fabs(r);
    ference = 2 * M_PI * radius;
    area = M_PI * radius * radius;
    return *this;
}

Circle& Circle::setFerence(double f) {
    ference = f;
    radius = f / (2 * M_PI);
    area = M_PI * radius * radius;
    return *this;
}

Circle& Circle::setArea(double a) {
    area = a;
    radius = sqrt(a / M_PI);
    ference = 2 * M_PI * radius;
    return *this;
}

double Circle::getRadius() const { return radius; }
double Circle::getFerence() const { return ference; }
double Circle::getArea() const { return area; }
