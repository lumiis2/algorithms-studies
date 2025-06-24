#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Estrutura para representar um item
struct Item {
    int value, weight;
    double ratio;
};

// Estrutura de um nó na árvore de busca
struct Node {
    int level;         // Nível na árvore (índice do item atual)
    int profit;        // Lucro acumulado até agora
    int weight;        // Peso acumulado até agora
    double bound;      // Limite superior estimado (relaxação fracionária)

    // Operador para ordenar na fila de prioridade (max-heap pelo bound)
    bool operator<(const Node& other) const {
        return bound < other.bound;  // bound maior = mais prioridade
    }
};

// Função para calcular o bound (limite superior) do lucro possível a partir de um nó
double calculateBound(const Node& node, int n, int capacity, const vector<Item>& items) {
    if (node.weight >= capacity)
        return 0;  // Inviável, passou da capacidade

    double bound = node.profit;
    int totalWeight = node.weight;
    int idx = node.level;

    // Tenta adicionar itens completos enquanto couber
    while (idx < n && totalWeight + items[idx].weight <= capacity) {
        totalWeight += items[idx].weight;
        bound += items[idx].value;
        idx++;
    }

    // Se ainda tiver capacidade, adiciona fração do próximo item
    if (idx < n) {
        int remaining = capacity - totalWeight;
        bound += items[idx].value * ((double)remaining / items[idx].weight);
    }

    return bound;

    // isso tá em O(n) Poderíamos pré-processar somas acumuladas de valores e pesos,
    // e transformar o cálculo do bound em praticamente O(1) para somas inteiras + uma divisão para a fração.
}

int knapsack(int capacity, const vector<Item>& items) {
    int n = items.size();

    // Fila de prioridade (max-heap) organizada pelo maior bound
    priority_queue<Node> pq;

    // Nó inicial (root)
    Node root;
    root.level = 0;
    root.profit = 0;
    root.weight = 0;
    root.bound = calculateBound(root, n, capacity, items);
    pq.push(root);

    int maxProfit = 0;

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        // Se o bound do nó for menor que a melhor solução, ignora
        if (node.bound <= maxProfit)
            continue;

        // Próximo nível
        int level = node.level;

        // Se passou do último item, continua
        if (level >= n)
            continue;

        // ----- Escolher incluir o item -----
        Node withItem;
        withItem.level = level + 1;
        withItem.weight = node.weight + items[level].weight;
        withItem.profit = node.profit + items[level].value;

        // Se não excede a capacidade, verifica se é melhor solução
        if (withItem.weight <= capacity) {
            if (withItem.profit > maxProfit)
                maxProfit = withItem.profit;

            withItem.bound = calculateBound(withItem, n, capacity, items);
            if (withItem.bound > maxProfit)
                pq.push(withItem);
        }

        // ----- Escolher não incluir o item -----
        Node withoutItem;
        withoutItem.level = level + 1;
        withoutItem.weight = node.weight;
        withoutItem.profit = node.profit;
        withoutItem.bound = calculateBound(withoutItem, n, capacity, items);

        if (withoutItem.bound > maxProfit)
            pq.push(withoutItem);
    }

    return maxProfit;
}

int main() {
    // Exemplo de entrada
    vector<Item> items = {
        {40, 2},
        {30, 5},
        {50, 10},
        {10, 5}
    };

    // Calcula razão valor/peso
    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }

    // Ordena os itens por valor/peso decrescente
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    int capacity = 16;

    int result = knapsack(capacity, items);
    cout << "Maximum profit = " << result << endl;

    return 0;
}
