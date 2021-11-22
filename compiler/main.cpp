#include "m2p.h"

// Current Token
Token *token;

Node *code[N];

int label_number;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    // TODO: error;
    return 1;
  }
  // Init
  label_number = 0;
  std::string path = argv[1];

  // Input
  std::vector<std::string> inputs = read_file(path);

  // Tokenize
  token = tokenize(inputs);

  // Parse
  program();

  // Code generation
  std::vector<std::string> codes = gen();

  // Output file
  write_file(codes, path);

  return 0;
}
