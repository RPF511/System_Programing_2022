//shell 에서 >> 만들때 필요

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void){
    int fd, fd1;
    if((fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1){
        perror("creat");
        exit(1);
    }
    close(1);
    // close(STDOUT_FILENO);    //STDOUT_FILENO  = 1 in linux
    fd1 = dup(fd);
    printf("Ori FD = %d\n", fd);
    printf("DUP FD = %d\n", fd1);
    printf("Standard Output Redirection\n");
    close(fd);
    return 0;
}

// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// int main(void){
//     int fd;
//     if((fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1){
//         perror("creat");
//         exit(1);
//     }
//     dup2(fd, 1);
//     printf("DUP2: Standard Output Redirection\n");
//     close(fd);
//     return 0;
// }