#include <stdio.h>
#define MAX 100

typedef struct{
    int v[MAX];
    int inicio, fim;
    int tam;
}fila;

fila *criafila(){
    fila *f = (fila*)malloc(sizeof(fila));
    f -> inicio = f -> fim = 0;
    f -> tam = 0;
    return f;
}

void push(fila *f, int x){
    f -> v[f -> fim] = x;
    f -> fim = (f -> fim + 1) % MAX;
    f -> tam++;
}

int pop(fila *f){
    int aux = f -> v[f -> inicio];
    f -> inicio = (f -> inicio + 1) % MAX;
    f -> tam--;
    return aux;
}

int filavazia(fila*f){
    if(f -> tam == 0){
        return 0;
    }
    return 1;
}
