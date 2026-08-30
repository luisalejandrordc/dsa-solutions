#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <cmath>
#include <iostream>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

bool verifySymmetry(vector<optional<int>> &vec, int level) {
  if (vec.size() < pow(2, level))
    return false;
  int l = 0, r = vec.size() - 1;
  while (l < r) {
    if (vec[l++] != vec[r--])
      return false;
  }
  return true;
}

bool isSymmetric(TreeNode *root) {
  if (root == nullptr)
    return false;
  vector<optional<int>> levelNodes;
  int realNodes = 1, currLevel = 0;
  queue<pair<int, TreeNode *>> nodes;
  nodes.push({0, root});
  while (realNodes > 0) {
    auto [level, node] = nodes.front();
    if (level > currLevel) {
      if (!verifySymmetry(levelNodes, level - 1))
        return false;
      levelNodes.clear();
      currLevel++;
    }
    if (node == nullptr) {
      levelNodes.push_back(nullopt);
      nodes.push({level + 1, nullptr});
      nodes.push({level + 1, nullptr});
    } else {
      realNodes--;
      levelNodes.push_back(node->val);
      nodes.push({level + 1, node->left});
      nodes.push({level + 1, node->right});
      if (node->left != nullptr)
        realNodes++;
      if (node->right != nullptr)
        realNodes++;
    }
    nodes.pop();
  }
  // complete levelNodes with nullopt until filling the required size
  for (int i = levelNodes.size(); i < pow(2, currLevel); i++)
    levelNodes.push_back(nullopt);
  return verifySymmetry(levelNodes, currLevel);
}

int main() {
  printTitle("Symmetric Tree");
  vector<optional<int>> nums = {1, 2, 2, 3, 4, 4, 3};
  TreeNode *root = arrayToBinaryTree(nums);
  string solution = timedCall(isSymmetric, root) ? "True" : "False";
  cout << "Solution: " << solution << endl;
  return 0;
}
