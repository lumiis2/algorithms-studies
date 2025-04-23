#include <bits/stdc++.h>

using namespace std;

// dp[i][w] maximum value achievable using the first i items with a total weight limit of w

int knapsack(const vector<int>& values, const vector<int>& weights, int capacity) { // bottom up
    int n = values.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i - 1] <= w) { // if the weight of my i object is less then the capacity
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]); // add the object
            } else {
                dp[i][w] = dp[i - 1][w]; // mantain
            }
        }
    }
    
    return dp[n][capacity]; // solution using n objects and maximum capacity
}

int main() {
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int capacity = 5;

    int max_value = knapsack(values, weights, capacity);
    cout << "Maximum value that can be carried: " << max_value << endl;

    return 0;
}