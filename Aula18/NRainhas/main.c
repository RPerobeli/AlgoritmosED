#include <stdio.h>

#define N 4

#define false   0
#define true    1

cont =0;
int isSoluton(int *a, int k, int *tab)
{
    return 0;
}

void ProcessSolution()
{
    cont++;
}

void Candidatos(int *a,int *tab,  int *c, int k, int *nCandidates)
{

}
void BackTracking(int *a, int k, int *tab)
{
    if(isSoluton(a,k,tab))
    {
        ProcessSolution(a, k, tab);
    }
    else
    {
        k++;
        int c=*tab;
        int nCandidates = 0;
        Candidatos(a, tab, &c, k, &nCandidates);
        for(int i=1;i<nCandidates;i++)
        {
            BackTracking(a,k,tab);
        }
    }
}
int main()
{
    //Use backtracking para resolver o problema das N rainhas: dado um tabuleiro de xadrez
    //com dimensões N x N, posicione N rainhas de modo que nenhuma rainha possa atacar
    //nenhuma outra.
    //resp para 8: 92
    int a[N][N][N], k=0, tabuleiro[N][N];

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            a[i][j]=0;
            tabuleiro[i][j]=1;
        }
    }
    BackTracking(a,k,N);

    return 0;
}
