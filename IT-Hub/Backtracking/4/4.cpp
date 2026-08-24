#include "../../../include/utils.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void dfs(vector<string> &board, vector<vector<string>> &result, int n,
         int row) {
  // base case
  if (row == n) {
    result.push_back(board);
    return;
  }
  // explore all possibilities
  for (int col = 0; col < n; col++) {
    if (board[row][col] == ' ') {
      board[row][col] = 'Q';       // place the queen
      vector<pair<int, int>> dots; // record new dots
      // fill row
      for (int y = 0; y < n; y++)
        if (board[row][y] == ' ') {
          board[row][y] = '.';
          dots.push_back({row, y});
        }
      // fill column
      for (int x = row + 1; x < n; x++)
        if (board[x][col] == ' ') {
          board[x][col] = '.';
          dots.push_back({x, col});
        }
      // fill left diagonal
      for (int x = row + 1, y = col - 1; x < n && y >= 0; x++, y--)
        if (board[x][y] == ' ') {
          board[x][y] = '.';
          dots.push_back({x, y});
        }
      // fill right diagonal
      for (int x = row + 1, y = col + 1; x < n && y < n; x++, y++)
        if (board[x][y] == ' ') {
          board[x][y] = '.';
          dots.push_back({x, y});
        }
      dfs(board, result, n, row + 1);
      // backtracking
      board[row][col] = ' ';
      for (const auto dot : dots)
        board[dot.first][dot.second] = ' ';
    }
  }
}

vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> result;
  vector<string> board(n, string(n, ' ')); // empty board
  dfs(board, result, n, 0);
  return result;
}

int main() {
  printTitle("N-Queens");
  vector<vector<string>> solution = timedCall(solveNQueens, 4);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
