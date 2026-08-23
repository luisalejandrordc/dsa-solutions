#include "../../../include/utils.h"
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

void dfs(unordered_set<int> &numsRemaining, vector<int> &current,
         vector<vector<int>> &result) {
  if (numsRemaining.size() == 0)
    result.push_back(current);
  // choices for the loop to avoid problems with insert and erase operations
  auto choices = numsRemaining; // tradeoff -> more memory usage
  for (const int x : choices) {
    current.push_back(x);
    numsRemaining.erase(x);
    dfs(numsRemaining, current, result);
    current.pop_back();
    numsRemaining.insert(x);
  }
}

vector<vector<int>> permute(vector<int> &nums) {
  // vector<int> -> unordered_set<int> for faster operations
  unordered_set<int> numsRemaining;
  for (const int x : nums)
    numsRemaining.insert(x);

  vector<vector<int>> result;
  vector<int> current;
  dfs(numsRemaining, current, result);
  return result;
}

int main() {
  printTitle("Permutations");
  vector<int> nums = {1, 2, 3};
  vector<vector<int>> solution = timedCall(permute, nums);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
