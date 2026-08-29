#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <algorithm>
#include <iostream>
#include <optional>
#include <ostream>
#include <vector>

// DFS: Find all the ancestors of p and q
void recs(TreeNode *root, TreeNode *p, TreeNode *q,
          std::vector<TreeNode *> &p_ancestors,
          std::vector<TreeNode *> &q_ancestors, bool &p_found, bool &q_found) {
  if (root == nullptr || p == nullptr || q == nullptr)
    return;

  if (!p_found) {
    p_ancestors.push_back(root);
    if (p == root)
      p_found = true;
  }
  if (!q_found) {
    q_ancestors.push_back(root);
    if (q == root)
      q_found = true;
  }

  if (!p_found || !q_found) {
    recs(root->left, p, q, p_ancestors, q_ancestors, p_found, q_found);
    recs(root->right, p, q, p_ancestors, q_ancestors, p_found, q_found);
  }

  if (!p_found)
    p_ancestors.pop_back();
  if (!q_found)
    q_ancestors.pop_back();
}

TreeNode *lowestCommonAcestor(TreeNode *root, TreeNode *p, TreeNode *q) {
  // Find all ancestors of p and q
  std::vector<TreeNode *> p_ancestors, q_ancestors;
  bool p_found = false, q_found = false;
  recs(root, p, q, p_ancestors, q_ancestors, p_found, q_found);
  // No common ancestors
  if (p_ancestors[0] != q_ancestors[0])
    return nullptr;
  // Return Lowest Common Ancestor
  int i = 1;
  for (; i < std::min(p_ancestors.size(), q_ancestors.size()); i++) {
    if (p_ancestors[i] != q_ancestors[i])
      return p_ancestors[i - 1];
  }
  if (i == p_ancestors.size())
    return p_ancestors[i - 1];
  else
    return q_ancestors[i - 1];
}

int main() {
  printTitle("Lowest Common Ancestor of a Binary Tree");
  std::vector<std::optional<int>> nums = {
      3, 5, 1, 6, 2, 0, 8, std::nullopt, std::nullopt, 7, 4};
  TreeNode *root = arrayToBinaryTree(nums);
  TreeNode *p = root->left->left;
  TreeNode *q = root->left->right->right;
  TreeNode *solution = lowestCommonAcestor(root, p, q);
  std::cout << "Solution: " << solution->val << std::endl;
  return 0;
}
