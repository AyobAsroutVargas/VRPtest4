#include "intercambio-intra.h"

std::vector<std::vector<int>> SwapIntra::Apply(Solution initialSolution, int maxClients) {
  int cost = initialSolution.tourDistance();
  int bestCost = cost;
  int iValue =0, jValue = 0, kValue = 0;
  for (int i = 0; i < initialSolution.solution_.size(); i++) {
    for (int j = 1; j < initialSolution.solution_[i].size() - 1; j++) {
      for (int k = j + 1; k < initialSolution.solution_[i].size() - 1; k++) {
        if (j == k) {
          continue;
        }
        int tempCost = cost;
        std::vector<int> actualRoute = initialSolution.solution_[i];
        tempCost -= initialSolution.distanceMatrix_[actualRoute[j - 1]][actualRoute[j]];
        tempCost -= initialSolution.distanceMatrix_[actualRoute[j]][actualRoute[j + 1]];
        if(k - 1 != j) {
          tempCost -= initialSolution.distanceMatrix_[actualRoute[k - 1]][actualRoute[k]];
        }
        tempCost -= initialSolution.distanceMatrix_[actualRoute[k]][actualRoute[k + 1]];

        tempCost += initialSolution.distanceMatrix_[actualRoute[j - 1]][actualRoute[k]];
        if(k - 1 != j) {
          tempCost += initialSolution.distanceMatrix_[actualRoute[k]][actualRoute[j + 1]];
          tempCost += initialSolution.distanceMatrix_[actualRoute[k - 1]][actualRoute[j]];
        } else {
          tempCost += initialSolution.distanceMatrix_[actualRoute[k]][actualRoute[j]];
        }
        tempCost += initialSolution.distanceMatrix_[actualRoute[j]][actualRoute[k + 1]];
        if (tempCost < bestCost) {
          bestCost = tempCost;
          iValue = i;
          jValue = j;
          kValue = k;
        }
      }
    }
  }
  std::vector<std::vector<int>> BestSolution(initialSolution.solution_);
  if (bestCost < cost) {
    int temp = initialSolution.solution_[iValue][jValue];
    BestSolution[iValue][jValue] = initialSolution.solution_[iValue][kValue];
    BestSolution[iValue][kValue] = temp;
  }
  return BestSolution;
}

std::vector<std::vector<int>> SwapIntra::Search(Solution initialSolution, int maxClients) {
  Solution currentSolution(initialSolution.solution_, initialSolution.distanceMatrix_);
  Solution BestSolution(Apply(initialSolution, maxClients), initialSolution.distanceMatrix_);
  while (BestSolution.tourDistance() < currentSolution.tourDistance()) {
    currentSolution.solution_ = BestSolution.solution_;
    BestSolution.solution_ = Apply(BestSolution, maxClients);
  }
  return BestSolution.solution_;
}