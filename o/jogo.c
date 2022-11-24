#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void limpatela();

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    char jogador1[20];
    int modo_jogo;  // 0 = humano x maquina / 1 = humano x humano
    
    printf ("\n ******************************************");
    printf ("\n     Escolha as configurações do jogo     \n");
    printf (" ******************************************\n\n");
    
    // configurações básicas do jogo
    printf ("Digite seu nome: ");
    scanf("%s", jogador1);
    
    printf ("\nDigite 0 p/ jogar contra a máquina\nDigite 1 p/ jogar contra outro jogador");
    printf ("\nSua escolha: ");
    scanf("%i", &modo_jogo);
    
    limpatela();
    
    //humano x maquina
    if(modo_jogo == 0) {
        int dificuldade;
        printf ("\nDigite 1(Fácil), 2(Médio) ou 3(Difícil) para escolher a dificuldade: ");
        scanf("%i", &modo_jogo);
    }
    
    //humano x humano
    else if(modo_jogo == 1) {
        char jogador2[20], palavra_passe[20];
        printf ("Digite o nome do jogador 2: ");
        scanf("%s", jogador2);
        
        printf ("\nDigite a palavra: ");
        scanf("%s", palavra_passe);
        
        limpatela();
        
        
    }
    
    else {
        printf ("Impossível continuar! Modo de jogo inválido!");
    }
    
    return 0;
}

void limpatela() {
    // funcao para limpar a tela
    system("clear");
    //system("cls");
}
