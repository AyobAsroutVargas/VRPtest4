#include "solution.h"

Solution::Solution(std::vector<std::vector<int>> solution, std::vector<std::vector<int>> distanceMatrix) {
  solution_ = solution;
  distanceMatrix_ = distanceMatrix;
}

int Solution::routeDistance(std::vector<int> route) {
  int distance = 0;
  for ( int i = 0; i+1 < route.size(); i++) {
    distance += distanceMatrix_[route[i]][route[i + 1]];
  }
  return distance;
}

int Solution::tourDistance() {
  int distance = 0;

  for (int i = 0; i < solution_.size(); i++) {
    distance += routeDistance(solution_[i]);
  }
  cost = distance;
  return distance;
}

void Solution::print() {
  for (int i = 0; i < solution_.size(); i++) {
    std::cout << "  Ruta " << i << ":(coste: " << routeDistance(solution_[i]) << ")" << "\n";
    for (int j = 0; j < solution_[i].size(); j++) {
      std::cout << "  " << solution_[i][j] << ", ";
    }
    std::cout << "\n";
  }
  std::cout << "  Tour distance: " << tourDistance() << "\n";
}