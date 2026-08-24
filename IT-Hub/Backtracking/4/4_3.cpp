#include "../../../include/utils.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// we build the board after finding a solution
// columns represents the column index of the queen at each row i
// we permute its values inside dfs()
void dfs(vector<vector<string>> &result, vector<int> &columns,
         vector<bool> &leftDiag, vector<bool> &rightDiag, int n, int row) {
  // base case
  if (row == n) {
    vector<string> board(n, string(n, '.'));
    for (int i = 0; i < n; i++)
      board[i][columns[i]] = 'Q';
    result.push_back(board);
    return;
  }
  // explore all possibilities
  for (int i = row; i < n; i++) {
    int col = columns[i];
    // verify if the cell is available for placing the queen
    if (!leftDiag[row + col] && !rightDiag[row - col + n - 1]) {
      // place the queen
      swap(columns[row], columns[i]);
      leftDiag[row + col] = true;
      rightDiag[row - col + n - 1] = true;
      // move to the next row
      dfs(result, columns, leftDiag, rightDiag, n, row + 1);
      // backtracking
      swap(columns[row], columns[i]);
      leftDiag[row + col] = false;
      rightDiag[row - col + n - 1] = false;
    }
  }
}

vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> result;
  // columns[0, row-1] -> columns chosen for previous rows
  // columns[row, n-1] -> columns still avaiable
  vector<int> columns(n); // column index of the queen at row i
  for (int i = 0; i < n; i++)
    columns[i] = i;
  vector<bool> leftDiag(2 * n - 1);  // is left diagonal i restricted?
  vector<bool> rightDiag(2 * n - 1); // is right diagonal i restricted?
  dfs(result, columns, leftDiag, rightDiag, n, 0);
  return result;
}

int main() {
  printTitle("N-Queens");
  vector<vector<string>> solution = timedCall(solveNQueens, 4);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
