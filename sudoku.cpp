#include <iostream>
using namespace std;

#define N 9 // Size of the grid (9x9)

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if placing num at grid[row][col] is valid
bool isValid(int grid[N][N], int row, int col, int num) {
    // Check if the number is already in the row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;
    
    // Check if the number is already in the column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check if the number is in the 3x3 sub-grid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true; // If no conflicts, it's valid
}

// Recursive function to solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool emptyCell = false;

    // Find an empty cell (marked as 0)
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                emptyCell = true;
                break;
            }
        }
        if (emptyCell)
            break;
    }

    // No empty cells means the Sudoku is solved
    if (!emptyCell)
        return true;

    // Try placing numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num; // Place the number
            
            // Recursively try to solve the rest of the grid
            if (solveSudoku(grid))
                return true;

            // If the current number doesn't lead to a solution, backtrack
            grid[row][col] = 0; // Reset the cell
        }
    }

    return false; // Trigger backtracking
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}
