#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: a. out <pathname>");
        exit(1);
    }
    if (access(argv[1], R_OK) < 0)
        perror("access error");
    else
        printf("read access OK\n");
    if (open(argv[1], O_RDONLY) < 0)
        perror("open error");
    else
        printf("open for reading OK\n");
    exit(0);
}