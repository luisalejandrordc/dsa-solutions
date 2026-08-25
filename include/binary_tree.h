#pragma once
#include <iostream>
#include <ostream>
#include <queue>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(0), left(l), right(r) {}
};

inline TreeNode *arrayToBinaryTree(std::vector<int> &nums) {
  if (nums.empty())
    return nullptr;
  TreeNode *root = new TreeNode(nums[0]);
  std::queue<TreeNode *> children;
  children.push(root);
  for (int i = 1; i + 1 < nums.size(); i += 2) {
    TreeNode *curr = children.front();
    curr->left = new TreeNode(nums[i]);
    children.push(curr->left);
    curr->right = new TreeNode(nums[i + 1]);
    children.push(curr->right);
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
