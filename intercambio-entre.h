#ifndef INTERCAMBIO_ENTRE
#define INTERCAMBIO_ENTRE

#include "estructura-entorno.h"

class SwapEntre : public EnviromentStructure {
 public:
  std::vector<std::vector<int>> Apply(Solution initialSolution, int maxClients);
  std::vector<std::vector<int>> Search(Solution initialSolution, int maxClients);
};

#endif