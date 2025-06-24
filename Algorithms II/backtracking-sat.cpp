#include <iostream>
#include <vector>
using namespace std;

// Representação de cláusulas: cada cláusula é um vetor de inteiros
// Literal positivo = variável verdadeira, negativo = falsa
vector<vector<int>> clauses = {
    {1, -2},
    {-1, 3},
    {2, 3}
};

int num_vars = 3;  // Número de variáveis

bool isSatisfied(const vector<int>& assignment) {
    for (const auto& clause : clauses) {
        bool clause_satisfied = false;
        for (int literal : clause) {
            int var = abs(literal);
            bool value = assignment[var];
            if (literal > 0 && value) clause_satisfied = true;
            if (literal < 0 && !value) clause_satisfied = true;
        }
        if (!clause_satisfied) return false;
    }
    return true;
}

bool solveSAT(int var, vector<int>& assignment) {
    if (var > num_vars) {
        if (isSatisfied(assignment)) {
            cout << "Satisfying assignment: ";
            for (int i = 1; i <= num_vars; i++) {
                cout << (assignment[i] ? "T " : "F ");
            }
            cout << endl;
            return true;
        }
        return false;
    }

    // Tenta verdadeiro
    assignment[var] = 1;
    if (solveSAT(var + 1, assignment)) return true;

    // Tenta falso (backtrack)
    assignment[var] = 0;
    if (solveSAT(var + 1, assignment)) return true;

    return false;
}

int main() {
    vector<int> assignment(num_vars + 1, 0);  // Vetor 1-indexado
    if (!solveSAT(1, assignment)) {
        cout << "No satisfying assignment found." << endl;
    }
    return 0;
}
