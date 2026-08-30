#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

// are these two nodes symmetric?
bool recs(TreeNode *nodeLeft, TreeNode *nodeRight) {
  // base case
  if (nodeLeft == nullptr || nodeRight == nullptr)
    return nodeLeft == nodeRight;
  // verify values
  if (nodeLeft->val != nodeRight->val)
    return false;
  // verify children
  return recs(nodeLeft->left, nodeRight->right) &&
         recs(nodeLeft->right, nodeRight->left);
}

bool isSymmetric(TreeNode *root) {
  if (root == nullptr)
    return false;
  return recs(root->left, root->right);
}

int main() {
  printTitle("Symmetric Tree");
  vector<optional<int>> nums = {1, 2, 2, 3, 4, 4, 3};
  TreeNode *root = arrayToBinaryTree(nums);
  string solution = timedCall(isSymmetric, root) ? "True" : "False";
  cout << "Solution: " << solution << endl;
  return 0;
}
