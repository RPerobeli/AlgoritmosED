#include <stdio.h>

#define tam 100
#define grava 0

int matriz[tam][tam];

void LeArquivo(FILE *arquivo)
{
    for(int i=0;i<tam;i++)
    {
        for(int j=0;j<tam;j++)
        {
            fscanf(arquivo,"%d", &matriz[i][j]);
        }
    }
    return;
}

float CalculaMediaArea(int n, int linhaAtual, int colunaAtual)
{
    //calcula a media em cada sub área
    float media=0,
          soma=0;
    //int valor = 0;
    for(int i=linhaAtual; i<linhaAtual+n;i++)
    {
        for(int j=colunaAtual;j<colunaAtual+n;j++)
        {
            //valor = matriz[i][j];
            soma = soma + matriz[i][j];
        }
    }
    media= soma/(n*n);
    //printf("%.2f ", media);
    return media;
}

void ImprimePosicao(int linha, int coluna, float media)
{
    printf("\nA area com menor media teve valor %.2f, com identificacao %d,%d", media, linha, coluna);

    return;
}

void ProcuraArea(int n, int *linha, int *coluna)
{
    //função que procura na matriz inteira pelas sub áreas com menor valor medio de desmatamento
    int i,j;
    float media =0, menor;
    for(i=0;i<tam-n;i++)
    {
        for(j=0;j<tam-n;j++)
        {
            media =CalculaMediaArea(n, i, j);
            if(i==0 && j==0)
            {
                //caso seja a primeira vez que o codigo é executado, inicializa media com um valor para servir de referencia nas proximas iterações
                menor = media;
            }else
            {
                if(media < menor)
                {
                    menor = media;
                    *linha = i;
                    *coluna = j;
                }
            }
        }
    }
    ImprimePosicao(*linha,*coluna,menor);
    return;
}

void ImprimeMatriz()
{
    for(int i=0;i<tam;i++)
    {
        for(int j =0;j<tam;j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    return;
}

int main()
{
//    Construir um programa estruturado para análise de desmatamento. Fotos de satélite são traduzidas em matrizes 100×100 de inteiros.
    //Os valores inteiros positivos indicam a densidade de mata. Seu programa deverá ler o arquivo texto como parâmetro na hora da execução.
    //As linhas do arquivo contem os dados das linhas da matriz.
//    Ex:
//    1  2  3  …  100
//    1  2  3  …  100
//    … 97x

//    1 2  3  …  100

//    O programa perguntará ao usuário o tamanho de uma sub-área quadrada e procurará na área total, uma sub-área com o tamanho informado,
    //com menor média de densidade. Caso haja médias iguais, informar a primeira encontrada numa busca da esquerda para direita e de cima para baixo.
    //A identificação da sub-área encontrada será a coordenada do canto superior esquerdo da mesma. A resposta é dada na console (coordenada e média).

//    Novas buscas serão realizadas para novos valores de tamanho de sub-área até que o usuário informe um tamanho inválido de sub-área
    //(zero ou maior que a área total), evento que deverá ser notificado.

//    Verifique se o arquivo existe e informe o erro se não existir.


    FILE *arquivo;
    //primeiramente, fazer o programa que cria o arquivo de texto
#if grava
    arquivo = fopen("matrizDesmatamento.txt","w");

    for(int i=0;i<tam;i++)
    {
        for(int j=0;j<tam;j++)
        {
           fprintf(arquivo, "%d ", j+1);
        }
    }
    fclose(arquivo);

#else

    //programa que faz oq realmente está sendo pedido
    arquivo = fopen("matrizDesmatamento.txt","r");
    if(!arquivo)
    {
        printf("\nerro ao abrir arquivo");
    }else
    {
        LeArquivo(arquivo);
        //ImprimeMatriz();
    }

    int n =0;
    do
    {
        printf("\nInsira o tamanho da area quadrada:");
        scanf("%d", &n);
        if(n < 2 || n >tam)
        {
            printf("Insira um valor adequado, maior do que 1");
        }else
        {
            int linha=0,coluna=0;
            int *pcoluna=&linha,*plinha=&coluna;
            ProcuraArea(n, plinha, pcoluna);
        }
    }while(n>=2 && n<=tam);
    fclose(arquivo);
#endif
    return 0;
}
