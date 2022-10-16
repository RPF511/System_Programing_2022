#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int glob = 6;

int main(void){
    int var;
    pid_t pid;
    var = 88;
    // if((pid = fork())<0){
    if((pid = vfork())<0){
        perror("fork error");
        exit(1);
    }else if(pid==0){
        glob++;
        var++;
        _exit(0);
    }
    printf("pid = %d, glob = %d, var = %d\n",getpid(),glob,var);
    exit(0);
}