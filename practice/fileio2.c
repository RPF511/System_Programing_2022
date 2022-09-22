#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void){
    int fd;
    mode_t mode;
    // mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* 0644 */
    mode =  S_IWUSR | S_IRGRP | S_IROTH; /* 0244 */
    if((fd = open("test", O_CREAT, mode)) == -1){
        perror("creat");
        exit(1);
    }
    close(fd);
    return 0;
}

// /* create new file */
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// int main(void){
//     int fd;
//     mode_t mode;
//     mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* 0644 */
//     if((fd = open("test", O_CREAT | O_EXCL, mode)) == -1){
//         perror("creat");
//         exit(1);
//     }
//     close(fd);
//     return 0;
// }


// /* create new file */
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// int main(void){
//     int fd;
//     mode_t mode;
//     mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* 0644 */
//     if((fd = open("test", O_CREAT | O_TRUNC, mode)) == -1){
//         perror("creat");
//         exit(1);
//     }
//     close(fd);
//     return 0;
// }