#pragma once
#include <iostream>
#include <optional>
#include <ostream>
#include <queue>
#include <type_traits>
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
  if (nums.empty())
    return nullptr;
  TreeNode *root = new TreeNode(nums[0]);
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

inline void printBinaryTree(TreeNode *root) {
  std::queue<TreeNode *> children;
  children.push(root);
  std::cout << "{";
  while (!children.empty()) {
    TreeNode *curr = children.front();
    if (curr != root)
      std::cout << ", ";
    std::cout << curr->val;
    if (curr->left != nullptr)
      children.push(curr->left);
    if (curr->right != nullptr)
      children.push(curr->right);
    children.pop();
  }
  std::cout << "}" << std::endl;
}
