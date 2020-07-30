#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int cont = 0;
float sequencia[1000];

void IniciaVetor(float *vetor)
{
    for(int i=0;i<sizeof(vetor);i++)
    {
        vetor[i] = 0;
    }
    return;
}

float Fibonacci(int n)
{
    float resposta = 0;
    if(n ==1)
    {
        resposta = 0;
        sequencia[n-1] = 0;
        return resposta;
    }else if(n == 2 || n==3)
    {
        resposta = 1;
        sequencia[n-1] = 1;
        return resposta;
    }else
    {
        resposta = Fibonacci(n-2)+Fibonacci(n-1);
        sequencia[n-1] = resposta;
        return resposta;
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    while(true)
    {
        int n =0;
        float res = 0;
        printf("Insira o numero de valores de fibonacci desejado:");
        scanf("%d", &n);
        IniciaVetor(sequencia);
        cont = n-1;
        res = Fibonacci(n);
        printf("A resp e: %f\n", res);
        for(int i = 0; i<n;i++)
        {
            cout << sequencia[i] << " ";
        }
    }
    return a.exec();
}
