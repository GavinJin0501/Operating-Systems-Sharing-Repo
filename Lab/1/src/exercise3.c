#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

const char* GCC = "/usr/bin/gcc";
char* PATH = "./concurrent-compilation";

int get_length(char* str) {
    int length = 0;
    char ch;
    while ((ch = str[length]) != '\0') {
        length++;
    }
    return length;
}


int main(int argc, char* argv[]) {
    int pid, files_num = argc - 1, count = 0;
    char object_files[20][64];
    int status[files_num];
    char* folder;
    DIR* dr;
    struct dirent* file;

    folder = (argc > 1) ? argv[1] : PATH;
    dr = opendir(folder);

    if (dr == NULL) {
        printf("Could not open dir: %s\n", folder);
        return -1;
    }

    while ((file = readdir(dr)) != NULL) {
        char* file_name = file->d_name;
        int len = get_length(file_name);
        if (file_name[0] != '.' && file_name[len - 1] == 'c') {
            char object_file[len + 1];
            char from_path[256] = "./concurrent-compilation/";
            char to_path[256] = "./obj/";

            strcpy(object_file, file_name);
            object_file[len - 1] = 'o';
            strcat(from_path, file_name);
            strcat(to_path, object_file);
            strcpy(object_files[count], to_path);
            count++;
            
            pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(-1);
            } else if (pid == 0) {
                execl(GCC, "gcc", "-Wall", "-c", from_path, "-o", to_path, "-I", NULL);
                exit(0);
            }
        }
    }

    for (int j = 0; j < count; j++) {
        wait(&status[j]);
    }
    for (int j = 0; j < count; j++) {
        if (WEXITSTATUS(status[j]) != 0) {
            return -1;
        }
    }
    char final_cmd[256] = "gcc -Wall -o prog";
    for (int j = 0; j < count; j++) {
        strcat(final_cmd, " ");
        strcat(final_cmd, object_files[j]);
    }
    printf("%s\n", final_cmd);
    execl(GCC, final_cmd);

    closedir(dr);
    return 0;
}