% Verifica se todos os elementos de Set estão na união de Cover
covers_all(Set, Cover) :-
    flatten(Cover, FlatCover),
    sort(FlatCover, UniqueCover),
    subset(Set, UniqueCover).

% CoverDecision(+Set, +Subsets, +Goal, -Cover)
CoverDecision(Set, Subsets, Goal, Cover) :-
    length(Cover, N),
    N =< Goal,
    subset(Cover, Subsets),
    covers_all(Set, Cover).

% coverOptimization(+Set, +Subsets, -Cover)
coverOptimization(Set, Subsets, Cover) :-
    length(Subsets, Max),
    between(1, Max, Goal),
    CoverDecision(Set, Subsets, Goal, Cover),
    !.  % corta na primeira solução (a menor)