#include "m2p.h"

int is_alnum(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
         ('0' <= c && c <= '9') || (c == '_');
}

std::string format(const std::string &fmt, int arg) {
  size_t len = std::snprintf(nullptr, 0, fmt.c_str(), arg);
  std::vector<char> buf(len + 1);
  std::snprintf(&buf[0], len + 1, fmt.c_str(), arg);

  return std::string(&buf[0], &buf[0] + len);
}

std::string extract_file_name(std::string path) {
  int path_index = path.find_last_of("/") + 1;
  int ext_index = path.find_last_of(".");
  std::string name = path.substr(path_index, ext_index - path_index);

  return name;
}

int label_num() { return label_number++; }
