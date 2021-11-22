#include "m2p.h"

std::vector<std::string> read_file(std::string path) {
  std::vector<std::string> inputs;

  std::ifstream ifs(path, std::ios::in);
  if (!ifs) {
    std::cout << "Failed to open file" << std::endl;
    std::exit(1);
  }

  std::string line = "";
  while (std::getline(ifs, line)) {
    inputs.push_back(line);
  }

  return inputs;
}

void write_file(const std::vector<std::string> &codes, std::string path) {
  int path_index = path.find_last_of("/") + 1;
  int ext_index = path.find_last_of(".");
  std::string file_name =
      "./" + path.substr(path_index, ext_index - path_index) + ".OBJ";

  std::ofstream ofs;
  ofs.open(file_name, std::ios::out);

  if (ofs.fail()) {
    std::cout << "Failed to open file" << std::endl;
    std::exit(1);
  }

  for (int i = 0; i < (int)codes.size(); ++i) {
    ofs << codes[i] << std::endl;
  }
}
