#include "m2p.h"

std::vector<std::string> gen() {
  std::vector<std::string> codes;
  std::map<std::string, int> flags;

  for (int i = 0; code[i]; ++i) {
    emit(codes, flags, code[i]);
  }

  return codes;
}

void emit(std::vector<std::string> &codes, std::map<std::string, int> &flags,
          Node *node) {
  if (node->kind == ND_NUM) {
    codes.push_back(format("LDC %d", node->val));
    //    std::cout << codes.back() << std::endl;
    return;
  }
  if (node->kind == ND_VAR) {
    codes.push_back(format("LOD %d", node->offset));
    //    std::cout << codes.back() << std::endl;
    return;
  }
  if (node->kind == ND_READ) {
    codes.push_back(format("GET %d", node->offset));
    //    std::cout << codes.back() << std::endl;
    return;
  }
  if (node->kind == ND_WRITE) {
    codes.push_back(format("PUT %d", node->offset));
    //    std::cout << codes.back() << std::endl;
    return;
  }
  if (node->kind == ND_ASS) {
    emit(codes, flags, node->rhs);
    codes.push_back(format("STR %d", node->offset));
    //    std::cout << codes.back() << std::endl;
    return;
  }
  if (node->kind == ND_WHILE) {
    int label = label_num();
    emit(codes, flags, node->cond);
    codes.push_back(format("CJP label%d", label));
    //    std::cout << codes.back() << std::endl;
    for (int i = 0; i < (int)node->then.size(); ++i) {
      emit(codes, flags, node->then[i]);
      //      std::cout << codes.back() << std::endl;
    }
    flags[format("label%d", label)] = (int)codes.size();
    return;
  }

  emit(codes, flags, node->lhs);
  emit(codes, flags, node->rhs);
  switch (node->kind) {
    case ND_ADD:
      codes.push_back("ADD");
      //    std::cout << codes.back() << std::endl;
      break;
    case ND_SUB:
      codes.push_back("SUB");
      //    std::cout << codes.back() << std::endl;
      break;
    case ND_MUL:
      codes.push_back("MLT");
      //    std::cout << codes.back() << std::endl;
      break;
    case ND_DIV:
      codes.push_back("DIV");
      //    std::cout << codes.back() << std::endl;
      break;
    case ND_EQT:
      codes.push_back("EQT");
      //    std::cout << codes.back() << std::endl;
      break;
    case ND_LES:
      codes.push_back("LET");
      //    std::cout << codes.back() << std::endl;
      break;
  }
}

void resolve(std::vector<std::string> &codes,
             std::map<std::string, int> &flags);
