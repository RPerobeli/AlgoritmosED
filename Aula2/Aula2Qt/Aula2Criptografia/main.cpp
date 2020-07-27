#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <limits>

using namespace std;

int row=0, column=0;

int Matriz[5][5] = {
    {12,      13,      14,      15,      16},
    {11,      2,        3,        4,        17},
    {10,      1,        0,        5,        18},
    {9,        8,        7,        6,        19},
    {24,      23,      22,      21,      20}
};

void ProcuraValorCriptografado(int valor)
{
   int k = 4;
   for(int i =0;i<5;i++)
   {
       for(int j=0;j<5;j++)
       {
           if(Matriz[i][j]== valor)
           {
               row=k-2;
               column=j-2;
               return;
           }
       }
       k--;
   }
   printf("nao achou");
   return;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    Escreva uma funcao que receba um inteiro, referente a uma posição
//    geografica criptografada, e imprima as coordenadas (x,y) correspondente
//    segundo o esquema de criptografia abaixo:

//    12      13      14      15      16
//    11      2        3        4        17
//    10      1        0        5        18
//    9        8        7        6        19
//    24      23      22      21      20
    while(true)
    {
        int valor = 0;

        printf("valor inteiro:");
        scanf("%d", &valor);

        ProcuraValorCriptografado(valor);

        printf("posicao = (%d,%d)\n", column, row);
    }
    return a.exec();
}
