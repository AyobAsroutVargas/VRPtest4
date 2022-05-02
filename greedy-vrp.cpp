#include "greedy-vrp.h"

GreedyVrp::GreedyVrp(Problem problem) {
  problem_ = problem;
}

int GreedyVrp::getClosestNode(int carIndex){
  int minDistance = INT_MAX;
  int bestNodeIndex;

  for (int nodeIndex = 1; nodeIndex <= problem_.nClients_; nodeIndex++) {
    if (problem_.nodes_.count(nodeIndex)) {
      int currentIndex = problem_.vehicles_[carIndex].tour.size() - 1;
      int tmpDistance = problem_.distanceMatrix_[problem_.vehicles_[carIndex].tour[currentIndex]][nodeIndex];
      if (tmpDistance < minDistance) {
        minDistance = tmpDistance;
        bestNodeIndex = nodeIndex;
      }
    }
  }
  return bestNodeIndex;
}

std::vector<std::vector<int>> GreedyVrp::Solve() {
  std::vector<std::vector<int>> solution;
  int carIndex = 0;

  while (problem_.nodes_.size() != 1) {
    int currentIndex = problem_.vehicles_[carIndex].tour.size() - 1;
    int bestNodeIndex = getClosestNode(carIndex);

    problem_.vehicles_[carIndex].tour.push_back(bestNodeIndex);
    problem_.nodes_.erase(bestNodeIndex);
    carIndex = (carIndex + 1) % problem_.nVehicles_;
  }

  for (int i = 0; i < problem_.nVehicles_; i++) {
    problem_.vehicles_[i].tour.push_back(0);
    solution.push_back(problem_.vehicles_[i].tour);
  }

  return solution;
}