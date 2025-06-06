// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMNode {
 public:
  char value;
  std::vector<PMNode*> children;
  explicit PMNode(char val) : value(val) {}
  ~PMNode() {
    for (auto child : children)
      delete child;
  }
};

class PMTree {
 private:
  PMNode* root;
  std::vector<char> elems;
  void build(PMNode* node, std::vector<char> rem);

 public:
  explicit PMTree(const std::vector<char>& vec);
  ~PMTree() { delete root; }
  PMNode* getRoot() const { return root; }
  const std::vector<char>& getElems() const { return elems; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);


#endif  // INCLUDE_TREE_H_
