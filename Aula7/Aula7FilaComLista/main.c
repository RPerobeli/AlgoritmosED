#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Celula
{
    int valor;
    struct Celula *next;

}Celula;

void InsereFila(Celula **lista, int v)
{
    Celula *atual = malloc(sizeof(Celula));
    atual->valor = v;
    atual->next = NULL;

    if(*lista == NULL)
    {
        *lista = atual;
    }else
    {
        Celula *percorreLista = *lista;
        while(percorreLista->next!= NULL)
        {
            percorreLista = percorreLista->next;
        }
        percorreLista->next = atual;
    }
    return;
}

int RemoveFila(Celula **lista)
{
    int resp =0;
    Celula *atual = *lista;

    if(atual == NULL)
    {
        printf("fila vazia");
    }else
    {
        resp = atual->valor;
        *lista= atual->next;
        return resp;
    }
    return 0;
}

int main()
{
    Celula *lista=NULL;

    InsereFila(&lista,10);
    InsereFila(&lista,20);
    printf("%d \n", RemoveFila(&lista));
    printf("%d \n", RemoveFila(&lista));
    printf("%d \n", RemoveFila(&lista));



    return 0;
}
