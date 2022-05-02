#ifndef INTERCAMBIO_INTRA
#define INTERCAMBIO_INTRA

#include "estructura-entorno.h"

class SwapIntra : public EnviromentStructure {
 public:
  std::vector<std::vector<int>> Apply(Solution initialSolution, int maxClients);
  std::vector<std::vector<int>> Search(Solution initialSolution, int maxClients);
};

#endif