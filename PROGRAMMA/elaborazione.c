#include"gestione.h"
#include"bmp.h"
#include<time.h>

int Livelli(char NomeFile[]){

	BMP_Image img, risultato;
	Pixel livelli[10] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225};
	short int ok;
	int i, j, k, a;
	a=loadBMP(NomeFile, &img);
	if (a) {printf("impossibile aprire l’immagine (vedi sopra)\n"); return 0;}

	for(i=0;i<256;i++){
		for(j=0;j<256;j++){
			ok=1;k=9;
			do{
				if(img.data[i][j].grey>=livelli[k].grey) {img.data[i][j]=livelli[k]; ok=0;}
				else k--;
			}while(ok);
		}
	}
	saveBMP(img,"./modificate/livelli.bmp");
	return 1;
}



int Area (char NomeFile[]){
	int a, b, i, j, count=0;
	float area;
	BMP_Image im;
	a = CreaContorno(NomeFile);
	b = loadBMP("./modificate/contorno.bmp", &im);
	if (b) {printf("impossibile aprire l’immagine (vedi sopra)\n"); return 0;}
	if(a==1){
		for(i=0;i<DATA_DIM;i++)
		for(j=0;j<DATA_DIM;j++)
		if (im.data[i][j].grey==255)
			count++;
		printf("L’area dell’immagine significativa è di %d pixel\n", count);
		area = count*0.00625;
		printf("L’area è di %f mm^2\n", area);
		return 1;
	}
	else
		{printf("CreaContorno non è andata a buon fine\n");
		return 0;}
}



int ChiaroScuro(char NomeFile[], float* areaC, float* areaS){
	
	BMP_Image im;
	int th, tl, a, i, j, s=50;
	int countl=0;
	int  counth=0;
	a=loadBMP(NomeFile, &im);
	if (a) {printf("impossibile aprire l’immagine (vedi sopra)\n"); return 0;}

	for(i=0; i<DATA_DIM;i++){
		j=0;
		while (im.data[i][j].grey<s && j<256) {
			im.data[i][j].grey=128;
			j++;}}
	for(i=0; i<DATA_DIM;i++){
		j=255;
		while (im.data[i][j].grey<s && j>-1) {
			im.data[i][j].grey=128;
			j--;}}
			
	for(j=0;j<DATA_DIM;j++){
		i=0;
		while(im.data[i][j].grey<s && i<256){
			im.data[i][j].grey=128;
			i++;}
	}
		
	for(j=0;j<DATA_DIM;j++){
		i=255;
		while(im.data[i][j].grey<s && i>-1){
			im.data[i][j].grey=128;
			i--;}
	}
	
	printf("Inserisci il valore della soglia scura(minore di 128)\n");
	scanf("%d", &tl);
	printf("Inserisci il valore della soglia chiara(maggiore di 128)\n");
	scanf("%d", &th);

	for(i=0; i<DATA_DIM;i++)
		for(j=0; j<DATA_DIM;j++){

			if(im.data[i][j].grey<tl){
				countl++;
				im.data[i][j].grey=0;}

			if(im.data[i][j].grey>th){
				counth++;
				im.data[i][j].grey=255;}
		}

	*areaC=counth*0.00625;
	*areaS=countl*0.00625;

	printf("\nL’area dell’immagine significativa molto chiara è di %d pixel\n", counth);
	printf("L’area dell’immagine significativa molto chiara è di %f mm^2\n", *areaC);
	printf("L’area dell’immagine significativa molto scura è di %d pixel\n", countl);
	printf("L’area dell’immagine significativa molto scura è di %f mm^2\n", *areaS);

	saveBMP(im, "./modificate/ChiaroScuroBrutto.bmp");
	return 1;
}


void Confronta(char Nomefile1[], char Nomefile2[]){

	float area1C, area1S, area2C, area2S, scartoC, scartoS;

	printf("--prima immagine--\n");
	if(!ChiaroScuro(Nomefile1, &area1C, &area1S)) return;
	printf("--seconda immagine--\n");
	if(!ChiaroScuro(Nomefile2, &area2C, &area2S)) return;

	scartoC=area1C-area2C;
	scartoS=area1S-area2S;

	printf("\nL’area chiara dall’ immagine %s all’immagine %s è cresciuta di: %f mm^2\n", Nomefile1, Nomefile2, scartoC);
	printf("L’area scura  dall’ immagine %s all’immagine %s è cresciuta di: %f mm^2\n", Nomefile1, Nomefile2, scartoS);
}



int CreaContorno (char NomeDelFile[]) {

	int a, i, j;
	BMP_Image im;
	char choose;
	int soglia =50;
	
	printf("\nSoglia predefinita:%d\nSi desidera modificarla? [Y/n]:", soglia);
	scanf(" %c", &choose);
	if(choose=='Y') {
		printf("si inserisca la soglia:");
		scanf("%d", &soglia);
	}
	
	a = loadBMP(NomeDelFile, &im);
    if (a) {printf("\nimpossibile aprire l’immagine (vedi sopra)\n"); return 0;}

	for(i=0;i<DATA_DIM;i++){
		for(j=0;j<DATA_DIM;j++){
			if(im.data[i][j].grey==0) im.data[i][j].grey=1;
		}		
	}


	for(i=0;i<DATA_DIM;i++){
		j=0;
		while(im.data[i][j].grey<soglia && j<254){
			im.data[i][j].grey=0;
			j++;}
		im.data[i][j].grey=255;
	}

	

	for(j=0;j<DATA_DIM;j++){
		i=0;
		while(im.data[i][j].grey<soglia && i<254){
			im.data[i][j].grey=0;
			i++;}
		im.data[i][j].grey=255;
	}


	for(i=0;i<DATA_DIM;i++){
		j =255;
		while(im.data[i][j].grey<soglia && j>0){
			im.data[i][j].grey=0;
		    j--;}
		im.data[i][j].grey=255;
	}



	for(j=0;j<DATA_DIM;j++){
		i=255;
		while(im.data[i][j].grey<soglia && i>0){
		  im.data[i][j].grey=0;
		    i--;}
		im.data[i][j].grey=255;
	}
	
	for(i=0;i<DATA_DIM;i++){
		for(j=0;j<DATA_DIM;j++){
			if(im.data[i][j].grey!=0) im.data[i][j].grey=255;
		}		
	}
	
	saveBMP(im, "./modificate/contorno.bmp");
	return 1;	
}	



int SchermataConfronto(struct s_paziente* t){
	int choice, a, b, c, d;
	char Nome[25];
	struct s_paziente* p;
	struct s_reperto* r1;
	struct s_reperto* r2;
	
	do{
	CP(t, &p);
	}while(p==NULL);
	
	a=CercaRepertoConStampa(p, &r1);

	if (!a) return 0;

	printf("Come si desidera procedere?\n");
	printf("1. cercare un altro reperto inserendolo manualmente\n");
	printf("2. cercare un altro reperto appartenente allo stesso paziente\n");
	printf("3. cercare un altro reperto del medesimo livello di quello scelto inizialmente\n");
	printf("4. cercare un reperto successivo a quello già in esame dello stesso paziente\n");
	scanf("%d", &choice);
	switch (choice) {
		case 1:
	printf("Scrivere il nome del reperto da confrontare\n");
	scanf("%s",Nome);
	Confronta(r1->NomeDelFile, Nome);
		break;
		case 2:
	b=CercaRepertoConStampa(p, &r2);
	Confronta(r1->NomeDelFile, r2->NomeDelFile);
		break;
		case 3:
	c=CercaStessoLivello(t, r1,Nome);
	Confronta(r1->NomeDelFile, Nome);
		break;
		case 4:
	d=CercaSuccessivo(p, r1, Nome);
	Confronta(r1->NomeDelFile, Nome);
		break;
		default: printf("non riconosciuto\n");
		break;
	}
}



int CercaSuccessivo(struct s_paziente* p, struct s_reperto* r1, char Nome[]){	
	
	short int ok;
	struct s_reperto* scorriR;
	char nomecercato[25];
	
	scorriR=p->PAPR;
	
	while(!(scorriR==NULL)){
		if( (r1->livello==(scorriR->livello)-1)   &&   (r1->piano==scorriR->piano) ){
			printf("%s\t%d\t%c", scorriR->NomeDelFile, scorriR->livello, scorriR->piano);
			printf("\n");
			}
		scorriR=scorriR->next;
	}

	printf("quale reperto si desidera analizzare?");
	scanf("%s", nomecercato);

	ok=trovato(p->PAPR, nomecercato);
	if(ok) {
		strcpy(Nome ,nomecercato);
		return 1;
	}
	else {printf("il seguente reperto non esiste in questo paziente\n"); return 0;}
}



int CercaStessoLivello(struct s_paziente* t, struct s_reperto* r1, char Nome[]){
	struct s_paziente* scorriP;
	struct s_reperto* scorriR;
	char nomecercato [25];

	scorriP=t;

	while (!(scorriP==NULL)){
		scorriR=scorriP->PAPR;
		while(!(scorriR==NULL)){
			if (scorriR->livello==r1->livello && scorriR->piano==r1->piano)
					printf("%s\n", scorriR->NomeDelFile);
			scorriR=scorriR->next;
			}
		scorriP=scorriP->next;
	}

	printf("quale reperto si desidera analizzare?");
	scanf("%s", nomecercato);

	scorriP=t;
	while(!(scorriP->next==NULL)){
		if(trovato(scorriP->PAPR, nomecercato)){
			strcpy(Nome, nomecercato);
			return 1;}
		scorriP=scorriP->next;}
	return 0;
}


int LivelliGrigio(char NomeFile[], int livelli[]){ 

	BMP_Image im;
	int a,i,j,k,ok;
	int t=0;

	a=loadBMP(NomeFile, &im);
	if (a) {
		printf("impossibile aprire l’immagine (vedi sopra)\n");
		return -1;
	}
	for(i=0;i<DATA_DIM;i++){
		for(j=0;j<DATA_DIM;j++){
			ok=0;
			for(k=0;k<=t;k++){
			
				if(livelli[k]==im.data[i][j].grey){
					ok=1;
					break;}
			}
			if(!ok){
				livelli[t]=im.data[i][j].grey;
					t++;}
		}
	}
	printf("I livelli di grigio sono %d\n:", t);

	return t;

}



void GreyDistribution (char NomeFile[]){
	
	int count[DATA_DIM];
    int NUMMAX;
	int livelli[DATA_DIM]={-1};
	BMP_Image im;
	int a,j,x,i;
	a = loadBMP(NomeFile, &im);

	NUMMAX=LivelliGrigio(NomeFile, livelli);

	if(NUMMAX==-1) {printf("*ERRORE* durante elaborazione occorrenze\n"); return;}

        if (a==0){
            for(i=0; i<=NUMMAX; i++)
                for (j=0; j<DATA_DIM; j++)
                    for(x=0; x<DATA_DIM; x++)
                        if(  livelli[i] == im.data[j][x].grey  )
                            count[i]++;
			for(i=0; i<=NUMMAX; i++)
				printf("la sfumatura di grigio %d ricorre %d volte nell’immagine\n", livelli[i], count[i]);
		}else printf("Immagine non caricata correttamente\n");
}



void SchermataElaborazione(struct s_paziente* t){

	int OK,a,b;
	float area1, area2;
	struct s_reperto* reperto;
	struct s_paziente * pazientedaesaminare;
	pazientedaesaminare=NULL;
	int livelli[DATA_DIM]={-1};
	
	printf("***schermata elaborazione immagine***\n");
	printf("Si scelga una tra le seguenti opzioni:\n");
	printf("1. calcolare il numero di livelli di grigio\n");
	printf("2. calcolare la distribuzione dei livelli di grigio\n");
	printf("3. ridurre i livelli di grigio a 10 \n");
	printf("4. definire il contorno della zona informativa\n");
	printf("5. calcolare la dimensione dell'area informativa\n");
	printf("6. calcolare la dimensione dell'area chiara e di quella scura\n");
	printf("7. confrontare due immagini\n");
	scanf("%d",&OK);

	if(OK>=8 || OK<=0) {printf("Si inserisca un numero valido\n"); return;}
	else{
	
		if(OK==7){
			a=SchermataConfronto(t);
			if(a) return;
			else {printf("Schermata confronto chiusa senza successo\n"); return;}
		}
	
		else{
			do{
			CP(t,&pazientedaesaminare);
			}while(pazientedaesaminare==NULL);
			b=CercaRepertoConStampa(pazientedaesaminare,&reperto);

			switch(OK){
				case 1:
					b=LivelliGrigio(reperto->NomeDelFile, livelli);
					break;
				case 2:
					GreyDistribution (reperto->NomeDelFile);
					break;
				case 3:
					b=Livelli(reperto->NomeDelFile);
					break;
				case 4:
					b=CreaContorno(reperto->NomeDelFile) ;
					break;
				case 5:
					b= Area(reperto->NomeDelFile);
					break;
				default:
					b=ChiaroScuro(reperto->NomeDelFile,&area1,&area2);
					break;
			}
		}
	}
}



