/*
*
*	Contiene tutte le 
*	funzioni per la gestione
*	dei pazienti e delle immagini
*
*/

#include "tipiestrutture.h"

//associa il paziente all'immagine fornita
void match(struct s_paziente* t) {
 
    char nomecercato[25];
    struct s_paziente* scorriP;
 
    scorriP=t;
 
    printf("Nome reperto da cercare:");
    scanf("%s", nomecercato);
    while(!(scorriP==NULL)){
		if(trovato(scorriP->PAPR, nomecercato)){
        	printf("Il reperto cercato appartiene al paziente %s %s\n", scorriP->anagrafica.nome, scorriP->anagrafica.cognome);
        	return;
        }
		else
        	scorriP=scorriP->next;
    }
	printf("**ERROR** %s non appartiene a nessun paziente\n", nomecercato);        
}
 
int trovato (struct s_reperto* scorriR, char nomecercato[]) {
	//fornito un puntatore a reperto(il primo di una catena) e una stringa restituisce 1 se esiste un reperto con il nome uguale a quello fornito nella stringa nella catena altrimenti 0
		while(!(scorriR==NULL)){
			if( !(strcmp(nomecercato, scorriR->NomeDelFile)) )
				return 1;
			else
				scorriR = scorriR->next;
		}
		return 0;
}	


//INSERISCI ANAGRARFICA
void IA(struct s_paziente **a ){
	
    printf("inserisci in questo formato nome[spazio]cognome[spazio]codicefiscale:\n\n");
    scanf("%s %s %s", (*a)->anagrafica.nome, (*a)->anagrafica.cognome, (*a)->anagrafica.codice_fiscale);
    printf("inserisci ID medico:");
    scanf("%d", &(*a)->anagrafica.ID_medico_di_base);
 
    (*a)->Numero_Radiografie=0;
}
 
void crea (struct s_paziente **dato){
 
  *dato = (struct s_paziente*) malloc(sizeof(struct s_paziente));
  (*dato)->next = NULL;
  (*dato)->PAPR = NULL;
  IA(dato);
}
 
void InserisciInTesta(struct s_paziente** t){
 
    struct s_paziente *new;
    printf("\n-- Inserimento paziente --\n");
 
    crea(&new);
    new->next=*t;
    *t = new;
}
 
int CercaRepertoConStampa(struct s_paziente* p, struct s_reperto** r){
//elenca tutti i reperti del paziente puntato da puntatore fornito. Poi chiede un nomereperto e lo cerca. Se lo trova lo associa al puntatore passato e torna 1, altrimenti 0;
    short int ok;
    struct s_reperto* scorriR;
    char nomecercato[25];
    
    if(p->PAPR==NULL) {printf("non ci sono reperti in questo paziente\n"); return 0;}
    scorriR=p->PAPR;
    
    while(!(scorriR==NULL)){            //stampa tutti i reperti del paziente
        printf("%s\n", scorriR->NomeDelFile);
        scorriR=scorriR->next;
     }
    
    printf("quale reperto si desidera analizzare?\n");
    scanf("%s", nomecercato);
    
    ok=trovato(p->PAPR, nomecercato);                    
    
    if(ok) {
        scorriR=p->PAPR;
        while(strcmp(scorriR->NomeDelFile, nomecercato)){
            scorriR=scorriR->next;
        }
        *r=scorriR;
        return 1;
    }    
    else {printf("reperto non trovato\n"); return 0;}
} 

//CERCAPAZIENTE
void CP (struct s_paziente* t /*testa*/, struct s_paziente** p /*puntatore che punterà*/) {
//riceve il puntatore alla testa e l'indirizzo di un puntatore che se tutto va a buon fine alla chiusura
//della funzione punterà al paziente richiesto. Il paziente viene richiesto all'interno della funzione.
//Se il paziente non compare tra i salvati allora verrà stampato a schermo un messaggio d'errore e
//il puntatore verrà reimposto a NULL per sicurezza.
 
    struct s_paziente* lampo;
    char CF[17];
    lampo=t;
    //short int a=1;
 
    printf("si inserisca il codice fiscale del paziente cercato:\n");
    scanf("%s", CF);
    
    while(!(lampo==NULL)){
    	if(!(strcmp(lampo->anagrafica.codice_fiscale, CF))){
    		printf("il paziente è stato trovato\n");
    		*p=lampo;
    		return;
    	}
    lampo=lampo->next;
    }
    printf("il paziente cercato non è stato trovato\n");
}

void caratteristiche_reperto (struct s_reperto* a){
 
    //chiedere il nome del file da inserire
    printf (" \n Inserire il nome del nuovo file immagine da inserire: ");
    scanf ("%s", a->NomeDelFile);
    printf("\n Inserire la data del file \n giorno:\n");
    scanf("%hi", &a->data.giorno);
    printf("\n mese:\n");
    scanf("%hi", &a->data.mese);
    printf("\n anno:\n");
    scanf("%hi", &a->data.anno);
    printf("\n ora:\n");
    scanf("%hi", &a->data.ora);
    printf("\n minuto:\n");
    scanf("%hi", &a->data.minuto);
    printf("\n secondo:\n");
    scanf("%hi", &a->data.secondo);
    printf("\n livello:\n");
    scanf("%d", &a->livello);
    printf("\n piano:\n");
    scanf(" %c", &a->piano);
}
 
void crea_reperto (struct s_reperto** r){
 
    *r=malloc(sizeof(struct s_reperto));
    (*r)->next = NULL;
    caratteristiche_reperto(*r);
}

//AGGIUNGI REPERTO
void AR(struct s_paziente * t /*TESTA*/) {
 
    struct s_paziente* paziente;
    paziente=NULL;
    struct s_reperto* R;
    

    do{
        CP(t, &paziente);
    }while(paziente==NULL);
    // ora paziente punta al paziente desiderato
    
    printf("--inserimento reperto--\n");
    crea_reperto(&R);
    // ora R ha della memoria allocata e vi sono salvati tutti i dati necessari.
 
    R->next=paziente->PAPR;        // inserimento
    paziente->PAPR=R;              // in testa
    paziente->Numero_Radiografie++;
}

// FILE //-----------------------------------------------------------------------------------------------------
void esporta(struct s_paziente* t) {

	FILE* fp;
	struct s_reperto*  scorriR;
	struct s_paziente* scorriP;
	scorriP=t;
	scorriR=t->PAPR;    
	
	fp=fopen("memoria.txt", "w+");
	if(fp!=NULL){
		printf("il file è stato aperto correttamente (ESPORTA).\n");
		while(!(scorriP==NULL)){
	
	 		fprintf(fp, "%s\n%s\n%s\n%d\n%hi\n", scorriP->anagrafica.nome, scorriP->anagrafica.cognome, scorriP->anagrafica.codice_fiscale, scorriP->anagrafica.ID_medico_di_base, scorriP->Numero_Radiografie);		
			
			scorriR=scorriP->PAPR;	
			while(!(scorriR==NULL)){
			
				fprintf(fp, "%s\n%hi\t%hi\t%hi\n%hi\t%hi\t%hi\n%d\n%c\n", scorriR->NomeDelFile, scorriR->data.giorno, scorriR->data.mese, scorriR->data.anno, scorriR->data.ora, scorriR->data.minuto, scorriR->data.secondo, scorriR->livello, scorriR->piano);
				scorriR=scorriR->next;
			}
			scorriP=scorriP->next;
		}
	}
	else{
		printf("\n**ERROR** apertura fallita del file memoria \n");
		fclose(fp);
		return;}
			printf("fine\n");
	fclose(fp);
}

void scriviP(struct s_paziente** dato, FILE* fp, struct s_paziente*** t){

	*dato = (struct s_paziente*) malloc(sizeof(struct s_paziente));
	(*dato)->PAPR=NULL;
	fscanf(fp, "%s\n%s\n%s\n%d\n%hi\n", (*dato)->anagrafica.nome, (*dato)->anagrafica.cognome,(*dato)->anagrafica.codice_fiscale, &((*dato)->anagrafica.ID_medico_di_base), &((*dato)->Numero_Radiografie) );
	
	printf("%s\n%s\n%s\n%d\n%hi\n",(*dato)->anagrafica.nome, (*dato)->anagrafica.cognome,(*dato)->anagrafica.codice_fiscale, (*dato)->anagrafica.ID_medico_di_base, (*dato)->Numero_Radiografie);
	
	(*dato)->next=**t;
	**t=*dato;
}



void scriviR(struct s_reperto** dato, FILE* fp, struct s_reperto** t){

	*dato=(struct s_reperto*)malloc(sizeof(struct s_reperto));
	fscanf(fp, "%s\n%hi\t%hi\t%hi\n%hi\t%hi\t%hi\n%d\n%c\n", (*dato)->NomeDelFile, &((*dato)->data.giorno), &((*dato)->data.mese), &((*dato)->data.anno), &((*dato)->data.ora), &((*dato)->data.minuto), &((*dato)->data.secondo), &((*dato)->livello), &((*dato)->piano) );
	
	printf("%s\n%hi\t%hi\t%hi\n%hi\t%hi\t%hi\n%d\n%c\n", (*dato)->NomeDelFile, ((*dato)->data.giorno), ((*dato)->data.mese), ((*dato)->data.anno), ((*dato)->data.ora), ((*dato)->data.minuto), ((*dato)->data.secondo), ((*dato)->livello), ((*dato)->piano) );
	
	(*dato)->next=*t;
	*t=*dato;
}



void importa(struct s_paziente** t){
    
	FILE* fp;
	struct s_paziente* scorriP;
	struct s_reperto* scorriR;
	scorriP=NULL;
	scorriR=NULL;
	int NR;

	
	fp=fopen("memoria.txt", "r+");
	if(fp!=NULL) {
	printf("Il file è stato aperto correttamente(IMPORTA)\n");

	while(!feof(fp)){
		
		scriviP(&scorriP, fp, &t);
		NR=scorriP->Numero_Radiografie;
		while(NR--){
			scriviR(&scorriR, fp, &(scorriP->PAPR));
		}
	}
	
	}else{
		printf("\n**ERROR** apertura fallita del file memoria \n");
		fclose(fp);}
	fclose(fp);
}



