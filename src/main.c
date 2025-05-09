#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <unistd.h>
#include <time.h>




int main(){ 
    FILE *arquivo = fopen("log", "r"); //abre o arquivo  "log" em modo de leitura para verificar se o mesmo existe
    int *faseatual = malloc(sizeof(int)); //aloca espaço para a fase atual
    int *vidas = malloc(sizeof(int)); //aloca espaço para o número de vidas
    *faseatual = 1; //inicializa a fase atual como 1
    *vidas = 3; //inicializa o número de vidas como 3
    if(arquivo == NULL){ //se não existir, toca a introdução e ao final da mesma, cria o arquivo log.
        intro();
        save_arquivo(vidas, faseatual); //cria o arquivo de save
        menu(faseatual, vidas);
    }else{ //se existir, pula direto para o menu, dispensando a introdução.
        fclose(arquivo);
        menu(faseatual, vidas);
    }
    return 0;
}