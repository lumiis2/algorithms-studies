#include <iostream>
#include <vector>
using namespace std;

int n;  // Número de vértices
int k;  // Número de cores

vector<vector<int>> adj;  // Lista de adjacência
vector<int> color;        // Cor de cada vértice (0 = não colorido)

// Verifica se é seguro colorir o vértice v com a cor c
bool isValid(int v, int c) {
    for (int neighbor : adj[v]) {
        if (color[neighbor] == c) {
            return false;  // Vizinhos não podem ter a mesma cor
        }
    }
    return true;
}

// Backtracking
bool solve(int v) {
    if (v == n) {
        // Todos os vértices foram coloridos
        cout << "Valid coloring: ";
        for (int i = 0; i < n; i++) {
            cout << color[i] << " ";
        }
        cout << endl;
        return true;  // Para uma solução, ou comente se quiser todas
    }

    for (int c = 1; c <= k; c++) {
        if (isValid(v, c)) {
            color[v] = c;
            if (solve(v + 1)) {
                return true;  // Para na primeira solução
            }
            color[v] = 0;  // Backtrack
        }
    }

    return false;
}

int main() {
    // Exemplo: grafo de 4 vértices (formando um ciclo)
    n = 4;
    k = 3;
    adj = {
        {1, 2},  // Vértice 0 conecta com 1 e 2
        {0, 2, 3},
        {0, 1, 3},
        {1, 2}
    };

    color.assign(n, 0);

    if (!solve(0)) {
        cout << "No valid coloring with " << k << " colors." << endl;
    }

    return 0;
}
