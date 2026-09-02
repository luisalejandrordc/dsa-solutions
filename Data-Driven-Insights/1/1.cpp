#include "../../include/utils.h"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> twoSum1(vector<int> &nums, int target) {
    for (int i = 0; i < nums.size() - 1; i++)
      for (int j = i + 1; j < nums.size(); j++)
        if (nums[i] + nums[j] == target)
          return {i, j};

    return {};
  }

  vector<int> twoSum2(vector<int> &nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
      int diff = target - nums[i];
      if (auto it = map.find(diff); it != map.end())
        return {it->second, i};
      map[nums[i]] = i;
    }

    return {};
  }
};

int main() {
  printTitle("Two Sum");
  vector<int> nums = {2, 7, 11, 15};
  int target = 9;

  Solution s;
  auto sol = timedCall(&Solution::twoSum1, s, nums, target);
  printVector(sol);

  vector<int> sol1 = Solution().twoSum1(nums, target);
  cout << "Solution 1: " << "[" << sol1[0] << ", " << sol1[1] << "]" << endl;
  vector<int> sol2 = Solution().twoSum2(nums, target);
  cout << "Solution 2: " << "[" << sol2[0] << ", " << sol2[1] << "]" << endl;
  return 0;
}
