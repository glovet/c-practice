
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>
#include <sched.h>

#include <iostream>
#include <atomic>

#include "mpmc-bounded-queue.hpp"

#define MAX_NUM 65500
#define test_num 100000000
// #define test_num 10000000

std::atomic<int> push_num(0);
std::atomic<int> pop_num(0);
std::atomic<bool> flag(false);

struct Test
{
    char buf[96];
    int a;
};

uint64_t get_sec()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*1000000 + tv.tv_usec;
}

mpmc_bounded_queue_t<Test*> test_queue(65536);

void* push(void* arg)
{
    int thread_id = *(int*)(arg);
    uint64_t start_sec = get_sec();
    while (1) {
        Test* test = new Test();
        test_queue.enqueue(test);
        push_num ++;
        if (test_num <= push_num.load()) {
            break;
        }
        if (test_queue.size() > MAX_NUM) {
            sched_yield();
            continue;
        }
    }
    uint64_t end_sec = get_sec();

    size_t num = push_num;
    printf("push thread %d, push num %zu, use time %f sec\n", thread_id, num, (end_sec - start_sec) / 1000000.0f);
    flag = true;
}

void* pop(void* arg)
{
    int thread_id = *(int*)(arg);
    uint64_t start_sec = get_sec();
    while (1) {
        if (flag) {
            //printf("thread id:%d, num:%d\n", thread_id, pop_num.load());
        }
        Test* test = NULL;
        if (!test_queue.dequeue(test)) {
            sched_yield();
            // usleep(10);//10 ms
            continue;
        }
        delete test;
        pop_num++;
        if (test_num <= pop_num.load()) {
            break;
        }
    }
    uint64_t end_sec = get_sec();

    size_t num = push_num;
    printf("pop thread %d, pop num %zu, use time %f sec\n", thread_id, num, (end_sec - start_sec) / 1000000.0f);
}

int main()
{
    pthread_t id1, id2, id3, id4, id5, id6 = 0;
    int push_tid1 = 1;
    int  push_tid2 = 2;
    int  push_tid3 = 3;
    int pop_tid1 = 1;
    int  pop_tid2 = 2;
    int  pop_tid3 = 3;

    pthread_create(&id1, NULL, push, &push_tid1);
    pthread_create(&id2, NULL, pop, &pop_tid1);

    pthread_create(&id3, NULL, push, &push_tid2);
    pthread_create(&id4, NULL, pop, &pop_tid2);

    // pthread_create(&id5, NULL, push, &push_tid3);
    // pthread_create(&id6, NULL, pop, &pop_tid3);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);
    pthread_join(id4, NULL);
    // pthread_join(id5, NULL);
    // pthread_join(id6, NULL);

    return 1;
}
