/* Esercizio per osservare che:
 * Ad ogni iterazione i thread aspettano un numero 
 * di secondi pari all'indice dell'iterazione.
 * Capiamo che bisogna bilanciare il lavoro su ogni thread
 *
 * versione 4 con dynamic e chunk, ci consente di stressare
 * il codice, ad esempio potrei metterlo a 1000 (valore della costante)
 *per fare tutte le operazioni sequenziali al thread 0
 * */


#include <time.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 1000
#define CHUNK 10


//#include <windows.h>

int main()
{
        //dichiarazione variabili
        //dichiariamo per gestire la stampa in maniera più esplicita:

        int n_threads, i;


        #pragma omp parallel for private(i) schedule(dynamic, CHUNK) num_threads(4) 

        for(i=0; i<=16; i++)
        {
                //aspetta un numero pari ad i secondi
                sleep(i);

                printf("Il thread %d ha completato iterazione %d.\n", omp_get_thread_num(), i);

       }

        printf("Tutti i thread hanno terminato!\n");


  return 0;
}

