#ifndef SOLUTION
#define SOLUTION

#include <vector>
#include <iostream>

class Solution {
 public:
  Solution(std::vector<std::vector<int>> solution, std::vector<std::vector<int>> distanceMatrix);
  std::vector<std::vector<int>> solution_;
  int routeDistance(std::vector<int> route);
  int tourDistance();
  void print();
  int cost;
  std::vector<std::vector<int>> distanceMatrix_;
};

#endif