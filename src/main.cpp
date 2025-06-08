// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  auto peremen = getAllPerms(tree);
  std::cout << "All permutations:\n";
  for (const auto& p : peremen) {
    for (char c : p)
      std::cout << c;
    std::cout << '\n';
  }

  std::vector<char> p1 = getPerm1(tree, 2);
  std::cout << "\ngetPerm1(2): ";
  for (char c : p1)
    std::cout << c;
  std::cout << '\n';

  std::vector<char> p2 = getPerm2(tree, 2);
  std::cout << "getPerm2(2): ";
  for (char c : p2)
    std::cout << c;
  std::cout << '\n';

  std::cout << "\nBenchmarking...\n";

  for (int n = 3; n <= 9; ++n) {
    std::vector<char> alpha;
    for (int i = 0; i < n; ++i)
      alpha.push_back('1' + i);

    PMTree t(alpha);

    int tot = 1;
    for (int i = 2; i <= n; ++i)
      tot *= i;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, tot);

    int targ = dis(gen);

    auto starting1 = std::chrono::high_resolution_clock::now();
    getAllPerms(t);
    auto ending1 = std::chrono::high_resolution_clock::now();

    auto starting2 = std::chrono::high_resolution_clock::now();
    getPerm1(t, targ);
    auto ending2 = std::chrono::high_resolution_clock::now();

    auto starting3 = std::chrono::high_resolution_clock::now();
    getPerm2(t, targ);
    auto ending3 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> d1 = ending1 - starting1;
    std::chrono::duration<double> d2 = ending2 - starting2;
    std::chrono::duration<double> d3 = ending3 - starting3;

    std::cout << "n = " << n
              << ", getAllPerms: " << d1.count()
              << "s, getPerm1: " << d2.count()
              << "s, getPerm2: " << d3.count() << "s\n";
  }

  return 0;
}
