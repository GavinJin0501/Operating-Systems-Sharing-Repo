/**** multi-converter.c ****/

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <converters.h>

#define _XOPEN_SOURCE 700

int main(int argc, char **argv)
{
    // read variables
    int i, pid;
    char* input_currency = argv[1];
    double amount = strtod(argv[2], NULL);

    printf("Conversion for: %s %.3f\n", input_currency, amount);
    
    // create child processes
    for (i = 0; (i < NB_CONVERTERS) && ((pid = fork()) > 0); i++);

    if (pid == -1) {
        perror("fork");
        exit(-1);
    } else if (pid == 0) { // child process
        char* output_currency = determine_currency(i);
        double converted_amount = convert(input_currency, output_currency, amount);
        display_result(i, converted_amount);
        exit(0);
    } else {
        for (int j = 0; j < NB_CONVERTERS; j++) {
            wait(0);
        }
    }

    printf("End of conversion\n");
    return EXIT_SUCCESS;
}
