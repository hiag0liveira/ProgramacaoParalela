//Hiago de Oliveira Mendes e Lucas Rocha Rangel

#include <stdio.h>
#include <pthread.h>

// Função que a primeira Thread vai executar
void* imprimirProgramacaoParalela(void* arg) {
    printf("Programacao Paralela\n");
    return NULL;
}

// Função que a segunda Thread vai executar
void* imprimirSistemasInformacao(void* arg) {
    printf("Sistemas de Informacao\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Criar a primeira Thread
    pthread_create(&thread1, NULL, imprimirProgramacaoParalela, NULL);

    // Criar a segunda Thread
    pthread_create(&thread2, NULL, imprimirSistemasInformacao, NULL);

    // Esperar as Threads terminarem
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
