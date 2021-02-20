:- encoding(utf8).


% Task 2: Relational Data

% The line below imports the data
:- ['three.pl'].

group(X,L) :- findall(Z,student(X,Z),L).


% Для каждого предмета найти число несдавших студентов

% Сначала найду оценку за предмет у ученика
grade(_,[], _).
grade(Subj, [grade(Subj, X)|L],X) :- grade(_ ,L, _).

mark(Stud, Subj,X) :- student(_, Stud, List), grade(Subj,List, X).

% Я прохожу по всему списку студентов и проверяю, какая у них оценка по предмету

