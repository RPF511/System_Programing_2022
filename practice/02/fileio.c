#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
char *workfile = "test";
int main() {
    int fd;
    /* <fcntl.h>에 정의된 O_RDWR을 사용하여 파일을 읽기/쓰기로 개방한다 */
    if ((fd = open(workfile, O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }
    /* 프로그램의 나머지 부분 */
    exit(0); /* 정상적인 퇴장 */
}