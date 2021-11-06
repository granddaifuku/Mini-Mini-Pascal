#pragma once

#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

// ------------------------
// Tokenizer Implementation
// ------------------------
enum TokenKind {
  TK_RESERVED, // Symbols
  TK_IDNET,    // Identifier
  TK_NUM,      // Number
  TK_READ,     // Read
  TK_WRITE,    // Write
  TK_WHILE,    // While
  TK_DO,       // Do
  TK_ENDWHILE, // Endwhile
  TK_EOF,      // End of File
};

struct Token {
  TokenKind kind;
  Token *next;
  int val;
  std::string str;

public:
  Token();
};

extern bool consume(std::string op);
extern void expect(std::string op);
extern int expect_number();
extern bool at_eof();

extern Token *new_token(TokenKind kind_, Token *cur_, std::string str_);
extern Token *tokenize(std::vector<std::string> user_inputs);

extern Token *token;

// -----------------
// Utility functions
// -----------------
extern int is_alnum(char c);
