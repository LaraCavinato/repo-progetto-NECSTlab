#include "elaborazione.h"

void main () {
	short int OK;
	short int lepre;
	char continuare;					
	struct s_paziente* pazientedaesaminare;
	pazientedaesaminare=NULL;
    struct s_paziente* TESTA;
    TESTA=NULL;
    importa(&TESTA);
    if(TESTA==NULL) printf("CAZZO");
    do{
		printf("\n***BENVENUTI A RAPTURE*** \nnow would you kindly....\n");    
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
	  default: SchermataElaborazione(TESTA);
		break;
		}
		printf("\n  si desidera continuare? [Y/n]\n");
		scanf(" %c", &continuare);	
	}while(continuare=='Y');
	esporta(TESTA);
}
