#include <stdio.h>
#include <stdlib.h>
#define TAM 5
typedef struct {
    int v [TAM];
    int f,i; // posição de entrada
    int aux;
} fila;
fila* cria_fila(){
    fila *F;
    F = (fila*) malloc(sizeof(fila));
    F->f = 0; // proxima posicao para entrada
    F->i = 0; // proxima posicao para saida
    F->aux=0;
    return F;
};
int entrada(fila* f, int v){
    if (!(f->f==TAM)){
        f->v[f->f]=v;
        if(f->f==f->i-1)
        {
            f->aux = 1;
        }
        f->f=f->f+1;

        return 1;
    }
    else{
        if(f->i == 0 || f->aux == 1)
        {
             printf("Fila cheia \n");
        }else
        {
            f->f=0;
            entrada(f,v);
        }

    }
}
int saida(fila* f){
    int resp;
    if(f->f==f->i){
        printf("Fila vazia \n");
        resp = 0;
    }
    else {
        resp=f->v[f->i];
        f->i++;
        f->aux =0;
        if(f->i >= TAM)
        {
            f->i=0;
        }
    }
    return resp;
}

int main(){

    //IMPLEMENTAR FILA CIRCULAR
    int i;
    fila *f1;
    f1=cria_fila();
    for(i=1;i<=6;i++)
       entrada(f1,i);
    for(i=1;i<=4;i++)
       printf("%d\n",saida(f1));
    for(i=1;i<=6;i++)
       entrada(f1,i);
    for(i=1;i<=2;i++)
       printf("%d\n",saida(f1));
    return 0;
}
