#include "gestione.h"

void main () {
	short int OK;
	short int lepre;
	char continuare;					
	struct s_paziente* pazientedaesaminare;
    struct s_paziente* TESTA;
    importa(TESTA);
    do{
		printf("***BENVENUTI A RAPTURE*** \nnow would you kindly....\n");    
		printf("1. Aggiungi paziente\n");
		printf("2. Aggiungi reperto\n");
		printf("3. Ricerca paziente a cui appartiene una data immagine\n");
		printf("4. Elaborare un’immagine\n");
		printf("Si scelga il numero della funzione desiderata\n");
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
		printf("si desidera continuare? [Y/n]\n");
		scanf(" %c", &continuare);	
	}while(continuare=='Y');
	esporta(TESTA);
}
