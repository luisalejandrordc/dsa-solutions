#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> recs(vector<int> &nums, int idx) {
  if (idx == nums.size())
    return {{}};
  vector<vector<int>> result = recs(nums, idx + 1);
  int originalSize = result.size();
  for (int i = 0; i < originalSize; i++) {
    result.push_back(result[i]);
    result.back().push_back(nums[idx]);
  }
  return result;
}

vector<vector<int>> subsets(vector<int> &nums) {
  // idx -> subsets that can be formed from this idx
  return recs(nums, 0);
}

int main() {
  printTitle("Subsets");
  vector<int> nums = {1, 2, 3};
  vector<vector<int>> solution = timedCall(subsets, nums);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
