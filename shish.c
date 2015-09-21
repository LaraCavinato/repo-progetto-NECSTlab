#include "gestione.h"

void main () {

    struct s_paziente* TESTA;
    printf("***BENVENUTI A RAPTURE*** \n now would you kindly....");

    
    printf("1. Aggiungi paziente\n");
    printf("2. Aggiungi reperto\n");
    printf("3. Ricerca paziente a cui appartiene una data immagine\n");
    printf("4. Elaborare un’immagine\n");
    printf("Si scelga il numero della funzione desiderata\n");
    short int lepre;
    scanf("%hd", &lepre);
    switch (lepre) {
  case 1:  InserisciInTesta(&TESTA); 
  	break;
  case 2:  AR(TESTA);
  	break;
  case 3:  match(TESTA);	
  	break;
  default: printf("OH COME ON!");
	break;
	}
}
