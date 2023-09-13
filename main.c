#include "main.h"
#include <signal.h>

int main(int argc, char **argv) {
    char *lineptr = NULL;
    char **cmd = NULL;
    int status = 0;
    pid_t child;
    (void) argc;
    (void) argv;

    while (1) {
        if (isatty(STDOUT_FILENO)) {
            write(STDOUT_FILENO, "$ ", 2);
        }

        lineptr = read_line();

        if (lineptr == NULL) {
            if (isatty(STDOUT_FILENO)) {
                write(STDOUT_FILENO, "\n", 1);
            }
            free(lineptr);
            exit(status);
        }

        cmd = tokenizer(lineptr);

        if (!cmd || cmd[0] == NULL) {
            free(lineptr);
            continue;
        }

        child = fork();

        if (child == -1) {
            perror("fork");
            free(lineptr);
            exit(1);
        }

        if (child == 0) {
            execve(cmd[0], cmd, environ);
            perror("execve");
            free(lineptr);
            exit(1);
        } else {
            waitpid(child, &status, 0);
        }
        _free(cmd);
    }
}

