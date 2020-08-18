#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *esq;
    struct no *dir;
} no;

void insere(no** r, int v){
    if(*r==NULL){
        *r=malloc(sizeof(no));
        (*r)->dir=NULL;
        (*r)->esq=NULL;
        (*r)->valor=v;
    }
    else
        if ((*r)->valor > v)
            // insere a esquerda
            insere(&(*r)->esq,v);
        else
            // insere a direita
            insere(&((*r)->dir),v);
}

no* insere1(no* r, int v){
    if(r==NULL){
        r=malloc(sizeof(no));
        (r)->dir=NULL;
        (r)->esq=NULL;
        (r)->valor=v;
        return r;
    }
    else
        if ((r)->valor > v)
            // insere a esquerda
            r->esq = insere1(r->esq,v);
        else
            // insere a direita
            r->dir = insere1((r->dir),v);
    return r;
}

void lista(no* r){
  if (r!=NULL){
      lista(r->esq);
      printf("%d\n",r->valor);
      lista(r->dir);
      }
}

int getAlt(no *r){
    if(r==NULL){
        return -1;
    }
    else{
        int hEsq = getAlt(r->esq);
        int hDir = getAlt(r->dir);
        return (hEsq>hDir?hEsq:hDir)+1;
    }
}

int busca(no *r, int v){ // 1: achou  0: nao achou

    if(r == NULL){
        return 0;
    }
    if(r->valor == v){
        return 1;
    }
    if(v < r->valor){
        return busca(r->esq, v);
    }
    else{
        return busca(r->dir, v);
    }

}

int main()
{
    int valor;
    printf("Entre valor:");
    scanf("%d",&valor);
    no *raiz = NULL;
    while (valor!=0){
        insere(&raiz,valor);
        //raiz = insere1(raiz,valor);
        printf("Entre valor:");
        scanf("%d",&valor);
    }
    lista(raiz);
    printf("Entre valor para busca:");
    scanf("%d",&valor);
    int achou;
    achou = busca(raiz, valor);
    if(achou){
      printf("O valor esta na arvore.\n");
    }
    else{
      printf("O valor nao esta na arvore.\n");
    }
    return 0;
}
