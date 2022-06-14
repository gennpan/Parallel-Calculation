/* Progetto di Calcolo Parallelo e Distribuito 2021/2022
 *
 * CFU: 9
 * 
 * Autore: Panico Gennaro - '0124002115'
 * 
 * Il codice che segue è costituito da commenti 
 * di riga, ove espongo per l'appunto, riga per riga ciò
 * che faccio, ma per avere informazioni riguardo l'idea
 * di sviluppo e i risultati dei test, consultare l'annessa 
 * documentazione presente su gitHub.
 * La macchina su cui gira possiede max: 4 thread e 2 core.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "lib.h"

#define CHUNK 2     //aumentando questo valore lo schedule tende ad essere static mentre diminuendolo tende ad essere di tipo dynamic.

//FUNZIONE PER ESTRARRE GLI ELEMENTI PRESENTI SULLA DIAGONALE PRINCIPALE E SUCCESSIVAMENTE SOMMARLI.

void parallel_sum(double *matrix, int dim){
    
    //Sezione eseguita dal Master Thread.
    int i, num_proc=4;
    double *vector;
    double t0, t1, ts0, ts1, final_t=0.0, final_s=0.0, sum=0.0;
  
    
    //Allocazione dinamica del vettore.
    vector = (double *)calloc(dim,sizeof(double));

    if(dim<=20){
    printf("\n\n----------------| Thread View: copia in PARALLELO degli elementi sulla diagonale principale, nel vettore 'A'.\n\n");
    }

    //Sezione eseguita in Parallelo	    
    //Genero un team di thread con la direttiva #pragma omp parallel.
    t0 = omp_get_wtime();
    #pragma omp parallel for default(none) private(i) shared(vector,matrix,dim) schedule(dynamic, CHUNK) num_threads(num_proc)
    for(i=0; i<dim; i++){
        if(dim<=20){    
        printf("\nIl thread %d ha completato l'iterazione(%d) e ha estratto il valore.\n", omp_get_thread_num(), i);
        }
        vector[i] = matrix[i+i*dim];
    }
    t1 = omp_get_wtime();
    final_t = t1-t0;

    if(dim<=20){
    printf("\n||||> Vettore A (valori estratti sulla diagonale principale): ");
    for(i=0; i<dim; i++){
        printf("%f ", vector[i]);
        }
    }
    


    printf("\n\n----------------| Thread View: somma in PARALLELO degli elementi nel vettore 'A'.\n\n");
    ts0 = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(dynamic, CHUNK) num_threads(num_proc) //optare per guided o dynamic  
        for(i=0; i<dim; i++){
            if(dim<=20){
                printf("\nIl thread %d, ha completato l'iterazione(%d)\n", omp_get_thread_num(), i);
            }
            sum = sum + vector[i]; //valutare in caso non ci sia un numero divisibile per t.
        }
    ts1 = omp_get_wtime();
    final_s = ts1-ts0;
    

    printf("\n\n||||> La somma dei valori sulla diagonale principale vale:  %f", sum);

    //Sezione di stampa dei tempi.
    printf("\n\n\n\n----------------| Tempi presi.\n\n\n");
    printf("\nStart: %lf   End: %lf\n\n", t0, t1);
    printf("\n||||> Tempo di calcolo Copia: %lf\n\n", final_t);
    printf("\nStart: %lf   End: %lf\n\n", ts0, ts1);
    printf("\n||||> Tempo di calcolo Somma: %lf\n\n", final_s);

    free(vector);
    
}
