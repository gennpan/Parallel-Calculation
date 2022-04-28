#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 

/*Attenzione, ovviamente il programma funziona solo quando il numero da sommare è multiplo del numero dei thread, 
 * non c'è un controllo che evita ciò in questo algoritmo.*/


int main()
{	

	//Parte sequenziale
       	int i,N,t,nloc;
  	float sumtot,sum,*a;
  	
	sumtot=0;

  	printf("Inserire N\n");
  	scanf("%d",&N);

  	a=(float *)calloc(N,sizeof(float));

  	printf("Inserire i numeri da sommare\n");
  	
	for (i=0;i<N;i++)
  	{
      		scanf("%f",&a[i]);
  	}
	
	//Parte Parallela
	//Secondo la prima strategia
	
	#pragma omp parallel private(sum,nloc,i) shared(sumtot)

  { // se piu di un'istruzione

   	 t=omp_get_num_threads();	//come prima cosa vado a capire quanti thread siamo a fare ciò 
	 nloc=N/t;	//ricordo che è privato per ora
	 printf("sono %d, di %d: numeri %d\n",omp_get_thread_num(),t,nloc);	//metto una stampa per capire chi sta facendo cosa
    	
	 sum=0;		//è privata, ognuno fa la sua somma
    	
	for(i=0;i<nloc;i++)
    	{
       		sum=sum+a[i+nloc*omp_get_thread_num()];
    	}
    	sumtot+=sum;

  } //fine direttiva
  	
	printf("somma totale: %f\n",sumtot);

}
