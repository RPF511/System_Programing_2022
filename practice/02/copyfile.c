#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFSIZE 8
// #define BUFSIZE 512 /* 한 번에 읽을 문자열의 크기 */
#define PERM 0644   /* 새로 만든 파일의 사용 권한 */

/**
 * 파일을 복사하여 사본을 생성한다.
 * @param src 원본 파일 이름
 * @param dst 사본 파일 이름
 * @return 정상적으로 처리된 경우 0, 오류가 있는 경우 1
 */
int copy_file(const char *src, const char *dst);
void create_holed_file(const char *str);
int fatal(const char *str);

int main() {
  create_holed_file("file.hole");
	copy_file("file.hole", "file2.hole");
	return 0;
}

int copy_file(const char *src, const char *dst)
{
    int fd_s, fd_d, n, m;
    char buffer[BUFSIZE];
    if ((fd_s = open(src, O_RDONLY)) == -1)
    {
        fatal("source file error");
    }

    if ((fd_d = open(dst, O_CREAT | O_WRONLY | O_TRUNC, PERM)) == -1)
    {
        fatal("file create error");
    }

    while ((n = read(fd_s, buffer, BUFSIZE)) != 0)
    {
        printf("%d buffer : %s\n",n,buffer);
        if (n == -1){
            fatal("source file read error");
        }
        if (write(fd_d, buffer, n) != n){
            fatal("file copy error");
        }
    }
    close(fd_s);
    close(fd_d);

    return 0;
}

void create_holed_file(const char *str)
{
    char buf1[] = "abcdefghij", buf2[] = "ABCDEFGHIJ";
    int fd;

    if ((fd = creat(str, 0640)) < 0)
        fatal("creat error");

    if (write(fd, buf1, 10) != 10)
        fatal("buf1 write error");

    if (lseek(fd, 40, SEEK_SET) == -1)
        fatal("lseek error");

    if (write(fd, buf2, 10) != 10)
        fatal("buf2 write error");
}

int fatal(const char *str) {
  perror(str);
  return 1;
}
