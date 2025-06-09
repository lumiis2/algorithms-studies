using JuMP, Gurobi

function vertex_cover(n, edges)
    model = Model(Gurobi.Optimizer)
    @variable(model, x[1:n], Bin)

    for (u, v) in edges
        @constraint(model, x[u] + x[v] ≥ 1)
    end

    @objective(model, Min, sum(x))

    optimize!(model)
    return value.(x)
end

n = 4
edges = [(1, 2), (1, 3), (2, 4)]
println("Vertex Cover: ", vertex_cover(n, edges))
