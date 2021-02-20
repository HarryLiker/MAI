parents('Igor Korolew', 'Michail Korolew', 'Irina Vorontsova').
parents('Marina Korolewa', 'Michail Korolew', 'Irina Vorontsova').
parents('Irina Vorontsova', 'Sergey Sharkov', 'Natalia Korotkova').
parents('Natalia Korotkova', 'Alexandr Korotkov', 'Lidia Anozina').
parents('Alla Korotkova', 'Alexandr Korotkov', 'Lidia Anozina').
parents('Vitaliy Korotkov', 'Alexandr Korotkov', 'Lidia Anozina').
parents('Michail Korolew', 'Anatoliy Korolew', 'Nadezda Bobileva').
parents('Sergey Korolew', 'Anatoliy Korolew', 'Nadezda Bobileva').
parents('Elena Korolewa', 'Anatoliy Korolew', 'Nadezda Bobileva').
parents('Dmitriy Korolew', 'Sergey Korolew', 'Evgenia Basova').
parents('Natalia Korolewa', 'Sergey Korolew', 'Evgenia Basova').
parents('Uriy Koriavets', 'Andrey Koriavets', 'Elena Korolewa').
parents('Klavdiya Bobileva', 'Ilya Bobilev', 'Pelageya Riazskaya').
parents('Vladimir Bobilev', 'Ilya Bobilev', 'Pelageya Riazskaya').
parents('Nadezda Bobileva', 'Ilya Bobilev', 'Pelageya Riazskaya').
parents('Taisiya Bobileva', 'Ilya Bobilev', 'Pelageya Riazskaya').
parents('Ilya Bobilev', 'Ivan Bobilev', 'Evdokiya Tuboleva').
parents('Anatoliy Korolew', 'Grigoriy Korolew', 'Maria Kalmikova').
parents('Viktor Korolew', 'Grigoriy Korolew', 'Maria Kalmikova').
parents('Maria Kalmikova', 'Kondratiy Kalmikov', 'Lukeria').
parents('Grigoriy Korolew', 'Pavel Korolew', 'Evdokiya').
parents('Lidia Anozina', 'Petr Anozin', 'Antonina Groholskaya').
parents('Alexey Korotkov', 'Vitaliy Korotkov', 'Vera Tarasova').
parents('Ekaterina Korotkova', 'Alexey Korotkov', 'Tatiana Danina').
parents('Ilya Korotkov', 'Sergey', 'Ekaterina Korotkova').
parents('Olga Nikishina', 'Leonid Nikishin', 'Alla Korotkova').
parents('Iosif Nikishin', 'Leonid Nikishin', 'Alla Korotkova').
parents('Stanislav Durnev', 'Evgeniy Durnev', 'Olga Nikishina').
parents('Anastasia Durneva', 'Evgeniy Durnev', 'Olga Nikishina').
parents('Nikita Durnev', 'Evgeniy Durnev', 'Olga Nikishina').
parents('Semen', 'Roman', 'Anastasia Durneva').
parents('Anna', 'Roman', 'Anastasia Durneva').
parents('Gleb Durnev', 'Stanislav Durnev', 'Kristina Vilenkina').
parents('Zlata Durneva', 'Stanislav Durnev', 'Kristina Vilenkina').
parents('Evgeniya Durneva', 'Nikita Durnev', 'Irina Zaytseva').
parents('Maria Durneva', 'Nikita Durnev', 'Irina Zaytseva').
parents('Antonina Durneva', 'Nikita Durnev', 'Irina Zaytseva').
parents('Svetlana Korolewa', 'Viktor Korolew', 'Galina Feoktistova').
parents('Ulia Korolewa', 'Viktor Korolew', 'Galina Feoktistova').
parents('Ekaterina Korolewa', 'Viktor Korolew', 'Galina Feoktistova').
parents('Dmitriy Buzovkin', 'Maksim Buzovkin', 'Svetlana Korolewa').
parents('Vladimir Maltzev', 'Andrey Maltzev', 'Ulia Korolewa').
parents('Viktoriya Maltzeva', 'Andrey Maltzev', 'Ulia Korolewa').
parents('Stanislav Maltzev', 'Andrey Maltzev', 'Ulia Korolewa').
parents('Valeriya Maltzeva', 'Andrey Maltzev', 'Ulia Korolewa').
parents('Polina', 'Pavel', 'Ekaterina Korolewa').
parents('Valeriya', 'Pavel', 'Ekaterina Korolewa').
parents('Vera Tarasova', 'Alexey Tarasov', 'Nadezda Klinina').

% Проверка двух людей, на то что они яляются родными братьями или сёстрами
sibling(X, Y) :- parents(X, Parent1, Parent2), parents(Y, Parent1, Parent2), X\=Y.

% Проверка двух людей, на то что они яляются двоюродными братьями или сёстрами
double_sibling(X, Y) :- parents(X, Parent11, _), parents(Y, Parent21, _), sibling(Parent11, Parent21).
double_sibling(X, Y) :- parents(X, Parent11, _), parents(Y, _, Parent22), sibling(Parent11, Parent22).
double_sibling(X, Y) :- parents(X, _, Parent12), parents(Y, Parent21, _), sibling(Parent12, Parent21).
double_sibling(X, Y) :- parents(X, _, Parent12), parents(Y, _, Parent22), sibling(Parent12, Parent22).

% Проверка двух людей, на то что они яляются троюродными братьями или сёстрами
triple_sibling(X, Y) :- parents(X, Parent11, _), parents(Y, Parent21, _), double_sibling(Parent11, Parent21).
triple_sibling(X, Y) :- parents(X, Parent11, _), parents(Y, _, Parent22), double_sibling(Parent11, Parent22).
triple_sibling(X, Y) :- parents(X, _, Parent12), parents(Y, Parent21, _), double_sibling(Parent12, Parent21).
triple_sibling(X, Y) :- parents(X, _, Parent12), parents(Y, _, Parent22), double_sibling(Parent12, Parent22).

% Все родственники, которые прямо связаны друг с другом (не через других людей)
direct_relation(husband, Husband, Wife) :- parents(_, Husband, Wife).
direct_relation(wife, Wife, Husband) :- parents(_, Husband, Wife).
direct_relation(sibling, X, Y) :- sibling(X, Y).
direct_relation(father, Father, Child) :- parents(Child, Father, _).
direct_relation(mother, Mother, Child) :- parents(Child, _, Mother).
direct_relation(child, Child, Father) :- parents(Child, Father, _).
direct_relation(child, Child, Mother) :- parents(Child, _, Mother).

% Переход между родственниками
move(X, Y) :- direct_relation(_, X, Y).

% Предикат продления пути
prolong([X|T], [Y,X|T]) :- move(X, Y), not(member(Y, [X|T])).

% Предикат рекурсивного поиска в ширину
breadth([[Finish|T]|_], Finish, [Finish|T]).

% Продление первого пути в очереди всеми возможными способами
breadth([P|Q1], X, R) :- findall(Y, prolong(P, Y), T),
    append(Q1, T, Q2),
    breadth(Q2, X, R), !.

breadth([_|T], Y, L) :- breadth(T, Y, L).

% Предикат поиска пути в ширину. Находит путь, который состоит из людей, через которых связаны два человек.
breadth_search(Start, Finish, Path) :- breadth([[Start]], Finish, L), reverse(L, Path).

% Находит путь по родственникам, через которых связаны два человека
relative_path(X, Y, Result) :- breadth_search(X, Y, Result).

% Предикат построения цепочки родства для родственников, находящихся в списке
conversation([_], []) :- !.
conversation([First,Second|Tail], ResultList) :- direct_relation(Relation, First, Second),
    ResultList = [Relation|PrevList],
    conversation([Second|Tail], PrevList), !.

% Предикат нахождения всего родственного пути для двух людей
relative(X, Y, Result) :- breadth_search(X, Y, PeopleChain), !, conversation(PeopleChain, Result).

% Естественно-языковый инерфейс

% Предикат, нужный для дальнейшего перебора прямых связей между людьми 
which_relation(X) :- member(X, [father, mother, child, sibling, husband, wife]).

question_word(X) :- member(X, [who, how, "Who", "How"]).

% Количественное
count(X) :- member(X, [much, many]).

plurals(X) :- member(X, [child, children, sibling, siblings]).
plural(sibling, siblings).
plural(child, children).

% Вспомогательные слово
help_word(X) :- member(X, [do, does]).

have_has(X) :- member(X, [have, has]).

is(X) :- member(X, ["Is", is]).

s(X) :- member(X, ["'s"]).

question_mark(X) :- member(X, ['?']).

% Нахождение, кто кем является по прямой связи
find_relative(X, Y, Result) :- which_relation(Result), !, direct_relation(Result, X, Y).

% How many _ does _ have?
question(List) :- List = [How, Many, C, Does, E, Have, G],
    question_word(How),
    count(Many),
    plurals(C),
    help_word(Does),
    have_has(Have),
    question_mark(G),
    plural(Y, C),
    setof(X, find_relative(X, E, Y), T),
    length(T, Result),
    write(E),
    write(" has "),
    ((Result =:= 1, write(Result), write(" "), write( Y)) ; 
    (not(Result =:= 1), write(Result), write(" "), write( C))), !.

% Who is _ _ ?
question(List) :- List = [Who, Is, C, S, E, F],
    question_word(Who),
    is(Is),
    s(S),
    which_relation(E),
    question_mark(F), !,
    direct_relation(E, Result, C),
    write(Result), write(" is "), write(C), write("'s "), write(E).
