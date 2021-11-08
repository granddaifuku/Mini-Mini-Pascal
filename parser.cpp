#include "m2p.h"

Node::Node() {}

Node *new_node(NodeKind kind, Node *lhs, Node *rhs) {
  Node *node = new Node;
  node->kind = kind;
  node->lhs = lhs;
  node->rhs = rhs;

  return node;
}

Node *new_node_num(int val) {
  Node *node = new Node;
  node->kind = ND_NUM;
  node->val = val;

  return node;
}

void program() {
  int i = 0;
  while (!at_eof()) {
    code[i++] = stmt();
  }
  expect(".");
  code[i] = NULL;
}

Node *stmt() {
  if (consume("READ")) {
    Node *node = new Node;
    node->kind = ND_READ;
    expect("(");

    Token *tok = consume_ident();
    node->offset =
        tok->str[0] - 'A';  // Only single-character variable is allowed
    expect(")");

    return node;
  }

  if (consume("WRITE")) {
    Node *node = new Node;
    node->kind = ND_WRITE;
    expect("(");
    Token *tok = consume_ident();
    node->offset = tok->str[0] - 'A';
    expect(")");

    return node;
  }

  if (consume("WHILE")) {
    Node *node = new Node;
    node->kind = ND_WHILE;
    node->cond = relational();
    expect("DO");
    node->then = stmt();
    expect("ENDWHILE");

    return node;
  }

  Node *node;
  if (!consume(";")) {
    // TODO: Error
  }

  return node;
}

// relational =  simple ("<" simple | "=" simple | ">" simple)
Node *relational() {
  Node *node = simple();
  if (consume("=")) {
    node = new_node(ND_EQT, node, simple());
  } else if (consume("<")) {
    node = new_node(ND_LES, node, simple());
  } else if (consume(">")) {
    node = new_node(ND_LES, simple(), node);
  } else {
    // TODO: error
  }

  return 0;
}

// simple = (("+ | "-")? term)+
Node *simple() {
  Node *node = new Node;
  if (consume("+")) {
    node = term();
  } else if (consume("-")) {
    node = term();
  } else {
    //  TODO: error
  }

  for (;;) {
    if (consume("+")) {
      node = new_node(ND_ADD, node, term());
    } else if (consume("-")) {
      node = new_node(ND_SUB, node, term());
    } else {
      return node;
    }
  }
}

// term = factor ("*" factor / "/" factor)*
Node *term() {
  Node *node = factor();
  for (;;) {
    if (consume("*")) {
      node = new_node(ND_MUL, node, factor());
    } else if (consume("/")) {
      node = new_node(ND_DIV, node, factor());
    } else {
      return node;
    }
  }
}

// factor = ident | num | "(" simple ")"
Node *factor() {
  if (consume("(")) {
    Node *node = simple();
    expect(")");

    return node;
  }

  Token *tok = consume_ident();
  if (tok) {
    Node *node = new Node;
    node->kind = ND_VAR;
    node->offset = tok->str[0] - 'A';
  }

  return primary();
}

// primary = num
Node *primary() { return new_node_num(expect_number()); }
