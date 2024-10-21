#include <bits/stdc++.h> 

using namespace std;
typedef long long int ll; 
typedef long double ld; 

const int BoardSize = 9; // Sudoku board size (9x9)
const int CellSize = 3; // Subgrid size (3x3)

int Board[BoardSize][BoardSize]; // Stores the current state of the Sudoku board
int Possible_Solutions = 0; // Counter for the number of possible Sudoku solutions

// Arrays to keep track of numbers taken in each row, column, and subgrid
int takenrow[BoardSize]; 
int takencol[BoardSize]; 
int takengrid[CellSize][CellSize]; 

// Function to make a move by placing a number (ch) on the board at position (row, col)
void makemove(int ch, int row, int col) {
    Board[row][col] = ch; // Place the number on the board
    takenrow[row] |= (1 << ch); // Mark the number as used in the row
    takencol[col] |= (1 << ch); // Mark the number as used in the column
    takengrid[row / CellSize][col / CellSize] |= (1 << ch); // Mark the number as used in the subgrid
}

// Function to revert a move (i.e., remove a number from the board)
void revertmove(int ch, int row, int col) {
    Board[row][col] = 0; // Remove the number from the board
    takenrow[row] ^= (1 << ch); // Unmark the number from the row
    takencol[col] ^= (1 << ch); // Unmark the number from the column
    takengrid[row / CellSize][col / CellSize] ^= (1 << ch); // Unmark the number from the subgrid
}

// Function to get all possible numbers (choices) that can be placed at position (row, col)
int getchoices(int row, int col) {
    // Combine taken numbers in the current row, column, and subgrid
    int taken = takenrow[row] | takencol[col] | takengrid[row / CellSize][col / CellSize]; 
    // Determine which numbers are not taken
    int nottaken = ((1 << (BoardSize + 1)) - 1) ^ taken;
    // Exclude '0' as a possible choice
    if (nottaken & 1) nottaken ^= (1);
    return nottaken; // Return the available choices
}

// Recursive backtracking Sudoku solver function
void solver(int row, int col) {
    // Move to the next row if we reach the end of the current row
    if (col == BoardSize) {
        solver(row + 1, 0);
        return;
    }

    // If we reach the end of the board, we've found a solution
    if (row == BoardSize) {
        Possible_Solutions++; // Increment the solution counter
        cout << "Solution\n"; // Output the solution
        for (int i = 0; i < BoardSize; i++) {
            for (int j = 0; j < BoardSize; j++) {
                cout << Board[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        return;
    }

    // If the current cell is already filled, move to the next cell
    if (Board[row][col]) {
        solver(row, col + 1);
    } 
    else {
        // Get all possible numbers that can be placed in the current cell
        int choices = getchoices(row, col);
        for (int ch = 1; ch <= BoardSize; ch++) {
            if (choices & (1 << ch)) { // Check if the number 'ch' is a valid choice
                makemove(ch, row, col); // Make the move
                solver(row, col + 1); // Recursively solve the rest of the board
                revertmove(ch, row, col); // Backtrack by reverting the move
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); // Optimize input/output performance
    cin.tie(0); // Untie cin from cout for faster input
    cout.tie(0); // Untie cout from cin for faster output

    // Input the initial Sudoku board state
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            int c;
            cin >> c; // Input each cell value
            Board[i][j] = c; // Store the cell value on the board
            if (c) {
                makemove(c, i, j); // Mark the number as used in the row, column, and subgrid
            }
        }
    }

    solver(0, 0); // Start solving the board from the top-left corner (0, 0)
    return 0; // End the program
}
