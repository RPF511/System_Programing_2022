#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

void creatEnv();

void fatal(const char *str, int exit_no);
void access_perm(char *perm, mode_t mode);
/**
 * 파일을 복사하여 사본을 생성한다.
 * @param buf   경로명을 저장할 버퍼 변수.
 * @param size  버퍼 변수의 크기
 * @return 버퍼 변수의 시작 주소, 즉 buf
 */

char * find_dir_name(char *buf, char *current_progress, size_t size, ino_t inode)
{
    DIR *dp;
    struct dirent *dent;
    struct stat statbuf;
    char current[500];
    char dirname[50];
    dirname[0] = '/'; dirname[1] = '\0';
    char perm[11];
    ino_t current_inode = 0;
    ino_t parent_inode = 0;
    // printf("find cwd in progress : %s  inode : %ld\n",current_progress, inode);
    strcpy(buf, current_progress);
    if ((dp = opendir(current_progress)) == NULL)
        fatal("opendir error", 1);
    printf("find cwd in progress : %s   inode : %ld\n", current_progress, inode );
    while ((dent = readdir(dp)) != NULL)
    {
        sprintf(current, "%s/%s",current_progress, dent->d_name);
        // printf("current : %s\n", current);
        if (stat(current, &statbuf) < 0)
        {
            // perror("stat error");
            continue;
        }
        access_perm(perm, statbuf.st_mode);
        printf("%s %8ld %20ld %s\n", perm, statbuf.st_size, statbuf.st_ino,dent->d_name);

        
        if (!strcmp(dent->d_name, ".."))
        {
            // printf("%s %8ld %20ld %s\n", perm, statbuf.st_size, statbuf.st_ino,dent->d_name);
            parent_inode = statbuf.st_ino;
            
            continue;
        }
        if (!strcmp(dent->d_name, "."))
        {
            // printf("%s %8ld %20ld %s\n", perm, statbuf.st_size, statbuf.st_ino,dent->d_name);
            current_inode = statbuf.st_ino;
            
            continue;
        }
        if (statbuf.st_ino == inode)
        {
            //   current_progress[0] = '/';
            //   current_progress[1] = '\0';
            //   strcat(current_progress, dent->d_name);
            //   strcat(current_progress, buf);
            // printf("%s %8ld %20ld %s\n", perm, statbuf.st_size, statbuf.st_ino,dent->d_name);
            
            strcat(dirname, dent->d_name);
        }
    }
    printf("parent inode : %ld\n", statbuf.st_ino);
    printf("current inode : %ld\n", statbuf.st_ino);
    printf("dirname : %s\n", dirname);
    closedir(dp);

    if (current_inode == parent_inode)
    {
        strcpy(buf,"/");
        strcpy(buf,dirname);
        return buf;
    }
    else
    {
        
        strcat(current_progress,"/..");
        find_dir_name(buf,current_progress,size,current_inode);
        strcat(buf,dirname);
        return buf;
    }

}



char *mygetcwd(char *buf, size_t size)
{
    struct stat statbuf;
    char current_progress[size];
    // current_progress[0] = '\0';
    current_progress[0] = '.';
    current_progress[1] = '.';
    current_progress[2] = '\0';
    if (stat(".", &statbuf) < 0)
        fatal("stat error", 1);
    find_dir_name(buf, current_progress, size, statbuf.st_ino);
    return buf;
}

int main(void)
{
    pid_t pid;
    int status;
    char buf[255];

    creatEnv();
    chdir("dir/sub");

    printf("original func: %s\n", getcwd(NULL, 0));
    printf("mygetcwd func: %s\n", mygetcwd(buf, 255));

    return 0;
}

void creatEnv()
{
    mkdir("dir", 0755);
    mkdir("dir/sub", 0755);
    mkdir("dir/sub2", 0);

    creat("dir/a", 0755);
    creat("dir/b", 0755);
    creat("dir/sub/x", 0755);
    symlink("dir/a", "dir/sl");
    symlink("dir/x", "dir/dsl");
}

void fatal(const char *str, int exit_no)
{
    perror(str);
    exit(exit_no);
}

void access_perm(char *perm, mode_t mode)
{
    int i;
    char permchar[] = "rwx";
    memset(perm, '-', 10);
    perm[10] = '\0';
    if (S_ISDIR(mode))
        perm[0] = 'd';
    else if (S_ISCHR(mode))
        perm[0] = 'c';
    else if (S_ISBLK(mode))
        perm[0] = 'b';
    else if (S_ISFIFO(mode))
        perm[0] = 'p';
    else if (S_ISLNK(mode))
        perm[0] = 'l';
    for (i = 0; i < 9; i++)
        if ((mode << i) & 0x100)
            perm[i + 1] = permchar[i % 3];
    if (mode & S_ISUID)
        perm[3] = 's';
    if (mode & S_ISGID)
        perm[6] = 's';
    if (mode & S_ISVTX)
        perm[9] = 't';
}