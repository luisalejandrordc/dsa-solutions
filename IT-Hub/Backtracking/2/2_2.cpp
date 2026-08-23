#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

// less memory usage but more processing time because of erase and insert
// but you must consider the extra time of creating copies in 2_1.cpp
void dfs(vector<int> &nums, vector<int> &current, vector<vector<int>> &result) {
  if (nums.size() == 0) {
    result.push_back(current);
    return;
  }
  for (int i = 0; i < nums.size(); i++) {
    current.push_back(nums[i]);
    nums.erase(nums.begin() + i);
    dfs(nums, current, result);
    nums.insert(nums.begin() + i, current.back());
    current.pop_back();
  }
}

vector<vector<int>> permute(vector<int> &nums) {
  vector<vector<int>> result;
  vector<int> current;
  dfs(nums, current, result);
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
