#include "m2p.h"

std::vector<std::string> gen() {
  std::vector<std::string> codes;
  std::map<std::string, int> flags;

  for (int i = 0; code[i]; ++i) {
    emit(codes, flags, code[i]);
  }

  resolve(codes, flags);

  return codes;
}

void emit(std::vector<std::string> &codes, std::map<std::string, int> &flags,
          Node *node) {
  if (node->kind == ND_NUM) {
    codes.push_back(format("LDC %d", node->val));
    return;
  }
  if (node->kind == ND_VAR) {
    codes.push_back(format("LOD %d", node->offset));
    return;
  }
  if (node->kind == ND_READ) {
    codes.push_back(format("GET %d", node->offset));
    return;
  }
  if (node->kind == ND_WRITE) {
    codes.push_back(format("PUT %d", node->offset));
    return;
  }
  if (node->kind == ND_ASS) {
    emit(codes, flags, node->rhs);
    codes.push_back(format("STR %d", node->offset));
    return;
  }
  if (node->kind == ND_WHILE) {
    int label_begin = label_num();
    int label_end = label_num();
    flags[format("_label%d_", label_end)] = (int)codes.size();
    emit(codes, flags, node->cond);
    codes.push_back(format("CJP _label%d_", label_begin));
    for (int i = 0; i < (int)node->then.size(); ++i) {
      emit(codes, flags, node->then[i]);
    }
    codes.push_back(format("UJP _label%d_", label_end));
    flags[format("_label%d_", label_begin)] = (int)codes.size();
    return;
  }

  emit(codes, flags, node->lhs);
  emit(codes, flags, node->rhs);
  switch (node->kind) {
  case ND_ADD:
    codes.push_back("ADD");
    break;
  case ND_SUB:
    codes.push_back("SUB");
    break;
  case ND_MUL:
    codes.push_back("MLT");
    break;
  case ND_DIV:
    codes.push_back("DIV");
    break;
  case ND_EQT:
    codes.push_back("EQT");
    break;
  case ND_LES:
    codes.push_back("LET");
    break;
  }
}

void resolve(std::vector<std::string> &codes,
             std::map<std::string, int> &flags) {
  // Find the label
  for (int i = 0; i < (int)codes.size(); ++i) {
    std::string label = "";
    std::string base = "";
    bool is_label = false;
    for (int j = 0; j < (int)codes[i].size(); ++j) {
      if (is_label) {
        label += codes[i][j];
      } else {
        if (codes[i][j] != '_') {
          base += codes[i][j];
        }
      }
      if (codes[i][j] == '_') {
        if (is_label) {
          is_label = false;
        } else {
          is_label = true;
          label += codes[i][j];
        }
      }
    }
    base += "%d";
    if (label != "") {
      codes[i] = format(base, flags[label]);
    }
  }
}
