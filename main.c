#include "elaborazione.h"

void main () {
	short int OK;
	short int a;
	char continuare;					
	struct s_paziente* pazientedaesaminare;
	pazientedaesaminare=NULL;
    struct s_paziente* TESTA;
    TESTA=NULL;
    importa(&TESTA);
    printf("NB: Nel caso il paziente abbia due nomi si prega di inserirli con un underscore tra di essi.\nEsempio Homer_J Simpson HRJSMP30B55C957Y.\n");
    do{    
		printf("1. Aggiungi paziente\n");
		printf("2. Aggiungi reperto\n");
		printf("3. Ricerca paziente a cui appartiene una data immagine\n");
		printf("4. Elaborare un’immagine\n");
		do{
		printf("Si scelga il numero della funzione desiderata\n");
		scanf("%hd", &a);
		}while(a<1 || a>4);
		switch (a) {
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
