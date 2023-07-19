#include <stdio.h>
#define MAX 100

typedef struct{
    int v[MAX];
    int inicio, fim;
    int tam;
}fila;

fila *criafila();

void push(fila *f, int x);

int pop(fila *f);

int filavazia(fila*f);
