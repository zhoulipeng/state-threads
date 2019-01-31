
//gcc -I../obj -g huge_threads.c ../obj/libst.a -o huge_threads
//./huge_threads 10000
//./huge_threads 30000
//
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "st.h"
 
#define SLEEP_INTERVAL 30  //in ms
 
void* do_calc(void* arg){
    long pidx = *(long*)arg;
    printf("sthread [#%ld] start\n", pidx);
    for(;;){
        printf("sthread [#%ld] usleep\n", pidx);
        st_usleep(SLEEP_INTERVAL * 1000);
    }
    return NULL;
}
void* thread_func(void* name)
{
    if(st_init() < 0){
        printf("state threads lib runtime init error!");
        return NULL;
    }
 
    long i, count = atoi((const char*)name);
    for(i = 1; i <= count; i++){
        if(st_thread_create(do_calc, (void*)&i, 0, 0) == NULL){
            printf("create state thread %d failed\n", i);
            return NULL;
        }
        // 由于协成启动较慢，外部变了 i 已经变了，do_calc才执行
        st_usleep(SLEEP_INTERVAL * 10000);
    }
    st_thread_exit(NULL);
} 

int main(int argc, char** argv){
    if(argc <= 1){
        printf("Test the concurrence of state-threads!\n"
            "Usage: %s <sthread_count>\n"
            "eg. %s 10000\n", argv[0], argv[0]);
        return -1;
    }
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, argv[1]);
    pthread_join(tid, NULL);
 
    return 0;
}
/*
// --------------------- 

作者：雪峰流云 

来源：CSDN 

原文：https://blog.csdn.net/tao_627/article/details/45788013 

版权声明：本文为博主原创文章，转载请附上博文链接！
2.0 version author :zhoulipeng
*/

