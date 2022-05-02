#ifndef PROBLEM
#define PROBLEM

#include <vector>
#include <iostream>
#include <set>
#include <climits>
#include "vehicle.h"

class Problem {
 public:
  Problem(std::vector<std::vector<int>> distanceMatrix, int nClients, int nVehicles);
  Problem() = default;
  void print();
  std::vector<std::vector<int>> distanceMatrix_;
  int nClients_, nVehicles_;
  std::set<int> nodes_;
  std::vector<Car> vehicles_;
};

#endif