// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  auto perms = getAllPerms(tree);
  std::cout << "All permutations:\n";
  for (const auto& p : perms) {
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

    int total = 1;
    for (int i = 2; i <= n; ++i)
      total *= i;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, total);

    int target = dis(gen);

    auto start1 = std::chrono::high_resolution_clock::now();
    getAllPerms(t);
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    getPerm1(t, target);
    auto end2 = std::chrono::high_resolution_clock::now();

    auto start3 = std::chrono::high_resolution_clock::now();
    getPerm2(t, target);
    auto end3 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> dur1 = end1 - start1;
    std::chrono::duration<double> dur2 = end2 - start2;
    std::chrono::duration<double> dur3 = end3 - start3;

    std::cout << "n = " << n
              << ", getAllPerms: " << dur1.count()
              << "s, getPerm1: " << dur2.count()
              << "s, getPerm2: " << dur3.count() << "s\n";
  }

  return 0;
}
