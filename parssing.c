#include "main.h"
char **tokenizer(char *lineptr)
{
    char *token = NULL;
    char *lineptr_cpy = NULL;
    char **cmd = NULL;
    char delim[] = " \t\n";
    int cpt = 0;
    int i = 0, j;

    if (!lineptr)
        return (NULL);
    lineptr_cpy = _strdup(lineptr);

    if (!lineptr_cpy)
        return (NULL);
    token = strtok(lineptr_cpy, delim);

    if (!token)
    {
        free(lineptr_cpy);
        return (NULL);
    }

    while (token)
    {
        cpt++;
        token = strtok(NULL, delim);
    }
    free(lineptr_cpy);
    cmd = malloc(sizeof(char *) * (cpt + 1));

    if (!cmd)
    {
        return (NULL);
    }
    token = strtok(lineptr, delim);
    while (token)
    {
        cmd[i] = _strdup(token);

        if (!cmd[i])
        {
            for (j = 0; j < i; j++)
            {
                free(cmd[j]);
            }
            free(cmd);
            return (NULL);
        }
        token = strtok(NULL, delim);
        i++;
    }

    cmd[i] = NULL;
    return (cmd);
}

