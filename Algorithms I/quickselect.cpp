#include <iostream>
#include <vector>
#include <cstdlib>  // Para rand()
#include <ctime>    // Para srand()

using namespace std;

// Função para particionar o vetor em relação ao pivô
int partition(vector<int>& arr, int left, int right, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    swap(arr[pivotIndex], arr[right]); // Move o pivô para o fim
    int storeIndex = left;

    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            swap(arr[storeIndex], arr[i]);
            storeIndex++;
        }
    }
    swap(arr[storeIndex], arr[right]); // Move pivô para sua posição final
    return storeIndex;
}

// Quickselect para encontrar o k-ésimo menor elemento
int quickselect(vector<int>& arr, int left, int right, int k) {
    if (left == right)
        return arr[left];

    int pivotIndex = left + rand() % (right - left + 1);

    pivotIndex = partition(arr, left, right, pivotIndex);

    if (k == pivotIndex)
        return arr[k];
    else if (k < pivotIndex)
        return quickselect(arr, left, pivotIndex - 1, k);
    else
        return quickselect(arr, pivotIndex + 1, right, k);
}

// Função para calcular a mediana
int mediana(vector<int> arr) {
    int n = arr.size();
    int k = n / 2;

    if (n % 2 == 1) {
        return quickselect(arr, 0, n - 1, k);
    } else {
        int a = quickselect(arr, 0, n - 1, k - 1);
        int b = quickselect(arr, 0, n - 1, k);
        return (a + b) / 2; // Média dos dois valores centrais (para inteiros)
    }
}

int main() {
    srand(time(0)); // Inicializa o gerador de números aleatórios

    vector<int> lista = {7, 3, 5, 1, 9, 2};

    cout << "Mediana: " << mediana(lista) << endl;

    return 0;
}
