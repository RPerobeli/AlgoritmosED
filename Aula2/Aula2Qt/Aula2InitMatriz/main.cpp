#include <QCoreApplication>
#include <stdio.h>
#include <iostream>

#define N 4
#define n 10

using namespace std;


float vetSoma[10];

class Matriz
{
    private:
    public:
    float Matriz[N][N];

    void Inicia(float valor);
    void Preenche();
    void Show();
};

void Matriz::Inicia(float valor)
{
    for(int i =0;i<N;i++)
    {
        for(int j=0; j<N;j++)
        {
            this->Matriz[i][j] = valor;
        }
    }
    return;
}

void Matriz::Preenche()
{
    int k =0;
    int i = 0, imax = N;
    while(k<10)
    {
        for(int j=0;j<N;j++)
        {
            if((j>=i) && (this->Matriz[i][j]==0))
            {
                this->Matriz[i][j] = vetSoma[k];
                k++;
                i++;
                j=0;
                if(i==imax)
                {
                    i = 0;
                    imax--;
                }
            }
        }

    }

    return;
}

void Matriz::Show()
{
    for(int i =0;i<N;i++)
    {
        for(int j=0; j<N;j++)
        {
           cout << this->Matriz[i][j] << " ";
           if(j == N-1)
           {
               cout << "\n";
           }
        }
    }
    return;
}

void SomaSerie(int ene)
{
    float soma = 0;
    for(int i=1; i<=ene; i++)
    {
        float j = i;
        soma = soma + (1/j);
        vetSoma[i-1] = soma;
        //cout << vetSoma[i] << endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int valor = 0;
    Matriz M;

    M.Inicia(valor);
    SomaSerie(n);
    M.Preenche();
    M.Show();

    return a.exec();
}
