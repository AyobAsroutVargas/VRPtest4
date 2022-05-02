#ifndef GREEDY_VRP_
#define GREEDY_VRP_

#include <vector>
#include <set>
#include <climits>
#include "vehicle.h"
#include "problem.h"

class GreedyVrp {
 public:
  GreedyVrp(Problem problem);
  std::vector<std::vector<int>> Solve();
  int getClosestNode(int carIndex);
  Problem problem_;
};

#endif