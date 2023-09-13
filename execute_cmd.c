#include "main.h"
int execute_cmd(char **cmd, char **argv)
{
    pid_t child;
    int status;
    (void) argv;

    child = fork();
    if (child == -1)
    {
        perror("fork");
        return 1;
    }
    if (child == 0)
    {
        if (access(cmd[0], X_OK) == -1)
        {
            perror("access");
            _free(cmd);
            exit(EXIT_FAILURE);
        }
        if (execve(cmd[0], cmd, environ) == -1)
        {
            perror("Error");
            _free(cmd);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(child, &status, 0);
        _free(cmd);

        if (WIFEXITED(status))
        {
status = WEXITSTATUS(status);
        }
    }
    return status;
}
