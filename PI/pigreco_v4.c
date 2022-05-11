/* Questa versione è già più veloce in quanto
 * implementa la seconda strategia
 * */


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100000000

int main(int argc, char **argv)
{
        long int i, n=N;
        double x, dx, f, sum, pi;

        printf("numero di intervalli: %ld\n", n);
        sum = 0.0;

        dx = 1.0/(double)n;
        
	#pragma omp parallel for private(x,f,i)shared(dx,n)reduction(+:sum)
	//attenzione ho dovuto togliere sum dai parametri shared
        
	for(i=1; i<=n; i++)
        {
                x = dx * ((double)(i-0.5));
                f = 4.0 / (1.0 + x*x);

	//attenzione commento: #pragma omp critical

                sum = sum + f;
        }

        pi = dx * sum;
        printf("PI %24f\n", pi);

return 0;
}

