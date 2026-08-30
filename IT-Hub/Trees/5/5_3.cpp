#include "../../../include/binary_tree.h"
#include "../../../include/utils.h"
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

using namespace std;

bool isSymmetric(TreeNode *root) {
  if (root == nullptr)
    return true; // depends if you consider an empty tree symmetric or not
  queue<TreeNode *> nodes;
  nodes.push(root->left);
  nodes.push(root->right);
  while (!nodes.empty()) {
    // getting left and right nodes
    TreeNode *nodeLeft = nodes.front();
    nodes.pop();
    TreeNode *nodeRight = nodes.front();
    nodes.pop();
    // handle nodes as nullptr
    if (nodeLeft == nullptr || nodeRight == nullptr) {
      if (nodeLeft != nodeRight)
        return false;
      continue;
    }
    // verify values
    if (nodeLeft->val != nodeRight->val)
      return false;
    // push new nodes
    nodes.push(nodeLeft->left);
    nodes.push(nodeRight->right);
    // push new nodes
    nodes.push(nodeLeft->right);
    nodes.push(nodeRight->left);
  }
  return true;
}

int main() {
  printTitle("Symmetric Tree");
  vector<optional<int>> nums = {1, 2, 2, nullopt, 4, 4, nullopt};
  TreeNode *root = arrayToBinaryTree(nums);
  string solution = timedCall(isSymmetric, root) ? "True" : "False";
  cout << "Solution: " << solution << endl;
  return 0;
}
