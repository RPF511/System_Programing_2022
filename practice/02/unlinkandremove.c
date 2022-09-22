#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void){
    int cnt;
    cnt = unlink("tmp");
    if(cnt == -1){
        perror("unlink tmp");
        exit(1);
    }
    printf("unlink tmp success\n");
    return 0;
}

// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// int main(void){
//     int cnt;
//     cnt = remove("tmp");
//     if(cnt == -1){
//         perror("remove tmp");
//         exit(1);
//     }
//     printf("remove tmp success\n");
//     return 0;
// }