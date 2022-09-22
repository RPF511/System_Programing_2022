// /* 변수 선언 */
// off_t fsize;
// int fd;
// fd = open(filename, O_RDWR);

// /* 파일 크기 확인하기 */
// fsize= lseek(fd, (off_t)0, SEEK_END);

// /* 기존 파일 끝에 내용 추가하기 */
// lseek(fd, (off_t)0, SEEK_END);
// write(fd, buf, BSIZE);

// /* O_APPEND flag를 이용해 파일 끝에 내용 추가하는 방법 */
// fd = open("another", O_WRONLY | O_APPEND);
// write(fd, buf, BUFSIZE);

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
char buf1[] = "abcdefghijk", buf2[] = "ABCDEFGHIJK";

void fatal(const char *str, int errcode){
    perror(str);
    exit(errcode);
}

int main(void) {
    int fd;
    if ((fd = creat("file.hole", 0640)) < 0)
        fatal("creat error", 1);
    if (write(fd, buf1, 10) != 10)
        fatal("buf1 write error", 1);
    /* offset now = 10 */
    if (lseek(fd, 40, SEEK_SET) == -1)
        fatal("lseek error", 1);
    /* offset now = 40 */
    if (write(fd, buf2, 10) != 10)
        fatal("buf2 write error", 1);
    /* offset now = 50 */
    exit(0);
}