#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd1 = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd2 = open("test.txt", O_WRONLY);
    int fd3 = open("test.txt", O_WRONLY);
    int fd4 = open("test.txt", O_WRONLY);
    int fd5 = open("test.txt", O_WRONLY);

    printf("fds: %d %d %d %d %d\n",
            fd1, fd2, fd3, fd4, fd5);

    write(fd1, "AAA\n", 4);
    write(fd2, "BBB\n", 4);
    write(fd3, "CCC\n", 4);
    write(fd4, "DDD\n", 4);
    write(fd5, "EEE\n", 4);

    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    close(fd5);

    return 0;
}
