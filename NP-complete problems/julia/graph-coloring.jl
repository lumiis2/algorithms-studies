function graph_coloring(n, edges, k)
    model = Model(Gurobi.Optimizer)
    @variable(model, x[1:n, 1:k], Bin)

    # Cada vértice recebe uma cor
    for i in 1:n
        @constraint(model, sum(x[i, c] for c in 1:k) == 1)
    end

    # Vértices adjacentes não podem ter a mesma cor
    for (u, v) in edges
        for c in 1:k
            @constraint(model, x[u, c] + x[v, c] ≤ 1)
        end
    end

    @objective(model, Min, 0)  # Só verifica viabilidade com k cores

    optimize!(model)
    return value.(x)
end

k = 3
println("Graph Coloring (3 cores):")
display(graph_coloring(n, edges, k))
