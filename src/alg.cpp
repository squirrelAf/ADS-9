// Copyright 2022 NNTU-CS
#include <algorithm>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& vec) {
  elems = vec;
  std::sort(elems.begin(), elems.end());
  root = new PMNode('*');
  build(root, elems);
}

void PMTree::build(PMNode* node, std::vector<char> rem) {
  if (rem.empty())
    return;

  for (size_t i = 0; i < rem.size(); ++i) {
    PMNode* child = new PMNode(rem[i]);
    node->children.push_back(child);

    std::vector<char> nextRem = rem;
    nextRem.erase(nextRem.begin() + i);
    build(child, nextRem);
  }
}

void dfs(PMNode* node, std::vector<char>& path,
         std::vector<std::vector<char>>& res) {
  if (node->value != '*') {
    path.push_back(node->value);
  }
  if (node->children.empty()) {
    res.push_back(path);
  } else {
    for (auto child : node->children) {
      dfs(child, path, res);
    }
  }
  if (!path.empty())
    path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> perms;
  std::vector<char> path;
  dfs(tree.getRoot(), path, perms);
  return perms;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> perms = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(perms.size()))
    return {};
  return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;
  const std::vector<char>& elems = tree.getElems();
  int n = elems.size();
  int total = 1;
  for (int i = 2; i <= n; ++i)
    total *= i;
  if (num < 1 || num > total)
    return {};

  std::vector<char> rem = elems;
  --num;  // zero-based index

  for (int i = n; i > 0; --i) {
    int fact = 1;
    for (int j = 2; j < i; ++j)
      fact *= j;
    int idx = num / fact;
    result.push_back(rem[idx]);
    rem.erase(rem.begin() + idx);
    num %= fact;
  }

  return result;
}
