% Place your solution here

% Вариант 14

% В педагогическом институте Аркадьева, Бабанова, Корсакова, Дашков, Ильин и Флеров преподают географию, английский язык, французский язык, немецкий язык, историю и математику.
% Преподаватель немецкого языка и преподаватель математики в студенческие годы занимались художественной гимнастикой. 
% Ильин старше Флерова, но стаж работы у него меньше, чем у преподавателя географии. 
% Будучи студентками, Аркадьева и Бабанова учились вместе в одном университете.
% Все остальные окончили педагогический институт. 
% Флеров отец преподавателя французского языка. 
% Преподаватель английского языка самый старший из всех и по возрасту и по стажу. 
% Он работает в этом институте с тех пор, как окончил его. 
% Преподаватели математики и истории его бывшие студенты. 
% Аркадьева старше преподавателя немецкого языка. 
% Кто какой предмет преподает?

% Поправка от преподавателя: художественной гимнастикой занимались только женщины

% Акадьева, Бабанова, Корсакова, Дашков, Ильин, Флеров
% география, английский, французский, немецкий, история, математика.

gymnastic(X, Y) :- X = german, Y = maths.
gymnastic(X, Y) :- X = maths, Y = german.

who_gymnastic([A, B, K], X, Y) :- X = A, Y = B, gymnastic(A, B).
who_gymnastic([A, B, K], X, Y) :- X = A, Y = K, gymnastic(A, K).
who_gymnastic([A, B, K], X, Y) :- X = B, Y = K, gymnastic(B, K).

french(X) :- X = french.

older(I, F).
older(A, X) :- X = german.
oldest(List, X) :- member(X, List), X = english.

experience(I, X) :- X = geography.

experience(List, X) :- member(X, List), X = english.

english_teacher(List, X) :- oldest(List, X), experience(List, X), ended_institute(List, X).

english_ended_institute(X) :- ended_institute([A,B,K,D,I,F], X), X = english.

% Бывшие студенты
former_students(M, H, X) :- M = maths, H = history.

% Отец преподавателя
father(F, X, List) :- member(X, List), french(X).

% Учились вместе в университете
studied_together_university(A, B).

% Окончили институт
ended_institute(List, X) :- member(X, List), X \= A, X \= B.

solve :- permutation([A,B,K,D,I,F], [geography, english, french, german, history, maths]), older(I, F), older(A, Ger), who_gymnastic([A, B, K], Ger, Maths), former_students(Maths, Hisory, Eng), studied_together_university(A, B),
father(F, X, [A,B,K,D,I,F]), experience(I, G), english_teacher(Y, [A,B,K,D,I,F]), write([A, B, K, D, I, F]).