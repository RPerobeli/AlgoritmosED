#include <stdio.h>
#include <stdlib.h>

#define A 0.678033
#define tam 19


typedef struct cell
{
    int key;
    int key2;
    struct cell *next;
    struct cell *prev;
}cell;

int Hash(int k)
{
    float kA = k*A;
    int kA_int = kA/1;
    float frac = kA - kA_int;
    int res = (tam*frac)/1;
    return res;
}

void InsereListaHash(cell* Htable[], int k, int k2)
{
    cell *nova = malloc(sizeof(cell));
    nova->next = NULL;
    nova->prev = NULL;
    nova->key2 = k2;
    nova->key = k;

    int posicao = Hash(k);

    if(Htable[posicao] == NULL)
    {
        Htable[posicao] = nova;
    }else
    {
        cell *percorreLista = Htable[posicao];
        while(percorreLista->next != NULL)
        {
            percorreLista=percorreLista->next;
        }
        percorreLista->next = nova;
        nova->prev = percorreLista;
    }
    return;
}

cell* Buscar(cell* Htable[], int  k, int k2)
{
    cell *resp;
    int posicao = Hash(k);

    cell *percorreLista = Htable[posicao];
    while(percorreLista !=NULL && percorreLista->key2 != k2)
    {
        percorreLista = percorreLista->next;
    }
    resp = percorreLista;
    return resp;
}

void RemoverListaHash(cell* Htable[], int k, int k2)
{
    int posicao = Hash(k);
    cell *percorreLista = Htable[posicao];

    while (percorreLista != NULL)
    {
        if(percorreLista->key2 == k2)
        {
            if(percorreLista->next == NULL)
            {
                if(percorreLista->prev != NULL)
                {
                    percorreLista->prev->next = NULL;
                    free(percorreLista);
                }else
                {
                    Htable[posicao] = NULL;
                    return;
                }
            }else if(percorreLista->prev == NULL)
            {
                if(percorreLista->next!=NULL)
                {
                 percorreLista->next->prev = NULL;
                 Htable[posicao] = percorreLista->next;
                }else
                {
                    Htable[posicao] = NULL;
                    return;
                }
            }else
            {
                percorreLista->prev->next = percorreLista->next;
                percorreLista->next->prev = percorreLista->prev;
                free(percorreLista);
            }
        }
        percorreLista = percorreLista->next;
    }
    return;
}

void ImprimeHashTable(cell* Htable[])
{
    for(int i=0; i<tam;i++)
    {
        if(Htable[i] !=NULL)
        {
            cell *percorreLista = Htable[i];
            while(percorreLista !=NULL)
            {
                printf("\n Posicao H: %d;", i);
                printf("\t Prim Key: %d; Second key: %d", percorreLista->key, percorreLista->key2);
                percorreLista=percorreLista->next;
            }

        }
    }
    return;
}
int main()
{
    //Implementar um dos dois algoritmos de tabela de espalhamento.
    //Além das funções para inserção, remoção e busca, implementar adicionalmente uma função para imprimir todo o conteúdo
    //da tabela. Ao final da atividade, anexar o código implementado.

    //simulando uma mercearia, que guarda os clientes cadastrados atraves de inteiros, que compareceram no ultimo mes, com o valor da compra

    cell* Htable[tam];
    for(int i=0;i<tam;i++)
    {
        Htable[i]= NULL;
    }

    for(int j=0;j<40;j++)
    {
        InsereListaHash(Htable, 11*j+3, 2*j);
    }

    ImprimeHashTable(Htable);

    RemoverListaHash(Htable, 11*2+3, 2*2);
    RemoverListaHash(Htable, 11*3+3, 2*3);

    printf("\n\n");

    ImprimeHashTable(Htable);

    printf("\n\n");

    cell *desejado = Buscar(Htable, 11*2+3,2*2);
    if(desejado == NULL)
    {
        printf("\n Nao encontrado");
    }else
    {
        printf("\n Chave prim: %d; Chave sec.: %d", desejado->key,desejado->key2);
    }

    return 0;
}
