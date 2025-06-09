% nqueens(N, X) - X é uma solução para o problema das N rainhas
nqueens(N, X) :-
    length(X, N),
    range(1, N, Range),
    permutation(Range, X),
    safe(X).

% Gera uma lista de inteiros de A até B
range(A, B, []) :- A > B.
range(A, B, [A|T]) :-
    A =< B,
    A1 is A + 1,
    range(A1, B, T).

% Verifica se a lista de posições X é segura (sem ataques diagonais)
safe([]).
safe([Q|Qs]) :-
    safe(Qs),
    no_attack(Q, Qs, 1).

% Verifica que a rainha Q não ataca as outras rainhas em Qs,
% considerando a distância diagonal (Dif)
no_attack(_, [], _).
no_attack(Q, [Q1|Qs], Dif) :-
    Q =\= Q1 + Dif,
    Q =\= Q1 - Dif,
    Dif1 is Dif + 1,
    no_attack(Q, Qs, Dif1).
