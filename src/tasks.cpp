#include "tasks.h"
#include "circle.h"

double calculateRopeGap() {
  const double earthRadius = 6378.1 * 1000;  // Convert km to meters
  Circle earth(earthRadius);
  earth.setFerence(earth.getFerence() + 1.0);
  return earth.getRadius() - earthRadius;
}

PoolCost calculatePoolCost() {
  Circle pool(3.0);
  Circle outer(4.0);  // 3m pool + 1m path

  PoolCost result;
  result.concreteCost = (outer.getArea() - pool.getArea()) * 1000.0;
  result.fenceCost = outer.getFerence() * 2000.0;

  return result;
}