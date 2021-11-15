#include "m2p.h"

int main(int argc, char *argv[]) {
  std::vector<std::string> inputs = read_file(argv[1]);
  for (int i = 0; i < (int)inputs.size(); ++i) {
    std::cout << inputs[i] << std::endl;
  }

  return 0;
}
