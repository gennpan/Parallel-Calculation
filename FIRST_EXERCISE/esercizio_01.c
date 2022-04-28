/*Esercizio 'Hello from' per iniziare ad utilizzare
 * la libreria OpenMP, ideata per gli ambienti MIMD-SM
 * (Multiple Instruction, Multiple Data, Shared-Memory).
 * Siamo quindi in ambito Multi-Core.
*/



#include <omp.h>
#include <stdio.h>

int main()
{
        //dichiarazione variabili
        //dichiariamo per gestire la stampa in maniera più esplicita:

        int id, id_exe;

	//Posso stabilire con 'num_thread' il numero di thread da utilizzare, 
	//inserendo la funzione nel listato del pragma quindi a fianco a Shared in questo caso.
	//Oppure posso fare la stessa cosa, con il comando 'export OMP_NUM_THREADS=2' nel terminale subito dopo aver compilato, 
	//quindi da terminale stesso.

        #pragma omp parallel private(id) shared(id_exe)		//definizione delle variabili shared o private

        //aggiungiamo le parentesi graffe per creare un blocco di istruzioni
        {

	id = omp_get_thread_num();
	id_exe = omp_get_num_threads();
        printf("Hello from thread %d, nthreads %d\n", id, id_exe);

        } //fine blocco direttiva

        return 0;
}

