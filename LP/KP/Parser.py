import re

# ^ - начало строки
# $ - конец строки
# \s - любой пробельный символ
# \d - любая цифра [0;9]
# () - группирует выражение и возвращает найденный текст
# . - один любой символ, кроме новой строки
# + - 1 и более вхождений шаблона слева
# * - 0 и более вхождений шаблона слева

def FindIndex(line): 
    Index = re.search(r"^0\s+@I(\d+)@\s+INDI$", line)        # Функция нахождения индекса
    if Index is not None:
        return Index.group(1)

def FindName(line):
    Name = re.search(r"^1\s+NAME\s+(.+)\s+/(.*)/$", line)      # Функция нахождения имени
    if Name is not None:
        if Name.group(2) == "":                                # Если нет фамилии, то возвращает только имя
            return Name.group(1)
        else:
            return Name.group(1) + " " + Name.group(2)         # Возвращает имя и фамилию

if __name__ == '__main__':              # Проверяет, был ли запущен файл напрямую
    outfile = open("facts.pl", "w")

    FileLines = []
    with open("MyTree.ged") as File:
        FileLines = [string.strip() for string in File]        # Список со строками файла, который считывается

    idx = []               # Массив с индексами
    names = []             # Массив с именами
    for l in FileLines:
        k = FindIndex(l)
        n = FindName(l)
        if k is not None:
            idx.append(k)
        if n is not None:
            names.append(n)
    data = {Index: Name for Index, Name in zip(idx, names)} # Сопоставляет имя каждому индексу
    childParents = []      # Массив, в котором будут храниться списки с детьми и их родителями

    it = iter(FileLines)
    while True:
        try:                         # Пока в try не возникает исключений, except пропускается
            line = next(it)
            FindFather = re.search(r"1\s+HUSB\s+@I(\d+)@", line)      # Находит папу
            if FindFather is not None:
                father = data[FindFather.group(1)]
                continue

            FindMother = re.search(r"1\s+WIFE\s+@I(\d+)@", line)      # Находит маму
            if FindMother is not None:
                mother = data[FindMother.group(1)]
                continue

            FindChild = re.search(r"1\s+CHIL\s+@I(\d+)@", line)       # Находит ребёнка
            if FindChild is not None:
                lst = (data[FindChild.group(1)], father, mother)  # Список: ребёнок, папа, мама
                childParents.append(lst)
                continue
        except StopIteration:
            break

    PrintPredicate = lambda x, y, z: outfile.write("parents(\'{0}\', \'{1}\', \'{2}\').\n".format(x, y, z)) # Вывода факта с помощью лямбда-функции
    for count, i in enumerate(childParents):              # Выписывает каждого ребенка с его родителями: parents(Ребёнок, Папа, Мама).
        child, fath, moth = childParents[count]
        PrintPredicate(child, fath, moth)    # Записывает в файл предикат
    outfile.close()