function clique(n, edges)
    edge_set = Set(edges)
    complement_edges = [(i, j) for i in 1:n for j in i+1:n if !( (i, j) in edge_set || (j, i) in edge_set )]
    return independent_set(n, complement_edges)
end

println("Clique: ", clique(n, edges))
