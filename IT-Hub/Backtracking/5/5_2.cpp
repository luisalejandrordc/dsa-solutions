#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

// palindrome: sequence of characters that reads the same forward as backward

void dfs(const string &s, const vector<vector<bool>> &isPal,
         vector<vector<string>> &result, vector<string> &substrings, int n,
         int start) {
  // base case: solution found
  if (start == n) {
    result.push_back(substrings);
    return;
  }
  // choice: could the current substring be terminated at index end?
  for (int end = start; end < n; end++) {
    if (isPal[start][end]) {
      substrings.push_back(s.substr(start, end - start + 1));
      dfs(s, isPal, result, substrings, n, end + 1);
      substrings.pop_back(); // backtracking
    }
  }
}

vector<vector<string>> palindromePartition(string s) {
  // precompute palindrome susbtrings
  // isPal[start][end] -> true if s.substr(start, end-start+1) is palindrome
  int n = s.length();
  vector<vector<bool>> isPal(n, vector<bool>(n));
  for (int i = n - 1; i >= 0; i--)
    for (int j = i; j < n; j++)
      if (s[i] == s[j] && (j - i <= 1 || isPal[i + 1][j - 1]))
        isPal[i][j] = true;

  vector<vector<string>> result;
  vector<string> substrings;
  substrings.reserve(n);
  dfs(s, isPal, result, substrings, n, 0);
  return result;
}

int main() {
  printTitle("Palindrome Partitioning");
  string s = "abba";
  vector<vector<string>> solution = timedCall(palindromePartition, s);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
