% multiknap(Pantry, Capacity, Knapsack)
multiknap(Pantry, Capacity, Knapsack) :-
    multiknap_aux(Pantry, Capacity, [], 0, 0, Knapsack).

% multiknap_aux(Pantry, CapRestante, KnapTemp, ValorTemp, PesoTemp, KnapFinal)
% tenta escolher itens para maximizar valor respeitando capacidade
multiknap_aux([], _, Knapsack, _, _, Knapsack).

multiknap_aux([food(Name, W, V)|Rest], Capacity, KnapTemp, ValTemp, PesoTemp, KnapFinal) :-
    % tenta escolher k cópias deste item, com k >= 0
    max_copies(Capacity, PesoTemp, W, MaxCopies),
    try_copies(0, MaxCopies, food(Name, W, V), Rest, Capacity, KnapTemp, ValTemp, PesoTemp, KnapFinal).

# % calcula o máximo de cópias possíveis dado o peso atual e capacidade
max_copies(Capacity, PesoTemp, W, MaxCopies) :-
    MaxCopies is (Capacity - PesoTemp) // W.

% tenta todas as quantidades possíveis de cópias e escolhe a melhor solução
try_copies(K, MaxK, _, _, _, KnapTemp, ValTemp, PesoTemp, KnapFinal) :-
    K > MaxK,
    !,
    fail.
try_copies(K, MaxK, Item, Rest, Capacity, KnapTemp, ValTemp, PesoTemp, KnapFinal) :-
    K =< MaxK,
    Item = food(Name, W, V),
    NewPeso is PesoTemp + K * W,
    NewVal is ValTemp + K * V,
    append_n_copies(K, Item, KnapTemp, NewKnapTemp),
    multiknap_aux(Rest, Capacity, NewKnapTemp, NewVal, NewPeso, Candidate),
    % tenta próxima quantidade maior e guarda o melhor resultado
    ( try_copies(K+1, MaxK, Item, Rest, Capacity, KnapTemp, ValTemp, PesoTemp, KnapFinal)
    -> better_knapsack(Candidate, KnapFinal)
    ;  KnapFinal = Candidate
    ).
    
% adiciona K cópias do Item à lista
append_n_copies(0, _, L, L).
append_n_copies(K, Item, L, Result) :-
    K > 0,
    K1 is K - 1,
    append(L, [Item], L1),
    append_n_copies(K1, Item, L1, Result).

% escolhe o melhor entre duas soluções (a de maior valor)
better_knapsack(Knap1, Knap2) :-
    value_knapsack(Knap1, V1),
    value_knapsack(Knap2, V2),
    (V1 >= V2 -> Knap2 = Knap1 ; Knap2 = Knap2).

% calcula o valor total de um knapsack
value_knapsack([], 0).
value_knapsack([food(_,_,V)|T], Total) :-
    value_knapsack(T, Rest),
    Total is Rest + V.
