#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <unistd.h>
#include <time.h>




int main(){
    FILE *arquivo = fopen("log", "r");
    if(arquivo == NULL){
        intro();
        menu();
    }else{
        menu();
    }
}