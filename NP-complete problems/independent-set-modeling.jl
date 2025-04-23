function independent_set(n, edges)
    model = Model(Gurobi.Optimizer)
    @variable(model, x[1:n], Bin)

    for (u, v) in edges
        @constraint(model, x[u] + x[v] ≤ 1)
    end

    @objective(model, Max, sum(x))

    optimize!(model)
    return value.(x)
end

println("Independent Set: ", independent_set(n, edges))
