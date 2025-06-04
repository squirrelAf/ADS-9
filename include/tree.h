// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <iostream>
#include <vector>
#include <memory>

// Структура узла дерева
struct PMTree {
    char symbol; // символ, если лист
    std::shared_ptr<PMTree> left;
    std::shared_ptr<PMTree> right;
    bool isLeaf;

    // конструктор для листа
    PMTree(char s) : symbol(s), left(nullptr), right(nullptr), isLeaf(true) {}

    // конструктор для внутреннего узла
    PMTree(std::shared_ptr<PMTree> l, std::shared_ptr<PMTree> r)
        : left(l), right(r), isLeaf(false) {}
};

// Функция для построения дерева вариантов из вектора символов
std::shared_ptr<PMTree> buildTree(const std::vector<char>& symbols) {
    // Создаем вектор листьев
    std::vector<std::shared_ptr<PMTree>> nodes;
    for (char s : symbols) {
        nodes.push_back(std::make_shared<PMTree>(s));
    }

    // Построение дерева, объединяя в пары
    while (nodes.size() > 1) {
        std::vector<std::shared_ptr<PMTree>> newLevel;

        // Объединяем по два узла
        for (size_t i = 0; i + 1 < nodes.size(); i += 2) {
            newLevel.push_back(std::make_shared<PMTree>(nodes[i], nodes[i + 1]));
        }

        // Если нечетное число узлов, добавляем последний без пар
        if (nodes.size() % 2 != 0) {
            newLevel.push_back(nodes.back());
        }

        nodes = newLevel;
    }

    // Осталось один корень
    return nodes.front();
}

// Функция для вывода дерева (например, в предфиксном порядке)
void printTree(const std::shared_ptr<PMTree>& node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) std::cout << "  ";
    if (node->isLeaf) {
        std::cout << "Leaf: " << node->symbol << std::endl;
    } else {
        std::cout << "Node" << std::endl;
        printTree(node->left, depth + 1);
        printTree(node->right, depth + 1);
    }
}
#endif  // INCLUDE_TREE_H_
