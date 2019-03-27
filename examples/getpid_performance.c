#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
    int64_t i;
    struct timeval start;
    gettimeofday(&start, NULL);
    printf("%ld, %ld", start.tv_sec, start.tv_usec);
    for (i = 0; i < 10000000ULL; i++) {
        //getpid(); // state-threads的 getpid可以去掉,提高性能
    }
    gettimeofday(&start, NULL);
    printf("%ld, %ld", start.tv_sec, start.tv_usec);
    return 0;
}

