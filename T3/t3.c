//Hiago de Oliveira Mendes e Lucas Rocha Rangel

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#define MAX_THREADS 4

/* Índices para facilitar a referência aos vetores */
enum { IDX_SOMA = 3, IDX_SUBTRACAO = 2, IDX_MULTIPLICACAO = 1, IDX_DIVISAO = 0 };

/* Estrutura compartilhada por todas as threads (somente leitura durante as N execuções) */
typedef struct {
    int a, b;           /* Operandos (b != 0) */
    int N;              /* Número de sequências (N >= 1) */
    int tempos[4];      /* t_i(tempo inteiro) de cada operação: fixos em todas as repetições (1..10) */
    sem_t sem[4];       /* Semáforos para impor a ordem So -> Su -> Mu -> Di */
} Compartilhado;

/* Estrutura com os dados que serão passados para cada Thread */
typedef struct {
    Compartilhado *S;
    int indiceOperacao;         /* 0=So, 1=Su, 2=Mu, 3=Di */
    char operacao[20];          /* "SOMA", "SUBTRACAO", "MULTIPLICACAO", "DIVISAO" */
} DadosThread;

/* Função de apoio para calcular o resultado e o símbolo textual da operação */
static int calcularResultado(int a, int b, int idx, char *simbolo /*out*/) {
    switch (idx) {
        case IDX_SOMA:          *simbolo = '+'; return a + b;
        case IDX_SUBTRACAO:     *simbolo = '-'; return a - b;
        case IDX_MULTIPLICACAO: *simbolo = '*'; return a * b;
        case IDX_DIVISAO:       *simbolo = '/'; return a / b;
        default: *simbolo = '?'; return 0;
    }
}

/* Função executada por cada Thread */
void* executarOperacao(void* arg) {
    DadosThread* dados = (DadosThread*) arg;
    Compartilhado *S = dados->S;
    const int idx = dados->indiceOperacao;
    const int tempo = S->tempos[idx];

    for (int k = 1; k <= S->N; ++k) {
        /* Aguarda o direito de execução da k-ésima sequência desta operação */
        sem_wait(&S->sem[idx]);

        sleep(tempo);

        /* Calcula e imprime o resultado da operação da sequência k */
        char op;
        int resultado = calcularResultado(S->a, S->b, idx, &op);
        printf("Seq %d - Thread %s: %d %c %d = %d (t=%ds)\n",
               k, dados->operacao, S->a, op, S->b, resultado, tempo);

        /* Libera a próxima operação da sequência k, ou inicia a próxima sequência */
        if (idx == IDX_DIVISAO) {
            if (k < S->N) sem_post(&S->sem[IDX_SOMA]);   /* inicia Soma da sequência k+1 */
        } else {
            sem_post(&S->sem[idx - 1]);                  /* libera a próxima operação da mesma sequência */
        }
    }

    pthread_exit(NULL);
}

int main(void) {
    int a, b, N;
    pthread_t threads[MAX_THREADS];
    DadosThread dados[MAX_THREADS];
    Compartilhado S;     /* “Compartilhado S” é só o objeto que guarda tudo o que é comum a TODAS as threads.
    A ideia é ter um único bloco de memória com os parâmetros e os semáforos, e cada thread recebe um ponteiro
    para esse mesmo bloco. Assim, todas “enxergam” os mesmos valores e os mesmos semáforos. */

    const char* operacoes[] = {"DIVISAO", "MULTIPLICACAO", "SUBTRACAO", "SOMA"};

    /* Entrada simples */
    printf("Digite o valor de a: ");
    scanf("%d", &a);

    do {
        printf("Digite o valor de b (b != 0): ");
        scanf("%d", &b);
    } while (b == 0);

    do {
        printf("Digite N (N >= 1): ");     /*Quantas vezes vai ser repetido a sequencia */
        scanf("%d", &N);
    } while (N < 1);

    /* Preenche estrutura compartilhada */
    S.a = a;
    S.b = b;
    S.N = N;

    /* Semente e sorteio dos tempos (aleatoriamente) (1..10), uma vez por operação */
    srand((unsigned)time(NULL));
    for (int i = 0; i < MAX_THREADS; ++i) {
        S.tempos[i] = (rand() % 10) + 1;
    }

    /* Mostra os tempos sorteados (facilita a avaliação) */
    printf("\nTempos fixos por operacao:\n");

    printf("Tempo de soma: tSoma = %ds\n", S.tempos[IDX_SOMA]);

    printf("Tempo de subtracao: tSubtracao = %ds\n", S.tempos[IDX_SUBTRACAO]);

    printf("Tempo de multiplicacao: tMultiplicacao = %ds\n", S.tempos[IDX_MULTIPLICACAO]);

    printf("Tempo de divisao: tDivisao = %ds\n\n", S.tempos[IDX_DIVISAO]);


    /* Inicialização dos semáforos:
       - Soma inicia liberada (1) para dar início à 1ª sequência (Força a ordem para começar em soma)
       - Demais operações iniciam bloqueadas (0) */
    sem_init(&S.sem[IDX_SOMA], 0, 1);
    sem_init(&S.sem[IDX_SUBTRACAO], 0, 0);
    sem_init(&S.sem[IDX_MULTIPLICACAO], 0, 0);
    sem_init(&S.sem[IDX_DIVISAO], 0, 0);

    /* Criação das quatro threads (persistem durante toda a execução) */
    for (int i = 0; i < MAX_THREADS; ++i) {
        dados[i].S = &S;
        dados[i].indiceOperacao = i;
        strcpy(dados[i].operacao, operacoes[i]);
        pthread_create(&threads[i], NULL, executarOperacao, (void*)&dados[i]);
    }

    /* Aguarda todas as threads finalizarem */
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    /* Destrói os semáforos e encerra */
    for (int i = 0; i < MAX_THREADS; ++i) {
        sem_destroy(&S.sem[i]);
    }

    printf("\nExecucao finalizada.\n");
    return 0;
}
