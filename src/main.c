#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <unistd.h>
#include <time.h>




int main(){ 
    FILE *arquivo = fopen("log", "r"); //abre o arquivo  "log" em modo de leitura para verificar se o mesmo existe
    if(arquivo == NULL){ //se não existir, toca a introdução e ao final da mesma, cria o arquivo log.
        intro();
        menu();
    }else{ //se existir, pula direto para o menu, dispensando a introdução.
        menu();
    }
}