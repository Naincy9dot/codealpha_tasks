//SUDOKU SOLVER
#include <iostream>
using namespace std;

#define N 9  // Sudoku grid size

// Function to print Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Check if placing num is valid in grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Row check
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num) return false;

    // Column check
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num) return false;

    // Subgrid check (3x3)
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num) return false;

    return true;
}

// Backtracking Sudoku solver
bool solveSudoku(int grid[N][N], int row, int col) {
    if (row == N - 1 && col == N)  // reached end
        return true;

    if (col == N) {  // move to next row
        row++;
        col = 0;
    }

    if (grid[row][col] != 0)  // skip pre-filled cells
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num; // place number

            if (solveSudoku(grid, row, col + 1))
                return true;

            grid[row][col] = 0; // backtrack
        }
    }
    return false; // trigger backtracking
}

// Main function
int main() {
    int grid[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 0, 0, 0, 6, 8},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    if (solveSudoku(grid, 0, 0))
        printGrid(grid);
    else
        cout << "No solution exists!" << endl;

    return 0;
}