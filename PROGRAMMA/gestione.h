/*
*
*	Contiene tutte le dichiarazioni
*	delle funzioni per la gestione
*	dei pazienti e delle immagini
*
*/

#include "tipiestrutture.h"

void match(struct s_paziente*);

int trovato (struct s_reperto*, char []);

void IA(struct s_paziente**);
void crea (struct s_paziente**);
void InserisciInTesta(struct s_paziente**);
void CP(struct s_paziente* , struct s_paziente**);

void caratteristiche_reperto (struct s_reperto*);
void crea_reperto (struct s_reperto**); 
void AR(struct s_paziente*);
int CercaRepertoConStampa(struct s_paziente*, struct s_reperto**);

void importa(struct s_paziente**);
void esporta(struct s_paziente*);
void scriviR(struct s_reperto**, FILE*, struct s_reperto**);
void scriviP(struct s_paziente**, FILE*, struct s_paziente***);


