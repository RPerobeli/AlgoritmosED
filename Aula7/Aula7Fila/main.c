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

int entrada(fila* F, int v){
    if (!(F->f==TAM)){
        F->v[F->f]=v;
        if(F->f==F->i-1)
        {
            F->aux = 1;
        }
        F->f=F->f+1;

        return 1;
    }
    else{
        if(F->i == 0 || F->aux == 1)
        {
             printf("Fila cheia \n");
        }else
        {
            F->f=0;
            entrada(F,v);
        }
    }
}
int saida(fila* F){
    int resp;
    if(F->f==F->i){
        printf("Fila vazia \n");
        resp = 0;
    }
    else {
        resp=F->v[F->i];
        F->i++;
        F->aux =0;
        if(F->i >= TAM)
        {
            F->i=0;
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
       entrada(f1,i+1);
    for(i=1;i<=2;i++)
       printf("%d\n",saida(f1));
    return 0;
}
