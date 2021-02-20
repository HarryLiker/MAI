#ifndef LAB_4_H
#define LAB_4_H

#include <fcntl.h>

const char *BackingFile = "back";
const char *BackingFile2 = "back2";
const char *SemaphoreName = "semaphore";
unsigned AccessPerms = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;

#endif //SHRMEM_H