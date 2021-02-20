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

% Вариант 15: Замена всех элементов списка с указанным значением на другое значение

% (Значение, Новое значение, Список, Изменённый список)
change(_, _, [], []).
change(V, N, [Y|L], [Y|S]) :- Y\=V, change(V, N, L, S).
change(V, N, [V|L], [N|S]) :- change(V, N, L, S).

% С использованием стандартных предикатов
std_ch(V, N, List, NewList) :- append([], List, A), change(V, N, A, NewList).

% Вариант 20: Разделение списка на два по порядковому принципу (первый - второй)
% (Начальный список, номер элемента в списке, список первый, список второй)

% Разделение списка на два подсписка
separation([], 0, [], []).
separation([Y|X], N, [Y|A], B) :- separation(X, K, A, B), N is K+1, N mod 2 =:= 0.
separation([Y|X], N, A, [Y|B]) :- separation(X, K, A, B), N is K+1, N mod 2 =:= 1.

% Разделение списка на два подсписка по порядку элементов со стандартным предикатом (Список 1, Список2, Начальный список)
standart_exchange(List2, List1, List) :- separation(List, _, List1, List2), length(List, K), K mod 2 =:= 1.
standart_exchange(List1, List2, List) :- separation(List, _, List1, List2), length(List, K), K mod 2 =:= 0.

% Разделение списка на два подсписка по порядку элементов со стандартным предикатом без стандартных предикатов
exchange(List2, List1, List) :- separation(List, N, List1, List2), N mod 2 =:= 1.
exchange(List1, List2, List) :- separation(List, N, List1, List2), N mod 2 =:= 0.

