////////////////////////////////////////////////////////////////////

// Trabalho Estrtutura de dados
// Aluno Thiago Aio

// UTILIZAR LETRAS MINUSCULAS EM TUDO QUE FOR DIGITADO

////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define vidas 7

// 1 = venceu
int vitoria = 0;

//Pilha que armazena jogadas / Variaveis úteis
struct jogadas { 
	char letras;
	struct jogadas *prox;
};
typedef struct jogadas PILHA;
PILHA *topo, *aux, *novo;
int quantidade_jogadas = 0;

//funcoes
void limpatela();
void desenha_corpo(int erros);
void inicializar_pilha();
void inserir_pilha(char letra_digitada);
void exibe_pilha();
int verifica_repeticao(char letra_digitada);
int verifica_acerto(char palavra_passe[], int tamanho_palavra, char letra);
void exibe_palavra_passe(char palavra_passe[], int tamanho_palavra);
int verifica_vitoria(char palavra_passe[], int tamanho_palavra);

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    char jogador1[20];
    int modo_jogo;  // 0 = humano x maquina / 1 = humano x humano
    
    printf ("\n ******************************************");
    printf ("\n     Escolha as configurações do jogo     \n");
    printf (" ******************************************\n\n");
    
    // usuário digita informações básicas do jogo
    printf ("Digite seu nome: ");
    scanf("%s", jogador1);
    
    printf ("\nDigite 0 p/ jogar contra o computador\nDigite 1 p/ jogar contra outro jogador");
    printf ("\nSua escolha: ");
    scanf("%i", &modo_jogo);
    
    limpatela();
    
    //humano x maquina
    if(modo_jogo == 0) {
        int quem_escolhe_palavra, dificuldade;
        
        // selecionando quem escolhe a palavra
        printf ("\nDigite 0 p/ o computador escolher a palavra secreta\nDigite 1 p/ você escolher a palavra secreta");
        printf ("\nSua escolha: ");
        scanf("%i", &quem_escolhe_palavra);
        
        // selecionando a dificuldade se for maquina escolhe palavra
        if(quem_escolhe_palavra == 0) {
            printf ("\nDigite 1 p/ jogar no fácil\nDigite 2 p/ jogar no médio\nDigite 3 p/ jogar no difícil");
            printf ("\nSua escolha: ");
            scanf("%i", &dificuldade);
        }
        
        limpatela();
        
        // maquina escolhe
        if(quem_escolhe_palavra == 0) {
            //vetores que armazenam as palavras
            //facil
            char palavras_faceis[5][4+1] = {"bolo", "casa", "olho", "deus", "vida"};
            
            //medio
            char palavras_medias[5][6+1] = {"escova", "piloto", "banana", "objeto", "teoria"};
            
            //dificil
            char palavras_dificeis[5][8+1] = {"cachorro", "bandeira", "amendoim", "complexo", "melancia"};
            
            // gerando valor aleatorio de 0 a 4
            srand(time(NULL));
            int numero = rand() % 4;
            
            // seleciona palavra de acordo com a dificuldade e numero aleatorio
            char palavra_passe1[10];
            if(dificuldade == 1) {
                for(int i=0; i<5; i++) {
                    palavra_passe1[i] = palavras_faceis[numero][i];
                }
            }
            
            else if(dificuldade == 2) {
                for(int i=0; i<7; i++) {
                    palavra_passe1[i] = palavras_medias[numero][i];
                }
            }
            
            else if(dificuldade == 3) {
                for(int i=0; i<9; i++) {
                    palavra_passe1[i] = palavras_dificeis[numero][i];
                }
            }
            
            else {
                
            }
            
            //////////////////////////////////////////////////////////////////////////////////
            //                              começando a jogar                              //
            
            inicializar_pilha();
            int quantidade_erros1 = 0; // chegando a 7 será a derrota
            char letra1; // letra digitadas pelo jogador
            
            // mostra quantos caracteres tem a palavra palavra passe
            int tamanho_palavra1 = strlen(palavra_passe1); 
            
            //while que roda até jogador perder ou ganhar
            while(quantidade_erros1 < vidas && vitoria < 1) {   
                limpatela();
                
                //função que desenha a pessoa baseado nos erros
                desenha_corpo(quantidade_erros1); 
                
                // revela as letras da palavra passe
                printf("Palavra secreta: ");
                exibe_palavra_passe(palavra_passe1, tamanho_palavra1);
                
                //função que exibe as letras digitadas
                printf("\n\nLetras já digitadas: ");
                exibe_pilha();
                
                if (verifica_vitoria(palavra_passe1, tamanho_palavra1) < 1) { // só pede uma letra se ainda não tiver ganhado
                    // digitando uma letra e gardando
                    scanf("%*c");
                    printf("\n\nDigite uma letra: ");
                    scanf("%c", &letra1);
                    
                    // verifica se a letra ja foi digitada
                    if(verifica_repeticao(letra1) == 1) {
                        // se retornar 1 quer dizer que a letra já foi digitada
                        printf("\nletra já utilizada! Aguarde!\n");
                        sleep(1.2);
                    }
                    else {
                        // inserido na pilha
                        inserir_pilha(letra1);
                        quantidade_jogadas++;
                        
                        // verifica se acertou 
                        if(verifica_acerto(palavra_passe1, tamanho_palavra1, letra1) != 1) {
                            // se retornar diferente de 1 o jogador errou e é contabilizado erro
                            quantidade_erros1++;
                        }
                    }
                }
            }
            
            if(vitoria == 1) {
                printf("\n\nVITÓRIA a palavra era '%s'! você teve %d tentativas e %d erros.", palavra_passe1,quantidade_jogadas,quantidade_erros1);
            }
            else {
                printf("\n\nDERROTA a palavra era '%s'! %s perdeu para o computador, você teve %d tentativas e %d erros o máximo é 6.", palavra_passe1,jogador1,quantidade_jogadas,quantidade_erros1);
            }
        }
        
        else {
            
            //////////////////////////////////////////////////////////////////////////////////
            //                              começando a jogar                              //
            
        }
    }
    
    //humano x humano
    else if(modo_jogo == 1) {
        char jogador2[20], palavra_passe[20];
        printf ("Digite o nome do jogador 2: ");
        scanf("%s", jogador2);
        
        printf ("\nDigite a palavra secreta: ");
        scanf("%s", palavra_passe);
        
        // mostra quantos caracteres tem a palavra palavra passe
        int tamanho_palavra = strlen(palavra_passe); 
        
        limpatela();
        
        inicializar_pilha();
        int quantidade_erros = 0; // chegando a 7 será a derrota
        char letra; // letra digitadas pelo jogador
        
        //while que roda até jogador perder ou ganhar
        while(quantidade_erros < vidas && vitoria < 1) {   
            limpatela();
            
            //função que desenha a pessoa baseado nos erros
            desenha_corpo(quantidade_erros); 
            
            // revela as letras da palavra passe
            printf("Palavra secreta: ");
            exibe_palavra_passe(palavra_passe, tamanho_palavra);
            
            //função que exibe as letras digitadas
            printf("\n\nLetras já digitadas: ");
            exibe_pilha();
            
            if (verifica_vitoria(palavra_passe, tamanho_palavra) < 1) { // só pede uma letra se ainda não tiver ganhado
                // digitando uma letra e gardando
                scanf("%*c");
                printf("\n\nDigite uma letra: ");
                scanf("%c", &letra);
            
                // verifica se a letra ja foi digitada
                if(verifica_repeticao(letra) == 1) {
                    // se retornar 1 quer dizer que a letra já foi digitada
                    printf("\nletra já utilizada! Aguarde!\n");
                    sleep(1.2);
                }
                else {
                    inserir_pilha(letra);
                    quantidade_jogadas++;
                    
                    // verifica se acertou 
                    if(verifica_acerto(palavra_passe, tamanho_palavra, letra) != 1) {
                        // se retornar diferente de 1 o jogador errou e é contabilizado erro
                        quantidade_erros++;
                    }
                }
            }
        }
        
        if(vitoria == 1) {
            printf("\n\nVITÓRIA a palavra era '%s'! %s venceu de %s, você teve %d tentativas e %d erros.", palavra_passe,jogador2,jogador1,quantidade_jogadas,quantidade_erros);
        }
        else {
            printf("\n\nDERROTA a palavra era '%s'! %s perdeu para %s, você teve %d tentativas e %d erros o máximo é 6.", palavra_passe,jogador2,jogador1,quantidade_jogadas,quantidade_erros);
        }
    }
    
    else {
        printf("Impossível continuar! Modo de jogo inválido!");
    }
    
    printf("\n\n");
    system("pause");
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
//                    funções que manipulam a pilha                       //
void inicializar_pilha() {
	topo = NULL;		
}

void inserir_pilha(char letra_digitada) {
    // função para inserir na pilha
	if(topo == NULL) {  // se for o primeiro elemento
		topo = malloc(sizeof(PILHA));
		topo->letras = letra_digitada;
		topo->prox = NULL;
	}
	else {
		novo = malloc(sizeof(PILHA));
		novo->letras = letra_digitada;
		novo->prox = topo;
		topo = novo;
	}
}

void exibe_pilha() {
    // função para exibir a pilha
    // usada para exibir as letras já digitadas
    aux = topo;
	if(aux != NULL) {
	    while(aux != NULL){
	        printf("%c ", aux->letras);
			aux = aux->prox;
	    }
	}
}

int verifica_repeticao(char letra_digitada) {
    // função que verifica se a letra digitada é repitida
    aux = topo;
	if(aux != NULL) {
	    while(aux != NULL){
	        if(letra_digitada == aux->letras) {  // se letra digitada é igual elemento pilha
	            return 1;
	        }
	        aux = aux->prox;
	    }
	}
}

void exibe_palavra_passe(char palavra_passe[], int tamanho_palavra) {
    // função para exibir as letras descobertas
    int i;    // contador
    char resposta[tamanho_palavra]; // char que armazenara as letras ja descobertas
    
    // setando campos '_' na palavra passe
    for(i=0; i<tamanho_palavra; i++) {
        resposta[i] = '_'; 
	}
    
    // percorre a pilha e se encontra uma letra igual a da palavra passe armaneza na posição correspondente na char resposta
	aux = topo;
	if(aux != NULL) {
	    while(aux != NULL){
	        char x = aux->letras;
	        for(i=0; i<tamanho_palavra; i++) {
	            if(x == palavra_passe[i]) {
	                resposta[i] = x;
	            }
	        }
			aux = aux->prox;
	    }
	}
	
	// pritando a resposta na tela
	for(i=0; i<tamanho_palavra; i++) {
        printf("%c ", resposta[i]); 
	}
}

int verifica_vitoria(char palavra_passe[], int tamanho_palavra) {
    // vefica se todos os caracteres da palavra_passe estão na pilha
    aux = topo;
    int i; // contador
    int quantidade_caracteres_iguais = 0;
	if(aux != NULL) {
	    while(aux != NULL) {
	        char x = aux->letras;
	        for(i=0; i<tamanho_palavra; i++) {
	            if(x == palavra_passe[i]) {
	                quantidade_caracteres_iguais++;
	            }
	        }
			aux = aux->prox;
	    }
	}
	
	if(quantidade_caracteres_iguais == tamanho_palavra) {
	    vitoria = 1;
	    return 1;
	}
	else {
	    vitoria = 0;
	    return 0;
	}
}
/////////////////////////////////////////////////////////////////////////////

int verifica_acerto(char palavra_passe[], int tamanho_palavra, char letra) {
    int i = 0; // contador
    while (i < tamanho_palavra) {
        if(letra == palavra_passe[i]) {
            return 1;
        }
        i++;
    }
}

void limpatela() {
    // função para limpar o terminal
    system("clear");
    //system("cls");
}

void desenha_corpo(int erros) {
    // recebe quantos erros há e exibe o desenho correspondente
    printf ("\n******************************************");
    printf ("\n              JOGO DA FORCA             \n");
    
    if(erros == 0) {
        printf("___________     \n");
        printf("|        |      \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
    }
    else if(erros == 1) {
        printf("___________     \n");
        printf("|        |      \n");
        printf("|     (° _ °)   \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
    }
    else if(erros == 2) {
        printf("___________     \n");
        printf("|        |      \n");
        printf("|     (° _ °)   \n");
        printf("|        |      \n");
        printf("|        |      \n");
        printf("|        |      \n");
        printf("|        |      \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
    }
    else if(erros == 3) {
        printf("___________     \n");
        printf("|        |      \n");
        printf("|     (° _ °)   \n");
        printf("|        |      \n");
        printf("|        |---   \n");
        printf("|        |      \n");
        printf("|        |      \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");
    }
    else if(erros == 4) {
        printf("___________     \n");
        printf("|        |      \n");
        printf("|     (° _ °)   \n");
        printf("|        |      \n");
        printf("|     ---|---   \n");
        printf("|        |      \n");
        printf("|        |      \n");
        printf("|               \n");
        printf("|               \n");
        printf("|               \n");

    }
    else if(erros == 5) {
        printf("___________     \n");
        printf("|        |      \n");
        printf("|     (° _ °)   \n");
        printf("|        |      \n");
        printf("|     ---|---   \n");
        printf("|        |      \n");
        printf("|        |_     \n");
        printf("|          |    \n");
        printf("|          |    \n");
        printf("|               \n");
    }
    else {
        printf("___________     \n");
        printf("|        |      \n");
        printf("|     (° _ °)   \n");
        printf("|        |      \n");
        printf("|     ---|---   \n");
        printf("|        |      \n");
        printf("|       _|_     \n");
        printf("|      |   |    \n");
        printf("|      |   |    \n");
        printf("|               \n");
    }
}

