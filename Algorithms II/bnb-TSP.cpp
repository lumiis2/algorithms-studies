#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

struct Node {
    vector<int> path;     // Caminho percorrido até agora
    vector<bool> visited; // Quais cidades já foram visitadas
    int cost;             // Custo acumulado
    int bound;            // Estimativa inferior de custo total
    int level;            // Nível na árvore (quantas cidades já visitamos)

    bool operator<(const Node& other) const {
        return bound > other.bound;  // Min-heap pelo menor bound (prioridade mais alta)
    }
};

// Calcula o bound de um nó
int calculateBound(const Node& node, const vector<vector<int>>& dist, int n) {
    int bound = node.cost;

    // Para cada cidade não visitada, adiciona o menor custo de saída
    for (int i = 0; i < n; i++) {
        if (!node.visited[i]) {
            int min_out = INF;
            for (int j = 0; j < n; j++) {
                if (i != j && (!node.visited[j] || j == node.path[0])) {
                    min_out = min(min_out, dist[i][j]);
                }
            }
            if (min_out != INF)
                bound += min_out;
        }
    }

    return bound;
}

int tspBranchAndBound(const vector<vector<int>>& dist) {
    int n = dist.size();
    priority_queue<Node> pq;

    Node root;
    root.path.push_back(0);          // Começa da cidade 0
    root.visited.assign(n, false);
    root.visited[0] = true;
    root.level = 1;
    root.cost = 0;
    root.bound = calculateBound(root, dist, n);
    pq.push(root);

    int bestCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.bound >= bestCost)
            continue;  // Poda

        if (node.level == n) {
            int last = node.path.back();
            int totalCost = node.cost + dist[last][0];  // volta à cidade inicial
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestPath = node.path;
            }
            continue;
        }

        int current = node.path.back();

        for (int next = 0; next < n; next++) {
            if (!node.visited[next] && dist[current][next] != INF) {
                Node child = node;
                child.path.push_back(next);
                child.visited[next] = true;
                child.level = node.level + 1;
                child.cost = node.cost + dist[current][next];
                child.bound = calculateBound(child, dist, n);

                if (child.bound < bestCost) {
                    pq.push(child);
                }
            }
        }
    }

    cout << "Melhor custo: " << bestCost << endl;
    cout << "Caminho: ";
    for (int city : bestPath) cout << city << " ";
    cout << "0\n";  // retorna à cidade inicial

    return bestCost;
}

int main() {
    // Matriz de distâncias entre as cidades (INF representa ausência de aresta)
    vector<vector<int>> dist = {
        {INF, 10, 15, 20},
        {10, INF, 35, 25},
        {15, 35, INF, 30},
        {20, 25, 30, INF}
    };

    tspBranchAndBound(dist);

    return 0;
}
