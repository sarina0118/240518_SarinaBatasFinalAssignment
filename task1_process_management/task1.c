#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t lock;
void* worker(void* arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        printf("Thread %d -> Counter = %d\n", id, counter);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}
int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    pthread_mutex_init(&lock, NULL);
    for(int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    printf("\nFinal Counter = %d\n", counter);
    return 0;
}
