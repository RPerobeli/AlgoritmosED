#include <stdio.h>
#include <stdlib.h>

typedef struct me {
    int tam;
    int *vet;
    double *valor;
    int max;
    int quant;
} me;

void init(me* mat, int tam, int max){
    mat->tam = tam;
    mat->vet = malloc(sizeof(int)*max);
    mat->valor = malloc(sizeof(double)*max);
    mat->max = max;
    mat->quant=0;
}
void atual(me* mat, int l, int c, double val){
    if (l>mat->tam-1 || l<0  || c>mat->tam-1 || c<0){
        printf("indices invalidos na função atual\n");
        return;
    };
    int j, f=0, i = (l*mat->tam)+c;
    for(j=0;j<mat->max;j++)
        if (mat->vet[j]==i){
                mat->valor[j]=val;
                f=1;
                break;
        }
    if(!f)
        if(mat->quant < mat->max){
            mat->vet[mat->quant]=i;
            mat->valor[mat->quant]=val;
            mat->quant++;
        }
}
double le(me* mat, int l, int c){
    if (l>mat->tam-1 || l<0  || c>mat->tam-1 || c<0){
        printf("indices invalidos na função le\n");
        return 0;
    };

    int j, i = (l*mat->tam)+c;
       for(j=0;j<mat->max;j++)
          if (mat->vet[j]==i)
            return mat->valor[j];
    return 0;
}

int main()
{
    me m;
    init(&m,1000,100);
    atual(&m,10,10,3.2);
    atual(&m,500,500,10.1);
    printf("[10,10]:%f , [0,0]: %f",le(&m,10,10), le(&m,0,0));
    return 0;
}
