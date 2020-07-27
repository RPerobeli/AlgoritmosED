#include <QCoreApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    Construa um programa em C que leia um inteiro n da console e
//    imprima o resultado da serie : 1/1 + 1/2 + … + 1/n

    while(true)
    {
        int n = 0;
        float soma=0;
        printf("insira o numero de iteracoes da serie:");
        scanf("%d", &n);

        for(float i=1; i<=n; i++)
        {

            soma = soma + (1/i);
        }
        cout << "soma = " << soma << endl;
    }


    return a.exec();
}
