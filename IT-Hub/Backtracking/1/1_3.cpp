#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

void dfs(const vector<int> &nums, vector<int> &current,
         vector<vector<int>> &result, int idx) {
  if (idx == nums.size()) {
    result.push_back(current);
    return;
  }
  // choice: no modificaction
  dfs(nums, current, result, idx + 1);
  // choice: insert element
  current.push_back(nums[idx]);
  dfs(nums, current, result, idx + 1);
  current.pop_back(); // undo choice
}

vector<vector<int>> subsets(vector<int> &nums) {
  vector<vector<int>> result;
  vector<int> current;
  dfs(nums, current, result, 0);
  return result;
}

int main() {
  printTitle("Subsets");
  vector<int> nums = {1, 2, 3};
  vector<vector<int>> solution = timedCall(subsets, nums);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
