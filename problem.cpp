#include "problem.h"

Problem::Problem(std::vector<std::vector<int>> distanceMatrix, int nClients, int nVehicles) {
  distanceMatrix_ = distanceMatrix;
  nClients_ = nClients;
  nVehicles_ = nVehicles;
  vehicles_.resize(nVehicles_);
  for (int i = 0; i < nVehicles_; i++) {
    vehicles_[i].tour.push_back(0);
  }
  for (int i = 0; i <= nClients; i++) {
    nodes_.insert(i);
  }
}

void Problem::print() {
  for (int i = 0; i < distanceMatrix_.size(); i++) {
    for (int j = 0; j < distanceMatrix_.size(); j++) {
      std::cout << distanceMatrix_[i][j] << " ";
    }
    std::cout << "\n";
  }
}