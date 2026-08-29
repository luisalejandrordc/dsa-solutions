#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

// return max length (number of edges, max between left and right)
int recs(TreeNode *root, int &diameter) {
  // base case
  if (root == nullptr)
    return -1;
  int maxLeft = 1 + recs(root->left, diameter);
  int maxRight = 1 + recs(root->right, diameter);
  diameter = max(diameter, maxLeft + maxRight);
  return max(maxLeft, maxRight);
}

int diameterOfBinaryTree(TreeNode *root) {
  int diameter = 0;
  recs(root, diameter);
  return diameter;
}

int main() {
  printTitle("Diameter of Binary Tree");
  vector<optional<int>> nums = {1, 2, 3, 4, 5};
  TreeNode *root = arrayToBinaryTree(nums);
  int solution = timedCall(diameterOfBinaryTree, root);
  cout << "Solution: " << solution << endl;
  return 0;
}
