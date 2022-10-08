#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
    char buffer[255];
    if(chdir(argv[1])){
        perror("error ");
        return 1;
    }
    getcwd(buffer,255);
    printf("cwd : %s\n", buffer);
    return 0;
}