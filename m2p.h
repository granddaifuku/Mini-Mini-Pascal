#pragma once

#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int N = 1000;

// -------------------
// File Implementation
// -------------------
std::vector<std::string> read_file(std::string path);
extern void write_file(const std::vector<std::string> &codes, std::string path);

// ------------------------
// Tokenizer Implementation
// ------------------------
enum TokenKind {
  TK_RESERVED,  // Symbols
  TK_IDNET,     // Identifier
  TK_NUM,       // Number
  TK_READ,      // Read
  TK_WRITE,     // Write
  TK_WHILE,     // While
  TK_DO,        // Do
  TK_ENDWHILE,  // Endwhile
  TK_EOF,       // End of File
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
extern Token *consume_ident();
extern void expect(std::string op);
extern int expect_number();
extern bool at_eof();

extern Token *new_token(TokenKind kind_, Token *cur_, std::string str_);
extern Token *tokenize(std::vector<std::string> user_inputs);

extern Token *token;

// ---------------------
// Parser Implementation
// ---------------------
enum NodeKind {
  ND_ADD,    // +
  ND_SUB,    // -
  ND_MUL,    // *
  ND_DIV,    // /
  ND_EQT,    // =
  ND_LES,    // <
  ND_ASS,    // :=
  ND_READ,   // Read
  ND_WRITE,  // Write
  ND_WHILE,  // While
  ND_NUM,    // Number
  ND_VAR,    // Variable
};

struct Node {
  NodeKind kind;
  Node *lhs;  // Left-hand side
  Node *rhs;  // Right-hand side
  int val;
  int offset;

  // WHILE cond DO then ENDWHILE
  Node *cond;
  std::vector<Node *> then;

 public:
  Node();
};

extern Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
extern Node *new_node_num(int val);

// Parser
extern void program();
extern Node *stmt();
extern Node *relational();
extern Node *simple();
extern Node *term();
extern Node *factor();
extern Node *primary();

extern Node *code[N];

// -----------------
// Utility functions
// -----------------
extern int is_alnum(char c);
