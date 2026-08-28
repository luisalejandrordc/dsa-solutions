#pragma once
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

template <typename T> struct is_optional : std::false_type {};

template <typename T> struct is_optional<std::optional<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_optional_v = is_optional<T>::value;

template <typename T>
inline TreeNode *arrayToBinaryTree(const std::vector<T> &nums) {
  if (nums.empty() || (is_optional_v<T> && !nums[0].has_value()))
    return nullptr;
  TreeNode *root;
  if constexpr (is_optional_v<T>)
    root = new TreeNode(*nums[0]);
  else
    root = new TreeNode(nums[0]);
  std::queue<TreeNode *> children;
  children.push(root);
  for (int i = 1; i + 1 < nums.size(); i += 2) {
    TreeNode *curr = children.front();
    if (curr == nullptr) {
      children.push(nullptr); // left child
      children.push(nullptr); // right child
    } else {
      if constexpr (is_optional_v<T>) {
        if (nums[i].has_value())
          curr->left = new TreeNode(*nums[i]);
        if (nums[i + 1].has_value())
          curr->right = new TreeNode(*nums[i + 1]);
      } else {
        curr->left = new TreeNode(nums[i]);
        curr->right = new TreeNode(nums[i + 1]);
      }
      children.push(curr->left);
      children.push(curr->right);
    }
    children.pop();
  }
  return root;
}

inline std::vector<std::optional<int>> binaryTreeToArray(TreeNode *root) {
  std::vector<std::optional<int>> result;
  std::queue<TreeNode *> children;
  children.push(root);
  int realNodes = root == nullptr ? 0 : 1;
  while (realNodes > 0) {
    TreeNode *curr = children.front();
    if (curr == nullptr) {
      result.push_back(std::nullopt);
      children.push(nullptr);
      children.push(nullptr);
    } else {
      realNodes--;
      children.push(curr->left);
      children.push(curr->right);
      if (curr->left != nullptr)
        realNodes++;
      if (curr->right != nullptr)
        realNodes++;
    }
    children.pop();
  }
  return result;
}

inline void printBinaryTree(TreeNode *root) {
  std::queue<std::pair<int, TreeNode *>> children; // {layer, node}
  std::pair<int, int> state = {0, 0};              // {layer, nodes printed}
  children.push({0, root});
  int realNodes = root == nullptr ? 0 : 1;
  std::cout << "{";
  while (realNodes > 0) {
    std::pair<int, TreeNode *> curr = children.front();
    if (curr.second != root)
      std::cout << ", ";
    if (curr.first > state.first) {
      state.first = curr.first;
      state.second = 0;
    }
    if (curr.first == state.first)
      state.second++;
    if (curr.second == nullptr) {
      std::cout << "null";
      children.push({curr.first + 1, nullptr}); // left child
      children.push({curr.first + 1, nullptr}); // right child
    } else {
      realNodes--;
      std::cout << curr.second->val;
      children.push({curr.first + 1, curr.second->left});
      children.push({curr.first + 1, curr.second->right});
      if (curr.second->left != nullptr)
        realNodes++;
      if (curr.second->right != nullptr)
        realNodes++;
    }
    children.pop();
  }
  while (state.second < pow(2, state.first)) {
    std::cout << ", null";
  }
  std::cout << "}" << std::endl;
}
