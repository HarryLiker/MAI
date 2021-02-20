// Лабораторная работа № 2
// Вариант 16

#include "stdio.h"
#include "string.h"
#include "unistd.h"

int main() {
    printf("Введите имя файла: ");
    char filename [256];
    scanf("%s", filename);
    FILE *file_to_write = fopen(filename, "w");
    int fd1[2];
    int fd2[2];
    if (pipe(fd2) < 0) {
        printf("Pipe erroror!");
        return -1;
    }
    if (pipe(fd1) < 0) {
        printf("Pipe erroror!");
        return -1;
    }
    int ID = fork();
    if (ID < 0) {
        printf("Fork erroror!");
        return -1;
    } else if (ID > 0) { // Родительский процесс
        close(fd1[0]);
        close(fd2[1]);
        char input[200];
        char error[200];
        int is_error;
        while(scanf("%s",input) > 0)
        {
            input[strlen(input)] = '\n';
            write(fd1[1], input, strlen(input));
            read(fd2[0], &is_error, sizeof(is_error));
            if(is_error){
                read(fd2[0], error, sizeof(error));
                printf("Error line: %s\n", error);
            }
            memset(input,'\0',257); // Заполнение input символами '\0'
        }
        close(fd1[1]);
        close(fd2[0]);
    } else { // Дочерний процесс
        close(fd1[1]);
        close(fd2[0]);
        dup2(fd1[0], STDIN_FILENO);
        dup2(fileno(file_to_write), STDOUT_FILENO);
        char arg[1] = {(char) fd2[1]};
        execl("./child.out", "child.out", arg, (char *)NULL);
    }
    fclose(file_to_write);
}