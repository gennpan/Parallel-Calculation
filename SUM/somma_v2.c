/*Esercizio da ultimare, segui slide 8 del laboratorio 28 aprile*/



#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{

        //Parte sequenziale
        int i, N, t, nloc, id, step, r;

        float sumtot,sum,*a;
	
	id = omp_get_thread_num();
        sumtot = 0;

        printf("Inserire N\n");
        scanf("%d",&N);

        a = (float *)calloc(N,sizeof(float));

        printf("Inserire i numeri da sommare\n");

        for (i=0;i<N;i++){
                scanf("%f",&a[i]);
        }

        //Parte Parallela
        //Rifacendoci alla prima strategia
        #pragma omp parallel private(sum,nloc,i,id) shared(sumtot,r,step)

     {      	   
	 t = omp_get_num_threads();       //come prima cosa vado a capire quanti thread siamo a fare ciò 
         nloc = N/t;      		  //ricordo che è privato per ora
         
	 r = N%t;

	 id = omp_get_thread_num();

	 //Stampa di prova
	 printf("sono %d, di %d: numeri %d, r=%d\n", id, t, nloc, r);
        
	 if (id < r){
                 nloc++;
                 step = 0;
         	}
                else
                    step = r;
	 
	 //Stampa di prova
	 printf("sono %d, di %d: numeri %d\n",omp_get_thread_num(),t,nloc);     //metto una stampa per capire chi sta facendo cosa

         sum = 0;         //è privata, ognuno fa la sua somma

         for(i=0;i<nloc;i++){
                sum = sum + a[i+nloc*omp_get_thread_num()+step];
         	}

	 //Stampa di prova
	 printf("Sono %d, di %d: numeri %d, r=%d, i mia sum=%f\n", id, t, nloc, r, sum);

         sumtot += sum;

     } //fine direttiva

        printf("somma totale: %f\n",sumtot);
}

