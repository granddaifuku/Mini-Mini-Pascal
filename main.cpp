#include "m2p.h"

// Current Token
Token *token;

Node *code[N];

int label_number;
std::string file_name;
std::vector<std::string> inputs;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    // TODO: error;
    return 1;
  }

  // Init
  label_number = 0;
  std::string path = argv[1];
  file_name = extract_file_name(path);

  // Input
  inputs = read_file(path);

  // Tokenize
  token = tokenize(inputs);

  // Parse
  program();

  // Code generation
  std::vector<std::string> codes = gen();

  // Output
  write_file(codes);

  return 0;
}
