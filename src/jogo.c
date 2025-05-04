#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <unistd.h>
#include <time.h>



void digitacao(){
    printf("anon1mo333: "); // print fixo
    fflush(stdout);

    for(int i = 0; i < 2; i++){ // simula por alguns ciclos
        printf("\ranon1mo333: Digitando.  ");
        fflush(stdout);
        sleep(1);
        printf("\ranon1mo333: Digitando.. ");
        fflush(stdout);
        sleep(1);
        printf("\ranon1mo333: Digitando...");
        fflush(stdout);
        sleep(1);
    }
    printf("\r                         \r");
    fflush(stdout);
}

int guessgame(){
    srand(time(NULL));
    int numero;
    int numero_correto = 69; //rand() % 101;
    int escolha;
    printf("Olá! Bem vindo ao Guess Game! Adivinhe qual numero estou pensando de 1 a 100 :D\n");
    while(1){
        scanf("%d", &numero);
        if(numero > numero_correto){
            printf("\nHmm, seu número é maior que o meu! Tente denovo!\n");
        }else if(numero < numero_correto){
            printf("\nHmm, seu número é menor que o meu! Tente denovo!\n");
        }else{
            printf("\nParabéns! Você acertou! O número que eu estava pensando é: %d\n", numero_correto);
            break;
}
}
}