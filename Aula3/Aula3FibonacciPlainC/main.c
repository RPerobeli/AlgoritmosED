#include <stdio.h>
#include <stdlib.h>

float Fibonacci(int n)
{
    if(n ==1)
    {
        return 0;
    }else if(n == 2 || n==3)
    {
        return 1;
    }else
    {
        return Fibonacci(n-2)+Fibonacci(n-1);
    }
}


int main()
{
    while(1)
    {
        int n =0;
        float res = 0;
        printf("Insira o numero de valores de fibonacci desejado:");
        scanf("%d", &n);

        res = Fibonacci(n);
        printf("A resp e: %f\n", res);
    }
    return 0;
}
