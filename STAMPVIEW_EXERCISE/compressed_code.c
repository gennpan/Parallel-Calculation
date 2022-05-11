/* Versione compressa per la visualizzazione del
 * thread e della sua corrispondente iterazione
*/



#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
        //dichiarazione variabili
        //dichiariamo per gestire la stampa in maniera più esplicita:

        int id_thread, i;

	omp_set_num_threads(3);
	#pragma omp parallel for private(id_thread)

      	for(i=0; i<=4; i++)
      	{
      		id_thread = omp_get_thread_num();
      		
      		printf("Iterazione %d del thread %d\n", i, id_thread);

       }

        return 0;
}

