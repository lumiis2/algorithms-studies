## NP-Complete Problems

Here I’m studying the most common and classic NP-complete problems and their variations. These problems frequently appear in programming and algorithm courses, so it is important to understand their concepts deeply. Mastering these problems helps to generalize solutions and strategies when working on other types of optimization or decision problems.
The idea is to both model the problems using Julia and solve them using C++. The Julia models use the Gurobi solver, ensuring that a correct formulation yields an optimal solution. This allows me to validate my C++ implementation by comparing it against the result from the solver.
---

### 0/1 Knapsack Problem

**Definition:**  
The 0/1 Knapsack Problem consists of selecting a subset of `n` items, each with a value `vᵢ` and weight `wᵢ`, to include in a knapsack with a total capacity `B`. The goal is to maximize the total value of the selected items without exceeding the knapsack's weight capacity. Each item can be either included (1) or not included (0), hence the name "0/1".

---

**Modeling Idea (Julia):**  
In Julia, this problem can be formulated as an Integer Linear Programming (ILP) problem. We define binary decision variables `xᵢ` such that `xᵢ = 1` if item `i` is included, and `0` otherwise.

---

**Solving Strategy (C++):**  
In C++, we usually solve this using dynamic programming. Let `dp[i][w]` be the maximum value achievable using the first `i` items with a total weight limit of `w`.
