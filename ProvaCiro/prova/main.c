#include <stdio.h>
#include <stdlib.h>

typedef struct no {
char valor;
struct no *esq;
struct no *dir;
} no;


no* novo (int v){
    no* tmp = malloc(sizeof(no));
    tmp->dir = NULL;
    tmp->esq = NULL;
    tmp->valor = v;
    return tmp;
}

no* inserir2 (int nivel, no* raiz, int val){
    no* resp = NULL;
    if (nivel==0){
        if (raiz==NULL)
            return novo(val);
        else
            return NULL;
    }
    else {
        resp = inserir2(nivel-1,raiz->esq, val);
        if (resp!=NULL){
            raiz->esq=resp;
        }
        else {
            resp = inserir2(nivel-1,raiz->dir, val);
            if (resp!=NULL)
                raiz->dir=resp;
        }
    }
    if (resp==NULL) return NULL;
        else return raiz;
}

no* inserir1 (no* raiz, int val){
    if (raiz==NULL)
        return novo(val);
    else {
        int nivel=0;
        no* resp=NULL;
        while (resp==NULL) {
            resp=inserir2(nivel,raiz->esq, val);
            if (resp!=NULL)
                raiz->esq=resp;
            else {
                resp = inserir2(nivel,raiz->dir, val);
                if (resp!=NULL)
                    raiz->dir=resp;
            }
            if (resp!=NULL)
                return raiz;
            else
                nivel++;
        }
        return NULL;
    }
}
typedef struct {
    int v [TAM];
    int f,i; // posição de entrada
    int aux;
} fila;
int Remove(fila *F)
{
    if(F->f==F->i)
    {
        printf("vazia");
    }else
    {
        val = F->v[F->f];
        F->i++;
        printf("Valor retirado: %d", val);
    }
    return valor;
}
