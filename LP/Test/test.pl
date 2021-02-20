% Нахождение длины списка
mylength([], 0).
mylength([_|X], N) :- mylength(X, K), N is K+1.

% Проверка на принадлежность элемента списку
mymember(X, [X|_]).
mymember(X, [_|Y]) :- mymember(X,Y).

%Конкатенация списков
myappend([], X, X).
myappend([C|X], Y, [C|Z]) :- myappend(X, Y, Z).

% Удаление элемента из списка 
myremove(X, [X|Y], Y).
myremove(X, [K|Y], [K|Z]) :- myremove(X,Y,Z).

% Перестановки элементов в списке
mypermute([], []).
mypermute(X, [K|Y]) :- myremove(K, X, Z), mypermute(Z,Y).

mysublist(Sublist, List) :- myappend(_, List2, List), myappend(Sublist, _, List2).


% Счётчик
numerator(0).
numerator(N) :- numerator(M), N is M + 1.

% Нахождение факториала
factorial(0, 1).
factorial(X, Result) :- factorial(Y, Res1), X is Y + 1, Result is (Res1 * (Y+1)).

% Поиск в глубину
dfs(A,[A|Path],[A|Path]).
dfs(A,[Y|Path1],Path) :- 
    exist(X,Y), % Ребро
    not(member(X,Path1)),
    dfs(A,[X,Y|Path1],Path).

% Поиск в ширину
bfs([[Node|Path]|_],Node,[Node|Path]).
bfs([[B|Path]|Paths],Z,Solution) :- 
    findall(S, new_node(B,S,Path), NewPaths),
    conc(Paths,NewPaths,Paths1),!, 
    bfs(Paths1,Z,Solution);bfs(Paths,Z,Solution).  

new_node(B,S,Path) :- 
    exist(B,B1), 
    not(member(B1,[B|Path])), 
    S=[B1,B|Path].

% Реверс списка
rev(X,Y):- 
    rev([],X,Y).  
rev(Y,[],Y).  
rev(X1,[Z|X2],Y):- 
    rev([Z|X1],X2,Y).

% Проверяет, являются ли все множители числа различными
unique_factors(X) :- factor(X, L), uniq(L).
% Раскладывает число на простые сомножители
factor(X, L) :- factor(2, X, [], L).
factor(N, X, L, R) :- X mod N =\= 0, N1 is N+1, N1 =< X, factor(N1, X, L, R).
factor(N,X,L,R) :- 0 is X mod N, X1 is X/N, factor(N, X1, [N|L], R).
factor(N,X,L,L) :- N > X.

%uniq([]).
%uniq([X|T]) :- not_member(X, T), uniq(T).

not_member(X, []).
not_member(X, [Y|T]) :- X \= Y, not_member(X,T).

uniq([]).
uniq([X|T]) :- not(member(X,T)), uniq(T).

p([_]).
p([_,_|X]) :- p(X), write(X).

% Фибоначчи с помощью хвостовой рекурсии
fib(1,1):- !.
fib(2,1):- !.
fib(N,F):- N1 is N-1,
fib(N1,F1),
N2 is N-2,
fib(N2,F2),
F is F1+F2.

k([_|X], A) :- k(X,A).
k([X],X).

f([X],X).
f([_|T], X) :- f(T, X).

h(X, [X|T], T).
h(X, [Y|T], [Y|Z]) :- h(X,T,Z).



v([H|T],N) :- v(T,N1), N1 is N-1.
v([], 0).
















fact(0, 1).
fact(N, F) :- N1 is N-1, fact(N1, F1), F is F1*N.

% Функция нахождения последнего элемента списка
last(X, List) :- append([], [X], List).

% Функция вычисления суммы элементов списка с помощью хвостовой рекурсии
sum(L, N) :- sum(L, 0, N).
sum([X|T], S, N) :- S1 is S + X, sum(T, S1, N).
sum([],N,N).

last3(L, [X,Y,Z]) :- append(_, [X,Y,Z], L), !.

p([X,_|T], [X|R]) :- p(T,R).
p([],[]).
p([X],[X]).

% Предикат нахождения 5, 3
st(F, 1, F) :- !.
st(Y, N, X) :- N1 is N-1, st(Y, N1, X1), X is X1*Y.