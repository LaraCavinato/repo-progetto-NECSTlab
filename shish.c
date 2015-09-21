#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//TIPO DATA
typedef struct{

	short int giorno;
	short int mese;
	short int anno;
	short int ora;
	short int minuto;
	short int secondo;} t_data;

//TIPO ANAGRAFICA
typedef struct{
 
	char nome[20];
	char cognome[20];
	char codice_fiscale[17];
	int ID_medico_di_base;} t_anagrafica;
     
//STRUCT REPERTO
struct s_reperto{

	char NomeDelFile[25];
	t_data data;
	struct s_reperto* next;};
 
//STRUCT PAZIENTE
struct s_paziente {
 
    t_anagrafica anagrafica;
    struct s_reperto* PAPR;  //PuntantoreAPrimoReperto
    short int Numero_Radiografie;
    struct s_paziente *next;};

void match(struct s_paziente*);
void crea (struct s_paziente**);
void IA(struct s_paziente**);
int trovato (struct s_reperto*, char []);
void salvafile (struct s_paziente*);
void AR(struct s_paziente*);
void leggo(struct s_paziente*);
void InserisciInTesta(struct s_paziente**);
void CP(struct s_paziente* , struct s_paziente**);
void caratteristiche_reperto (struct s_reperto*);
void crea_reperto (struct s_reperto**); 
void scriviR(struct s_reperto**, FILE*, struct s_reperto*);
void scriviP(struct s_paziente**, FILE*, struct s_paziente*);

//----------------

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


//-------------
//associa il paziente all'immagine fornita
void match(struct s_paziente* p0) {
 
    char nomecercato[25];
    struct s_paziente* scorriP;
 
    scorriP=p0;
 
    printf("Nome reperto da cercare:");
    scanf("%s", nomecercato);
 
    while( !( trovato(scorriP->PAPR, nomecercato) || (scorriP==NULL) ) ){
        scorriP=scorriP->next;
    }
 
    if(scorriP->next==NULL)
        printf("**ERROR** %s non appartiene a nessun paziente", nomecercato);
    else
        printf("Il reperto cercato appartiene al paziente %s %s\n", scorriP->anagrafica.nome,  scorriP->anagrafica.cognome);
}
 
int trovato (struct s_reperto* scorriR, char nomecercato[]) {
 
    do{
        if( !(strcmp(nomecercato, scorriR->NomeDelFile)) )
            return 1;
        else
            scorriR = scorriR->next;
    }while( !(scorriR->next==NULL));
 
    return 0;
}
 
void crea (struct s_paziente **dato){
 
  *dato = (struct s_paziente*) malloc(sizeof(struct s_paziente));
  (*dato)->next = NULL;
  IA(dato);
}
 
//INSERISCI ANAGRARFICA
void IA(struct s_paziente **a ){
 
    printf("inserisci in questo formato nome[spazio]cognome[spazio]codicefiscale:\n\n");
    scanf("%s %s %s", (*a)->anagrafica.nome, (*a)->anagrafica.cognome,  (*a)->anagrafica.codice_fiscale);
 
    printf("inserisci ID medico:");
    scanf("%d", &(*a)->anagrafica.ID_medico_di_base);
 
    (*a)->Numero_Radiografie=0;
}
 
void InserisciInTesta(struct s_paziente** t){
 
    struct s_paziente *new;
    printf("\n-- Inserimento paziente --\n");
 
    crea(&new);
    new->next=*t;
    *t = new;
}
 
 
void CP /*cercapaziente*/  (struct s_paziente* t /*testa*/, struct s_paziente** p /*puntatore che punterà*/) {
//DATI DI TARGA
//riceve il puntatore alla testa e l'indirizzo di un puntatore che se tutto va a buon fine alla chiusura
//della funzione punterà al paziente richiesto. Il paziente viene richiesto all'interno della funzione.
//se il paziente non compare tra i salvati allora verrà stampato a schermo un messaggio d'errore e
//il puntatore verrà reimposto a NULL per sicurezza. Il chiamante dovrebbe assicurarsi che tutto
//funzioni alla fine.
 
    struct s_paziente* lampo;
    char CF[17];
    lampo=t;
    short int a=1;
 
    printf("si inserisca il codice fiscale del paziente cercato:\n");
    scanf("%s", CF);
 
    while(  strcmp(lampo->anagrafica.codice_fiscale, CF)  && a){
        if(lampo->next==NULL){
            printf("Il paziente cercato non é presente nell'archivio\n");
            *p=NULL;
            a=0;
        }
        lampo=lampo->next;
    }
 
    if(a){   //il paziente è stato trovato
        printf("Il paziente cercato è stato trovato");
        *p=lampo;
    }
}
 
//AGGIUNGI REPERTO
void AR(struct s_paziente * t /*puntatore al primo paziente*/) {
 
    struct s_paziente* paziente;
    paziente=NULL;
    struct s_reperto* R;
    

    do{
        CP(t, &paziente);
    }while(paziente==NULL);
    // ora paziente punta al paziente desiderato
    
    crea_reperto(&R);
    // ora R ha della memoria allocata e vi sono salvati tutti i dati necessari.
 
    R->next=paziente->PAPR;        // inserimento
    paziente->PAPR=R;              // in testa
    paziente->Numero_Radiografie++;
}
 
void crea_reperto (struct s_reperto** r){
 
    *r=malloc(sizeof(struct s_reperto));
    (*r)->next = NULL;
    caratteristiche_reperto(*r);
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
}
 

// FILE //
void salvafile (struct s_paziente* t) {

	FILE* fp;
	struct s_reperto*  scorriR;
	struct s_paziente* scorriP;
	scorriP=t;
	scorriR=t->PAPR;    

	fp=fopen("memoria.txt", "w+");
	if(fp!=NULL){
		printf("il file è stato aperto correttamente. Attendere.");
		printf(".");
		printf(".");

		while(scorriP==NULL){
			fprintf(fp, "%s\n%s\n%s\n%d\n%hi\n", scorriP->anagrafica.nome, scorriP->anagrafica.cognome, scorriP->anagrafica.codice_fiscale, scorriP->anagrafica.ID_medico_di_base, scorriP->Numero_Radiografie);
			scorriP=scorriP->next;

			while(scorriR==NULL){
				fprintf(fp, "%s\n%hi\t%hi\t%hi\n%hi\t%hi\t%hi\n", scorriR->NomeDelFile, scorriR->data.giorno, scorriR->data.mese, scorriR->data.anno, scorriR->data.ora, scorriR->data.minuto, scorriR->data.secondo);

				scorriR=scorriR->next;
			}
		}
	}
	else{
		printf("apertura fallita\n");
		fclose(fp);}
}

void leggo(struct s_paziente* t){
    
	FILE* fp;
	struct s_paziente* scorriP;
	struct s_reperto* scorriR;

	fp=fopen("memoria.txt", "r");
		if(fp!=NULL) {
	printf("Il file è stato aperto correttamente\n");

	while(!feof(fp)){
		scriviP(&scorriP, fp, t);

		while((scorriP->Numero_Radiografie)--){
			scriviR(&scorriR, fp, scorriP->PAPR);
		}
	}
	
	}else{
		printf ("apertura fallita");
		fclose(fp);}
}

void scriviP(struct s_paziente** dato, FILE* fp, struct s_paziente* t){
	 
	*dato = (struct s_paziente*) malloc(sizeof(struct s_paziente));
	  
	fscanf(fp, "%s\n%s\n%s\n%d\n%hi\n", (*dato)->anagrafica.nome, (*dato)->anagrafica.cognome,(*dato)->anagrafica.codice_fiscale, &((*dato)->anagrafica.ID_medico_di_base), &((*dato)->Numero_Radiografie));


	(*dato)->next=t;
	t=*dato;}

void scriviR(struct s_reperto** dato, FILE* fp, struct s_reperto* t){
	*dato=(struct s_reperto*)malloc(sizeof(struct s_reperto));

	fprintf(fp, "%s\n%hi\t%hi\t%hi\n%hi\t%hi\t%hi\n", (*dato)->NomeDelFile, ((*dato)->data.giorno), ((*dato)->data.mese), ((*dato)->data.anno), ((*dato)->data.ora), ((*dato)->data.minuto), ((*dato)->data.secondo));

	(*dato)->next=t;
	t=*dato;}




