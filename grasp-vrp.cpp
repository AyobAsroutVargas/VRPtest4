#include "grasp-vrp.h"

GraspVrp::GraspVrp(Problem problem, EnviromentStructure* localSearch, int maxClients) {
  problem_ = problem;
  localSearch_ = localSearch;
  maxClients_ = maxClients;
}

int GraspVrp::getClosestNode(int carIndex, std::set<int>& tempNodes){
  int minDistance = INT_MAX;
  int bestNodeIndex;

  for (int nodeIndex = 1; nodeIndex <= problem_.nClients_; nodeIndex++) {
    if (tempNodes.count(nodeIndex)) {
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

int GraspVrp::selectFromRCL(int carIndex, std::set<int>& tempNodes) {
  std::vector<int> rcl;
  struct timeval time;
  gettimeofday(&time,NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
  int nodesSize =  tempNodes.size() - 1;
  for (int i = 0; i < 3 && i < nodesSize ; i++) {
    int closestNode = getClosestNode(carIndex, tempNodes);
    rcl.push_back(closestNode);
    tempNodes.erase(closestNode);
  }
  int randIndex = rand() % rcl.size();
  int returnResult = rcl[randIndex];
  for (int i = 0; i < rcl.size(); i++) {
    if (i != randIndex) {
      tempNodes.insert(rcl[i]);
    }
  }
  return returnResult;
}
 

std::vector<std::vector<int>> GraspVrp::constructSolution(){
  std::vector<std::vector<int>> solution;
  int carIndex = 0;
  std::set<int> tempNodes = problem_.nodes_;

  while (tempNodes.size() != 1) {
    int currentIndex = problem_.vehicles_[carIndex].tour.size() - 1;
    int bestNodeIndex = selectFromRCL(carIndex, tempNodes);

    problem_.vehicles_[carIndex].tour.push_back(bestNodeIndex);
    tempNodes.erase(bestNodeIndex);
    carIndex = (carIndex + 1) % problem_.nVehicles_;
  }

  for (int i = 0; i < problem_.nVehicles_; i++) {
    problem_.vehicles_[i].tour.push_back(0);
    solution.push_back(problem_.vehicles_[i].tour);
    problem_.vehicles_[i].tour.clear();
    problem_.vehicles_[i].tour.push_back(0);
  }
  
  return solution;
}

std::vector<std::vector<int>> GraspVrp::generateInitialSolution() {
  int noUpgradeCount = 0;
  Solution bestSolution(constructSolution(), problem_.distanceMatrix_);
  for (int i = 0; i < 2000 && noUpgradeCount < 500; i++) {
    Solution tempSolution(constructSolution(), problem_.distanceMatrix_);
    Solution neighborSolution(localSearch_->Search(tempSolution, maxClients_), problem_.distanceMatrix_);
    if (neighborSolution.tourDistance() < bestSolution.tourDistance()) {
      bestSolution.solution_ = neighborSolution.solution_;
    } else {
      noUpgradeCount++;
    }
  }
  return bestSolution.solution_;
}