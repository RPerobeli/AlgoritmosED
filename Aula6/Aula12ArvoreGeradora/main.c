#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Aresta
{
    int V_final;
    int peso;
    struct Aresta *prox;

}Aresta;

typedef struct Vertice
{
    int nome;
    struct Aresta *headAresta;
    struct Vertice *prox;
    int grau;
}Vertice; 

void InsereGrafo(Vertice **grafo, FILE *arq)
{
    int continueV = 1;
    int continueA = 1;
    int leitura;
    while(continueV)
    {
        fscanf(arq, "%d ", &leitura);
        if(leitura == -1)
        {
            printf("\nnao ha mais nada a ser lido");
            break;
        }else
        {
            Vertice *novoV = malloc(sizeof(Vertice));
            novoV->headAresta = NULL;
            novoV->prox = NULL;
            novoV->nome = leitura;
            novoV->grau = 0;

            if((*grafo)==NULL)
            {
                (*grafo) = novoV;

            }else{
                Vertice *percorreVertices = *grafo;
                while(percorreVertices->prox!=NULL)
                {
                    percorreVertices = percorreVertices->prox;
                }
                percorreVertices->prox = novoV;
            }

            //Após situar o vertice tenta achar as arestas daquele vertice
            while(continueA)
            {
                float peso = 0;
                int c;
                fscanf(arq, "%f/%d ", &peso, &c);
                if(c == 0)
                {
                    printf("\nnao ha nada mais sobre esse vertice");
                    break;
                }else
                {
                    Aresta *nova = malloc(sizeof(Aresta));
                    nova->prox = NULL;
                    nova->peso = peso;
                    nova->V_final = c;
                    if(novoV->headAresta == NULL)
                    {
                        novoV->headAresta=nova;
                        novoV->grau++;
                    }else
                    {
                        Aresta *percorreAresta = novoV->headAresta;
                        while(percorreAresta->prox!=NULL)
                        {
                            percorreAresta = percorreAresta->prox;
                        }
                        percorreAresta->prox = nova;
                        novoV->grau++;
                    }
                }
            }
        }
    }
}



void Prim(Vertice *grafo, int numV, int pai[])
{
    int i,j;
    int primeiro = 1;
    int menorCusto = -1;
    for(i=0;i<numV;i++)
    {
        pai[i] = -1;
    }
    pai[0] = grafo->nome; //a raiz do vertice origem do grafo é ele mesmo

    while(1)
    {
        for(i=0;i<numV;i++)
        {
            if(pai[i] != -1) //acha um vertice com predecessor(pai)
            {
                Vertice *percorreVertices = grafo;
                while(percorreVertices !=NULL)
                {
                    if(percorreVertices->nome == pai[i])
                    {
                        Aresta *percorreArestas = percorreVertices->headAresta;
                        while(percorreArestas !=NULL)
                        {
                            if()
                        }
                    }
                }
            }
        }
        if(primeiro ==1)
        {
            break;
        }
    }






}

int main()
{
//    Implementar um dos algoritmos de árvore geradora mínima vistos em aula.
//    A entrada, com as arestas e seus pesos, deve ser lida de arquivo. Ao final da atividade, adicionar apenas o código fonte desenvolvido.
    FILE *arquivo;

    arquivo = fopen("ArquivoTXT.txt","r");
    int numVertices = 0;
    fscanf(arquivo,"%d ", &numVertices);

    int pai[numVertices];

    Vertice *grafo=NULL;
    if(arquivo)
    {
        InsereGrafo(&grafo, arquivo);
    }else
    {
        printf("nao abriu o arquivo\n");
    }
    printf("\nPreencheu o grafo");

    Prim(grafo, numVertices, pai);

    return 0;
}
