#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//  Um elevador suporta 500 kg, uma pessoa carrega o elevador com  caixas de no mínimo 10 kg. As caixas são colocadas
//  em fila para serem postas no elevador. Caso uma caixa não possa ser colocada no elevador deve-se retirá-la da
//  fila. Todas as vezes que se informa, ao programa, o peso da caixa, e é possivel embarca-la, ele retorna: OK,
//  e quando o elevador atingir um valor maior que 491, deve retornar: SUBIU e zerar o peso do elevador para começar
//  novamente
    float caixaAtual=0;
    float pesoTotal = 0;
    int pesoMax = 500;

    printf("coloque o peso da primeira caixa:");
    scanf("%f", &caixaAtual);

    while(pesoTotal < pesoMax)
    {
        pesoTotal = pesoTotal + caixaAtual;
        if(pesoTotal <= pesoMax - 10)
        {
            printf("proxima caixa:");
            scanf("%f", &caixaAtual);

        }else if(pesoTotal > pesoMax)
        {
            printf("peso maximo excedido");
            pesoTotal = pesoTotal - caixaAtual;
            caixaAtual = 0;

        }else if(pesoTotal <= pesoMax && pesoTotal >= pesoMax-10)
        {
            printf("Subindo");
            break;
        }else
        {
            printf("erro");
        }
    }


    return a.exec();
}
