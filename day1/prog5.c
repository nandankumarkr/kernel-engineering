#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define BYTES_PER_LINE 16

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    unsigned char buffer[BYTES_PER_LINE];
    ssize_t n;
    long offset = 0;

    while ((n = read(fd, buffer, BYTES_PER_LINE)) > 0)
    {
        /* offset */
        printf("%08lx: ", offset);

        /* hex bytes */
        for (int i = 0; i < BYTES_PER_LINE; i++)
        {
            if (i < n)
                printf("%02x", buffer[i]);
            else
                printf("  ");

            if (i % 2 == 1)
                printf(" ");
        }

        /* ascii */
        printf(" ");

        for (int i = 0; i < n; i++)
        {
            if (isprint(buffer[i]))
                printf("%c", buffer[i]);
            else
                printf(".");
        }

        printf("\n");

        offset += n;
    }

    close(fd);
    return 0;
}
