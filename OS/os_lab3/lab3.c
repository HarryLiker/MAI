#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"
#include "time.h"
#include "inttypes.h"
#include "limits.h"
#include "string.h"
#include "pthread.h"
#include "time.h"

#define DEC_SIZE 40
#define NUMBER_SIZE 32
//#define FILE_SIZE 1000000

typedef unsigned __int128 int128_t;

unsigned long long num_count = 0;
unsigned long long threads_number = 0;
unsigned long long member_size = 0;

typedef struct thread {
    int128_t localsum; // Локальная сумма (среднее арифметическое) потока
    off_t start_position; // Позиция в файле, с которой поток будет считывать определённое количество чисел
    long long numbers_in_thread; // controller of number of threads
} thread;


char *file_name = "test_1000000.txt";

void initialise(thread *pointer, unsigned long long threads_num, long long num_count) {
    pointer[0].localsum = 0;
    pointer[0].start_position = 0;
    pointer[0].numbers_in_thread = (num_count / threads_num);
    for (int i = 1; i < threads_num; ++i) {
        pointer[i].localsum = 0;
        pointer[i].start_position = i * (pointer[i - 1].numbers_in_thread * (NUMBER_SIZE + 1));
        pointer[i].numbers_in_thread = pointer[i-1].numbers_in_thread;
    }
    pointer[threads_num - 1].numbers_in_thread += num_count % threads_num;
}

// Функция вывода 128-битного числа
void print_int128(int128_t count) {
    char buf[DEC_SIZE + 1];
    int i;
    for (i = 0; i < DEC_SIZE; ++i) {
        buf[i] = '0';
    }
    buf[DEC_SIZE] = '\0';
    for (i = DEC_SIZE - 1; count > 0; --i) {
        buf[i] = (int) (count % 10) + '0';
        count /= 10;
    }
    if (i == DEC_SIZE - 1) {
        printf("%d\n", 0);
    } else {
        printf("%s\n", &buf[i + 1]);
    }
}

// Проверка символа на число
int is_number(char *s) {
    return (*s >= '0' && *s <= '9');
}

// Функция преобразования числа с 16-ой СС в 10-ю
int hex_to_dec(char *s) {
    if(*s == 'A')
        return 10;
    if(*s == 'B')
        return 11;
    if(*s == 'C')
        return 12;
    if(*s == 'D')
        return 13;
    if(*s == 'E')
        return 14;
    if(*s == 'F')
        return 15;
    return 0;
}

// Функция нахождения значения 128-битного числа, записанного в 16-ой СС
int128_t big_int(char *str) {
    int128_t result = 0;
    while (*str) {
        if(is_number(str))
            result = result * 16 + (*str - '0');
        else {
            int dec = hex_to_dec(str);
            result = result * 16 + dec;
        }
        ++str; 
    }
    return result;
}

// Функция потока на выполнение
void *thread_function(void *another_pointer) {
    thread *thread_parameter = (thread *)another_pointer;
    char buf[NUMBER_SIZE + 1];
    char c;
    int fd = open(file_name, O_RDWR| O_CREAT, 0666);
    lseek(fd, thread_parameter->start_position, SEEK_SET);
    for (int i = 0; i < thread_parameter->numbers_in_thread; ++i) {
        read(fd, buf, NUMBER_SIZE);
        buf[NUMBER_SIZE] = '\0';
        int128_t s;
        s = big_int(buf);
        s /= num_count;
        thread_parameter->localsum += s;
        read(fd, &c, 1);
        if (c != '\n' && c != '\0') {
            fprintf(stderr, "%s\n", "Error format of file!");
            exit(EXIT_FAILURE);
        }
    }
    close(fd);
    return 0; 
}
/*
void generate() {
    int fd = open(file_name, O_RDWR| O_CREAT, 0666);
    char buf[NUMBER_SIZE];
    srand(time(NULL));
    for (int i = 0; i < FILE_SIZE; ++i) {
        for (int i = 0; i < NUMBER_SIZE; ++i) {
            if (((int) rand()) % 2 == 0) {
                buf[i] = '0' + (((int) rand()) % 10);
            } else {
                buf[i] = 'A' + (((int) rand()) % 6);
            }
        }
        write(fd, &buf, NUMBER_SIZE);
        write(fd, "\n", 1);
    }
    close(fd);
}
*/
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "%s\n", "Not enough arguments!");
        exit(EXIT_FAILURE);
    } else { 
        if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0) {
            fprintf(stderr, "%s\n", "Entered incorrect parameters!");
            exit(EXIT_FAILURE);
        }
        threads_number = atoi(argv[1]);
        member_size = atoi(argv[2]);
    }
    //generate();
    // Проверка, хватает ли оперативной памяти для заданного количества потоков
    if (threads_number * sizeof(thread) + threads_number * sizeof(pthread_t) > member_size) {
        fprintf(stderr, "%s\n", "Too much threads for this amount of memory");
        exit(EXIT_FAILURE);
    }
    // Выделение памяти для потоков
    pthread_t *thread_id = (pthread_t *) malloc(threads_number * sizeof(pthread_t));
    // Выделение памяти для параметров каждого потока
    thread *thread_sum = (thread *) malloc(threads_number * sizeof(thread));
    int i, j;
    int fd = open(file_name, O_RDWR | O_CREAT, 0666);
    // Подсчёт всех символов в файле
    long long size = lseek(fd, 0, SEEK_END);
    close(fd);
    // Подчёт количества чисел в файле
    num_count = size / (NUMBER_SIZE + 1); 
    // Инициализация значений для каждого потока
    initialise(thread_sum, threads_number, num_count);
    //long double start, end;
    long double thread_start, thread_end;
    clock_t start = clock();
    // Создаются потоки и выполняются функции подсчёта локальной суммы для каждого потока
    for (i = 0; i < threads_number; ++i) {
        pthread_create(&thread_id[i], NULL, thread_function, (void *) &thread_sum[i]); //last null is param
    }
    // Ожидание окончания работы всех потоков
    for (j = 0; j < threads_number; ++j) {
        pthread_join(thread_id[j], NULL); 
    }
    int128_t sum = 0;
    // Суммирование локальных сумм всех потоков
    for (int i = 0; i < threads_number; ++i) {
        sum += thread_sum[i].localsum;
    }
    clock_t end = clock();
    printf("Averange result: ");
    print_int128(sum);
    printf("Execution time %f ms\n", (double)(end - start) * 1000.0 / CLOCKS_PER_SEC);
    return 0;
}