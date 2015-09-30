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
    char piano;
    int livello; 
    struct s_reperto* next;};
 
//STRUCT PAZIENTE
struct s_paziente {
 
    t_anagrafica anagrafica;
    struct s_reperto* PAPR;  //PuntantoreAPrimoReperto
    short int Numero_Radiografie;
    struct s_paziente *next;};
