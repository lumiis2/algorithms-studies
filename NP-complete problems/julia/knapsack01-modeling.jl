using JuMP
using Gurobi

function knapsack(weights, values, capacity)
    n = length(weights)
    model = Model(Gurobi.Optimizer)
    @variable(model, x[1:n], Bin)

    @constraint(model, sum(weights[i] * x[i] for i in 1:n) ≤ capacity)
    @objective(model, Max, sum(values[i] * x[i] for i in 1:n))

    optimize!(model)
    return value.(x)
end

weights = [2, 3, 4, 5]
values = [3, 4, 5, 6]
capacity = 5
println("Knapsack 0/1: ", knapsack(weights, values, capacity))

solution = knapsack(weights, values, capacity)
println("Knapsack 0/1 solution: ", solution)


