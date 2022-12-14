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

//Pilha que armazena jogadas 
struct jogadas { 
	char letras;
	struct jogadas *prox;
};
typedef struct jogadas PILHA;
PILHA *topo, *aux, *novo;

int quantidade_jogadas = 0;

//Pilha do certo ou errado
// essa pilha serve para armazenar se cada letra digitada foi um acerto ou erro
struct certo { 
	int valor; // 1 = certo / 0 = errado
	struct certo *prox2;
};
typedef struct certo PILHA2;
PILHA2 *topo2, *aux2, *novo2;

//funcoes
void limpatela();
void desenha_corpo(int erros);
void inicializar_pilha();
void inicializar_pilha2();
void inserir_pilha(char letra_digitada);
void inserir_pilha2(int valor);
void exibe_pilha();
int verifica_repeticao(char letra_digitada);
int verifica_acerto(char palavra_passe[], int tamanho_palavra, char letra);
void exibe_palavra_passe(char palavra_passe[], int tamanho_palavra);
int verifica_vitoria(char palavra_passe[], int tamanho_palavra);
char tentativa_cpu();
void retrocede_pilha();
void retrocede_pilha2();
int ve_topo();

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
            inicializar_pilha2();
            int quantidade_erros1 = 0; // chegando a 7 será a derrota
            char letra1; // letra digitadas pelo jogador
            
            // mostra quantos caracteres tem a palavra palavra passe
            int tamanho_palavra1 = strlen(palavra_passe1); 
            
            //while que roda até jogador perder ou ganhar
            while(quantidade_erros1 < vidas && vitoria < 1) {
                A2:
                limpatela();
                
                //função que desenha a pessoa baseado nos erros
                desenha_corpo(quantidade_erros1); 
                
                // revela as letras da palavra passe
                printf("Palavra secreta: ");
                exibe_palavra_passe(palavra_passe1, tamanho_palavra1);
                
                //função que exibe as letras digitadas
                printf("\n\nLetras já digitadas: ");
                exibe_pilha();
                
                // se houver pelo menos uma jogada sera possivel retroceder
                int escolha_retroceder;
                if(quantidade_jogadas > 0) {
                printf("\n\nDigite 0 para retroceder ou 1 para continuar: ");
                scanf("%d", &escolha_retroceder);
                    if(escolha_retroceder == 0) {
                        
                        quantidade_jogadas--;
                        // exclui topo
                        retrocede_pilha();
                        
                        // ve o valor de topo na pilha 2 para saber se a letra foi um acerto ou erro
                        // 1 = acertou / 0 = errou
                        int valor_temporario = ve_topo();
                        
                        // se a letra tinha sido um erro retirar na quantidade de erros 
                        if(valor_temporario == 0) {
                            quantidade_erros1--;
                        }
                        
                        // exclui topo da segunda pilha que indica se a jogada foi um erro o acerto
                        retrocede_pilha2();
                        
                        goto A2;
                        
                    }
                }
                
                B2:
                if(verifica_vitoria(palavra_passe1, tamanho_palavra1) < 1) { // só pede uma letra se ainda não tiver ganhado
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
                        
                        // verificando denovo para armazenar na segunda pilha 
                        int valor1 = verifica_acerto(palavra_passe1, tamanho_palavra1, letra1);
                        inserir_pilha2(valor1);
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
            // recebendo a palavra secreta
            char palavra_passe2[20];
            printf ("\nDigite a palavra secreta: ");
            scanf("%s", palavra_passe2);
            
            // mostra quantos caracteres tem a palavra palavra passe
            int tamanho_palavra2 = strlen(palavra_passe2);
            
            limpatela();
            
            //////////////////////////////////////////////////////////////////////////////////
            //                              começando a jogar                              //
            
            inicializar_pilha();
            int quantidade_erros2 = 0; // chegando a 7 será a derrota
            char letra2; // letras que a maquina vai gerar
            
            //while que roda até jogador perder ou ganhar
            while(quantidade_erros2 < vidas && vitoria < 1) { 
                limpatela();
                
                //função que desenha a pessoa baseado nos erros
                desenha_corpo(quantidade_erros2); 
                
                // revela as letras da palavra passe
                printf("Palavra secreta: ");
                exibe_palavra_passe(palavra_passe2, tamanho_palavra2);
                
                //função que exibe as tentativas da maquina
                printf("\n\nLetras que o computador tentou: ");
                exibe_pilha();

                if (verifica_vitoria(palavra_passe2, tamanho_palavra2) < 1) { // só pede uma letra se ainda não tiver ganhado
                    letra2 = tentativa_cpu();
                
                    // verifica se a letra ja foi digitada
                    if(verifica_repeticao(letra2) == 1) {
                        // se retornar 1 quer dizer que a letra já foi digitada
                        //printf("\nletra já utilizada! Aguarde!\n"); // não é necessário exibir pois é o pc que esta jogando
                    }
                    else {
                        inserir_pilha(letra2);
                        quantidade_jogadas++;
                        
                        // verifica se acertou 
                        if(verifica_acerto(palavra_passe2, tamanho_palavra2, letra2) != 1) {
                            // se retornar diferente de 1 o jogador errou e é contabilizado erro
                            quantidade_erros2++;
                        }
                    }
                }
                
                sleep(2.5);
            }
            
            if(vitoria == 1) {
                printf("\n\nVITÓRIA a palavra era '%s'! O computador venceu de %s, o computador fez %d tentativas e teve %d erros.", palavra_passe2,jogador1,quantidade_jogadas,quantidade_erros2);
            }
            else {
                printf("\n\nDERROTA a palavra era '%s'! O computador perdeu para %s, o computador fez %d tentativas e teve %d erros o máximo é 6.", palavra_passe2,jogador1,quantidade_jogadas,quantidade_erros2);
            }    
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
        inicializar_pilha2();
        int quantidade_erros = 0; // chegando a 7 será a derrota
        char letra; // letra digitadas pelo jogador
        
        //while que roda até jogador perder ou ganhar
        while(quantidade_erros < vidas && vitoria < 1) {
            A:
            limpatela();
            
            //função que desenha a pessoa baseado nos erros
            desenha_corpo(quantidade_erros); 
            
            // revela as letras da palavra passe
            printf("Palavra secreta: ");
            exibe_palavra_passe(palavra_passe, tamanho_palavra);
            
            //função que exibe as letras digitadas
            printf("\n\nLetras já digitadas: ");
            exibe_pilha();
            
            // se houver pelo menos uma jogada sera possivel retroceder
            int escolha_retroceder;
            if(quantidade_jogadas > 0) {
            printf("\n\nDigite 0 para retroceder ou 1 para continuar: ");
            scanf("%d", &escolha_retroceder);
                if(escolha_retroceder == 0) {
                    
                    quantidade_jogadas--;
                    // exclui topo
                    retrocede_pilha();
                    
                    // ve o valor de topo na pilha 2 para saber se a letra foi um acerto ou erro
                    // 1 = acertou / 0 = errou
                    int temporario = ve_topo();
                    
                    // se a letra tinha sido um erro retirar na quantidade de erros 
                    if(temporario == 0) {
                        quantidade_erros = quantidade_erros - 1;   
                    }
                    
                    // exclui topo da segunda pilha que indica se a jogada foi um erro o acerto
                    retrocede_pilha2();
                    
                    goto A;
                }
            }
            
            B:
            if (verifica_vitoria(palavra_passe, tamanho_palavra) < 1) { // só pede uma letra se ainda não tiver ganhado
                // digitando uma letra e guardando
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
                    
                    // verificando denovo para armazenar na segunda pilha 
                    int  valor_erro_acerto = verifica_acerto(palavra_passe, tamanho_palavra, letra);
                    inserir_pilha2(valor_erro_acerto);
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

void retrocede_pilha() {
    // função para excluir ultima jogada
    if( topo == NULL) {
        // pilha vazia
    }
	else {
		aux = topo->prox;
		free(topo);
		topo = aux;
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





/////////////////////////////////////////////////////////////////////////////
//                 funções da pilha certo ou errado                       //

void inicializar_pilha2() {
	topo2 = NULL;		
}

void inserir_pilha2(int valor_recebido) {
    // função para inserir na pilha de certo ou errado
	if(topo2 == NULL) {  // se for o primeiro elemento
		topo2 = malloc(sizeof(PILHA2));
		topo2->valor = valor_recebido;
		topo2->prox2 = NULL;
	}
	else {
		novo2 = malloc(sizeof(PILHA2));
		novo2->valor = valor_recebido;
		novo2->prox2 = topo2;
		topo2 = novo2;
	}
}

int ve_topo() {
    // função para comparar os valores para ver se foi acerto ou erro
    if(topo2 == NULL) {
        // pilha vazia
    }
	else {
	    aux2 = topo2->prox2;
		if(topo2->valor == 0) {
		    return 0;
		}
		else {
		    return 1;
		}
	}
	return 1;
}

void retrocede_pilha2() {
    // função para excluir ultima jogada
    if(topo2 == NULL) {
        // pilha vazia
    }
	else {
		aux2 = topo2->prox2;
		free(topo2);
		topo2 = aux2;
	}
}
///////////////////////////////////////////////////////////////////////////





char tentativa_cpu() {
    // função que o cumputador 'chuta uma letra' para tentar acertar a palavra secreta
    
    // vetor com todas as letras
    char v[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    
    // gerando valor aleatorio de 0 a 25
    srand(time(NULL));
    int numero = rand() % 25;
    
    // retorna a letra na posição correspondente ao numero gerado
    return v[numero];
    
}

int verifica_acerto(char palavra_passe[], int tamanho_palavra, char letra) {
    int i = 0; // contador
    while (i < tamanho_palavra) {
        if(letra == palavra_passe[i]) {
            return 1;
        }
        i++;
    }
    return 0;
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
