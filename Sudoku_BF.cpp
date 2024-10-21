#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef long double ld;

const int BoardSize = 9;
const int CellSize = 3;

int Board[BoardSize][BoardSize];
int Possible_Solutions = 0;

bool check(int ch, int row, int col) {
    // Check row
    for (int i = 0; i < BoardSize; i++) {
        if (Board[row][i] == ch) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < BoardSize; i++) {
        if (Board[i][col] == ch) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int str = (row / CellSize) * CellSize;
    int stc = (col / CellSize) * CellSize;
    for (int dx = 0; dx < CellSize; dx++) {
        for (int dy = 0; dy < CellSize; dy++) {
            if (Board[str + dx][stc + dy] == ch) {
                return false;
            }
        }
    }

    return true;
}

void solver(int row, int col) {
    if (col == BoardSize) {
        solver(row + 1, 0);
        return;
    }
    
    if (row == BoardSize) {
        Possible_Solutions++;
        cout << "Solution\n";
        for (int i = 0; i < BoardSize; i++) {
            for (int j = 0; j < BoardSize; j++) {
                cout << Board[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        return;
    }

    if (Board[row][col]) {
        solver(row, col + 1);
    } else {
        for (int ch = 1; ch <= BoardSize; ch++) {
            if (check(ch, row, col)) {
                Board[row][col] = ch;
                solver(row, col + 1);
                Board[row][col] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            cin >> Board[i][j];
        }
    }

    solver(0,0);
    return 0;
}