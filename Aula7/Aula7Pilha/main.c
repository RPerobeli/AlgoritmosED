#include <stdio.h>
#include <stdlib.h>
#define num 100

typedef struct pilha{
    char vet[num];
    int topo;
} pilha;

void init_pilha(pilha** p){
    *p=malloc(sizeof(pilha));
    (*p)->topo = 0;
}

void poe(pilha* p, char e){
    if(p->topo<=num-1){
        p->vet[p->topo]=e;
        p->topo++;
    }
}
char pega(pilha* p){
    if(p->topo>0){
        p->topo--;
        return p->vet[p->topo];
    }
    else
        printf("pilha vazia\n");
    return '.';
}

