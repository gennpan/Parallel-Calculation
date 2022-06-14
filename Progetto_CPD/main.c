/* Progetto di Calcolo Parallelo e Distribuito 2021/2022
 *
 * CFU: 9
 * 
 * Autore: Panico Gennaro - '0124002115'
 * 
 * Il codice che segue è costituito da commenti di riga, 
 * ove espongo per l'appunto, riga per riga, ciò che faccio, 
 * ma per avere informazioni riguardo l'idea di sviluppo e 
 * i risultati dei test, consultare l'annessa documentazione 
 * presente su gitHub.
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include "lib.h"
#include <time.h>

int main() {

    //Sezione eseguita dal Master Thread. 	
    //Dichiarazione delle variabili.
    int i, j, n; 
    double *mat;
    
    
    //Ricorda di valutare un possibile controllo sui pari e sul max della dimensione.
    printf("\n\n\t\t\t\t\tBENVENUTO!\nData la dimensione, questo programma genera una matrice randomica con valori compresi tra 10 e 99, questa scelta è stata presa unicamente per visualizzare al meglio la matrice di double\nsuccessivamente, ricopia in parallelo i valori sulla diagonale principale e li somma (in parallelo).\n\n");
    printf("\n\n\t\t----------------| Start |----------------\n\n\n");
    printf("ATTENZIONE, con valori <=20 è possibile vedere come lavorano i thread, anche se si suggerisce di inserire valori da 500 in poi per accertare i test.\n\n");
    printf("Inserisci il valore delle dimensioni della matrice quadrata (nxn) che sia <= 2000:\t");
    scanf("%d", &n);
    printf("\n\n----------------| Stai generando i valori in una matrice quadtrata %dx%d. --> Ordine: %d \n\n", n, n, n);

    if(n<=2000){
    //Allocazione dinamica delle matrice.
    mat = calloc(n*n,sizeof(double*));
   
    //Riempimento della matrice. 
    srand(time(NULL));
    for(i=0; i<n; i++)        
        for(j=0; j<n; j++){
            mat [j+i*n] = ( (double)rand() * ( 100 - 10 ) ) / (double)RAND_MAX + 10;  //genero la matrice randomica con numeri compresi tra 10 e 99 (10<numeri<99).
        }
    }   else {
           printf("ERRORE: dimensione errata della matrice, problemi con la visualizzazione della matrice.\n\n\n");
           return 0; 
    }


    printf("\n\n\n\n----------------| Matrice %dx%d, generata!\n\n\n", n, n);

    if(n<=20){
    //Sezione di stampa a video della matrice.  
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%f  ", mat[j+i*n]);
        }
        printf("\n");
    }
}
    printf("\n\n\t\t----------------| Start Algoritmo Sequenziale |----------------\n\n\n");
    seq_sum(mat,n);
    printf("\n\n\t\t----------------| Start Algoritmo Parallelo |----------------\n\n\n");
    parallel_sum(mat,n);
    free(mat);        
}
