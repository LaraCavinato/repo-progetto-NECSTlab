#include"gestione.h"
#include"bmp.h"

int Livelli(char []);
int Area (char []);
int ChiaroScuro(char, float*, float*);
void Confronta(char [], char []);
int CreaContorno (char []);
int SchermataConfronto(struct s_paziente*);
int CercaSuccessivo(struct s_paziente*, struct s_reperto*, char);
int CercaStessoLivello(struct s_paziente*, struct s_reperto*, char);
void GreyDistribution (char []);
int LivelliGrigio(char [], int []);
void SchermataElaborazione(struct s_paziente*);
