#include "m2p.h"

// Current Token
Token *token;

Node *code[N];

int main(int argc, char *argv[]) {
  if (argc != 2) {
    // TODO: error;
    return 1;
  }

  // Tokenize
  // Parse
  program();

  return 0;
}
