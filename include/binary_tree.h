#pragma once
#include "utils.h"
#include <cmath>
#include <iostream>
#include <optional>
#include <ostream>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(0), left(l), right(r) {}
};

template <typename T>
inline TreeNode *arrayToBinaryTree(const std::vector<std::optional<T>> &nums) {
  if (nums.empty() || (!nums[0].has_value()))
    return nullptr;
  TreeNode *root = new TreeNode(*nums[0]);
  std::queue<TreeNode *> children;
  children.push(root);
  for (int i = 1; i + 1 < nums.size(); i += 2) {
    TreeNode *curr = children.front();
    if (curr == nullptr) {
      children.push(nullptr); // left child
      children.push(nullptr); // right child
    } else {
      if (nums[i].has_value())
        curr->left = new TreeNode(*nums[i]);
      if (nums[i + 1].has_value())
        curr->right = new TreeNode(*nums[i + 1]);
      children.push(curr->left);
      children.push(curr->right);
    }
    children.pop();
  }
  return root;
}

inline std::vector<std::optional<int>> binaryTreeToArray(TreeNode *root) {
  if (root == nullptr)
    return {};
  std::vector<std::optional<int>> result;
  std::queue<TreeNode *> children;
  children.push(root);
  int realNodes = 1;
  while (realNodes > 0) {
    TreeNode *curr = children.front();
    if (curr == nullptr) {
      result.push_back(std::nullopt);
      children.push(nullptr);
      children.push(nullptr);
    } else {
      realNodes--;
      result.push_back(curr->val);
      children.push(curr->left);
      children.push(curr->right);
      if (curr->left != nullptr)
        realNodes++;
      if (curr->right != nullptr)
        realNodes++;
    }
    children.pop();
  }
  int nodesLeft = result.size();
  int levelSize = 1;
  while (nodesLeft > 0) {
    nodesLeft -= levelSize;
    levelSize *= 2;
  }
  for (; nodesLeft < 0; nodesLeft++)
    result.push_back(std::nullopt);
  return result;
}

inline void printBinaryTree(TreeNode *root) {
  if (root == nullptr) {
    std::cout << "[]" << std::endl;
    return;
  }
  std::queue<TreeNode *> children;
  children.push(root);
  int nodesPrinted = 0, realNodes = 1;
  std::cout << "[";
  while (realNodes > 0) {
    TreeNode *curr = children.front();
    if (curr != root)
      std::cout << ", ";
    if (curr == nullptr) {
      std::cout << "null";
      children.push(nullptr); // left child
      children.push(nullptr); // right child
    } else {
      realNodes--;
      std::cout << curr->val;
      children.push(curr->left);
      children.push(curr->right);
      if (curr->left != nullptr)
        realNodes++;
      if (curr->right != nullptr)
        realNodes++;
    }
    nodesPrinted++;
    children.pop();
  }
  int levelSize = 1;
  while (nodesPrinted > 0) {
    nodesPrinted -= levelSize;
    levelSize *= 2;
  }
  for (; nodesPrinted < 0; nodesPrinted++)
    std::cout << ", null";
  std::cout << "]" << std::endl;
}
