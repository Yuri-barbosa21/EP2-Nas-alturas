#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b)   ((a > b) ? a : b)

//______________________________________________________________________________
                               //IMPLEMENTAÇÃO BST
//______________________________________________________________________________

//----------------- Cria a estrutura de uma BST --------------
typedef struct noBST{
    int chaveBST;
    struct noBST * fdir;
    struct noBST * fesq;
    unsigned alturaBST;
} noBST;

typedef noBST * BST; //Ponteiro para um tipo de dados noBST

//---------------- Cria um nó de uma BST ----------------
BST novo_no_BST(int chaveBST){
    BST novo_no_BST = malloc(sizeof(noBST));
    novo_no_BST->chaveBST = chaveBST;
    novo_no_BST->fesq = NULL;
    novo_no_BST->fdir = NULL;
    novo_no_BST->alturaBST = 1;
    return novo_no_BST;
}

//---------------- Função de busca para testar a funcionalidade da BST ----------------
BST busca_BST(BST raiz, int alvo){
    if(raiz == NULL || raiz->chaveBST == alvo)
        return raiz;
    else if(raiz->chaveBST > alvo)
        return busca_BST(raiz->fesq, alvo); 
    else
        return busca_BST(raiz->fdir, alvo);
}

//------------------ Inserção na BST -----------------
BST insere_BST(BST raiz, int novo){
    if(raiz == NULL)
        return novo_no_BST(novo);

    if(raiz->chaveBST == novo)
        return raiz;
    
    if(raiz->chaveBST > novo)
        raiz->fesq = insere_BST(raiz->fesq, novo);
    else
        raiz->fdir = insere_BST(raiz->fdir, novo);

    return raiz;
}    

//---------------- Retorna a altura da BST ------------- 
int altura_BST(BST raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = altura_BST(raiz->fesq);
        int dir = altura_BST(raiz->fdir);
        if(esq > dir){
            return esq + 1;
        }
        else{
            return dir + 1;
        }
    }
}

//----------------- Retorno de minimo e máximo para teste de funcionaliade ------------
BST min_BST(BST raiz){
    while(raiz->fesq)
        raiz = raiz->fesq;

    return raiz;
}
BST max_BST(BST raiz){
    while(raiz->fdir)
        raiz = raiz->fdir;

    return raiz;
}

//---------------- Printa a BST na tela para teste de funcionalidade ----------------
void mostra_in_ordem_BST(BST raiz){
    if(raiz){
        mostra_in_ordem_BST(raiz->fesq);
        printf("%d\n", raiz->chaveBST);
        mostra_in_ordem_BST(raiz->fdir);
    }
}

//----------------- Liberação de memória da arvore inteira ------------------
void libera_BST(BST raiz){
    if(raiz){
        libera_BST(raiz->fesq);
        libera_BST(raiz->fdir);
        free(raiz);
    }
}
//______________________________________________________________________________


//______________________________________________________________________________
                               //IMPLEMENTAÇÃO AVL
//______________________________________________________________________________

//----------------- Cria a estrutura de uma AVL ----------------
typedef struct noAVL{
    int chaveAVL;
    struct noAVL * fesqAVL;
    struct noAVL * fdirAVL;
    unsigned alturaAVL;
}noAVL;

typedef noAVL * AVL; //Ponteiro para um tipo de dados noAVL

//-------------------- Cria um novo nó na AVL ---------------------
AVL novo_no_AVL(int chave){
    AVL novo_no_AVL = malloc(sizeof(noAVL));
    novo_no_AVL->chaveAVL = chave;
    novo_no_AVL->fesqAVL = NULL;
    novo_no_AVL->fdirAVL = NULL;
    novo_no_AVL->alturaAVL = 1;
    return novo_no_AVL;
}

//------------------- Calculos de altura da AVL ----------------
unsigned altura_AVL(AVL no) {
    if (!no) return 0;
    return no->alturaAVL;
}

unsigned calcula_altura(AVL no) {
    return 1 + MAX(altura_AVL(no->fesqAVL), altura_AVL(no->fdirAVL));
}

//-------------------- Calcula fatos de balanceamento ----------------
int fb(AVL no) {
    return altura_AVL(no->fesqAVL) - altura_AVL(no->fdirAVL);
}

//------------------- Funlçoes de rotação na AVL -------------------
AVL rotL(AVL r) {
    AVL filho;
    filho = r->fdirAVL;        
    r->fdirAVL = filho->fesqAVL;
    filho->fesqAVL = r;        
    r->alturaAVL = calcula_altura(r);
    filho->alturaAVL = calcula_altura(filho);
    return filho;
}

AVL rotR(AVL r) {
    AVL filho;
    filho = r->fesqAVL;
    r->fesqAVL = filho->fdirAVL;
    filho->fdirAVL = r;
    r->alturaAVL = calcula_altura(r);
    filho->alturaAVL = calcula_altura(filho);
    return filho;
}


//---------------------- Inserção na AVL ------------------------
AVL insere_AVL(AVL raiz, int novo) {

    if (!raiz) return novo_no_AVL(novo);
    else if (raiz->chaveAVL == novo) return raiz;
    else if (raiz->chaveAVL > novo)
        raiz->fesqAVL = insere_AVL(raiz->fesqAVL, novo); 
    else
        raiz->fdirAVL = insere_AVL(raiz->fdirAVL, novo);
    
    raiz->alturaAVL = calcula_altura(raiz);
    int fator = fb(raiz);

    if (fator == +2) {
        if (fb(raiz->fesqAVL) < 0)
            raiz->fesqAVL = rotL(raiz->fesqAVL);
        raiz = rotR(raiz);
    } 
    else if (fator == -2) {
        if (fb(raiz->fdirAVL) > 0)
            raiz->fdirAVL = rotR(raiz->fdirAVL);
        raiz = rotL(raiz);
    }

    return raiz;
}

//------------------------ Printa AVL para teste de funcionalidade --------------------
void mostra_in_ordem_AVL(AVL raiz) {
    if (raiz != NULL) {
        mostra_in_ordem_AVL(raiz->fesqAVL);
        printf("%d\n", raiz->chaveAVL);
        mostra_in_ordem_AVL(raiz->fdirAVL);
    }
}

//-------------------- Libera memória de toda a arvore ---------------------
void libera_AVL(AVL raiz) {
    if (raiz != NULL) {
        libera_AVL(raiz->fesqAVL); 
        libera_AVL(raiz->fdirAVL); 
        free(raiz); 
    }
}
//_____________________________________________________________________________________
//                                       MAIN
//_____________________________________________________________________________________
int main() {
    int opcao, amostra, elemento;
    float media_BST = 0, media_AVL = 0, media_geral = 0;
    double media_tempo_AVL = 0, media_tempo_BST = 0, media_tempo_geral = 0;
    
    srand(time(NULL)); // INICIALIZAÇÃO DA SEMENTE

    //O TEMPO SERÁ MEDIDO POR CLOCK NO PROCESSADOR
    //---------- INICIA O CLOCK ----------- 
    clock_t inicio_BST, final_BST;
    double tempo_BST;
    clock_t inicio_AVL, final_AVL;
    double tempo_AVL;


    // LOOP DO PROGRAMA
    do{
        printf("\n\n--------------------------------------------------------------------\n");
        printf("1 - Nova Simulação  |  2 - Sair\n> ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("\nDigite a quantidade de amostras: ");
            scanf("%d", &amostra);
            
            printf("Digite a quantidade de elementos para cada amostra: ");
            scanf("%d", &elemento);
            printf("\n");

            //--------- INICIA AS ARVORES COM NULL ---------
            BST raiz_BST[amostra];
            AVL raiz_AVL[amostra];
            for(int i = 0; i < amostra; i++){
               raiz_BST[i] = NULL;
               raiz_AVL[i] = NULL;
            }

            //--------- CRIA VETOR COM VALORES ALEATÓRIOS ---------
            int v[amostra][elemento];
            for(int i = 0; i < amostra; i++){
                    for(int j = 0; j < elemento; j++){
                        v[i][j] = 1  + rand() % 99;
                }
            }

            //--------- PRINT VETOR COM VALORES ALEATÓRIOS ---------
            /*
            for(int i = 0; i < amostra; i++){
                for(int j = 0; j < elemento; j++){
                    printf("%d ", v[i][j]);
                }
                printf("\n\n");
            } 
            */

            //--------- INSERE VALORES ALEATÓRIOS NAS ARVORES ---------
            for(int i = 0; i < amostra; i++){
                for(int j = 0; j < elemento; j++){

                    //------------- EXPERIMENTO NA ARVORE BST COMUM --------------
                    inicio_BST = clock(); // MEDE O TEMPO ANTES DA TEREFA
                    
                    raiz_BST[i] = insere_BST(raiz_BST[i], v[i][j]);// INSERÇÃO NA ARVORE BST
                    
                    final_BST = clock(); // MEDO O TEMPO LOGO APÓS A TAREFA
                    tempo_BST = ((double) (final_BST-inicio_BST)/CLOCKS_PER_SEC);
                    media_tempo_BST += tempo_BST;
                    //____________________________________________________________

                    
                    //------------- EXPERIMENTO NA ARVORE AVL COMUM --------------
                    inicio_AVL = clock(); // MEDE O TEMPO ANTES DA TEREFA
                    
                    raiz_AVL[i] = insere_AVL(raiz_AVL[i], v[i][j]);
                    
                    final_AVL = clock(); // MEDO O TEMPO LOGO APÓS A TAREFA
                    tempo_AVL = ((double) (final_AVL-inicio_AVL)/CLOCKS_PER_SEC);
                    media_tempo_AVL += tempo_AVL;
                    //____________________________________________________________
                    
                }
                
                //mostra_in_ordem_BST(raiz_BST[i]);
                //mostra_in_ordem_AVL(raiz_AVL[i]);
                //printf("Altura AVL: %d\n", altura_AVL(raiz_AVL[i]));
                //printf("Altura BST: %d\n", altura_BST(raiz_BST[i]));
                
                //--------- SOMA DAS MEDIAS ---------
                media_geral = ((media_BST  / amostra) + (media_AVL / amostra)) / 2;
                media_BST += altura_BST(raiz_BST[i]);
                media_AVL += altura_AVL(raiz_AVL[i]);
                media_tempo_geral = ((media_tempo_AVL / amostra) + (media_tempo_BST / amostra)) / 2;    
                
                //--------- LIBERA MEMÓRIA DAS ARVORES CRIADAS ---------
                libera_BST(raiz_BST[i]);
                libera_AVL(raiz_AVL[i]);
            }

            //------------------ RETORNO DE TODOS OS TESTES --------------------
            printf("\n");
            printf("Experimento com A = %d e N = %d\n", amostra, elemento);
            printf("----------------------------------------------------");
            
            printf("\nAltura média geral: %.2f\n", media_geral);
            printf("Tempo médio geral de construção: %lf\n\n", media_tempo_geral);
            
            printf("Altura média BST comum: %.2f\n", media_BST / amostra);
            printf("Tempo médio de construção BST comum: %lf\n\n", media_tempo_BST / amostra);
            
            printf("Altura média AVL: %.2f\n", media_AVL / amostra);
            printf("Tempo médio de construção AVL: %lf\n\n", media_tempo_AVL / amostra);       
            printf("\n");
            
            break;                      
            
        }
    }while(opcao != 2);
    
    printf("Tchau!");

    
    return 0;
}