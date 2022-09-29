#define _XOPEN_SOURCE 700
#define GCC "gcc"
#define WALL "-Wall"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int main(int argc, char* argv[]) {
    int i, pid, files_num = argc - 1;

    // create a child process for each of the source file
    for (i = 0; (i < files_num) && ((pid = fork()) > 0); i++);

    if (pid == -1) {
        perror("fork");
        exit(-1);
    } else if (pid == 0) { // child process
        char* file_name = argv[i + 1];
        execlp(GCC, GCC, WALL, "-c", file_name, NULL);
        exit(0);
    } else { // main process
        for (int j = 0; j < files_num; j++) {
            wait(0);
        }

        char* args[5 + files_num];
        args[0] = (char*) malloc(sizeof(GCC));
        memcpy(args[0], GCC, strlen(GCC));
        args[1] = (char*) malloc(sizeof(WALL));
        memcpy(args[1], WALL, strlen(WALL));
        args[2] = (char*) malloc(sizeof("-o"));
        memcpy(args[2], "-o", strlen("-o"));
        args[3] = (char*) malloc(sizeof("my_exec"));
        memcpy(args[3], "my_exec", strlen("my_exec"));

        for (int j = 0; j < files_num; j++) {
            char* file_name = argv[j + 1];
            args[4 + j] = (char*) malloc(sizeof(file_name));
            // strcpy(args[4 + j], file_name);
            memcpy(args[4 + j], file_name, strlen(file_name));
            args[4 + j][strlen(args[4 + j]) - 1] = 'o';
        }
        args[4 + files_num] = NULL;

        execvp(GCC, args);
    }


    return EXIT_SUCCESS;
}