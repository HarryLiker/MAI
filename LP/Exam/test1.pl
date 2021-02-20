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

% Находит последний элемент списка
f([X],X).
f([_|T], X) :- f(T, X).

% Удаление из списка заданного элемента
h(X, [X|T], T).
h(X, [Y|T], [Y|Z]) :- h(X,T,Z).

% Сумма элементов в списке
summ(L,N) :- summ(L, 0, N).
summ([X|T], S, N) :- S1 is S+X, summ(T,S1,N).
summ([],N,N).


% Перевод в префиксную и постфиксную форму
razb(X,List):-X=..[A,B,C],razb(B,List1),razb(C,List2),string_chars(A,Op),append(Op,List1,Listh),append(Listh,List2,List),!.
razb(X,[X]):-!.

razb(X,List):-X=..[A,B,C],razb(B,List1),razb(C,List2),string_chars(A,Op),append(List1,List2,Listh),append(Listh,Op,List),!.
razb(X,[X]):-!.


% Удаление последнего элемента в списке
del_last([_],[]).

del_last([H|T1],[H|T2]):-del_last(T1,T2).

subst(Z1,Z2,X,Res):-X=..[A,B,C],subst(Z1,Z2,B,B1),subst(Z1,Z2,C,C1),Res=..[A,B1,C1],!.

subst(Z1,Z2,Z1,Z2):-!.

subst(Z1,_,X,X):-X\=Z1,!.



% Вариант 4

% Проход справа налево
% Созданы стек и список. В стек будут помещаться операции, а в список = операнды

% Заданный приоритет операций
not_priority([], '+').
not_priority([], '-').
not_priority([], '*').
not_priority([], '/').

not_priority('+', '*').
not_priority('+', '/').

not_priority('-', '*').
not_priority('-', '/').

priority('+', []).
priority('+', '+').
priority('+', '-').

priority('-', []).
priority('-', '+').
priority('-', '-').

priority('*', []).
priority('*', '+').
priority('*', '-').
priority('*', '*').
priority('*', '/').

priority('/', []).
priority('/', '+').
priority('/', '-').
priority('/', '/').
priority('/', '*').

% Проверка нового элемента на число или операцию
is_number(X) :- number(X).

% Предикат удаления вершины из стека
delete_from_stack([], []).
delete_from_stack([_|Stack], NewStack) :- NewStack = Stack.

%Добавление операции в список

% Предикат нахождения вершины списка
get_top([], []).
get_top([X|_], X).


% Удаление всех элементов из стека, которые выше по приоритету, чем заданная операция, до первого встречного элемента с таким же приоритетом.
% В итоге все эти элементы удалятся и результатом будет изменённый стек
delete_sequence(_,[],[]) :- !.

delete_sequence('*', _, []) :- !.
delete_sequence('/', _, []) :- !.

delete_sequence('-', [X|List],Result) :- (X = '-'; X = '+'), Result = [X|List], !.
delete_sequence('-', [X|List], Result) :- X\='-', X\='+', delete_sequence('-', List, Result), !.

delete_sequence('+', [X|List], Result) :- (X='-'; X='+'), Result = [X|List], !.
delete_sequence('+', [X|List], Result) :- X\='-', X\='+', delete_sequence('+', List, Result), !.


% Нахождение элементов стека, которые выше по приоритету, чем заданная операция, до первого всречного с таким же приоритетом и запись их в отдельный список
save(_, [], []) :- !.

save('*', _, []) :- !.
save('/', _, []) :- !. 

save('-', [X|_], []) :- (X='+'; X='-'), !.
save('-', [X|Stack], [X|List]) :- not_priority('-', X), save('-', Stack, List), !.

save('+', [X|_], []) :- (X='+'; X='-'), !.
save('+', [X|Stack], [X|List]) :- not_priority('+', X), save('+', Stack, List), !.


expression_walk([],[],[]).

% Если элемент - число, то добавляем его в список
expression_walk(Expression, Stack, List) :- append([X], PrevExpression, Expression), 
    append([X], PrevList, List), 
    is_number(X), 
    expression_walk(PrevExpression, Stack, PrevList), !.

% Если приоритет новой операции выше, чем на вершине стека, то она добавляется в стек.
expression_walk(Expression, Stack, List) :- append([X], PrevExpression, Expression), 
    append([X], PrevStack, Stack),
    not(is_number(X)), 
    get_top(PrevStack, Y),
    priority(X, Y), 
    expression_walk(PrevExpression, PrevStack, List), !.

% Если приоритет новой операции ниже или равен, чем на вершине стека, то все первые элементы, которые выше по приоритету, чем указанная операция, с вершины стека помещаются в список, а эта новая операция добавляется в стек.
expression_walk(Expression, Stack, List) :- append([X], PrevExpression, Expression), 
    append([X], NStack, Stack), 
    append(Result, PrevList, List), 
    not(is_number(X)),   
    get_top(LastStack, Y), 
    not_priority(X,Y),
    expression_walk(PrevExpression, LastStack, PrevList), 
    delete_sequence(X, LastStack, NStack), 
    save(X, LastStack, AddInList), 
    reverse(AddInList, Result), !.

calculate(Expression, X) :- expression_walk(Expression, Stack, List), 
    reverse(Stack, NewStack), 
    append(NewStack, List, X), !.