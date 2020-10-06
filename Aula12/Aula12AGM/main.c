#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------------------------------------------------------------------*/
typedef struct Aresta
{
    struct Aresta *prev;
    float peso;
    int vFinal;
    struct Aresta *next;

}Aresta;

typedef struct Vertice
{
    int v_id;
    struct Aresta *headAresta;
    struct Vertice *next;
    struct Vertice *prev;
}Vertice;

/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*Funções Basicas de Lista */
void ImprimeGrafo(Vertice *grafo)
{
    Vertice *percorreVertices = grafo;
    while(percorreVertices!=NULL)
    {
        printf("\nVertice %d: ", percorreVertices->v_id);
        while(percorreVertices->headAresta!=NULL)
        {
            printf("\n   Aresta com o vertice %d com peso %.1f", percorreVertices->headAresta->vFinal, percorreVertices->headAresta->peso);
            percorreVertices->headAresta = percorreVertices->headAresta->next;
        }
        percorreVertices= percorreVertices->next;
    }
}

void InsereVertice(Vertice **list, int v_id)
{
    //separa o espaço de memoria
    Vertice *novoV = malloc(sizeof(Vertice));
    novoV->next = NULL;
    novoV->prev = NULL;
    novoV->v_id = v_id;
    novoV->headAresta = NULL;

    if((*list) == NULL)
    {
        (*list) = novoV;
    }else
    {
        Vertice *percorreVertice = (*list);
        while(percorreVertice->next!=NULL)
        {
            percorreVertice = percorreVertice->next;
        }
        percorreVertice->next = novoV;
        novoV->prev = percorreVertice;
    }

}

void InsereAresta(Aresta **list, float peso, int v_id)
{
    //deve receber um head aresta de um vertice
    Aresta *nova  = malloc(sizeof(Aresta));
    nova->next = NULL;
    nova->prev = NULL;
    nova->peso = peso;
    nova->vFinal = v_id;

    if((*list)==NULL)
    {
        (*list)=nova;
    }else
    {
        Aresta *percorreArestas = *list;
        while(percorreArestas->next !=NULL)
        {
            percorreArestas=percorreArestas->next;
        }
        percorreArestas->next = nova;
        nova->prev = percorreArestas;
    }

}

Vertice* BuscaVertice(Vertice *list, int v_id)
{
    Vertice *procurado = NULL;
    if(list == NULL)
    {
        printf("\nnao ha vertices para procurar");
        return procurado;
    }else
    {
        while(list!=NULL && list->v_id!=v_id)
        {
            list = list->next;
        }
        procurado = list;
        if(procurado == NULL)
        {
            //printf("\nO vertice procurado nao existe");
            return procurado;
        }else
        {
            return procurado;
        }
    }

}

Aresta* BuscaAresta(Aresta *list, float peso, int v_id)
{
    //deve receber um head aresta de um vertice
    Aresta *procurada = NULL;
    if(list == NULL)
    {
        printf("\nnao ha arestas para procurar");
        return procurada;
    }else
    {
        while(list!=NULL)
        {
            if(list->peso==peso && list->vFinal == v_id)
            {
                procurada = list;
                break;
            }else
            {
                list = list->next;
            }

        }
        if(procurada == NULL)
        {
            printf("\nO vertice procurado nao existe");
            return procurada;
        }else
        {
            return procurada;
        }
    }

}

void RemoveVertice(Vertice **list, int v_id)
{
    Vertice *Remover = NULL;
    Remover = BuscaVertice((*list),v_id);

    //remove o vertice que se tem que remover
    if(Remover->prev == NULL)
    {
        //se for o primeiro da lista, agr a cabeça da lista tem q ser o proximo
        (*list)= Remover->next;
        if((*list)==NULL)
        {
            return;
        }
        Remover->next->prev=NULL;

    }else if(Remover->next ==NULL)
    {
        Remover->prev->next = NULL;
    }else
    {
        Remover->prev->next = Remover->next;
        Remover->next->prev = Remover->prev;
    }

    free(Remover);

}

void RemoveAresta(Aresta **list, float peso,int v_id)
{
    Aresta *Remover = NULL;
    Remover = BuscaAresta((*list),peso,v_id);

    //remove a aresta que se tem que remover
    if(Remover->prev == NULL)
    {
        //se for o primeiro da lista, agr a cabeça da lista tem q ser o proximo
        (*list)= Remover->next;
        if((*list)==NULL)
        {
            return;
        }
        Remover->next->prev=NULL;

    }else if(Remover->next ==NULL)
    {
        Remover->prev->next = NULL;
    }else
    {
        Remover->prev->next = Remover->next;
        Remover->next->prev = Remover->prev;
    }

    free(Remover);

}

void InsereListaArestas(Aresta **listRecebe, Aresta *listFonte)
{
    //Já recebe 2 listas prontas, n é necessário alocar memoria
    if(*listRecebe == NULL)
    {
        (*listRecebe)= listFonte;
    }else
    {
        //Insere no final da lista
        Aresta *percorreArestas = *listRecebe;
        while(percorreArestas->next!=NULL)
        {
            percorreArestas=percorreArestas->next;
        }
        percorreArestas->next= listFonte;
    }

}
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*Funções Auxiliares do Problema*/
void InsereGrafo(Vertice **grafo, float *leitura, int numV)
{
    for(int i=0;i<numV;i++)
    {
        InsereVertice(&(*grafo), i+1);
        Vertice *procurado = BuscaVertice(*grafo,i+1);
        for(int j=0;j<numV;j++)
        {
            InsereAresta(&(procurado->headAresta), leitura[(i*numV)+j], j+1);
        }
    }

}


void BuscaCustoMinimo(Vertice *list,int *verticesConectados)
{
    Vertice *percorreLista = list;
    float custoMinimo = INT_MAX;

    if(percorreLista == NULL)
    {
        printf("erro na busca minima, a lista nao existe");
    }
    while(percorreLista!=NULL)
    {
        Aresta *percorreArestas = percorreLista->headAresta;
        while(percorreArestas!=NULL)
        {
            if(percorreArestas->peso>0)
            {
                if(percorreArestas->peso<=custoMinimo)
                {
                    custoMinimo = percorreArestas->peso;
                    verticesConectados[0] = percorreArestas->vFinal;
                    verticesConectados[1] = percorreLista->v_id;
                    verticesConectados[2] = custoMinimo;
                }
            }
            percorreArestas=percorreArestas->next;
        }
        percorreLista=percorreLista->next;
    }

    return;
}

void RemoveArestasExtras(Vertice **list)
{
    Vertice *percorreVertices = *list;
    while(percorreVertices!=NULL)
    {
        Aresta *percorreAresta = percorreVertices->headAresta;
        while(percorreAresta!=NULL)
        {
            if(BuscaVertice(*list,percorreAresta->vFinal)!=NULL)
            {
                RemoveAresta(&(percorreVertices->headAresta),percorreAresta->peso,percorreAresta->vFinal);
                percorreAresta = percorreVertices->headAresta;


            }else
            {
                percorreAresta=percorreAresta->next;
            }

        }
        percorreVertices=percorreVertices->next;
    }

}

void InsereArestasSelecionadas(Vertice **list, int *VSelecionados)
{
    Vertice *Atual = BuscaVertice(*list,VSelecionados[1]);
    InsereAresta(&((Atual)->headAresta),VSelecionados[2],VSelecionados[0]);
    Atual = BuscaVertice((*list),VSelecionados[0]);
    InsereAresta(&((Atual)->headAresta),VSelecionados[2],VSelecionados[1]);
}
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*Algoritmo de Prim*/
void Prim(Vertice **grafo, Vertice **AGM, int numV)
{
    Vertice *Usados = NULL;
    Vertice *Restantes = NULL;
    int VerticesConectados[3]={0, 0, 0}; //o primeiro elem é o proximo vertice, e o segundo é o vertice pai com menor peso e o terceiro é o peso
    for(int i=0;i<numV;i++)
    {
        InsereVertice(&Restantes,i+1);
    }

    InsereVertice(&Usados, (*grafo)->v_id);
    InsereListaArestas(&(Usados->headAresta),(*grafo)->headAresta);
    InsereVertice(&(*(AGM)), Usados->v_id);
    RemoveVertice(&Restantes,Usados->v_id);

    //Foram criadas as listas auxiliares de vertices ja usados, e suas arestas, e uma lista de vertices que restam no grafo inicial
    while(Restantes !=NULL)
    {
        //Busca o custo minimo e retorna os 2 vertices conectados e o peso entre eles
        BuscaCustoMinimo(Usados, VerticesConectados);
        InsereVertice(&Usados, VerticesConectados[0]);
        InsereListaArestas(&(BuscaVertice(Usados,VerticesConectados[0])->headAresta),BuscaVertice(*grafo,VerticesConectados[0])->headAresta);
        RemoveVertice(&Restantes,VerticesConectados[0]);
        //Mexe na AGM
        InsereVertice(&(*AGM),VerticesConectados[0]);
        InsereArestasSelecionadas(&(*AGM), VerticesConectados);
        //Retira de Usados, as arestas que ja foram usadas
        RemoveArestasExtras(&Usados);
    }
    printf("Arvore Geradora Minima Finalizada");



}
/*------------------------------------------------------------------------------------------------------------------------------------------*/
int main()
{
//    Implementar um dos algoritmos de árvore geradora mínima vistos em aula.
//    A entrada, com as arestas e seus pesos, deve ser lida de arquivo. Ao final da atividade, adicionar apenas o código fonte desenvolvido.
    FILE *arquivo;

    arquivo = fopen("ArquivoTXT.txt","r");
    int numVertices = 0;
    fscanf(arquivo,"%d ", &numVertices);

    float leitura[numVertices*numVertices];
    float num;
    for(int i=0;i<numVertices*numVertices;i++)
    {
        fscanf(arquivo,"%f ", &num);
        leitura[i] = num;
    }
    Vertice *AGM=NULL;
    Vertice *grafo=NULL;


    if(arquivo)
    {
        InsereGrafo(&grafo,leitura,numVertices);
    }else
    {
        printf("\nNao abriu o arquivo\n");
    }
    printf("\nPreencheu o grafo\n");

    Prim(&grafo, &AGM, numVertices);
    ImprimeGrafo(AGM);
    fclose(arquivo);

    return 0;
}
