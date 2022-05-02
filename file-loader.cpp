#include "file-loader.h"

bool check_number(std::string str) {
  for (int i = 0; i < str.length(); i++) {
    if (isdigit(str[i]) == false) return false;
  }
  return true;
}

void loadFromFile(const std::string filename, std::vector<std::vector<int>>& distanceMatrix, int &nClients , int &nVehicles) {
  std::string line;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Unable to open file";
    return;
  }

  for (int i = 0; i < 3; i++) {
    std::getline(file, line);
    std::istringstream iss (line);
    std::string word;

    while (iss >> word) {
      if (check_number(word)) {
        if (i == 0) {
          nClients = std::stoi(word);
        } else {
          nVehicles = std::stoi(word);
        }
      }
    }
  }

  while (std::getline(file, line)) {
    std::istringstream iss (line);
    int tmp;
    std::vector<int> tmpVector;
    while (iss >> tmp) {
      tmpVector.push_back(tmp);
    }
    distanceMatrix.push_back(tmpVector);
  }
  file.close();
}