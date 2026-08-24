#include "../../../include/utils.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void dfs(vector<string> &board, vector<vector<string>> &result,
         vector<bool> &columns, vector<bool> &leftDiag, vector<bool> &rightDiag,
         int n, int row) {
  // base case
  if (row == n) {
    result.push_back(board);
    return;
  }
  // explore all possibilities
  for (int col = 0; col < n; col++) {
    // verify if the cell is available for placing the queen
    if (!columns[col] && !leftDiag[row + col] &&
        !rightDiag[row - col + n - 1]) {
      // place the queen
      board[row][col] = 'Q';
      columns[col] = true;
      leftDiag[row + col] = true;
      rightDiag[row - col + n - 1] = true;
      // move to the next row
      dfs(board, result, columns, leftDiag, rightDiag, n, row + 1);
      // backtracking
      board[row][col] = '.';
      columns[col] = false;
      leftDiag[row + col] = false;
      rightDiag[row - col + n - 1] = false;
    }
  }
}

vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> result;
  vector<string> board(n, string(n, '.')); // initial board
  vector<bool> columns(n);                 // is there a queen in column i?
  vector<bool> leftDiag(2 * n - 1);        // is left diagonal i restricted?
  vector<bool> rightDiag(2 * n - 1);       // is right diagonal i restricted?
  dfs(board, result, columns, leftDiag, rightDiag, n, 0);
  return result;
}

int main() {
  printTitle("N-Queens");
  vector<vector<string>> solution = timedCall(solveNQueens, 4);
  cout << "Solution: ";
  printVector(solution);
  return 0;
}
