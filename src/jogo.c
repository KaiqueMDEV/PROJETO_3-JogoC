#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <unistd.h>
#include <time.h>


int intro(){ //introdução do jogo, mostra um jogo simples de "fachada" e logo em seguida ocorre uma pequena interação com o "hacker".
    for(int i = 0; i < 3; i++){ //repete o jogo falso por 3 rodadas ou até o jogador decidir parar.
        guessgame();
        printf("\nDeseja jogar novamente?\n1. Sim\n2. Não\n");
        int escolha = userinput(2);
        if(escolha == 2){ //se o jogador escolher 2, sai do loop
            break;
        }else{
            continue;
        } //inicio da interação com o hacker
    }
    limpartela();
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
    FILE *arquivolog = fopen("log", "w"); //cria o log de ações do jogador após a cena.
    fclose(arquivolog);
}

void menu(int *faseatual, int *vidas){
    while(1) {
        FILE *arquivolog = fopen("log", "a"); //abre o arquivo de log em modo append
        limpartela(); 
        printf("\n----Menu Principal----\n\n");
        printf("Digite o que deseja fazer a seguir: \n\n1. Continuar História\n2. Reiniciar Save\n3. Salvar Arquivo\n4. Carregar Arquivo\n5. Hard RESET\n6. Sair do Jogo\n");
        int escolha;
        inserir_vidas(vidas); //exibe as vidas atuais
        printf("\nFase atual: %d de 4\n", *faseatual); //exibe a fase atual do jogador
        escolha = userinput(6); //pega a entrada do jogador e verifica se é válida
        switch (escolha) {
            case 1:
                switch(*faseatual) { //verifica a fase atual do jogador e inicia o jogo na fase correspondente
                    case 1:
                        desafio1(vidas);
                        *faseatual = 2; //atualiza a fase atual do jogador
                        break;
                    case 2:
                        desafio2(vidas);
                        *faseatual = 3; //atualiza a fase atual do jogador
                        break;
                    case 3:
                        desafio3(vidas);
                        if (*vidas == 0) { //se o jogador perder todas as vidas, encerra o jogo
                            limpartela();
                            printf("\033[31mVocê perdeu todas as suas vidas... \n \033[0m");
                            sleep(1);
                            digitacao();
                            printf("anon1mo333: Você não é digno de continuar.\n");
                            fflush(stdout);
                            sleep(1);
                            digitacao();
                            printf("anon1mo333: \033[31mFIM DE JOGO.\n \033[0m");
                            fflush(stdout);
                            return;
                        }
                        *faseatual = 4; //atualiza a fase atual do jogador
                        break;
                    case 4:
                        desafio4(vidas); //chama o desafio 4
                        if (*vidas == 0) { //se o jogador perder todas as vidas, encerra o jogo
                            limpartela();
                            printf("\033[31mVocê perdeu todas as suas vidas... \n \033[0m");
                            sleep(1);
                            digitacao();
                            printf("anon1mo333: Você não é digno de continuar.\n");
                            fflush(stdout);
                            sleep(1);
                            digitacao();
                            printf("anon1mo333: \033[31mFIM DE JOGO.\n \033[0m");
                            fflush(stdout);
                            FILE *arquivolog = fopen("log", "a");
                            fprintf(arquivolog, "DERROTA\n");
                            fclose(arquivolog);
                            return;
                        }else{
                            limpartela();
                            digitacao();
                            printf("anon1mo333: Parabéns, você completou o jogo.\n");
                            fflush(stdout);
                            sleep(1);
                            digitacao();
                            printf("anon1mo333: Você está livre pra ir agora. Nos veremos novamente algum dia.\n");
                            fflush(stdout);
                            sleep(1);
                            printf("\033[0;32mFIM DE JOGO.\n\033[0m");
                            FILE *arquivolog = fopen("log", "a");
                            fprintf(arquivolog, "VITORIA\n");
                            fclose(arquivolog);
                            inserir_vidas(vidas); //exibe as vidas atuais
                            pressenter();
                            return;
                        }
                    default:
                        *faseatual = 1;
                }
                break; //Adicionando o break aqui para não cair no próximo case
            case 2:
                printf("Você tem certeza que deseja reiniciar o save?\n1. Sim\n2. Não\n");
                int escolha = userinput(2);
                if (escolha == 1) { //se o jogador escolher 1, modifica as vidas para 3 e a fase para 1 no arquivo
                    FILE *arquivosave = fopen("save.bin", "w");
                    *vidas = 3;
                    *faseatual = 1;
                    printf("Save reiniciado com sucesso!\n");
                    fwrite(vidas, sizeof(int), 1, arquivosave); //escreve o número de vidas no arquivo
                    fwrite(faseatual, sizeof(int), 1, arquivosave); //escreve a fase atual no arquivo
                    fprintf(arquivolog, "RESTART\n"); // Escreve a resposta do jogador no arquivo de log
                    fclose(arquivosave);
                    fclose(arquivolog);
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
                fprintf(arquivolog, "SAVE\n");
                fclose(arquivolog);
                break;
            case 4:
                load_arquivo(vidas, faseatual); //carrega o progresso do jogador
                // Após salvar os valores
                printf("Carregado: Fase: %d, Vidas: %d\n", *faseatual, *vidas);
                pressenter();
                fprintf(arquivolog, "LOAD\n");
                fclose(arquivolog);
                limpartela();
                break;
            case 5: //hard reset
                printf("Você tem certeza que deseja reiniciar TUDO?\n1. Sim\n2. Não\n");
                int escolha2 = userinput(2);
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
                fprintf(arquivolog, "SAIR\n");
                fclose(arquivolog);
                exit(0); //sai do jogo
                break;
            default:
                while (getchar() != '\n');  // Descartar o que foi digitado
                printf("Entrada invalida!\n");
                break; //se a entrada for inválida, exibe uma mensagem de erro
        }
    }
}

void digitacao(){ //função que simula uma interação com uma pessoa real, exibe no terminal uma digitação falsa que serve para dar mais imersão na cena
    printf("anon1mo333: "); //print fixo
    fflush(stdout); //limpa o buffer para garantir que a mensagem seja exibida imediatamente

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
    limpartela(); //limpa a tela
    int numero;
    int numero_correto = rand() % 101; //gera um número aleatóriamente como resultado correto
    printf("Olá! Bem vindo ao Guess Game! Adivinhe qual numero estou pensando de 1 a 100 :D\n");
    while(1){
        numero = userinput(100); //pega a entrada do jogador e verifica se é válida
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
            printf(" ❤️ ");
        } else {
            printf(" 🖤 ");
        }
    }
    printf("\n");
}

void desafio1(int *vidas) { //desafio 1 - trivia sobre "Hamlet"
    limpartela();
    digitacao();
    printf("anon1mo333: vamos para o primeiro jogo. Surpreenda-me.");
    fflush(stdout);
    sleep(1);
    pressenter();
        while (1) {
            limpartela();
            printf("\nJogo 1: Trivia\n");
            sleep(1);
             //pergunta sobre "Hamlet"
            inserir_vidas(vidas);  //exibe as vidas atuais
            printf("\nPergunta: Em 'Hamlet', o que leva à morte do próprio Hamlet?\n");
            printf("Escolha a alternativa correta:\n");
            printf("1. A traição de seu tio\n");
            printf("2. O veneno em sua espada\n");
            printf("3. Sua indecisão e falha em agir\n");
            printf("4. A luta com Laertes\n");
            int escolha = userinput(4); //pega a entrada do jogador e verifica se é válida
            FILE *arquivolog = fopen("log", "a");
            char escolha_char = escolha + '0'; //converte a escolha para char
            fprintf(arquivolog, "escolha: %c\n", escolha_char); //escreve a escolha do jogador no arquivo de log
            fclose(arquivolog); //fecha o arquivo de log
        
        //checando a resposta correta (A indecisão de Hamlet)
        if (escolha != 3) {  //Se o jogador escolher errado
            limpartela();
            printf("Incorreto. -1 chance.\n");
            remove_vida(vidas);  //Diminui uma vida
            pressenter(); 
            break; 

        } else {
            limpartela();
            printf("Correto.\n");
            pressenter();
            break;  //Sai do loop se o jogador acertar
        }

    }
    
}

void desafio2(int *vidas) { //desafio 2 - "O que eu sou"
    limpartela();
    digitacao();
    printf("anon1mo333: fique atento às oportunidades. Vamos ao segundo jogo. Boa sorte.");
    fflush(stdout);
    sleep(1);
    pressenter();
    char resposta[100]; //armazenar a resposta do jogador
    
    while (1) { 
        //dica do hacker
        printf("\nJogo 2: O que eu sou?\n");
        sleep(1);
        inserir_vidas(vidas);  //exibe as vidas atuais 
        printf("\nDica: Eu paraliso suas pernas e surjo diante do perigo, apesar de ser incapacitante sou eu que te mantenho vivo. Agora me diga, quem sou eu?\n");
        printf("\nDigite a palavra (em caixa alta): ");
        fflush(stdout);
        scanf("%s", resposta); //Lê a resposta do jogador
        FILE *arquivolog = fopen("log", "a"); //Abre o arquivo de log em modo append
        fprintf(arquivolog, "resposta: %s\n", resposta); //Escreve a resposta do jogador no arquivo de log
        fclose(arquivolog); //fecha o arquivo de log
        
        //Checando a resposta correta (a palavra é "medo")
        if (strcmp(resposta, "MEDO") != 0) {  //Se a resposta estiver errada
            limpartela();
            printf("Incorreto. Não aja impulsivamente.\n");
            remove_vida(vidas);  //Diminui uma vida
            pressenter();
            break;
        } else {
            printf("Você acertou. A palavra é 'MEDO'\n");
            pressenter();
            break;  //Sai do loop se o jogador acertar
        }
    }
}

void save_arquivo(int *vidas, int *faseatual){
    FILE *arquivosave = fopen("save.bin", "wb"); //cria o arquivo de save
    fwrite(vidas, sizeof(int), 1, arquivosave); //escreve o número de vidas no arquivo
    fwrite(faseatual, sizeof(int), 1, arquivosave); //escreve a fase atual no arquivo
    fclose(arquivosave); //fecha o arquivo
}

void load_arquivo(int *vidas, int *faseatual){
    FILE *arquivosave = fopen("save.bin", "rb"); //abre o arquivo de save
    if (arquivosave == NULL) {
        save_arquivo(vidas, faseatual); //se o arquivo não existir, cria um novo
    }
    fread(vidas, sizeof(int), 1, arquivosave); //lê o número de vidas do arquivo
    fread(faseatual, sizeof(int), 1, arquivosave); //lê a fase atual do arquivo
    fclose(arquivosave); //fecha o arquivo
}

void pressenter(){
    printf("\nPressione ENTER para continuar"); //adiciona mais interatividade ao código
    getchar(); //limpa o buffer
    getchar(); //solicita uma entrada do usuário
}

void remove_vida(int *vidas) { //remove uma vida do jogador
    (*vidas)--; //diminui uma vida
    char registro[] = "-1 vida"; //registra a perda de uma vida
    FILE *arquivolog = fopen("log", "a"); //abre o arquivo de log em modo de append
    fprintf(arquivolog, "%s\n", registro); //escreve a perda de vida no arquivo
    fclose(arquivolog); //fecha o arquivo
    return; 
}

int userinput(int maxopcoes){ //pega a entrada do jogador e verifica se é válida
    int escolha;
    int resultado;

    while (1) {
        printf("\nEscolha: ");
        resultado = scanf("%d", &escolha);  //tenta ler um número inteiro

        //verifica se o input não é um número
        if (resultado != 1) {
            while (getchar() != '\n');  //limpa o buffer
            printf("\nEntrada inválida. Por favor, digite um número.\n");
        } else if (escolha < 1 || escolha > maxopcoes) {  //verifica se o número está fora do intervalo
            printf("\nEntrada Inválida. Digite um número entre 1 e %d.\n", maxopcoes);
        } else {
            return escolha;  //retorna a escolha válida
        }
    }
}

void desafio3(int *vidas){
    limpartela();
    digitacao();
    printf("anon1mo333: Espero que você tenha vidas sobrando, pois o proximo jogo vai testar sua sorte.\n");
    fflush(stdout);
    sleep(1);
    pressenter();
    while(1){
        limpartela();
        printf("\nJogo 3: Pedra, Papel e Tesoura\n");
        sleep(1);
        inserir_vidas(vidas); //exibe as vidas atuais
        printf("\nEscolha sua opção:\n");
        printf("1. Pedra\n");
        printf("2. Papel\n");
        printf("3. Tesoura\n");
        int escolha = userinput(3); //pega a entrada do jogador e verifica se é válida
        FILE *arquivolog = fopen("log", "a"); //abre o arquivo de log em modo append
        char escolha_char = escolha + '0'; //converte a escolha para char
        fprintf(arquivolog, "escolha: %c\n", escolha_char); //escreve a escolha do jogador no arquivo de log
        fclose(arquivolog); //fecha o arquivo de log

        int computador = rand() % 3 + 1; //gera uma escolha aleatória para o computador

        if (escolha == computador) { //se o jogador e o computador escolherem a mesma coisa
            printf("Empate! Ambos escolheram ");
            switch (computador) {
                case 1:
                    printf("Pedra.\n");
                    break;
                case 2:
                    printf("Papel.\n");
                    break;
                case 3:
                    printf("Tesoura.\n");
                    break;
        }     
            pressenter();
            continue; //continua o loop se houver empate
        }else if ((escolha == 1 && computador == 3) || (escolha == 2 && computador == 1) || (escolha == 3 && computador == 2)) { //verifica se o jogador ganhou
            switch (escolha) {
                case 1:
                    printf("Você escolheu pedra e eu tesoura, você venceu, parabéns.\n");
                    break;
                case 2:
                    printf("Você escolheu papel e eu pedra, você venceu, parabéns\n");
                    break;
                case 3:
                    printf("Você escolheu tesoura e eu papel, você venceu, parabéns\n");
                    break;
            }
            pressenter();
            return; //sai do loop se o jogador ganhar
        }else { //se o jogador perder
            limpartela();
            switch (computador) {
                case 1:
                    printf("Você escolheu tesoura e eu pedra, você perdeu.\n");
                    break;
                case 2:
                    printf("Você escolheu pedra e eu papel, você perdeu.\n");
                    break;
                case 3:
                    printf("Você escolheu papel e eu tesoura, você perdeu.\n");
                    break;
            }
            remove_vida(vidas); //remove uma vida do jogador
            pressenter();
            return; //sai do loop se o jogador perder
    }
    }
}

void desafio4(int *vidas){ //desafio 4 - guess game
    limpartela();
    digitacao();
    printf("anon1mo333: Hora do último jogo, preparado?\n");
    fflush(stdout);
    pressenter();
    limpartela();
    digitacao();
    printf("anon1mo333: Que tal uma rodada de GUESS GAME? você terá 10 tentativas para adivinhar o número.\n");
    fflush(stdout);
    sleep(3);
    limpartela();
    srand(time(NULL)); //inicializa o gerador de números aleatórios com o tempo atual
    printf("Desafio 4: Guess Game\n");
    sleep(1);
    inserir_vidas(vidas); //exibe as vidas atuais
    printf("\nOlá, bem-vindo ao Guess Game! Adivinhe o número que estou pensando de 1 a 100 :)\n");
    int numero_correto = rand() % 101; //gera um número aleatóriamente como resultado correto
    int tentativas = 7; //número de tentativas
    while(1){
    printf("\nTentativas restantes: %d\n", tentativas); //exibe o número de tentativas restantes
    int numero = userinput(100); //pega a entrada do jogador e verifica se é válida
    char string[4]; //string para armazenar a escolha do jogador
    FILE *arquivolog = fopen("log", "a");
    sprintf(string, "%d", numero);
    fprintf(arquivolog, "escolha: %s\n", string); //escreve a escolha do jogador no arquivo de log
    fclose(arquivolog); //fecha o arquivo de log
    if (numero > numero_correto) { //se o número for maior que o correto
        printf("\nHmm, seu número é maior que o meu! Tente denovo!\n");
        tentativas--;
    }else if (numero < numero_correto) { //se o número for menor que o correto
        printf("\nHmm, seu número é menor que o meu! Tente denovo!\n");
        tentativas--;
    }else if(numero == numero_correto){ //se o número estiver correto
        printf("\nParabéns! Você acertou! O número que eu estava pensando é: %d\n", numero_correto);
        pressenter();
        return; //sai do loop se o jogador acertar
    } if(tentativas == 0) { //se o jogador não tiver mais tentativas
        printf("\nVocê não tem mais tentativas. O número correto era: %d :(\n", numero_correto);
        remove_vida(vidas); //remove uma vida do jogador
        pressenter();
        return; //sai do loop se o jogador perder
    }
}
}
