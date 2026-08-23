#include "../../../include/utils.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> subsets(vector<int> &nums) {
  vector<vector<int>> result = {{}};
  int counter = 0;
  for (const int &x : nums) {
    for (int i = 0; i < pow(2, counter); i++) {
      result.push_back(result[i]);
      result.back().push_back(x);
    }
    counter++;
  }
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
