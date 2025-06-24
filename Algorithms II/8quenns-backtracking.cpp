#include <iostream>
#include <vector>
using namespace std;

const int N = 8;
int board[N][N] = {0};

bool isSafe(int row, int col) {
    // Verifica a coluna
    for (int i = 0; i < row; i++) {
        if (board[i][col]) return false;
    }

    // Verifica a diagonal superior esquerda
    for (int i = row - 1, j = col - 1; i >=0 && j >=0; i--, j--) {
        if (board[i][j]) return false;
    }

    // Verifica a diagonal superior direita
    for (int i = row - 1, j = col + 1; i >=0 && j < N; i--, j++) {
        if (board[i][j]) return false;
    }

    return true;
}

bool solve(int row) {
    if (row == N) {
        // Solução encontrada, imprime o tabuleiro
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (board[i][j] ? "Q " : ". ");
            }
            cout << endl;
        }
        cout << "---------------------------" << endl;
        return false;  // Retorna false para continuar procurando outras soluções
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;      // Coloca rainha
            if (solve(row + 1))       // Recursão
                return true;
            board[row][col] = 0;      // Backtrack
        }
    }
    return false;  // Se não conseguiu colocar rainha nessa linha
}

int main() {
    solve(0);
    return 0;
}
