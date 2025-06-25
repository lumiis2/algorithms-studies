#include <iostream>
#include <vector>
#include <set>

using namespace std;


/*
### 2-approximate proof ###

In each iteration of the algorithm, we select an arbitrary edge (u,v) and add both endpoints 
u and v to the vertex cover set C. So, each selected edge contributes 2 vertices to the
approximate solution. Now, consider the optimal solution OPT. For any edge (u,v), at least
one of its endpoints must be included in OPT; otherwise, that edge would be uncovered, which
is not allowed in a valid vertex cover. Therefore, for each edge the algorithm selects, at 
least one of its two endpoints is necessarily in the optimal solution. This means that for 
every pair of vertices we add, the optimal solution must include at least one vertex — so 
we add at most twice as many vertices as the optimal.

∣C∣≤2⋅∣OPT∣

This inequality holds for any input graph, meaning that the algorithm's solution is never more
than twice as large as the optimal solution.

*/

int main() {
    int n, m; // n = número de vértices, m = número de arestas
    cin >> n >> m;

    // Lista de adjacência
    vector<vector<int>> adj(n);
    set<pair<int, int>> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.insert({min(u, v), max(u, v)});
    }

    vector<bool> visited(n, false);
    vector<int> cover;

    while (!edges.empty()) {
        // Pega uma aresta arbitrária
        auto [u, v] = *edges.begin();
        edges.erase(edges.begin());

        if (visited[u] || visited[v]) continue;

        // Adiciona u e v ao conjunto cover
        cover.push_back(u);
        cover.push_back(v);
        visited[u] = visited[v] = true;

        // Remove todas as arestas incidentes a u ou v
        for (int nei : adj[u]) {
            edges.erase({min(u, nei), max(u, nei)});
        }
        for (int nei : adj[v]) {
            edges.erase({min(v, nei), max(v, nei)});
        }
    }

    // Saída do conjunto cover
    cout << "Approximate Vertex Cover (size = " << cover.size() << "):\n";
    for (int v : cover) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
