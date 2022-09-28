#define _XOPEN_SOURCE 700
#define MAX_FILE_NUM 10
#define PATH "concurrent-compilation"
#define OBJ "obj/"
#define BUFFER_SIZE 256
#define GCC "/usr/bin/gcc"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int get_length(char* str) {
    int length = 0;
    char ch;
    while ((ch = str[length]) != '\0') {
        length++;
    }
    return length;
}

void prepare_files(char* folder, char* files[], int* count) {
    DIR* dr;
    struct dirent* file;

    dr = opendir(folder);

    if (dr == NULL) {
        printf("Could not open dir: %s\n", folder);
        exit(-1);
    }

    while ((file = readdir(dr)) != NULL) {
        char* file_name = file->d_name;
        int name_len = get_length(file_name);
        if (file_name[0] != '.' && file_name[name_len - 1] == 'c') {
            files[*count] = file_name;
            (*count)++;
        }
    }

    closedir(dr);
}

int main(int argc, char* argv[]) {
    int i, pid, files_num;
    char* source_folder;
    char* source_files[MAX_FILE_NUM];
    char header_inc[64];
    
    // obtain folder path and get the files from it
    source_folder = (argc > 1) ? argv[1] : PATH;
    strcat(strcat(header_inc, "-I"), source_folder);
    prepare_files(source_folder, source_files, &files_num);
    
    // initial main process create a child process for each file
    for (i = 0; (i < files_num) && ((pid = fork()) > 0); i++);

    if (pid == -1) {
        perror("fork");
        exit(-1);
    } else if (pid == 0) { // inside the child process
        char* source_file = source_files[i];
        int length = get_length(source_file);
        
        char from_path[BUFFER_SIZE];
        char to_path[BUFFER_SIZE] = OBJ;

        // get source file name & object file name & header path --> both with path
        strcat(strcat(strcpy(from_path, source_folder), "/"), source_file);
        strcat(to_path, source_file);
        to_path[get_length(OBJ) + length - 1] = 'o';
        
        // execl the gcc command
        // printf("%d: gcc -Wall -c -o %s %s %s\n", i, to_path, from_path, header_inc);
        execl(GCC, "gcc", "-Wall", "-c", "-o", to_path, from_path, header_inc, NULL);
        exit(0);
    } else { // inside the parent process
        int j;
        for (j = 0; j < files_num; j++) {
            wait(NULL);
        }
        printf("main process -> All successful!\n");
        char* cmd[5 + files_num];
        for (int z = 0; z < 5 + files_num; z++) {
            cmd[z] = (char*) malloc(sizeof(char*));
        }
        strcpy(cmd[0], "gcc");
        strcpy(cmd[1], "-Wall");
        strcpy(cmd[2], "-o");
        strcpy(cmd[3], "bin/prog");
        for (j = 0; j < files_num; j++) {
            char object_path[BUFFER_SIZE] = OBJ;
            strcat(object_path, source_files[j]);
            object_path[get_length(object_path) - 1] = 'o';
            strcpy(cmd[j + 4], object_path);
        }
        cmd[4+files_num] = NULL;
        printf("main process -> ");
        for (int z = 0; z < 4 + files_num; z++) {
            printf("%s ", cmd[z]);
        }
        printf("\n");

        if (fork() == 0) {
            execv(GCC, (char**) cmd);
        } else {
            wait(NULL);
        }

        if (fork() == 0) {
            execlp("bin/prog", "bin/prog", NULL);
        } else {
            wait(NULL);
        }
        
        for (int z = 0; z < 5 + files_num; z++) {
            free(cmd[z]);
        }
    }

    return 0;
}