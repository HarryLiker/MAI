import random
import string
from random import choice

def main():
    pattern_size = random.randint(3, 20)
    pattern = ""
    text = ""
    text_in_file = tuple()
    text_list = []
    words_in_pattern = ["dog", "cat", "bird"]
    words_in_text = ["dog", "cat", "bird", "umbrella", "kiss", "jump", "get", "hello", "python"]
    for i in range(pattern_size):
        if (i != 0):
            pattern = pattern + ' '
        pattern = pattern + choice(words_in_pattern)
    count = 0
    while (count < 10000):
        rand = random.randint(1, 100)
        if (count != 0):
            text = text + ' '
        if (rand > 20):
            text = text + pattern
            count  = count + pattern_size
        else:
            text = text + choice(words_in_text)
            count += 1
    test_file = open('test.txt', 'w')
    test_file.write(pattern)
    test_file.write('\n')
    test_file.write(text)
    test_file.close()
    print(text.count(pattern))


main()

    