#include "../../../include/utils.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int findContentChildren(vector<int> &g, vector<int> &s) {
  sort(g.begin(), g.end());
  sort(s.begin(), s.end());
  int childidx = 0, cookieidx = 0;
  while (childidx < g.size() && cookieidx < s.size()) {
    if (s[cookieidx] >= g[childidx])
      childidx++;
    cookieidx++;
  }
  return childidx;
}

int main() {
  printTitle("Assign Cookies");
  // vector<int> g = {1, 2, 3};
  // vector<int> s = {1, 1};
  vector<int> g = {1, 2};
  vector<int> s = {1, 2, 3};
  int solution = timedCall(findContentChildren, g, s);
  cout << "Solution: " << solution << endl;
  return 0;
}
