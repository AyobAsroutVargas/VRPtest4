#include "gvns.h"

Gvns::Gvns(Problem problem, int maxClients, int kMax) {
  problem_ = problem;
  maxClients_ = maxClients;
  kMax_ = kMax;
  EnviromentStructure* reinsertionIntra = new ReinsertionIntra();
  EnviromentStructure* reinsertionEntre = new ReinsertionEntre();
  EnviromentStructure* swapIntra = new SwapIntra();
  EnviromentStructure* swapEntre = new SwapEntre();
  localStructures_.push_back(reinsertionEntre);
  localStructures_.push_back(reinsertionIntra);
  localStructures_.push_back(swapEntre);
  localStructures_.push_back(swapIntra);
}

int Gvns::getClosestNode(int carIndex, std::set<int>& tempNodes){
  int minDistance = INT_MAX;
  int bestNodeIndex = 1;

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

int Gvns::selectFromRCL(int carIndex, std::set<int>& tempNodes) {
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
 

std::vector<std::vector<int>> Gvns::constructSolution(){
  std::vector<std::vector<int>> solution;
  int carIndex = 0;
  std::set<int> tempNodes = problem_.nodes_;

  while (tempNodes.size() != 1) {
    //int currentIndex = problem_.vehicles_[carIndex].tour.size() - 1;
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

std::vector<std::vector<int>> Gvns::shake(std::vector<std::vector<int>> initialSolution, int k) {
  struct timeval time;
  gettimeofday(&time,NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
  std::set<std::pair<std::pair<int,int>, std::pair<int,int>>> madeMoves;
  std::vector<std::vector<int>> result(initialSolution);

  for (int i = 0; i < k; i++) {
    int currentRoute = rand() % initialSolution.size();
    //int CurrentNodeIndex = rand() % initialSolution[currentRoute].size();
    int CurrentNodeIndex = 1 + (rand() % (initialSolution[currentRoute].size() - 2));


    // std::pair<int,int> testPair = std::make_pair(currentRoute, CurrentNodeIndex);

    // while (madeMoves.count(testPair)) {
    //   currentRoute = rand() % initialSolution.size();
    //   CurrentNodeIndex = 1 + (rand() % (initialSolution[currentRoute].size() - 2));
    // }

    int potentialRoute = rand() % initialSolution.size();
    while (currentRoute == potentialRoute) {
      potentialRoute = rand() % initialSolution.size();
    }
    //int NewNodeIndex = (rand() % (initialSolution[potentialRoute].size() - 2)) + 1;
    int NewNodeIndex = 1 + (rand() % (initialSolution[potentialRoute].size() - 2));

    // madeMoves.insert(std::make_pair(potentialRoute, NewNodeIndex));
    std::pair<int,int> currentPair = std::make_pair(currentRoute, CurrentNodeIndex);
    std::pair<int,int> potentialPair = std::make_pair(potentialRoute, NewNodeIndex);
    std::pair<std::pair<int,int>, std::pair<int,int>> test = std::make_pair(currentPair, potentialPair);

    while (madeMoves.count(test)) {
      currentRoute = rand() % initialSolution.size();
      CurrentNodeIndex = 1 + (rand() % (initialSolution[currentRoute].size() - 2));

      potentialRoute = rand() % initialSolution.size();
      while (currentRoute == potentialRoute) {
        potentialRoute = rand() % initialSolution.size();
      }
      NewNodeIndex = 1 + (rand() % (initialSolution[potentialRoute].size() - 2));

      currentPair = std::make_pair(currentRoute, CurrentNodeIndex);
      potentialPair = std::make_pair(potentialRoute, NewNodeIndex);
      test = std::make_pair(currentPair, potentialPair);
    }

    
    result[currentRoute].erase(result[currentRoute].begin() + CurrentNodeIndex);
    result[potentialRoute].insert(result[potentialRoute].begin() + NewNodeIndex, initialSolution[currentRoute][CurrentNodeIndex]);
  }
  return result;
}

std::vector<std::vector<int>> Gvns::intensifie(std::vector<std::vector<int>> initialSolution) {
  int lValue = 0;
  std::vector<std::vector<int>> result = initialSolution;
  while (lValue < 4) {
    Solution current(result, problem_.distanceMatrix_);
    std::vector<std::vector<int>> currentSolution = localStructures_[lValue]->Search(current, maxClients_);
    Solution bestNeighboor(currentSolution, problem_.distanceMatrix_);
    if (bestNeighboor.tourDistance() < current.tourDistance()) {
      result = currentSolution;
      lValue = 1;
    } else {
      lValue++;
    }
  }
  return result;
}

std::vector<std::vector<int>> Gvns::solve() {
  int k = 1;
  // int l = 1;
  int noUpgradeCount = 0;
  std::vector<std::vector<int>> initialSolution = constructSolution();
  //std::vector<std::vector<int>> currentSolution = initialSolution;
  std::vector<std::vector<int>> BestSolution = initialSolution;
  std::vector<std::vector<int>> BestLocalSolution = initialSolution;
  for (int i = 0; i < 2000 && noUpgradeCount < 1000; i++) {
    initialSolution = constructSolution();
    k = 1;
    BestLocalSolution = initialSolution;
    while (k < kMax_) {
      //std::vector<std::vector<int>> currentSolution = shake(initialSolution, k);
      //initialSolution = constructSolution();
      std::vector<std::vector<int>> intensifiedCurrent = intensifie(initialSolution);

      // Solution kk2(currentSolution, problem_.distanceMatrix_);
      // int kcurrentSolution22 = kk2.tourDistance();

      // Solution kk1(intensifiedCurrent, problem_.distanceMatrix_);
      // int kintensifiedCurrent11 = kk1.tourDistance();

      // Solution kk3(BestLocalSolution, problem_.distanceMatrix_);
      // int kBestSolution33 = kk3.tourDistance();
      // l = 1;
      // while (l < 4) {
      //   Solution current(currentSolution, problem_.distanceMatrix_);
      //   Solution intensified(intensifiedCurrent, problem_.distanceMatrix_);
      //   if (intensified.tourDistance() < current.tourDistance()) {
      //     currentSolution = intensifiedCurrent;
      //     l = 1;
      //   } else {
      //     l++;
      //   }
      // }
      Solution current(intensifiedCurrent, problem_.distanceMatrix_);
      Solution best(BestLocalSolution, problem_.distanceMatrix_);
      if (current.tourDistance() < best.tourDistance()) {
        BestLocalSolution = intensifiedCurrent;
        k = 1;
      } else {
        k++;
      }
    }
    Solution current(BestLocalSolution, problem_.distanceMatrix_);
    Solution best(BestSolution, problem_.distanceMatrix_);
    // int kbest44 = best.tourDistance();
    // int kbestLocal5 = current.tourDistance();
    if (current.tourDistance() < best.tourDistance()) {
      BestSolution = BestLocalSolution;
      noUpgradeCount = 0;
    } else {
      noUpgradeCount++;
    }
  }
  return BestSolution;
}