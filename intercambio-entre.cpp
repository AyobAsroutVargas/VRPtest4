#include "intercambio-entre.h"

std::vector<std::vector<int>> SwapEntre::Apply(Solution initialSolution, int maxClients) {
  int cost = initialSolution.tourDistance();
  int bestCost = cost;
  int iValue =0, jValue = 0, kValue = 0, lValue = 0;
  for (int i = 0; i < initialSolution.solution_.size(); i++) {
    for (int j = i + 1; j < initialSolution.solution_.size(); j++) {
      for (int k = 1; k < initialSolution.solution_[i].size() - 1; k++) {
        for (int l = 1; l < initialSolution.solution_[j].size() - 1; l++) {
          int tempCost = cost;
          std::vector<int> actualRoute = initialSolution.solution_[i];
          std::vector<int> potentialRoute = initialSolution.solution_[j];
          if (potentialRoute.size() >= maxClients + 2) continue;
          tempCost -= initialSolution.distanceMatrix_[actualRoute[k - 1]][actualRoute[k]];
          tempCost -= initialSolution.distanceMatrix_[actualRoute[k]][actualRoute[k + 1]];
          tempCost -= initialSolution.distanceMatrix_[potentialRoute[l - 1]][potentialRoute[l]];
          tempCost -= initialSolution.distanceMatrix_[potentialRoute[l]][potentialRoute[l + 1]];

          tempCost += initialSolution.distanceMatrix_[actualRoute[k - 1]][potentialRoute[l]];
          tempCost += initialSolution.distanceMatrix_[potentialRoute[l]][actualRoute[k + 1]];
          tempCost += initialSolution.distanceMatrix_[potentialRoute[l - 1]][actualRoute[k]];
          tempCost += initialSolution.distanceMatrix_[actualRoute[k]][potentialRoute[l + 1]];
          if (tempCost < bestCost) {
            bestCost = tempCost;
            iValue = i;
            jValue = j;
            kValue = k;
            lValue = l;
          }
        }
      }
    }
  }
  std::vector<std::vector<int>> BestSolution(initialSolution.solution_);
  if (bestCost < cost) {
    int temp = initialSolution.solution_[iValue][kValue];
    BestSolution[iValue][kValue] = initialSolution.solution_[jValue][lValue];
    BestSolution[jValue][lValue] = temp;
  }
  return BestSolution;
}

std::vector<std::vector<int>> SwapEntre::Search(Solution initialSolution, int maxClients) {
  Solution currentSolution(initialSolution.solution_, initialSolution.distanceMatrix_);
  Solution BestSolution(Apply(initialSolution, maxClients), initialSolution.distanceMatrix_);
  while (BestSolution.tourDistance() < currentSolution.tourDistance()) {
    currentSolution.solution_ = BestSolution.solution_;
    BestSolution.solution_ = Apply(BestSolution, maxClients);
  }
  return BestSolution.solution_;
}