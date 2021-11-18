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
  // TODO: Consider the need of EOF checking
  while (!at_eof()) {
    Node *node = stmt();
    if (consume(";")) {
      code[i++] = node;
      continue;
    } else if (consume(".")) {
      code[i++] = node;
      code[i] = NULL;
      break;
    } else {
      // TODO: Error
    }
  }
}

// stmt = READ "(" Ident ")" |
//        WRITE "(" Ident ")" |
//        IDENT ":" "=" simple |
//        WHILE relational DO stmt+ ENDWHILE  ";"?
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
    for (;;) {
      node->then.push_back(stmt());
      if (!consume(";")) {
        break;
      }
    }
    expect("ENDWHILE");

    return node;
  }

  // TODO: Refactor
  Node *node = new Node;
  Token *tok = consume_ident();
  if (!tok) {
    // TODO: Error
  }
  node->offset = tok->str[0] - 'A';
  expect(":=");
  node->kind = ND_ASS;
  node->rhs = simple();

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

  return node;
}

// simple = (("+ | "-")? term)+
Node *simple() {
  // TODO: consider case which symbol is not expected
  Node *node = new Node;
  if (consume("+")) {
    node = term();
  } else if (consume("-")) {
    node = new_node(ND_SUB, new_node_num(0), term());
  } else {
    node = term();
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
    return node;
  }

  return primary();
}

// primary = num
Node *primary() { return new_node_num(expect_number()); }
