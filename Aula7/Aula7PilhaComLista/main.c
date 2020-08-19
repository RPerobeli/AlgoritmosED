#include <stdio.h>
#include <stdlib.h>

typedef struct Celula
{
    int valor;
    struct Celula *next;
}Celula;

void Inserir(Celula **p, int val)
{
    //inicia uma nova celula na pilha usando recursividade
    if(*p == NULL)
    {
        *p = malloc(sizeof(Celula));
        (*p)->valor = val;
        (*p)->next = NULL;
    }else
    {
        Inserir(&((*p)->next), val);
    }
    return;
}

void Imprime(Celula *p)
{
    Celula *atual = p;
    while(atual != NULL)
    {
        printf("Valor: %d \n", atual->valor);
        atual = atual->next;
    }
    return;
}

void Retirar(Celula **p)
{
//    Celula *atual = *p;
//    while(atual->next!=NULL) //usa o atual->next pra ir até a ultima celula nao NULL
//    {
//        atual = atual->next;
//    }
//    int val = atual->valor;
//    atual = NULL;
//    return val;
    if((*p)==NULL)
    {
        printf("Fila Vazia \n");
    }else if((*p)->next == NULL)
    {
        int val = (*p)->valor;
        (*p) = NULL;
        printf("O valor retirado da pilha foi: %d \n", val);
    }else
    {
        Retirar(&((*p)->next));
    }

}
int main()
{
    Celula *Pilha = NULL;

    Inserir(&Pilha, 1);
    Inserir(&Pilha, 2);
    Inserir(&Pilha, 3);
    Inserir(&Pilha, 4);
    Imprime(Pilha);
    Retirar(&Pilha);



    return 0;
}
