#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

// optimal solution, no more copies, no insert or erase operations, just swap
void dfs(vector<int> &nums, vector<vector<int>> &result, const int start) {
  if (start == nums.size()) {
    result.push_back(nums);
    return;
  }
  for (int i = start; i < nums.size(); i++) {
    swap(nums[start], nums[i]);
    dfs(nums, result, start + 1);
    swap(nums[start], nums[i]);
  }
}

vector<vector<int>> permute(vector<int> &nums) {
  vector<vector<int>> result;
  dfs(nums, result, 0);
  return result;
}

int main() {
  printTitle("Permutations");
  vector<int> nums = {1, 2, 3, 4, 5, 6};
  vector<vector<int>> solution = timedCall(permute, nums);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
