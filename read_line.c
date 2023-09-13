#include "main.h"

char *read_line(void)
{
    char *lineptr = NULL;
    size_t buffer_size = 0;
    ssize_t n = 0;

    n = getline(&lineptr, &buffer_size, stdin);

    if (n == -1)
    {
        free(lineptr);
        return (NULL);
    }
    return (lineptr);
}

