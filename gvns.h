#ifndef GVNS
#define GVNS

#include <vector>
#include <set>
#include <climits>
#include <cstdlib>
#include <ctime>
#include "vehicle.h"
#include "problem.h"
#include "solution.h"
#include <sys/time.h>
#include "reinsercion-intra.h"
#include "intercambio-intra.h"
#include "reinsercion-entre.h"
#include "intercambio-entre.h"

class Gvns {
 public:
  Gvns(Problem problem, int maxClients, int kMax);
  int getClosestNode(int carIndex, std::set<int>& tempNodes);
  int selectFromRCL(int carIndex, std::set<int>& tempNodes);
  std::vector<std::vector<int>> constructSolution();
  std::vector<std::vector<int>> shake(std::vector<std::vector<int>>, int k);
  std::vector<std::vector<int>> intensifie(std::vector<std::vector<int>>);
  std::vector<std::vector<int>> solve();
  Problem problem_;
  int maxClients_;
  std::vector<EnviromentStructure*> localStructures_;
  int kMax_;
};

#endif