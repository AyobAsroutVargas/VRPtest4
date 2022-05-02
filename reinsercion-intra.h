#ifndef REINSERTION_INTRA
#define REINSERTION_INTRA

#include "estructura-entorno.h"

class ReinsertionIntra : public EnviromentStructure {
 public:
  std::vector<std::vector<int>> Apply(Solution initialSolution, int maxClients);
  std::vector<std::vector<int>> Search(Solution initialSolution, int maxClients);
};

#endif