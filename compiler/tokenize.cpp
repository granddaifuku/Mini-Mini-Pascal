#include "m2p.h"

Token::Token() {}

Token *new_token(TokenKind kind, Token *cur, std::string str) {
  Token *tok = new Token;
  tok->kind = kind;
  tok->str = str;
  cur->next = tok;

  return tok;
}

Token *tokenize(std::vector<std::string> user_inputs) {
  Token head;
  head.next = NULL;
  Token *cur = &head;

  for (int i = 0; i < (int)user_inputs.size(); ++i) {
    std::string user_input = user_inputs[i];
    int len = user_input.size();
    for (int j = 0; j < (int)user_input.size(); ++j) {
      char c = user_input[j];
      // Skip the white space
      if (isspace(user_input[j])) {
        continue;
      }
      // Assign
      if (c == ':') {
        if (j <= len - 2 && user_input[j + 1] == '=') {
          cur = new_token(TK_RESERVED, cur, ":=");
          j += 1;
          continue;
        }
      }
      // Symbols
      if (c == '.' || c == ';' || c == '<' || c == '=' || c == '>' ||
          c == '+' || c == '-' || c == '*' || c == '/' || c == '(' ||
          c == ')') {
        cur = new_token(TK_RESERVED, cur, {c});  // {c}: char -> string
        continue;
      }
      // READ
      if (c == 'R' && j <= len - 4) {
        std::string s = user_input.substr(j, 4);
        if (s == "READ") {
          if (j + 4 == len || (j + 4 < len && !is_alnum(user_input[j + 4]))) {
            cur = new_token(TK_READ, cur, "READ");
            j += 3;
            continue;
          }
        }
      }
      // WRITE
      if (c == 'W' && j <= len - 5) {
        std::string s = user_input.substr(j, 5);
        if (s == "WRITE") {
          if (j + 5 == len || (j + 5 < len && !is_alnum(user_input[j + 5]))) {
            cur = new_token(TK_WRITE, cur, "WRITE");
            j += 4;
            continue;
          }
        }
      }
      // WHILE
      if (c == 'W' && j <= len - 5) {
        std::string s = user_input.substr(j, 5);
        if (s == "WHILE") {
          if (j + 5 == len || (j + 5 < len && !is_alnum(user_input[j + 5]))) {
            cur = new_token(TK_WHILE, cur, "WHILE");
            j += 4;
            continue;
          }
        }
      }
      // DO
      if (c == 'D' && j <= len - 2) {
        std::string s = user_input.substr(j, 2);
        if (s == "DO") {
          if (j + 2 == len || (j + 2 < len && !is_alnum(user_input[j + 2]))) {
            cur = new_token(TK_READ, cur, "DO");
            j += 1;
            continue;
          }
        }
      }
      // ENDWHILE
      if (c == 'E' && j <= len - 8) {
        std::string s = user_input.substr(j, 8);
        if (s == "ENDWHILE") {
          if (j + 8 == len || (j + 8 < len && !is_alnum(user_input[j + 8]))) {
            cur = new_token(TK_READ, cur, "ENDWHILE");
            j += 7;
            continue;
          }
        }
      }
      if ('A' <= c && c <= 'Z') {
        cur = new_token(TK_IDNET, cur, {c});
        continue;
      }
      if (isdigit(c)) {
        int val = c - '0';
        int start_idx = j;
        while (j + 1 < len && isdigit(user_input[j + 1])) {
          j++;
          int v = user_input[j] - '0';
          val *= 10;
          val += v;
        }
        cur = new_token(TK_NUM, cur,
                        user_input.substr(start_idx, j - start_idx + 1));
        cur->val = val;
        continue;
      }

      // TODO: Error
    }
  }

  new_token(TK_EOF, cur, " ");
  return head.next;
}

bool consume(std::string op) {
  if ((token->kind != TK_RESERVED && token->kind != TK_READ &&
       token->kind != TK_WRITE && token->kind != TK_WHILE &&
       token->kind != TK_DO && token->kind != TK_ENDWHILE) ||
      op != token->str) {
    return false;
  }
  token = token->next;

  return true;
}

Token *consume_ident() {
  if (token->kind != TK_IDNET) {
    return 0;
  }
  Token *tok = token;
  token = token->next;

  return tok;
}

void expect(std::string op) {
  if (token->kind != TK_RESERVED || token->str != op) {
    // TODO: Error
  }
  token = token->next;
}

int expect_number() {
  if (token->kind != TK_NUM) {
    // TODO: Error
  }

  int val = token->val;
  token = token->next;

  return val;
}

bool at_eof() { return token->kind == TK_EOF; }
