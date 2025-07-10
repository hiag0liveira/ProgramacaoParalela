#include <stdio.h>

//para compilar usando gcc gcc q3.c -o q3.exe   
//executar .\q3.exe

void preencherVetor(int v[20]) {
  int contadorPar = 0;
  int contadorImpar = 0;

  for (int i = 0; i < 20; i++) {
    int resposta = 0;
    printf("Digite um numero: ");
    scanf("%d", &resposta);
    int resto = resposta % 2;
    if (resto == 0) {
      if (contadorPar < 10) {
        v[i] = resposta;
        contadorPar++;
      } else {
        printf("Voce ja digitou os 10 numeros pares! Digite um numero impar "
               "agora.\n");
        i--;
      }
    } else {
      if (contadorImpar < 10) {
        v[i] = resposta;
        contadorImpar++;
      } else {
        printf("Voce ja digitou os 10 numeros impares! Digite um numero pares "
               "agora.\n");
        i--;
      }
    }
  }
}

void organizarVetor(int v[20]) {
  for (int i = 0; i < 20; i++) {
    if (i % 2 == 0 && v[i] % 2 == 0) {
      for (int j = i + 1; j < 20; j++) {
        if ((j % 2) != (i % 2) && (v[j] % 2) == (j % 2)) {
          int tmp = v[i];
          v[i] = v[j];
          v[j] = tmp;
          break;
        }
      }
    }
  }
}

int main(void) {
  printf("Ola, seja bem vindo! Você deve digitar 10 numeros pares e 10 umeros "
         "impares, sem roubar em?!\n\n");
  int vetor[20];
  preencherVetor(vetor);
  organizarVetor(vetor);

  printf("vetor: [");
  for (int i = 0; i < 20; i++) {
    if (i == 19) {
      printf("%d]", vetor[i]);
    } else {
      printf("%d,", vetor[i]);
    }
  }

  return 0;
}