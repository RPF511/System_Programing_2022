#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <grp.h>
#include <pwd.h>

void printStat(struct stat *stat) {
  mode_t file_mode = stat->st_mode;
  if (S_ISREG(file_mode))
    printf("정규파일\n");
  else if (S_ISLNK(file_mode))
    printf("심볼릭링크\n");
  else if (S_ISDIR(file_mode))
    printf("디렉토리\n");
  else if (S_ISCHR(file_mode))
    printf("문자디바이스\n");
  else if (S_ISBLK(file_mode))
    printf("블럭디바이스\n");
  else if (S_ISFIFO(file_mode))
    printf("FIFO\n");
  else if (S_ISSOCK(file_mode))
    printf("소켓\n");
  struct passwd *my_passwd;
  struct group *my_group;
  my_passwd = getpwuid(stat->st_uid);
  my_group = getgrgid(stat->st_gid);
  printf("OWNER : %s\n", my_passwd->pw_name);
  printf("GROUP : %s\n", my_group->gr_name);
  printf("FILE SIZE IS : %ld\n", stat->st_size);
  printf("마지막읽은시간: %ld\n", stat->st_atime);
  printf("마지막수정시간: %ld\n", stat->st_mtime);
  printf("하드링크된파일수: %ld\n\n", stat->st_nlink);
}

int a_rX(char *pathname, struct stat *statbuf) {
  if (stat(pathname, statbuf) < 0) {
    perror("load stat error : ");
    return -1;
  }
  printStat(statbuf);
  mode_t st_mode_temp = statbuf->st_mode;
  if (chmod(pathname, st_mode_temp | S_IRUSR | S_IRGRP | S_IROTH) < 0) {
    perror("read permission error : ");
    return -1;
  }
  st_mode_temp = st_mode_temp | S_IRUSR | S_IRGRP | S_IROTH;
  if ((statbuf->st_mode & S_IXUSR) || S_ISDIR(statbuf->st_mode)) {
    if (chmod(pathname, st_mode_temp | S_IXUSR | S_IXGRP | S_IXOTH) < 0) {
      perror("execution permission error : ");
      return -1;
    }
  }

  return 0;
}

int main(int argc, char **argv) {
  struct stat tempstat;

  // printf("%d\n", argc);
  for (int i = 1; i < argc; i++) {
    // printf("%s\n", argv[i]);

    if (a_rX(argv[i], &tempstat) < 0)
      continue;
  }
  return 0;
}