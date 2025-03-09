#ifndef TASKS_H_
#define TASKS_H_

struct PoolCost {
  double concreteCost;
  double fenceCost;
};

double calculateRopeGap();
PoolCost calculatePoolCost();

#endif  // TASKS_H_