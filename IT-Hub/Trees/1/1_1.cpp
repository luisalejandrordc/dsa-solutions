#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

void recs(TreeNode *root) {
  if (root == nullptr)
    return;
  swap(root->left, root->right);
  recs(root->left);
  recs(root->right);
}

TreeNode *invertTree(TreeNode *root) {
  recs(root);
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
