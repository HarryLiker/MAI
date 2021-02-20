:- encoding(utf8).

% Task 2: Relational Data
% Вариант 3
% The line below imports the data
:- ['three.pl'].

%group(X,L) :- findall(Z,student(X,Z),L).

% 1 - Для каждого студента найти средний бал и сдал ли он экзамены или нет

% Оценки студента за предметы
grades(Stud, List) :- findall(M, mark_for_subj(Stud, _, M), List).

% Сумма оценок
summ_of_grades([], 0).
summ_of_grades([grade(_, Grade)|L], M) :- summ_of_grades(L, K), M is Grade + K.

% Средний балл студента
average_mark(Stud, Mark) :- student(_, Stud, List), summ_of_grades(List, Sum), length(List, Len), Mark is Sum / Len.

% Проверка на сдачу всех экзаменов
pass(Stud, P) :- grades(Stud, List), member(2, List), P is 1.
pass(Stud, P) :- grades(Stud, List), not(member(2, List)), P is 0.

% Вывод сообщения о сдаче / несдаче экзамена
print_pass(0, 'Все экзамены сданы').
print_pass(1, 'Экзамены не сданы').

% Средний балл студента и сдал ли он экзамены
sr_and_passed(Stud, Mark, P) :- average_mark(Stud, Mark), pass(Stud, K), print_pass(K, P).


% 2 - Для каждого предмета найти количество не сдавших студентов

% Оценка студента за предмет
mark_for_subj(Stud, Subj, X) :- student(_, Stud, List), member(grade(Subj, X), List).

% Счётчик вхождения элемента в список
counter([], _, 0).
counter([X|List], X, N) :- counter(List, X, K), N is K+1.
counter([Y|List], X, N) :- X\=Y, counter(List, X, N).

% Нахождение количества учеников, которые не сдали предмет
number_not_passed(Subj, Number) :- findall(X, mark_for_subj(_, Subj, X), List), counter(List, 2, Number).

% 3 - Для каждой группы найти студента (студентов) с максимальным средним баллом

% Максимальная оценка в списке
max([M],M).
max([M,T|L],Min) :- M=<T, max([T|L],Min).
max([M,T|L],Min) :- M>T, max([M|L],Min).

% Средние баллы студентов в группе
average_mark_in_gr(Group, Mark) :- student(Group, Stud, _), average_mark(Stud, Mark).

% Максимальная средняя оценка в группе
maximal_group_average_mark(Group, Mark) :- bagof(Mark, average_mark_in_gr(Group, Mark), List), max(List, Mark).

% Нахождение студента с наивысшим средним баллом
max_average_student(Group, Stud) :- student(Group, Stud, _), average_mark(Stud, AverMark), maximal_group_average_mark(Group, MaxMark), AverMark = MaxMark.
