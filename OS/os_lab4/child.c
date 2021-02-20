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

int string_validation(char *line) {
    int i = 0;
    while (line[i] != '\0') {
        i++;
    }
    if (line[i-1] == '.' || line[i-1] == ';') {
        return 0;
    }
    return -1;
}

int main(int argc, char *argv[]) {

    int fd1 = shm_open(BackingFile, O_RDWR | O_CREAT, AccessPerms); // Создаёт объект разделяемой памяти
    int fd2 = shm_open(BackingFile2, O_RDWR | O_CREAT, AccessPerms); // Создаёт объект разделяемой памяти
    if (fd1 == -1 || fd2 == -1) {
        perror("Can't open shared memory object!\n");
        exit(EXIT_FAILURE);
    }
    // Создание именованного семафора
    sem_t *sem_pointer = sem_open(SemaphoreName, O_CREAT, AccessPerms, 2);
    if (sem_pointer == SEM_FAILED) {
        perror("Can't initialize semaphore!\n");
        exit(EXIT_FAILURE);
    }
    // Отображение файлов в памяти 
    char *mapping_file = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    char *mapping_file2 = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    if (mapping_file == MAP_FAILED || mapping_file2 == MAP_FAILED) {
        perror("Can't map a file!\n");
        exit(EXIT_FAILURE);
    }

    char *string;
    int value;
    while(1) {
        if (sem_wait(sem_pointer) != 0) {
            perror("sem_wait error!\n");
            exit(EXIT_FAILURE);
        }
        sem_getvalue(sem_pointer, &value);
        //printf("Значение семафора: %d", value);
        if (mapping_file[0] != '\0') {
            //int value;
            sem_getvalue(sem_pointer, &value);
            if (mapping_file[0] == EOF) {
                sem_post(sem_pointer);
                break;
            }
            strcpy(string, mapping_file);
            if (string_validation(string) == 0) {
                printf("%s\n", string);
                memset(mapping_file, '\0', getpagesize());
            } else {
                strcpy(mapping_file2, string);
                memset(mapping_file, '\0', getpagesize());
            }
            //sem_getvalue(sem_pointer, &value);
        }
        fflush(stdout);
        if (sem_post(sem_pointer) != 0) {
            perror("sem_post error!\n");
            exit(EXIT_FAILURE);
        }
    }

    
    if (munmap(mapping_file, getpagesize()) != 0) {
        perror("Can't munmap!\n");
        exit(EXIT_FAILURE);
    }
    if (munmap(mapping_file2, getpagesize()) != 0) {
        perror("Can't munmap!\n");
        exit(EXIT_FAILURE);
    }
    sem_close(sem_pointer); // Закрытие именованного семафора
    return 0;
    
}