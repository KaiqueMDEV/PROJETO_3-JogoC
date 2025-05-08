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
    printf("anon1mo333: ... \n");
    fflush(stdout);
    sleep(3);
    digitacao();
    printf("anon1mo333: Agora, uma breve explicação: \n");
    fflush(stdout);
    sleep(1);
    digitacao();
    printf("anon1mo333: 3 erros é o seu limite, boa sorte. \n");
    fflush(stdout);
    sleep(3);
    digitacao();
    printf("anon1mo333: \033[31mNão falhe.\033[0m\n");
    fflush(stdout);
    sleep(3);
    pressenter();
    FILE *arquivo = fopen("log", "w"); //cria o log de ações do jogador após a cena.
    fclose(arquivo);
}


void menu(int *faseatual, int *vidas){
    while(1) {
        limpartela(); 
        printf("\n----Menu Principal----\n");
        printf("Digite o que deseja fazer a seguir: \n1. Continuar História\n2. Reiniciar Save\n3. Salvar Arquivo\n4. Carregar Arquivo\n5. Hard RESET\n6. Sair do Jogo\n");
        int escolha;
        printf("%d\n", *faseatual);
        printf("%d", *vidas);
        printf("\nescolha: ");
        scanf("%d", &escolha);
        int escolha2;
        switch (escolha) {
            case 1:
                switch(*faseatual) { //verifica a fase atual do jogador e inicia o jogo na fase correspondente
                    case 1:
                        desafio1(vidas, faseatual);
                        *faseatual = 2; //atualiza a fase atual do jogador
                        break;
                    case 2:
                        desafio2(vidas, faseatual);
                        *faseatual = 3; //atualiza a fase atual do jogador
                        break;
                    default:
                        *faseatual = 1;
                }
                break; // Adicionando o break aqui para não cair no próximo case
            case 2:
                printf("Você tem certeza que deseja reiniciar o save?\n1. Sim\n2. Não\n");
                scanf("%d", &escolha2);
                FILE *arquivo = fopen("save.bin", "w");
                if (escolha2 == 1) { //se o jogador escolher 1, modifica as vidas para 3 e a fase para 1 no arquivo
                    *vidas = 3;
                    *faseatual = 1;
                    printf("Save reiniciado com sucesso!\n");
                    fwrite(vidas, sizeof(int), 1, arquivo); //escreve o número de vidas no arquivo
                    fwrite(faseatual, sizeof(int), 1, arquivo); //escreve a fase atual no arquivo
                    pressenter();
                } else {
                    printf("Reinicialização cancelada.\n");
                    pressenter();
                }
                   
                break;
            case 3:
                save_arquivo(vidas, faseatual); //salva o progresso do jogador
                // Após carregar os valores
                printf("Salvando: Fase: %d, Vidas: %d\n", *faseatual, *vidas); 
                pressenter();
                break;
            case 4:
                load_arquivo(vidas, faseatual); //carrega o progresso do jogador
                // Após salvar os valores
                printf("Carregado: Fase: %d, Vidas: %d\n", *faseatual, *vidas);
                pressenter();
                break;
            case 5: //hard reset
                printf("Você tem certeza que deseja reiniciar TUDO?\n1. Sim\n2. Não\n");
                scanf("%d", &escolha2);
                if (escolha2 == 1) { //se o jogador escolher 1, apaga o arquivo log e o arquivo save.bin
                    remove("log");
                    remove("save.bin");
                    printf("Save reiniciado com sucesso!\n");
                    pressenter();
                    intro(); //chama a função de introdução novamente
                    *vidas = 3; //reinicia as vidas
                    *faseatual = 1; //reinicia a fase
                    save_arquivo(vidas, faseatual); //cria o arquivo de save
                } else {
                    printf("Reinicialização cancelada.\n");
                    pressenter();
                }
                break;
            case 6: //sai do jogo
                printf("Saindo do jogo...\n");
                exit(0); //sai do jogo
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
                break;
        }
    }
}

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
    srand(time(NULL)); //inicializa o gerador de números aleatórios com o tempo atual
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


void inserir_vidas(int *vidas) {
    
    //exibe os corações com base nas vidas restantes
    printf("\nVidas: ");
    for (int i = 0; i < 3; i++) {
        if (i < *vidas) {
            printf("❤️ "); //coração cheio
        } else {
            printf("💔 "); //coração quebrado
        }
    }
    printf("\n");
}

void desafio1(int *vidas, int *faseatual) { //desafio 1 - trivia sobre "Hamlet"
    digitacao();
    printf("\nanon1mo333: vamos para o primeiro jogo. Surpreenda-me.");
    fflush(stdout);
    sleep(1);
    pressenter();
    FILE *arquivo = fopen("log", "w"); //cria o log de ações do jogador após a cena.
    int escolha;
        while (1) {
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
        if (escolha != 3) {  //Se o jogador escolher errado
            limpartela();
            printf("Resposta errada! Perdeu uma vida.\n");
            (*vidas)--;  //Diminui uma vida
            fclose(arquivo);
            pressenter(); 
            break; 

        } else {
            printf("Você acertou!\n");
            fclose(arquivo);
            break;  //Sai do loop se o jogador acertar
        }

    }
    
}

void desafio2(int *vidas, int *faseatual) { //desafio 2 - "O que eu sou"
    digitacao();
    printf("anon1mo333: fique atento às oportunidades. Vamos ao segundo jogo. Boa sorte.");
    fflush(stdout);
    sleep(1);
    pressenter();  
    FILE *arquivo = fopen("log", "w"); //cria o log de ações do jogador após a cena.
    char resposta[100]; // Variável para armazenar a resposta do jogador
    
    while (1) {
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
            (*vidas)--;  // Diminui uma vida
            pressenter();
            fclose(arquivo);
            break;
        } else {
            printf("Você acertou! A palavra é 'medo'.\n");
            fclose(arquivo);
            pressenter();
            break;  // Sai do loop se o jogador acertar
        }
    }
}

void save_arquivo(int *vidas, int *faseatual){
    FILE *arquivo = fopen("save.bin", "wb"); //cria o arquivo de save
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de save.\n");
        return;
    }
    fwrite(vidas, sizeof(int), 1, arquivo); //escreve o número de vidas no arquivo
    fwrite(faseatual, sizeof(int), 1, arquivo); //escreve a fase atual no arquivo
    fclose(arquivo); //fecha o arquivo
}

void load_arquivo(int *vidas, int *faseatual){
    FILE *arquivo = fopen("save.bin", "rb"); //abre o arquivo de save
    if (arquivo == NULL) {
        save_arquivo(vidas, faseatual); //se o arquivo não existir, cria um novo
    }
    fread(vidas, sizeof(int), 1, arquivo); //lê o número de vidas do arquivo
    fread(faseatual, sizeof(int), 1, arquivo); //lê a fase atual do arquivo
    fclose(arquivo); //fecha o arquivo
}

void pressenter(){
    printf("\nPressione ENTER para continuar"); //adiciona mais interatividade ao código
    getchar(); //limpa o buffer
    getchar(); //solicita uma entrada do usuário
}