#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// void imprime(char* s)
// {
//     printf("%s", s);
//     return;
// }

// int main()
// {
//     char* c= "Hello world!\n";
//     imprime(c);

//     return 0;
// }

//Exercício proposto
// Exercício: Construa um programa que 
// a) leia 3 números inteiros da console, 
// b) verifica se eles formam um triângulo retângulo, 
// c) Informa na tela se é retângulo ou não, 
// d) se for retângulo, imprime a sua área.



int VerificaTriangulo(int lados[])
{
    bool res;
    int a = lados[0]*lados[0]; // problemas ao utilizar o pow(lados[0],2) 5^1 = 24
    printf("\n%d/  ", a);
    int b = lados[1]*lados[1];
    printf("%d/  ", b);
    int c = lados[2]*lados[2];
    printf("%d/ ", c);

    if(a == (b+c))
    {
        res = true;
    }else
    {
        res = false;
    }
    
    return res;
}

int main()
{
    int length = 3;
    int lados[length], aux = 0;
    printf("insira os 3 lados do triangulo:\n");
    scanf("%d", &lados[0]);
    scanf("%d", &lados[1]);
    scanf("%d", &lados[2]);

    //Ordena o Vetor 
    //tive ideia de usar ponteiros mas desisti
    for(int i=0;i<length;i++)
    {
       for(int j=0;j<length;j++)
       {
           if(lados[i]>lados[j]) // foi necessário debug
           {
               aux = lados[i];
               lados[i]= lados[j];
               lados[j]= aux;
           }
       }
    }
    for(int k=0;k<length;k++)
    {
        printf("%d|  ",lados[k]);
    }
    bool triangulo = VerificaTriangulo(lados);
    
    if(triangulo)
    {
        printf("Eh um triangulo retangulo");
    }else
    {
        printf("NAO eh um triangulo retangulo");
    }
    return 0;
}