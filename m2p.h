#pragma once

#include <cctype>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const int N = 1000;
const int LOWER_LIMIT = 32768;
const int UPPER_LIMIT = 32767;
extern int label_number;
extern std::string file_name;
extern std::vector<std::string> inputs;

// ----------------
// Error Processing
// ----------------

void error(int row, int col, std::string s, ...);

// -------------------
// File Implementation
// -------------------

extern std::vector<std::string> read_file(std::string path);
extern void write_file(const std::vector<std::string> &codes);

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
  int row;  // The row number of file input
  int col;  // The column number of file input

 public:
  Token();
};

extern bool consume(std::string op);
extern Token *consume_ident();
extern void expect(std::string op);
extern int expect_number();
extern bool at_eof();

extern Token *new_token(TokenKind kind, Token *cur, std::string str, int row,
                        int col);
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

// -----------------------------
// Code generator Implementation
// -----------------------------

extern std::vector<std::string> gen();
extern void emit(std::vector<std::string> &codes,
                 std::map<std::string, int> &flags, Node *node);
extern void resolve(std::vector<std::string> &codes,
                    std::map<std::string, int> &flags);

// -----------------
// Utility functions
// -----------------

extern int is_alnum(char c);
extern std::string format(const std::string &fmt, int arg);
extern std::string extract_file_name(std::string path);
extern int label_num();
