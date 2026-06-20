#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    char *path = getenv("PATH");

    if (path == NULL)
    {
        fprintf(stderr, "PATH not found\n");
        return 1;
    }

    printf("PATH = %s\n\n", path);

    char *copy = strdup(path);

    char *dir = strtok(copy, ":");

    while (dir != NULL)
    {
        char fullpath[1024];

        snprintf(fullpath,
                 sizeof(fullpath),
                 "%s/%s",
                 dir,
                 argv[1]);

        printf("Checking: %s\n", fullpath);

        if (access(fullpath, X_OK) == 0)
        {
            printf("\nFound executable:\n");
            printf("%s\n", fullpath);

            free(copy);
            return 0;
        }

        dir = strtok(NULL, ":");
    }

    printf("\nCommand not found\n");

    free(copy);
    return 1;
}
