#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <algorithm>
#include <iostream>
#include <optional>
#include <ostream>
#include <vector>

// DFS: Find all the ancestors of p and q
bool recs(TreeNode *root, TreeNode *p, TreeNode *q,
          std::vector<TreeNode *> &p_ancestors,
          std::vector<TreeNode *> &q_ancestors, bool &p_found, bool &q_found) {
  if (root == nullptr || p == nullptr || q == nullptr)
    return false;

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

  if (p_found && q_found)
    return true;

  if (recs(root->left, p, q, p_ancestors, q_ancestors, p_found, q_found))
    return true;
  if (recs(root->right, p, q, p_ancestors, q_ancestors, p_found, q_found))
    return true;

  if (!p_found)
    p_ancestors.pop_back();
  if (!q_found)
    q_ancestors.pop_back();
  return false;
}

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
  // Find all ancestors of p and q
  std::vector<TreeNode *> p_ancestors, q_ancestors;
  bool p_found = false, q_found = false;
  if (!recs(root, p, q, p_ancestors, q_ancestors, p_found, q_found))
    return nullptr; // p or q not found in tree

  // Return Lowest Common Ancestor
  int i = 1;
  int n = std::min(p_ancestors.size(), q_ancestors.size());
  while (i < n && p_ancestors[i] == q_ancestors[i])
    i++;
  return p_ancestors[i - 1];
}

int main() {
  printTitle("Lowest Common Ancestor of a Binary Tree");
  std::vector<std::optional<int>> nums = {
      3, 5, 1, 6, 2, 0, 8, std::nullopt, std::nullopt, 7, 4};
  TreeNode *root = arrayToBinaryTree(nums);
  TreeNode *p = root->left->left;
  TreeNode *q = root->left->right->right;
  TreeNode *solution = timedCall(lowestCommonAncestor, root, p, q);
  std::cout << "Solution: " << solution->val << std::endl;
  return 0;
}
