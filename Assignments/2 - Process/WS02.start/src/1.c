#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define _XOPEN_SOURCE 700

int main() {
    int i, j, p;
    for (i = 0; i <3; i ++)
        if ((p = fork ()) == 0){
            printf( "i = %d \n", i);
            j = 0;
            while (j < i && ((p = fork ()) == 0))
                j ++; 
            if (p == 0)
                printf ( "j = %d \n", j);
            else
                wait(NULL); 
            exit(j);
        }
    
    for (int z = 0; z < 3; z++)
        wait(NULL);
    return (0);
}