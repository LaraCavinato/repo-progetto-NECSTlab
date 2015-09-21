/*
*
*	Contiene tutte le dichiarazioni
*	delle funzioni per la gestione
*	dei pazienti e delle immagini
*
*/

#include "tipiestrutture.h"

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
