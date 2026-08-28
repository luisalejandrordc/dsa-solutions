#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

using namespace std;

TreeNode *invertTree(TreeNode *root) {
  queue<TreeNode *> children;
  if (root != nullptr)
    children.push(root);
  while (!children.empty()) {
    TreeNode *curr = children.front();
    swap(curr->left, curr->right);
    if (curr->left != nullptr)
      children.push(curr->left);
    if (curr->right != nullptr)
      children.push(curr->right);
    children.pop();
  }
  return root;
}

int main() {
  printTitle("Invert Binary Tree");
  vector<optional<int>> nums = {4, 2, 7, 1, 3, 6, 9};
  TreeNode *root = arrayToBinaryTree(nums);
  TreeNode *solution = timedCall(invertTree, root);
  cout << "Solution: ";
  printBinaryTree(solution); // actually root = solution
  return 0;
}
