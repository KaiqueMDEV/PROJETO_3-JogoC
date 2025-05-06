#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <unistd.h>
#include <time.h>


int intro(){ //introdução do jogo, mostra um jogo simples de "fachada" e logo em seguida ocorre uma pequena interação com o "hacker".
    int escolha;
    for(int i = 0; i < 3; i++){ //repete o jogo falso por 3 rodadas ou até o jogador decidir parar.
        guessgame();
        printf("\nDeseja jogar novamente?\n1. Sim\n2. Não\n");
        scanf("%d", &escolha);
        if(escolha == 2){
            break; 
        }
    } //inicio da interação com o hacker
    digitacao(); 
    printf("anon1mo333: Está se divertindo? Vejo que gostou do meu joguinho, mas agora que tal jogarmos juntos? :) \n");
    fflush(stdout);
    sleep(3);
    digitacao();
    printf("anon1mo333: Vou te explicar como vai funcionar... \n");
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
    printf("\nPressione ENTER para continuar para o menu principal."); //adiciona mais interatividade ao código
    getchar(); //limpa o buffer
    getchar(); //solicita uma entrada do usuário
    FILE *arquivo = fopen("log", "w"); //cria o log de ações do jogador após a cena.
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
       digitacao();
       printf("\nanon1mo333: vamos para o primeiro jogo. Surpreenda-me.");
       fflush(stdout);
       sleep(1);
       printf("\nPressione ENTER para continuar"); //adiciona mais interatividade ao código
       getchar(); //limpa o buffer
       getchar(); //solicita uma entrada do usuário
        desafio1();  // Chama o primeiro desafio
        sleep(1);
        digitacao();
       printf("\nanon1mo333: fique atento às oportunidades. Vamos ao segundo jogo. Boa sorte.");
       fflush(stdout);
       sleep(1);
       printf("\nPressione ENTER para continuar");
       getchar(); 
       getchar(); 
       desafio2();
        break;
    case 2:
       printf("\nReiniciando Save...\n");
       remove("log"); //remove o arquivo "log", futuramente será usado para apagar o arquivo de save do jogador.
       printf("LOG removido!");
       break;
    case 3:
       printf("\nSAIR\n");
       break;   
    default:
         printf("Opção inválida!");
    }
};

void digitacao(){ //função que simula uma interação com uma pessoa real, exibe no terminal uma digitação falsa que serve para dar mais imersão na cena
    printf("anon1mo333: "); //print fixo
    fflush(stdout); //limpa o 

    for(int i = 0; i < 2; i++){ //simula por alguns ciclos
        printf("\ranon1mo333: Digitando.  "); //esta parte atua como uma "animação", dando a entender que alguém está digitando de fato. 
        fflush(stdout); //força a impressão para o terminal imediatamente.
        sleep(1); //aguarda N segundos
        printf("\ranon1mo333: Digitando.. "); //o /r força o cursor a voltar para o começo da linha antes de exibir a saída.
        fflush(stdout);
        sleep(1);
        printf("\ranon1mo333: Digitando..."); 
        fflush(stdout);
        sleep(1);
    }
    printf("\r                         \r"); //este trecho serve para apagar qualquer coisa que esteja na linha antes da próxima mensagem.
    fflush(stdout);
}

int guessgame(){ //jogo de fachada, um simples jogo de adivinhação, digite um número de 1 a 100 e o programa te indicará se é maior ou menor que o número correto
    srand(time(NULL));
    int numero;
    int numero_correto = 69; //rand() % 101; //gera um número aleatóriamente como resultado correto
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


void inserir_vidas(int vidas) {
    
    //exibe os corações com base nas vidas restantes
    printf("\nVidas: ");
    for (int i = 0; i < 3; i++) {
        if (i < vidas) {
            printf("❤️ "); //coração cheio
        } else {
            printf("💔 "); //coração quebrado
        }
    }
    printf("\n");
}

void desafio1() {
    FILE *arquivo = fopen("log", "w"); //cria o log de ações do jogador após a cena.
    int vidas = 3; //número inicial de vidas
    int escolha;
        while (vidas > 0) {
            inserir_vidas(vidas);  //exibe as vidas atuais
            //pergunta sobre "Hamlet"
            printf("\nJogo 1: Trivia\n");
            printf("\nPergunta: Em 'Hamlet', o que leva à morte do próprio Hamlet?\n");
            printf("Escolha a alternativa correta:\n");
            printf("1. A traição de seu tio\n");
            printf("2. O veneno em sua espada\n");
            printf("3. Sua indecisão e falha em agir\n");
            printf("4. A luta com Laertes\n");
            printf("Digite o número da sua escolha: ");
            scanf("%d", &escolha);
        
        // Checando a resposta correta (A indecisão de Hamlet)
        if (escolha != 3) {  // Se o jogador escolher errado
            limpartela();
            printf("Resposta errada! Perdeu uma vida.\n");
            vidas--;  // Diminui uma vida
            fclose(arquivo);
            break; 

        } else {
            printf("Você acertou!\n");
            fclose(arquivo);
            break;  // Sai do loop se o jogador acertar
        }

    }
    
}

// Função para o Desafio 2 - "O que eu sou"
void desafio2() {
    FILE *arquivo = fopen("log", "w"); //cria o log de ações do jogador após a cena.
    int vidas = 3;  // Inicia com 3 vidas
    char resposta[100]; // Variável para armazenar a resposta do jogador
    
    while (vidas > 0) {
        inserir_vidas(vidas);  // Exibe as vidas atuais
        
        // Dica do hacker
        printf("\nJogo 2: O que eu sou?\n");
        printf("Dica: Eu paraliso suas pernas e surjo diante do perigo, apesar de ser incapacitante sou eu que te mantenho vivo. Agora me diga, quem sou eu?\n");
        printf("Digite a palavra (em caixa alta): ");
        scanf("%s", resposta); // Lê a resposta do jogador
        
        // Checando a resposta correta (a palavra é "medo")
        if (strcmp(resposta, "MEDO") != 0) {  // Se a resposta estiver errada
            limpartela();
            printf("Resposta errada! Perdeu uma vida.\n");
            vidas--;  // Diminui uma vida
            fclose(arquivo);
            break;
        } else {
            printf("Você acertou! A palavra é 'medo'.\n");
            fclose(arquivo);
            break;  // Sai do loop se o jogador acertar
        }
    }
    
    
}


