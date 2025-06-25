#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

const double INF = 1e9;

struct Point {
    double x, y;
};

double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

vector<vector<double>> buildGraph(const vector<Point>& points) {
    int n = points.size();
    vector<vector<double>> graph(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = dist(points[i], points[j]);
    return graph;
}

vector<vector<int>> primMST(const vector<vector<double>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<double> key(n, INF);
    vector<int> parent(n, -1);
    key[0] = 0;

    for (int count = 0; count < n; count++) {
        double minKey = INF;
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && key[v] < minKey)
                minKey = key[v], u = v;

        visited[u] = true;
        for (int v = 0; v < n; v++)
            if (graph[u][v] < key[v] && !visited[v])
                key[v] = graph[u][v], parent[v] = u;
    }

    vector<vector<int>> mst(n);
    for (int i = 1; i < n; i++) {
        mst[i].push_back(parent[i]);
        mst[parent[i]].push_back(i);
    }
    return mst;
}

vector<pair<int, int>> minPerfectMatchingBrute(const vector<int>& nodes, const vector<vector<double>>& graph) {
    double best = INF;
    vector<pair<int, int>> bestMatching;

    vector<int> perm = nodes;
    sort(perm.begin(), perm.end());

    do {
        double cost = 0;
        vector<pair<int, int>> matching;
        bool valid = true;
        for (int i = 0; i < (int)perm.size(); i += 2) {
            if (i + 1 >= (int)perm.size()) { valid = false; break; }
            cost += graph[perm[i]][perm[i + 1]];
            matching.emplace_back(perm[i], perm[i + 1]);
        }
        if (valid && cost < best) {
            best = cost;
            bestMatching = matching;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    return bestMatching;
}

void dfsEuler(int u, const vector<vector<int>>& adj, vector<vector<bool>>& used, vector<int>& path) {
    for (int& v : const_cast<vector<int>&>(adj[u])) {
        if (!used[u][v]) {
            used[u][v] = used[v][u] = true;
            dfsEuler(v, adj, used, path);
        }
    }
    path.push_back(u);
}

pair<vector<int>, double> christofides(const vector<Point>& points) {
    int n = points.size();
    auto graph = buildGraph(points);
    auto mst = primMST(graph);

    vector<int> degree(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : mst[u])
            degree[u]++;

    vector<int> oddNodes;
    for (int i = 0; i < n; i++)
        if (degree[i] % 2 != 0)
            oddNodes.push_back(i);

    auto matching = minPerfectMatchingBrute(oddNodes, graph);
    vector<vector<int>> multigraph = mst;
    for (auto [u, v] : matching) {
        multigraph[u].push_back(v);
        multigraph[v].push_back(u);
    }

    vector<vector<bool>> used(n, vector<bool>(n, false));
    vector<int> eulerPath;
    dfsEuler(0, multigraph, used, eulerPath);

    vector<int> tour;
    vector<bool> visited(n, false);
    for (int v : eulerPath)
        if (!visited[v]) tour.push_back(v), visited[v] = true;
    tour.push_back(tour[0]);

    double cost = 0;
    for (int i = 0; i < (int)tour.size() - 1; i++)
        cost += graph[tour[i]][tour[i + 1]];

    return {tour, cost};
}

int main() {
    vector<Point> points = {{0, 0}, {1, 3}, {4, 3}, {6, 1}, {3, 0}};
    
    auto [tour2, cost2] = christofides(points);
    cout << "Christofides: ";
    for (int v : tour2) cout << v << " ";
    cout << "\nCost: " << cost2 << "\n";

    return 0;
}
