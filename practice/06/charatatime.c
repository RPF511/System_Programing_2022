#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

static void charatatime(char * str){
    char * ptr;
    int c;
    setbuf(stdout, NULL);
    
    for(ptr = str ; c = *ptr++;)
        putc(c, stdout);
}

int main(void){
    pid_t pid;
    if((pid = fork()) < 0){
        perror("fork error\n");
        exit(1);
    } else if (pid == 0){
        // printf("here\n");
        pause();
        // printf("here\n");
        charatatime("output from child\n");
        
    }else{
        charatatime("output from parent\n");
        // sleep(3);
        kill(pid, SIGALRM);
    }
    exit(0);
}