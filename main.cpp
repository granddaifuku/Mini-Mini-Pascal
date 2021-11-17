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

  label_number = 0;

  // Input
  std::vector<std::string> inputs = read_file(argv[1]);

  // Tokenize
  token = tokenize(inputs);

  // Parse
  program();

  std::vector<std::string> codes = gen();
  for (int i = 0; i < (int)codes.size(); ++i) {
    std::cout << codes[i] << std::endl;
  }

  return 0;
}
