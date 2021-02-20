% Все передвижения шаров, которые могут быть
move(A,B) :- append(Begin,[b,X|End],A), append(Begin,[X,b|End],B).
move(A,B) :- append(Begin,[X,b|End],A), append(Begin,[b,X|End],B).
move(A,B) :- append(Begin,[w,X|End],A), append(Begin,[X,w|End],B).
move(A,B) :- append(Begin,[X,w|End],A), append(Begin,[w,X|End],B).


% Предикат вывода результата
answer_print([_]) :- !.

answer_print([A,B|T]) :- answer_print([B|T]), nl, 
    write(B), write(' -> '), write(A).


% Предикат продления пути с предотвращением петель
prolong([X|T], [Y,X|T]) :-
    move(X, Y),
    not(member(Y, [X|T])).


% Предикат рекурсивного поиска в глубину
depth([Finish|T], Finish, [Finish|T]).

depth(TPath, Finish, Path) :- prolong(TPath, NewPath), depth(NewPath, Finish, Path).

% Предикат выполнения поиска в глубину
depth_search(Start, Finish) :- 
    get_time(Begin),
    depth([Start], Finish, Path), 
    answer_print(Path), 
    get_time(End), nl,
    ResultTime is End - Begin,
    write('Search time is: '), write(ResultTime).


% Предикат рекурсивного поика в ширину
breadth([[X|T]|_], X, [X|T]).

% Продление первого пути в очереди всеми возможными способами
breadth([P|Q1], X, R) :- findall(Y, prolong(P, Y), T),
    append(Q1, T, Q2), !,
    breadth(Q2, X, R).

breadth([_|T], Y, L) :- breadth(T, Y, L).

% Предикат выполнения поиска в ширину
breadth_search(Start, Finish) :- 
    get_time(Begin),
    breadth([[Start]], Finish, Path),
    answer_print(Path),
    get_time(End), nl,
    ResultTime is End - Begin,
    write('Search time is: '), write(ResultTime).


% Предикат подсчёта высоты глубины 
depth_id([Finish|T], Finish, [Finish|T], 0).

depth_id(Path, Finish, R, N) :- 
    N > 0,
    prolong(Path,NewPath),
    N1 is N-1,
    depth_id(NewPath,Finish,R,N1).


% Предикат, генерирующий глубину поиска от 1 и далее
int(1).
int(K) :- int(N), K is N+1.

iterative_search(Start, Finish, Path, DepthLimit) :- depth_id([Start], Finish, Path, DepthLimit).

% Рекурсивный поиск в глубину с итеративным заглублением
iterative_search(Start, Finish, Path) :- 
    int(Limit),
    iterative_search(Start, Finish, Path, Limit).

% Предикат выполнения поиска в глубину с итеративным углублением 
iterative_search(Start, Finish) :- 
    get_time(Begin),
    iterative_search(Start,Finish, Path), 
    answer_print(Path), 
    get_time(End), nl,
    ResultTime is End - Begin,
    write('Search time is: '), write(ResultTime).



