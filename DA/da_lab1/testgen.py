import random 
import string

def main():
    n = random.randint(10, 1000000)
    test =[]
    answer = []
    for _ in range(n):
        key = random.randint(0, 18446744073709551615)
        value = random.randint(0, 18446744073709551615)
        test.append((key, value))
    
    with open('01.t', 'w') as ftest:
        for key, value in test:
            ftest.write(f'{key} {value}\n')

    answer = sorted(test)
    with open('01.a', 'w') as ftest:
        for key, value in answer:
            ftest.write(f'{key} {value}\n')
main()