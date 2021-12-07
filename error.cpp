#include "m2p.h"

void error(int row, int col, std::string fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  std::cerr << "Error on " << file_name << ".PAS" << std::endl;
  std::cerr << "Line: " << row + 1 << " Col: " << col + 1 << std::endl;
  // Point out where the error occurs
  std::cerr << inputs[row] << std::endl;
  for (int i = 0; i < col; ++i) {
    std::cerr << " ";
  }
  std::cerr << "^ ";
  std::cerr << std::endl;
  vfprintf(stderr, fmt.c_str(), ap);
  std::cerr << std::endl;

  exit(1);
}
