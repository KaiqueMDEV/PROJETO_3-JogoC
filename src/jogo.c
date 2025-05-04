#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <unistd.h>
#include <time.h>


int intro(){
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
    sleep(1);
    digitacao();
    printf("anon1mo333: Iremos jogar alguns jogos, se falhar 3 vezes, você perde.\n");
    fflush(stdout);
    sleep(3);
    digitacao();
    printf("anon1mo333: Se você perder? Digamos apenas que... Você receberá uma visitinha\n");
    fflush(stdout);
    sleep(3);
    printf("\nPressione ENTER para continuar para o menu principal.");
    getchar();
    getchar();
    FILE *arquivo = fopen("log", "w"); //cria o log de ações do jogador após a cutscene.
    fclose(arquivo);
}

void menu(){
    limpartela();
    printf("\n----Menu Principal----\n");
    printf("Digite o que deseja fazer a seguir: \n1. Continuar História\n2. Reiniciar Save\n3. Sair\n");
    int escolha;
    printf("\nescolha: ");
    scanf("%d", &escolha);
    switch (escolha){
    case 1:
       printf("\nContinuar");
       break;
    case 2:
       printf("\nReiniciando Save...\n");
       remove("log");
       printf("LOG removido!");
       break;
    case 3:
       printf("\nSAIR\n");
       break;   
    default:
         printf("Opção inválida!");
    }
};

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

void limpartela(){ //função para limpar o terminal com comandos ANSI, códigos especiais de escape que controlam a aparência e o comportamento do terminal
    printf("\033[2J");//limpa a tela
    printf("\033[H");//move o cursor pro topo (linha 0, coluna 0)
    fflush(stdout);
}