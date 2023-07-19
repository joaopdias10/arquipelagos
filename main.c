#include <stdio.h>
#include <string.h>
#include "FilaEstatica.h"

typedef struct nodo{
    int info;
    int valor;
    struct nodo *prox;
} nodo;

nodo *insere(nodo *lista, int x, int v){//Coloca as ilhas ligadas à uma ilha na lista da propria ilha
    if(lista == NULL){
        nodo *novo = (nodo*)malloc(sizeof(nodo));
        novo -> info = x;
        novo -> valor = v;
        novo -> prox = lista;
        return novo;
    }
    lista -> prox = insere(lista -> prox, x, v);
    return lista;
}

int *visitados;//Variaveis globais para facilitar certa parte do codigo
int *pai;
int *dist;
int ilhas;
int pontes;
int agua;

void dfs(nodo **lista, int r){  //Busca por profundidade
    int v = 0;
    printf(" %d ", r+1);
    ilhas++;
    nodo *aux = lista[r];
    visitados[r] = 1;
    for(;aux != NULL; aux = aux -> prox){
        v = aux -> info;
        v--;    //Tive que diminuir por causa do vetor de listas
        if(aux -> valor > agua){    //Inicialmente estava junto com o outro if mas para contar o numero de pontes foi separado dele
            pontes++;
            if(visitados[v] == 0){
                dfs(lista, v);
            }
        }
    }
}

void arquipelogos(nodo **lista, int n){//Função que define tudo sobre os arquipelogos
    int i = 0, cc = 0;

    for(i = 0; i < n; i++){
        visitados[i] = 0;
    }

    for(i = 0;i < n;i++){
        if(visitados[i] == 0){
            ilhas = 0;
            pontes = 0;
            printf("\n[");
            dfs(lista, i);
            printf("] (%d ilhas, %d pontes)", ilhas, pontes/2);
            cc++;
        }
    }
    printf("\nTotal: %d arquipelogos\n\n", cc);
}

void bfs(nodo **lista, int r){//Busca por largura
    int v = 0, w = 0;
    fila *f = criafila();
    dist[r] = 0;
    push(f, r);
    visitados[r] = 1;
    while(filavazia(f) != 0){
        v = pop(f);
        nodo *aux = lista[v];
        for(;aux != NULL; aux = aux -> prox){
            w = aux -> info;
            w--;    //Tive que diminuir por causa do vetor de listas
            if(visitados[w] == 0 && aux -> valor > agua){
                push(f, w);
                visitados[w] = 1;
                dist[w] = dist[v] + 1;
                pai[w] = v+1;   //Tive que acrescentar 1 pois diminui ali em cima
            }
        }
    }
    free(f);
}

imprime(int y, int x){//Imprime o caminho
    if(y != x){
        imprime(pai[y-1], x);
        printf(" -> %d", y);
    }
}

imprimecaminho(nodo **lista, int n, int y, int x){//Chama a busca em largura e a função que imprime o caminho
    for(int z = 0;z < n;z++){
        visitados[z] = 0;
        pai[z] = 0;
        dist[z] = 0;
    }

    bfs(lista, (x-1));

    printf("\n");
    if(dist[y-1] != 0){
        printf("%d", x);
        imprime(y, x);
        printf(" (%d pontes)", dist[y-1]);
    }
    if(dist[y-1] == 0){
        printf("sem caminho entre %d e %d", x, y);
    }
    printf("\n\n");
}

int main(){
    int n = 0, m = 0, i = 0, x = 0, y = 0, valor = 0;
    char aux[7] = {0};

    scanf("%d %d", &n, &m);

    nodo *lista[n];//Cria a lista adjacente
    for(;n > i;i++){
        lista[i] = NULL;
    }

    for(i = 0;m > i;i++){//Insere as ilhas e pontes nas listas
        scanf("%d %d %d", &x, &y, &valor);
        lista[x - 1] = insere(lista[x - 1], y, valor);
        lista[y - 1] = insere(lista[y - 1], x, valor);
    }

    visitados = (int*)malloc(sizeof(int) *n);//Aloca os vetores globais
    pai = (int*)malloc(sizeof(int) *n);
    dist = (int*)malloc(sizeof(int) *n);

    while(strcmp(aux, "fim") != 0){//Responde aos comandos

        scanf("%s", &aux);

        if(strcmp(aux, "agua") == 0){
            scanf(" %d", &agua);
            printf("\nNivel da agua: %d m\n\n", agua);
        }

        if(strcmp(aux, "arq") == 0){
            arquipelogos(lista, n);
        }

        if(strcmp(aux, "caminho") == 0){
            scanf(" %d %d", &x, &y);
            imprimecaminho(lista, n, y, x);
        }
    }

    for(n--;n >= 0;n--){//Libera a memoria alocada
        free(lista[n]);
    }
    free(visitados);
    free(pai);
    free(dist);

    return 0;
}
