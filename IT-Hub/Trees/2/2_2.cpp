#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int>> levelOrder(TreeNode *root) {
  vector<vector<int>> result;
  queue<pair<int, TreeNode *>> nodes; // {level, node}
  nodes.push({0, root});
  while (!nodes.empty()) {
    auto [level, node] = nodes.front();
    if (node != nullptr) {
      if (result.size() == level)
        result.push_back({});
      result[level].push_back(node->val);
      nodes.push({level + 1, node->left});
      nodes.push({level + 1, node->right});
    }
    nodes.pop();
  }
  return result;
}

int main() {
  printTitle("Binary Tree Level Order Traversal");
  vector<optional<int>> nums = {3, 9, 20, nullopt, nullopt, 15, 7};
  TreeNode *root = arrayToBinaryTree(nums);
  vector<vector<int>> solution = timedCall(levelOrder, root);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
