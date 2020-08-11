#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int tel;
    int mat;
    struct no * prox;
} no;

no *inicio; // inicio da lista

void insere_lista(int _m, int _t){

    no *tmp = malloc(sizeof(no));
    tmp->tel= _t;
    tmp->mat = _m;
    tmp->prox = NULL;

    if (inicio==NULL)
        inicio=tmp;
    else{
        no *t =inicio;
        while (t->prox!=NULL)
            t = t->prox;
        t->prox = tmp;
    }
}

void insere_ordenado(int _m, int _t){
    no *tmp = malloc(sizeof(no));
    tmp->tel= _t;
    tmp->mat = _m;
    tmp->prox = NULL;
    if (inicio==NULL) // lista vazia
        inicio=tmp;
    else{
          no *t1, *t2;
          t1=inicio; t2=NULL;
          if (t1->mat >= _m){ // novo <= primeiro
                inicio=tmp;
                inicio->prox=t1;
          }
          else{
              t2=t1; t1=t1->prox;
              do{
                    if (t1==NULL){ // novo eh ultimo da lista
                        t2->prox=tmp;
                        break;
                    }
                    else{
                        if (t1->mat>= _m){ // novo entre t2 e t1
                            t2->prox = tmp;
                            tmp->prox = t1;
                            break;
                        }
                        else{  // novo depois de t1
                            t2=t1;
                            t1=t1->prox;
                        }
                    }
              } while(1);
        }
    }
}

int main() {
    inicio = NULL;
    insere_ordenado(2,4002);
    insere_ordenado(3,4003);
    insere_ordenado(5,4005);
    insere_ordenado(1,4001);
    insere_ordenado(4,4004);

    no *t = inicio;
    while (t!=NULL){
        printf("Matricula:%d , Telefone:%d\n",t->mat, t->tel);
        t=t->prox;
    }
    return 0;
}
