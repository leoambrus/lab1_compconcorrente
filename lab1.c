#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2 
int vet[10000];

typedef struct{
    int posinicial, posfinal, vet1[];
} t_Args;

void *eleva(void *arg){
    t_Args *args = (t_Args *) arg;
    
    for(int i = args->posinicial; i < args->posfinal; i++){
        int temp = vet[i];
        vet[i] = temp*temp;
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t tid_sistema[NTHREADS];
    int inicio = 0, meio = 5000, fim = 10000;
    for (int s=0; s<10000;s++){
        vet[s] = s;
    }
    t_Args *arg;

    for(int thread = 0; thread < NTHREADS; thread++){
        arg = malloc(sizeof(t_Args));
        if (arg == NULL) {
            printf("--ERRO em malloc\n"); exit(-1);
        }
        for(int k=0; k < arg->posfinal; k++){
            arg->vet1[k] = vet[k];
        }
        if (thread == 0){
            arg->posinicial = inicio;
            arg->posfinal = meio;
        }
        else{
            arg->posinicial = meio;
            arg->posfinal = fim;
        }

        if (pthread_create(&tid_sistema[thread], NULL, eleva, (void*) arg)) {
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
        pthread_join(thread,NULL);
    }

    pthread_exit(NULL);

}