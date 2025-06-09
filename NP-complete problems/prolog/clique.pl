sublist([], []).
sublist([X|Xs], [X|Ys]) :- sublist(Xs, Ys).
sublist([_|Xs], Ys) :- sublist(Xs, Ys).

clique([]).
clique([_]).
clique([X|Xs]) :-
    all_connected(X, Xs),
    clique(Xs).

% Verifica se X está conectado a todos os elementos da lista
all_connected(_, []).
all_connected(X, [Y|Ys]) :-
    connected(X, Y),
    all_connected(X, Ys).

% Verifica se há uma aresta entre X e Y (em qualquer ordem)
connected(X, Y) :- edge(X, Y).
connected(X, Y) :- edge(Y, X).

% Arestas do grafo
edge(a, b).
edge(a, c).
edge(b, c).
edge(a, d).
edge(b, e).
edge(d, e).
edge(a, e).