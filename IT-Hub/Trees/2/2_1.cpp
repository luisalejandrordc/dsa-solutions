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
  result[layer].push_back(root->val);
  recs(root->left, result, layer + 1);
  recs(root->right, result, layer + 1);
}

vector<vector<int>> levelOrder(TreeNode *root) {
  // layer -> current node layer/level
  vector<vector<int>> result;
  recs(root, result, 0);
  return result;
}

int main() {
  printTitle("Binary Tree Level Order Traversal");
  vector<optional<int>> nums = {3, 9, 20, std::nullopt, std::nullopt, 15, 7};
  TreeNode *root = arrayToBinaryTree(nums);
  vector<vector<int>> solution = timedCall(levelOrder, root);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
