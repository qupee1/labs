#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *child(void *arg) {
    (void)arg;
    for (int i = 0; i < 5; i++) {
        printf("child:  line %d\n", i + 1);
        usleep(50 * 1000);
    }
    return NULL;
}

int main(void) {
    pthread_t tid;
    if (pthread_create(&tid, NULL, child, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("parent: line %d\n", i + 1);
        usleep(50 * 1000);
    }

    pthread_join(tid, NULL);
    return 0;
}
