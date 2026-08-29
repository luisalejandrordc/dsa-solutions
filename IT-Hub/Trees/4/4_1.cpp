#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

using namespace std;

// return max lengths: {left, right}
pair<int, int> recs(TreeNode *root, int &diameter) {
  // base case
  if (root == nullptr)
    return {-1, -1};
  pair<int, int> nodeLeft = recs(root->left, diameter);
  pair<int, int> nodeRight = recs(root->right, diameter);
  int maxLeft = 1 + max(nodeLeft.first, nodeLeft.second);
  int maxRight = 1 + max(nodeRight.first, nodeRight.second);
  diameter = max(diameter, maxLeft + maxRight);
  return {maxLeft, maxRight};
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
