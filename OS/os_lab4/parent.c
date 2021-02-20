#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <threads.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "shrmem.h"

// Функция чтения строки
char *getstring() {
    int length = 0;
    int capasity = 10;
    char *str = (char *)malloc(10 * sizeof(char));
    if (str == NULL) {
        perror("Can't read a string!\n");
        exit(6);
    }
    char c;
    while ((c = getchar()) != '\n') {
        str[length++] = c;
        if (c == EOF) {
            break;
        }
        if (length == capasity) {
            capasity *= 2;
            str = (char *)realloc(str, capasity * sizeof(char));
            if (str == NULL) {
                perror("Can't read a string!\n");
                exit(6);
            }
        }
    }
    str[length] = '\0';
    return str;
}


int main() {
    char filename[256];
    printf("Введите имя файла: ");
    scanf("%s", filename);
    // Создаём объект разделяемой памяти
    int fd1 = shm_open(BackingFile, O_RDWR | O_CREAT, AccessPerms);
    int fd2 = shm_open(BackingFile2, O_RDWR | O_CREAT, AccessPerms);
    if (fd1 == -1 || fd2 == -1) {
        perror("Can't open shared memory object!\n");
        exit(EXIT_FAILURE);
    }

    // Создание/открытие именованного семафора
    sem_t *sem_pointer = sem_open(SemaphoreName, O_CREAT, AccessPerms, 2);
    if (sem_pointer == SEM_FAILED) {
        perror("Can't initialize semaphore!\n");
        exit(EXIT_FAILURE);
    }
    // Изменение размера файлов
    ftruncate(fd1, getpagesize());
    ftruncate(fd2, getpagesize());
    // Отображение файлов в памяти
    char *mapping_file = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    
    char *mapping_file2 = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);

    if (mapping_file == MAP_FAILED || mapping_file2 == MAP_FAILED) {
        perror("Can't map a file!\n");
        exit(EXIT_FAILURE);
    }
    
    // Заполняем файлы
    memset(mapping_file, '\0', getpagesize());
    memset(mapping_file2, '\0', getpagesize());
    FILE *file_to_write = fopen(filename, "w");
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork error!\n");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) {
        int value;
        sem_getvalue(sem_pointer, &value); 
        if (value++ < 2) {
            sem_post(sem_pointer);
        }

        while(1) {
            if (sem_getvalue(sem_pointer, &value) != 0) {
                perror("Can't get value of semaphore!\n");
                exit(EXIT_FAILURE);
            }
            if (value == 2) {
                if(sem_wait(sem_pointer) != 0) {
                    perror("sem_wait error!\n");
                    exit(EXIT_FAILURE);
                }
                char *str = getstring();
                if (str[0] != EOF) {
                    strcpy(mapping_file, str);
                    if (sem_post(sem_pointer) != 0) {
                        perror("sem_post error!\n");
                        exit(EXIT_FAILURE);
                    }    
                } else {
                    mapping_file[0] = EOF;
                    if (sem_post(sem_pointer) != 0) {
                        perror("sem_post error!\n");
                        exit(EXIT_FAILURE);
                    }    
                    break;
                }
            } else {
                if (mapping_file2[0] != '\0') {
                    if(sem_wait(sem_pointer) != 0) {
                        perror("sem_wait error!\n");
                        exit(EXIT_FAILURE);
                    }
                    char *string = (char*) malloc(strlen(mapping_file2) * sizeof(char));
                    strcpy(string, mapping_file2);
                    printf("Error string: %s\n", string);
                    memset(mapping_file2, '\0', getpagesize());
                    free(string);
                    if (sem_post(sem_pointer) != 0) {
                        perror("sem_post error!\n");
                        exit(EXIT_FAILURE);
                    }  
                    continue;
                }
            }
            fflush(stdout);
        }
    }

    if (pid == 0) {
        printf("Дочерний процесс\n");
        dup2(fileno(file_to_write), STDOUT_FILENO);
        execl("./child.out", "child", NULL);
    }
    // Снятие отражения файлов в памяти
    if (munmap(mapping_file, getpagesize()) != 0) {
        perror("Can't munmap!\n");
        exit(EXIT_FAILURE);
    }
    close(fd1);
    if (munmap(mapping_file2, getpagesize()) != 0) {
        perror("Can't munmap!\n");
        exit(EXIT_FAILURE);
    }
    close(fd2);
    // Закрытие семафора
    if (sem_close(sem_pointer) != 0) {
        perror("Can't close semaphore!\n");
        exit(EXIT_FAILURE);
    }
    // Удаление именованных семафоров
    if (shm_unlink(BackingFile) != 0) {
        perror("Can't unlink shared memory object!\n");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(BackingFile2) != 0) {
        perror("Can't unlink shared memory object!\n");
        exit(EXIT_FAILURE);
    }
    // Закрытие файла на запись
    if (fclose(file_to_write) != 0) {
        printf("Can't close the file!\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}