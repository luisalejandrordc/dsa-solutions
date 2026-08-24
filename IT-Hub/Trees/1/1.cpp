#include "../../../include/utils.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

TreeNode *arrayToBinaryTree(const vector<int> &nums) {
  TreeNode *root = new TreeNode(nums[0]);
  queue<TreeNode *> children;
  children.push(root);
  for (int i = 1; i < nums.size(); i += 2) {
    TreeNode *curr = children.front();
    curr->left = new TreeNode(nums[i]);
    curr->right = new TreeNode(nums[i + 1]);
    children.push(curr->left);
    children.push(curr->right);
    children.pop();
  }
  return root;
}

void printBinaryTree(TreeNode *root) {}

int main() {
  printTitle("Invert Binary Tree");
  vector<int> nums = {4, 2, 7, 1, 3, 6, 9};
  TreeNode *root = arrayToBinaryTree(nums);
  cout << "Solution:";
  return 0;
}
