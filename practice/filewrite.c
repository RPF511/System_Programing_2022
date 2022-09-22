#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void){
    int fd, n, fd2;
    char buf[10];
    mode_t mode;
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* 0644 */
    if((fd = open("test", O_CREAT, mode)) == -1){
        perror("creat");
        exit(1);
    }
    if((n = read(fd, buf, 8)) == -1){
        perror("read");
        exit(1);
    }
    buf[n] = '\0';
    printf("n = %d, buf = %s\n", n, buf);
    if((fd2 = open("test2", O_CREAT | O_WRONLY, mode)) == -1){
        perror("creat2");
        exit(1);
    }
    if(write(fd2, buf, n) != n){
        perror("write");
        exit(1);
    }
    close(fd2);
    close(fd);
    return 0;
}