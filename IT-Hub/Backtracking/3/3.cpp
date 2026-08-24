#include "../../../include/utils.h"
#include <array>
#include <iostream>
#include <vector>

using namespace std;

const array<array<int, 2>, 4> DIRS = {{
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
}};

bool dfs(vector<vector<char>> &board, const string &word, int rows, int cols,
         int x, int y, int idx) {
  // outside the grid
  if ((x < 0 || x >= rows) || (y < 0 || y >= cols))
    return false;
  // cell already covered
  if (board[x][y] == '\0')
    return false;
  // does not match
  if (board[x][y] != word[idx])
    return false;
  // last letter found
  if (idx == word.length() - 1)
    return true;
  // track progress
  char temp = board[x][y];
  board[x][y] = '\0';
  // explore different options
  for (const auto dir : DIRS)
    if (dfs(board, word, rows, cols, x + dir[0], y + dir[1], idx + 1))
      return true;
  // backtracking
  board[x][y] = temp;
  return false;
}

bool exist(vector<vector<char>> &board, string &word) {
  int rows = board.size(), cols = board[0].size();
  for (int x = 0; x < rows; x++)
    for (int y = 0; y < cols; y++)
      if (dfs(board, word, rows, cols, x, y, 0))
        return true;
  return false;
}

int main() {
  printTitle("Word Search");
  vector<vector<char>> board = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  string word = "ABCCED";
  string solution = timedCall(exist, board, word) ? "True" : "False";
  cout << "Solution: " << solution << endl;
  return 0;
}
