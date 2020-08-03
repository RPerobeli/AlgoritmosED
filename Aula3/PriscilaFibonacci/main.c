#include <stdio.h>
#include <stdlib.h>

float fibonacci (int n)
{

    if (n==1)
    {
        return 0;
    }else if (n==2 || n==3) {
        return 1;
    } else{
        return fibonacci(n-2) + fibonacci (n-1);
    }
}


int main ()
{
    while (1)
    {
        int n, m=1;
        float res=0;

        printf ("Insira o numero de termos de Fibonacci desejado: ");
        scanf ("%d", &n);

        do{
            res = fibonacci (m);
            printf ("%.1f   ", res);

            m=m+1;
            n--;

        } while (n!=0);{
            return 0;
        }

    }
}
