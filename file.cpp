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

void write_file(const std::vector<std::string> &codes, std::string path = "") {
  if (path == "") {
    path = "./OUT.OBJ";
  }

  std::ofstream ofs;
  ofs.open(path, std::ios::out);

  for (int i = 0; i < (int)codes.size(); ++i) {
    ofs << codes[i] << std::endl;
  }
}
