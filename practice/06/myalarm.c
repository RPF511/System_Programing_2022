#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void myalarm()
{
    printf("ding dong dang\n");
}
int main()
{
    int i = 0;
    printf("alarm setting\n");
    // SIGALRM 이 발생하면 myalarm() 함수를 실행한다.
    signal(SIGALRM, myalarm);
    // 알람을 1초로 설정한다.
    alarm(1);
    while (i < 5)
    {
        printf("ok\n");
        // 신호를 기다린다.
        pause();
        // alarm 을 2초로 설정한다.
        alarm(2);
        i++;
    }
}