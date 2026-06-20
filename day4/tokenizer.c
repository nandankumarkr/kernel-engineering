#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **tokenize(char *line)
{
    int capacity = 10;
    int count = 0;

    char **argv = malloc(capacity * sizeof(char *));
    if (argv == NULL)
        return NULL;

    char *p = line;

    while (*p)
    {
        /* Skip spaces and tabs */
        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == '\0')
            break;

        /* Start of token */
        argv[count++] = p;

        /* Move to end of token */
        while (*p && *p != ' ' && *p != '\t')
            p++;

        /* End token */
        if (*p)
        {
            *p = '\0';
            p++;
        }

        /* Expand array if needed */
        if (count >= capacity - 1)
        {
            capacity *= 2;
            argv = realloc(argv, capacity * sizeof(char *));
            if (argv == NULL)
                return NULL;
        }
    }

    argv[count] = NULL;
    return argv;
}

int main()
{
    char line[256];

    printf("Enter command: ");
    fgets(line, sizeof(line), stdin);

    /* Remove newline */
    line[strcspn(line, "\n")] = '\0';

    char **argv = tokenize(line);

    printf("\nTokens:\n");
    for (int i = 0; argv[i] != NULL; i++)
    {
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    }

    free(argv);
    return 0;
}
