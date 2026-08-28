#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

void recs(TreeNode *root, vector<vector<int>> &result, int layer) {
  if (root == nullptr)
    return;
  if (layer == result.size())
    result.push_back({});
}

vector<vector<int>> levelOrder(TreeNode *root) {
  // layer -> current node layer
  vector<vector<int>> result;
  recs(root, result, 0);
  return result;
}

int main() {
  printTitle("Binary Tree Level Order Traversal");
  vector<optional<int>> nums = {3,  9,           20, std::nullopt, std::nullopt,
                                15, std::nullopt};
  TreeNode *root = arrayToBinaryTree(nums);
  vector<vector<int>> solution = timedCall(levelOrder, root);
  cout << "Solution: ";
  printVector(solution);
  TreeNode *my_root = arrayToBinaryTree(nums);
  printBinaryTree(my_root);
  binaryTreeToArray(root);
  return 0;
}
