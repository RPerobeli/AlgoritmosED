#include <stdio.h>
#include <stdlib.h>



void Merge(int *vetor, int p, int q, int r)
{
    int n1 = q-p+1;
    int n2 = r-q;
    int L[n1+1];
    int R[n2+1];
    int i=0;
    int j=0;
    int k=0;

    for(i=0; i<=n1;i++)
    {
        L[i] = vetor[p-1+i];
    }
    for(j=0; j<=n2;j++)
    {
        R[j] = vetor[q+j];
    }

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    i = 0;
    j = 0;

    for(k=p-1;k<r;k++)
    {
        if(L[i]<=R[j])
        {
            vetor[k] = L[i];
            i++;
        }else
        {
            vetor[k] = R[j];
            j++;
        }
    }
}

void DivideNConquer(int *vetor, int p, int r)
{
    if(p<r)
    {
        int q = (p+r)/2;
        DivideNConquer(vetor,p, q);
        DivideNConquer(vetor, q+1, r);
        Merge(vetor, p, q, r);
    }

}

void ImprimeVetor(int *vetor,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d\n",vetor[i]);
    }
}
int main()
{
    //Implementar o algoritmo de ordenação Merge Sort. Os números a serem ordenados devem ser lidos de arquivo. Ao final da atividade, anexar o arquivo com o código fonte.
    FILE *arquivo = NULL;
    int tam=0;
    arquivo = fopen("dados.txt", "r");

    if(arquivo)
    {

        fscanf(arquivo,"%d ", &tam);
        int vetor[tam];
        for(int i=0; i<tam; i++)
        {
            fscanf(arquivo,"%d ", &vetor[i]);

        }
        DivideNConquer(vetor,1,tam);
        ImprimeVetor(vetor,tam);

    }else
    {
        printf("Erro na abertura do arquivo");
    }
    return 0;
}
