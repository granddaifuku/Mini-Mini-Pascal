#include "m2p.h"

std::vector<std::string> read_file(std::string path) {
  std::vector<std::string> inputs;

  std::ifstream ifs(path, std::ios::in);
  if (!ifs) {
    std::cout << "Failed to open file\n" << std::endl;
    std::exit(1);
  }

  std::string line = "";
  while (std::getline(ifs, line)) {
    inputs.push_back(line);
  }

  return inputs;
}
