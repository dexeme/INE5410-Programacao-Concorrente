#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

FILE* out;
sem_t semaphoreA;
sem_t semaphoreB;

void *thread_a(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        sem_wait(&semaphoreA);
        fprintf(out, "A");
        fflush(stdout);
        sem_post(&semaphoreB);
    }
    return NULL;
}

void *thread_b(void *args) {
    for (int i = 0; i < *(int*)args; ++i) {
        sem_wait(&semaphoreB);
        fprintf(out, "B");
        fflush(stdout);
        sem_post(&semaphoreA);
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s [ITERAÇÕES]\n", argv[0]);
        return 1;
    }
    int iters = atoi(argv[1]);
    srand(time(NULL));
    out = fopen("result.txt", "w");

    pthread_t ta, tb;

    sem_init(&semaphoreA, 0, 1);
    sem_init(&semaphoreB, 0, 1);



    // Cria threads
    pthread_create(&ta, NULL, thread_a, &iters);
    pthread_create(&tb, NULL, thread_b, &iters);

    // Espera pelas threads
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    //Imprime quebra de linha e fecha arquivo
    fprintf(out, "\n");
    fclose(out);
  
    sem_destroy(&semaphoreA);
    sem_destroy(&semaphoreB);
    return 0;
}
