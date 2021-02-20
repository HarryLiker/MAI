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

% Художественной гимнастикой занимались только женщины

solve(Result) :- 
length(Result, 6),

member(teacher(_, _, _, geography), Result), !,
member(teacher(_, _, _, english), Result), !,
member(teacher(_, _, _, french), Result), !,
member(teacher(_, _, _, german), Result), !,
member(teacher(_, _, _, history), Result), !,
member(teacher(_, _, _, maths), Result), !,

member(teacher(arkadieva, female, _, _), Result),
member(teacher(babanova, female, _, _), Result),
member(teacher(korsakova, female, _, _), Result),
member(teacher(dashkov, male, _, _), Result),
member(teacher(ilin, male, _, _), Result),
member(teacher(flerov, male, _, _), Result),

% Преподаватели математики и немецкого занимались гимнастикой, значит, они женщины
member(teacher(_, female, _, maths), Result),
member(teacher(_, female, _, german), Result),

% Ильин не преподаватель английского
not(member(teacher(ilin, _, _, english), Result)),
% Ильин не преподаватель географии
not(member(teacher(ilin, _, _, geography), Result)),
% Флеров не преподаватель английского
not(member(teacher(flerov, _, _, english), Result)),
% Флеров не преподаватель французского
not(member(teacher(flerov, _, _, french), Result)),
% Ильин не преподаватель французского
not(member(teacher(ilin, _, _, french), Result)),
% Аркадьева не является преподавателем немецкого, т.к. она старше преподавателя по немецкому
not(member(teacher(arkadieva, _, _, german), Result)),

% Аркадьева и Бабанова учились в университете
member(teacher(arkadieva, female, university, _), Result),
member(teacher(babanova, female, university, _), Result),

% Корсакова, Дашков, Ильин, Флеров учились в институте
member(teacher(korsakova, female, institute, _), Result),
member(teacher(dashkov, male, institute, _), Result),
member(teacher(ilin, male, institute, _), Result),
member(teacher(flerov, male, institute, _), Result),

% Преподаватель английского учился в институте
member(teacher(_, _, institute, english),Result),

% Преподаватели математики и истории - бывшие ученики преподавателя английского
% Значит, они учились в институте, т.к. преподаватель английского преподавал в институте, после его окончания 
member(teacher(_, _, institute, maths), Result),
member(teacher(_, _, institute, history), Result).


solution :- solve(Result),
member(teacher(arkadieva, _, _, A), Result),
write('Arkadieva = '), write(A), nl,

member(teacher(babanova, _, _, B), Result),
write('Babanova = '), write(B), nl,

member(teacher(korsakova, _, _, K), Result),
write('Korsakova = '), write(K), nl,

member(teacher(dashkov, _, _, D), Result),
write('Dashkov = '), write(D), nl,

member(teacher(ilin, _, _, I), Result),
write('Ilin = '), write(I), nl,

member(teacher(flerov, _, _, F), Result),
write('Flerov = '), write(F), nl.