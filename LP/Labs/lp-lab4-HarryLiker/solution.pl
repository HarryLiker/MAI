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