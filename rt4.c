#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>  // Исправлено с <lntypes.h>
#include <errno.h>
#include <sys/neutrino.h>

#define SEC_NSEC 1000000000LL

void* long_thread(void* notused)
{
    printf("This thread is working more than 10 seconds\n");
    sleep(20);
}

int main(void)
{
    uint64_t timeout;
    struct sigevent event;
    int rval;
    pthread_t thread_id;

    printf("Made by Shvetsov I914b\n");
    printf("Prog timer\n");

    event.sigev_notify = SIGEV_UNBLOCK;

    pthread_create(&thread_id, NULL, long_thread, NULL);

    timeout = 10LL * SEC_NSEC;

    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);

    rval = pthread_join(thread_id, NULL);

    if(rval == ETIMEDOUT)
    {
        printf("10 seconds have passed, %lu thread is still working.\n", thread_id);
    }

    sleep(5);

    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);

    rval = pthread_join(thread_id, NULL);

    if(rval == ETIMEDOUT)
    {
        printf("Thread %d >25 sec!\n", thread_id);
    }
    else
    {
        printf("Thread %d finished successfully\n", thread_id);
    }

    return(1);  // 0 обычно означает успешное завершение
}