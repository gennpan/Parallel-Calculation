/* Esercizio stampa dei valori di pigreco 
 * implementazione algoritmo di base usando pragma,
 * trattasi di una prima versione parallela per i 
 * valori di pigreco
 */




#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100000000

int main(int argc, char **argv)
{
	long int i, n=N;
	double x, dx, f, sum, pi;

	printf("Numero di intervalli: %ld\n", n);
	sum = 0.0;

	dx = 1.0/(double)n;
	#pragma omp parallel for private(x,f,i)shared(dx,sum,n)
	
	for(i=1; i<=n; i++)
	{
		x = dx * ((double)(i-0.5));
		f = 4.0 / (1.0 + x*x);
		sum = sum + f;
	}

	pi = dx * sum;
	printf("PI %24f\n", pi);

return 0;

}


