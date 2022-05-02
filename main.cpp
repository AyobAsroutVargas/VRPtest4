#include "file-loader.h"
#include "greedy-vrp.h"
#include "grasp-vrp.h"
#include "solution.h"
#include "gvns.h"


int main(int argc, char* argv[]) {
  std::string filename = "I40j_2m_S1_1.txt";
  if (argc == 2) {
    filename = argv[1];
  }
  int nClients = 0, nVehicles = 0;
  std::vector<std::vector<int>> distanceMatrix;
  loadFromFile(filename, distanceMatrix, nClients, nVehicles);
  int maxClients = (nClients / nVehicles) + (nClients * 0.1);
  Problem problem(distanceMatrix, nClients, nVehicles);
  // GreedyVrp greedy(problem);
  // clock_t t0 = clock();
  // Solution greedySolution(greedy.Solve(), distanceMatrix);
  // long double time0 = (long double)(clock() - t0);
  // long double greedy_time = time0 / CLOCKS_PER_SEC;

  // EnviromentStructure* reinsertionIntra = new ReinsertionIntra();
  // EnviromentStructure* reinsertionEntre = new ReinsertionEntre();
  // EnviromentStructure* swapIntra = new SwapIntra();
  // EnviromentStructure* swapEntre = new SwapEntre();

  // GraspVrp graspRIntra(problem, reinsertionIntra, maxClients);
  // GraspVrp graspREntre(problem, reinsertionEntre, maxClients);
  // GraspVrp graspSIntra(problem, swapIntra, maxClients);
  // GraspVrp graspSEntre(problem, swapEntre, maxClients);

  Gvns gvns(problem, maxClients, 4);
  clock_t t1 = clock();
  Solution gvnsSolution(gvns.solve(), distanceMatrix);
  long double time1 = (long double)(clock() - t1);
  long double gvns_time = time1 / CLOCKS_PER_SEC;

  // clock_t t2 = clock();
  // Solution graspRIntraSolution(graspRIntra.generateInitialSolution(), distanceMatrix);
  // long double time2 = (long double)(clock() - t2);
  // long double graspRIntra_time = time2 / CLOCKS_PER_SEC;

  // clock_t t3 = clock();
  // Solution graspREntreSolution(graspREntre.generateInitialSolution(), distanceMatrix);
  // long double time3 = (long double)(clock() - t3);
  // long double graspREntre_time = time3 / CLOCKS_PER_SEC;

  // clock_t t4 = clock();
  // Solution graspSIntraSolution(graspSIntra.generateInitialSolution(), distanceMatrix);
  // long double time4 = (long double)(clock() - t4);
  // long double graspSIntra_time = time4 / CLOCKS_PER_SEC;
  
  // clock_t t5 = clock();
  // Solution graspSEntreSolution(graspSEntre.generateInitialSolution(), distanceMatrix);
  // long double time5 = (long double)(clock() - t5);
  // long double graspSEntre_time = time5 / CLOCKS_PER_SEC;

  // std::cout << "Greedy\n";
  // greedySolution.print();
  // std::cout << "Tiempo: " << greedy_time;
  // std::cout << "\n\n\n";
  // std::cout << "Grasp(reinsercion-Intra)\n";
  // graspRIntraSolution.print();
  // std::cout << "Tiempo: " << graspRIntra_time;
  // std::cout << "\n\n\n";
  // std::cout << "Grasp(reinsercion-Entre)\n";
  // graspREntreSolution.print();
  // std::cout << "Tiempo: " << graspREntre_time;
  // std::cout << "\n\n\n";
  // std::cout << "Grasp(intercambio-Intra)\n";
  // graspSIntraSolution.print();
  // std::cout << "Tiempo: " << graspSIntra_time;
  // std::cout << "\n\n\n";
  // std::cout << "Grasp(intercambio-Entre)\n";
  // graspSEntreSolution.print();
  // std::cout << "Tiempo: " << graspSEntre_time;
  // std::cout << "\n\n\n";
  std::cout << "GVNS\n";
  gvnsSolution.print();
  std::cout << "Tiempo: " << gvns_time;
  std::cout << "\n\n\n";
}