#include "../../../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

// improvement: perform s.substr(a, b) only after determining that the
// current substring IS a palindrome

// palindrome: sequence of characters that reads the same forward as backward
bool isPalindrome(string s, int l, int r) {
  for (; l < r; l++, r--)
    if (s[l] != s[r])
      return false;
  return true;
}

void dfs(const string &s, vector<vector<string>> &result,
         vector<string> &substrings, int idx, int start) {
  // base case: solution found
  if (idx == s.length()) {
    result.push_back(substrings);
    return;
  }
  // choice: no partition (not available for last character)
  if (idx != s.length() - 1)
    dfs(s, result, substrings, idx + 1, start);
  // choice: create partition
  if (isPalindrome(s, start, idx)) {
    substrings.push_back(s.substr(start, idx - start + 1));
    dfs(s, result, substrings, idx + 1, idx + 1);
    substrings.pop_back(); // backtracking
  }
}

vector<vector<string>> palindromePartition(string s) {
  vector<vector<string>> result;
  vector<string> substrings;
  substrings.reserve(s.length());
  dfs(s, result, substrings, 0, 0);
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
