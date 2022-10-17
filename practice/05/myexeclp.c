#define _XOPEN_SOURCE
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stddef.h>
#define MAXARGS 128
#define MAXFILENAME 1024
#define MAXPATHSTR 4096

extern char **environ;
int myexeclp(const char *file, const char *args, ...);
int myexecve_to_absolute_path(const char *file, char *const argv[], char *const envp[]);

int main(void)
{
    char path[MAXPATHSTR];
    pid_t pid;
    int status;

    sprintf(path, "PATH=%s:%s", getcwd(NULL, 0), getenv("PATH"));
    putenv(path);
    // prepare the executable file named "hello"
    system("cp hello.tmp hello.c");
    system("gcc -pthread -lm -o hello hello.c");
    system("rm hello.c");

    if ((pid = fork()) < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("child process : myexeclp\n");
        myexeclp("hello", "hello", "-a", "-b", "-c", NULL);
        // sleep(1);
        exit(0);
    }
    else
    {
        waitpid(pid, &status, 0);
        printf("\nparent process : execlp\n");
        execlp("hello", "hello", "-a", "-b", "-c", (char *)0);
        exit(0);
    }
    exit(0);

    return 0;
}

int myexeclp(const char *file, const char *args, ...)
{
    // 해당 밑의 주석처리된 함수 흔적들의 시도를 하였으나 stdarg 내부 구조를 파악하지 못해 너무 많은 문제가 발생했고, 오랜 시간 고민 끝에 
    /// execlp 와 execvpe의 소스 코드를 참고하였습니다
    // 해당 소스 코드를 참고하며 stdarg va_의 동작방식을 미약하게 이해한 것 같으나 아래의 에러들 발생이유는 잘 모르겠습니다
    ptrdiff_t argc;
    va_list ap;
    va_start(ap, args);
    for (argc = 1; va_arg(ap, const char *); argc++)
    {
        if (argc == MAXARGS)
        {
            va_end(ap);
            errno = E2BIG;
            return -1;
        }
    }
    va_end(ap);

    ptrdiff_t i;
    // char *argv[argc + 1];
    char *argv[MAXARGS];
    va_start(ap, args);
    argv[0] = (char *)args;
    for (i = 1; i <= argc; i++)
        argv[i] = va_arg(ap, char *);
    va_end(ap);

    // char temp_str[MAXARGS];
    // strcpy(temp_str,argv[i]);
    // strcpy(argv[i],getcwd(NULL, 0));
    // strcat(argv[i],temp_str);

    // for (i = 0; i <= argc; i++)
    //     printf("%s ",argv[i]);
    // printf("\n");
    
    // return execvpe (file, argv, __environ);
    return myexecve_to_absolute_path (file, argv, __environ);
}

int myexecve_to_absolute_path(const char *file, char *const argv[], char *const envp[]){
    char filepath[MAXARGS];
    strcpy(filepath,getcwd(NULL, 0));
    strcat(filepath,"/");
    strcat(filepath,file);
    // printf("%s\n",filepath);
    return execve(filepath,argv,envp);
}


///해당코드 cwd무한루프 출력
// int myexeclp(const char *file, const char *args, ...)
// {
//     va_list ap;
//     int i = 1;
//     char *str[MAXARGS] = {};
//     char s[MAXARGS];
//     sprintf(s,"%s/%s",getcwd(NULL, 0),file);
//     printf("%s\n",s);
//     // strcpy(str[0],args); // 해당 명령어가 있을 경우 밑에 while문이 돌지 않는다 -> 왜?
//     // strcpy(str[0],file);
//     // printf("%s\n",str[0]);
//     va_start(ap, args);
//     // printf("%s\n",args);
//     while (*args)
//     {
//         // strcpy(str[i++],va_arg(ap, char *));
//         // str[i++] = va_arg(ap, char *);
//         // s = va_arg(ap, char *);
//         printf("string %s\n", s);
//         // strcpy(str[i++],s);

//     }
    
//     va_end(ap);
//     printf("%s\n",file);
//     for(int j = 0; j < i ; j++){
//         printf("%s\n",str[j]);
//     }
    
// }

// int myexeclp(const char *file, const char *args, ...)
// {
//     va_list ap;
//     int d;
//     char c;
//     char *s;
//     printf("%s\n",args);
//     va_start(ap, args);
//     while (*args)
//     {
//         printf("args case %c\n",*args);
//         switch (*args++)
//         {
//         case 's': /* 문자열 */
//             s = va_arg(ap, char *);
//             printf("string %s\n", s);
//             break;
//         case 'd': /* int */
//             d = va_arg(ap, int);
//             printf("int %d\n", d);
//             break;
//         case 'c': /* char */
//             c = (char)va_arg(ap, int);
//             printf("char %c\n", c);
//             break;
//         }
//     }

//     va_end(ap);
// }