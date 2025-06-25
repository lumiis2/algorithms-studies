#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Estrutura para representar uma máquina (carga acumulada e índice)
struct Machine {
    int load;
    int index;
    bool operator>(const Machine& other) const {
        return load > other.load; // para min-heap
    }
};

int makespan_2_approx(const vector<int>& tasks, int m) {
    priority_queue<Machine, vector<Machine>, greater<>> pq;
    vector<int> loads(m, 0);

    // Inicializa as m máquinas com carga zero
    for (int i = 0; i < m; i++) {
        pq.push({0, i});
    }

    // Atribui cada tarefa à máquina menos carregada
    for (int t : tasks) {
        Machine mach = pq.top();
        pq.pop();
        loads[mach.index] += t;
        pq.push({loads[mach.index], mach.index});
    }

    // Retorna a carga máxima (makespan final)
    return *max_element(loads.begin(), loads.end());
}

int makespan_1_5_approx(vector<int> tasks, int m) {
    // Ordena as tarefas em ordem decrescente (LPT)
    sort(tasks.rbegin(), tasks.rend());

    priority_queue<Machine, vector<Machine>, greater<>> pq;
    vector<int> loads(m, 0);

    for (int i = 0; i < m; i++) {
        pq.push({0, i});
    }

    for (int t : tasks) {
        Machine mach = pq.top();
        pq.pop();
        loads[mach.index] += t;
        pq.push({loads[mach.index], mach.index});
    }

    return *max_element(loads.begin(), loads.end());
}

int main() {
    int m = 3; // número de máquinas
    vector<int> tasks = {2, 3, 7, 1, 8, 4}; // tempos das tarefas

    int result1 = makespan_2_approx(tasks, m);
    int result2 = makespan_1_5_approx(tasks, m);

    cout << "2-Approx Makespan: " << result1 << endl;
    cout << "1.5-Approx (LPT) Makespan: " << result2 << endl;

    return 0;
}
