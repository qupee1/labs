#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void cleanup(void *arg) {
    int id = *(int *)arg;
    printf("worker %d: cleanup — saying goodbye\n", id);
}

void *worker(void *arg) {
    int id = *(int *)arg;

    pthread_cleanup_push(cleanup, arg);

    for (int i = 0; ; i++) {
        printf("worker %d: tick %d\n", id, i);
        sleep(1);
    }

    pthread_cleanup_pop(0);
    return NULL;
}

int main(void) {
    enum { N = 3 };
    pthread_t tids[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        ids[i] = i + 1;
        pthread_create(&tids[i], NULL, worker, &ids[i]);
    }

    sleep(2);
    printf("main: cancelling workers\n");

    for (int i = 0; i < N; i++) {
        pthread_cancel(tids[i]);
        pthread_join(tids[i], NULL);
    }
    printf("main: done\n");
    return 0;
}
