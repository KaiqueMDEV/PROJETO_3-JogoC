#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <unistd.h>
#include <time.h>




int main(){
    int escolha;
    for(int i = 0; i < 3; i++){
        guessgame();
        printf("\nDeseja jogar novamente?\n1. Sim\n2. Não\n");
        scanf("%d", &escolha);
        if(escolha == 2){
            break;
        }
    }
    digitacao();
    printf("anon1mo333: Está se divertindo? Vejo que gostou do meu joguinho, mas agora eu quero jogar também :) \n");
    fflush(stdout);
    sleep(3);
    digitacao();
    printf("anon1mo333: Vou te explicar como vai funcionar agora... \n");
    fflush(stdout);
    digitacao();
    printf("anon1mo333: Iremos jogar alguns jogos, se falhar 3 vezes, você perde.");
    fflush(stdout);
    sleep(3);
}