#include <iostream>
#include <vector>
using namespace std;

// Função de backtracking
bool subsetSum(const vector<int>& nums, int index, int target, vector<int>& current) {
    if (target == 0) {
        cout << "Subset found: ";
        for (int num : current) {
            cout << num << " ";
        }
        cout << endl;
        return true;  // Encontrou uma solução
    }

    if (index == nums.size() || target < 0) {
        return false;  // Caso base: passou do fim ou excedeu o alvo
    }

    // Escolher o elemento nums[index]
    current.push_back(nums[index]);
    if (subsetSum(nums, index + 1, target - nums[index], current)) {
        return true;  // Se quiser parar na primeira solução
    }
    current.pop_back();  // Backtrack

    // Não escolher o elemento nums[index]
    if (subsetSum(nums, index + 1, target, current)) {
        return true;
    }

    return false;
}

int main() {
    vector<int> nums = {3, 34, 4, 12, 5, 2};
    int target = 9;

    vector<int> current;
    if (!subsetSum(nums, 0, target, current)) {
        cout << "No subset found with sum " << target << endl;
    }

    return 0;
}
