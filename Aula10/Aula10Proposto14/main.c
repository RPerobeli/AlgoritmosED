#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct sec{
    int val;
    struct sec *prox;
} sec;

typedef struct princ{
    int q_elem;
    sec *c;
    struct princ *prox;
    struct princ *ant;
} princ;


void insere_secundario(princ **Pr, int n){

    sec *s;
    s = malloc(sizeof(sec));
    s->val = n;
    s->prox = NULL;

    if((*Pr)->q_elem == 0){
        (*Pr)->c = s;
        (*Pr)->q_elem++;
    }else{
        sec *aux;
        aux = (*Pr)->c;
        while(aux != NULL){
            aux = aux->prox;
        }
        aux = s;
        (*Pr)->q_elem++;
    }
}

void insere(princ **Pr, int n){

    if(*Pr == NULL){
        (*Pr)= malloc(sizeof(princ));
        (*Pr)->q_elem = 0;
        insere_secundario(&(*Pr), n);
        (*Pr)->ant = NULL;
        (*Pr)->prox = NULL;
    }else{
        princ *atual = *Pr;

        while(atual->q_elem >= TAM){
            if(atual->prox == NULL)
            {
                princ *nova;
                nova = malloc(sizeof(princ));
                nova->q_elem = 0;
                nova->prox = NULL;
                atual->prox = nova;
                nova->ant = atual;
                insere_secundario(&nova, n);
                return;
            }
            atual = atual->prox;
        }
        insere_secundario(&atual,n);
    }

}


int main()
{
 princ *P = NULL;

 insere(&P, 1005);
 insere(&P, 1006);
 insere(&P, 1007);
 insere(&P, 1008);
    return 0;
}
