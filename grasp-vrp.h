#ifndef GRASP_VRP_
#define GRASP_VRP_

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

class GraspVrp {
 public:
  GraspVrp(Problem problem, EnviromentStructure* localSearch, int maxClients);
  std::vector<std::vector<int>> constructSolution();
  std::vector<std::vector<int>> generateInitialSolution();
  int getClosestNode(int carIndex, std::set<int>& tempNodes);
  int selectFromRCL(int carIndex, std::set<int>& tempNodes);
  Problem problem_;
  EnviromentStructure* localSearch_;
  int maxClients_;
};

#endif