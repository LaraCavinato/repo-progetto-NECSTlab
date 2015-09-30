#include"gestione.h"
#include"bmp.h"

int livelli(char NomeFile[]){

	BMP_Image img, risultato;
	Pixel livelli[10] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225};
	short int ok;
	int i, j, k, a;
	a=loadBMP(NomeFile, &img);
	if (a) {printf("impossibile aprire l’immagine (vedi sopra)"); return 0;}
	
	memcpy(risultato.magic, img.magic, sizeof(unsigned char [2])); 
	risultato.header=img.header;
	risultato.info=img.info;
	memcpy(risultato.color_table, img.color_table, sizeof(Pixel [DATA_DIM][DATA_DIM]));
	
	if(loadBMP(NomeFile, &risultato)){
		printf("***caricamento immagine non riuscito***");
		return;}
		
	for(i=0;i<256;i++){
		for(j=0;j<256;j++){
			ok=1;k=9;
			do{
				if(img.data[i][j].grey>=livelli[k].grey) {risultato.data[i][j]=livelli[k]; ok=0;}
				else k--;
			}while(ok);
		}
	}
	saveBMP(risultato,"./modificate/livelli.bmp");
	return 1;
}



int Area (char NomeFile[]){
	int a, b, i, j, count=0;
	float area;
	BMP_Image im;
	a = CreaContorno(NomeFile);
	b = loadBMP("./modificate/contorno.bmp", &im);
	if (b) {printf("impossibile aprire l’immagine (vedi sopra)"); return 0;}
	if(a==1){
		for(i=0;i<DATA_DIM;i++)
		for(j=0;j<DATA_DIM;j++)
		if (im.data[i][j].grey==255)
			count++;
		printf("L’area dell’immagine significativa è di %d pixel", count);
		area = count*0,00625;
		printf("L’area è di %f mm^2", area);
		return 1;
	}
	else 
		{printf("CreaContorno non è andata a buon fine");
		return 0;} 
}



int ChiaroScuro(char NomeFile[], float* areaC, float* areaS){

	BMP_Image im;
	int th, tl, a, i, j, s=15;
	int countl=0, counth=0;

	a=loadBMP(NomeFile, &im);
	if (a) {printf("impossibile aprire l’immagine (vedi sopra)"); return 0;}
	
	for(i=0; i<DATA_DIM;i++){
		j=0;
		while (im.data[i][j].grey<s || j<256) {
			im.data[i][j].grey=128;    
			j++;}}
	for(i=0; i<DATA_DIM;i++){
		j=256;
		while (im.data[i][j].grey<s || j>-1) {
			im.data[i][j].grey=128;    
			j--;}}
	
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

	printf("L’area dell’immagine significativa molto chiara è di %d pixel", counth);
	printf("L’area dell’immagine significativa molto chiara è di %f mm^2", *areaC); 
	printf("L’area dell’immagine significativa molto scura è di %d pixel", countl);
	printf("L’area dell’immagine significativa molto scura è di %f mm^2", *areaS);

	saveBMP(im, "./modificate/ChiaroScuroBrutto.bmp");
	return 1;
}



void Confronta(char Nomefile1[], char Nomefile2[]){

	float area1C, area1S, area2C, area2S, scartoC, scartoS;

	ChiaroScuro(Nomefile1, &area1C, &area1S);
	ChiaroScuro(Nomefile2, &area2C, &area2S);

	scartoC=area1C-area2C;
	scartoS=area1S-area2S;
	
	printf("L’area chiara dall’ immagine %s all’immagine %s è cresciuta di: %f\n", Nomefile1, Nomefile2, scartoC);     
	printf("L’area scura  dall’ immagine %s all’immagine %s è cresciuta di: %f\n", Nomefile1, Nomefile2, scartoS);
}



int CreaContorno (char NomeFile[]) {
    int matrix[DATA_DIM][DATA_DIM];
    BMP_Image im;
    int a, i, j;    
    int soglia=15;

    a=loadBMP(NomeFile, &im);
    if (a) {printf("impossibile aprire l’immagine (vedi sopra)"); return 0;}
    else{
        memcpy(matrix, im.data, sizeof(Pixel [DATA_DIM][DATA_DIM]));
        
        // settiamo a -1 tutto quello che è all’esterno del contorno
        for(i=0;i<DATA_DIM;i++){
		    j=0;
		    while(matrix[i][j]<soglia){    
				matrix[i][j]=-1;
		    	j++;}}
        for(i=0;i<DATA_DIM;i++){
            j =255;
            while(matrix[i][j]<soglia){
                j--;
                matrix[i][j]=-1;}}
    
        //il contorno esterno a -1 viene annerito. tutto il resto diventa bianco.
        for(i=0;i<DATA_DIM;i++){
            for(i=0;j<DATA_DIM;j++){
                if (matrix[i][j]!=-1) matrix[i][j]=255;
                else matrix[i][j]=0;}}

        memcpy(im.data, matrix, sizeof(Pixel[DATA_DIM][DATA_DIM]));
        saveBMP(im, "./modificate/contorno.bmp");
    	return 1;
	}
}



int SchermataConfronto(struct s_paziente* t){
	int choice,a,b,c,d;
	char Nome[25];
	struct s_paziente* p; 
	struct s_reperto* r1;
	struct s_reperto* r2;
	CP(t, &p);
	a=CercaRepertoConStampa(p, &r1); 
	
	if (!a) return 0;

	printf("Come si desidera procedere?\n");
	printf("1. cercare un altro reperto inserendolo manualmente\n");
	printf("2.cercare un altro reperto appartenente allo stesso paziente\n");
	printf("3. cercare un altro reperto del medesimo livello di quello scelto inizialmente\n");
	printf("4. cercare un reperto adiacente a quello già in esame dello stesso paziente");
	scanf("%d", &choice);

	switch (choice) {
		case 1: 
	printf("\nScrivere il nome del reperto da confrontare");
	scanf("%s",Nome);
	Confronta(r1->NomeDelFile, Nome); 
		break;
		case 2:    
	b=CercaRepertoConStampa(p, &r2);  
	Confronta(r1->NomeDelFile, r2->NomeDelFile);     
		break;
		case 3:
	c=CercaStessoLivello(t, r1,Nome);    
	Confronta (r1->NomeDelFile, Nome);
		break;
		case 4:
	d=CercaSuccessivo(t,r1,Nome);
	Confronta(r1->NomeDelFile, Nome);
		break;
		default: printf("non riconosciuto");
		break;
	}
}



int CercaSuccessivo(struct s_paziente* p, struct s_reperto* r1, char Nome[]){
	short int ok;
	struct s_reperto* scorriR;
	char nomecercato[25];
	scorriR=p->PAPR;

	while(scorriR==NULL){           
		if( (r1->livello==(scorriR->livello)+1)   &&   (r1->piano==scorriR->piano)  ){
			printf("%s\t%d\t%c", scorriR->NomeDelFile, scorriR->livello, scorriR->piano); 
			printf("\n"); 
			scorriR=scorriR->next;}
	}

	printf("quale reperto si desidera analizzare?");
	scanf("%s", nomecercato);

	ok=trovato(p->PAPR, nomecercato);                   
	if(ok) {
		strcpy(Nome ,nomecercato); 
		return 1;
	} 
	else {printf("il seguente reperto non esiste in questo paziente"); return 0;}
}



int CercaStessoLivello(struct s_paziente* p, struct s_reperto* r1, char Nome[]){
	struct s_paziente* scorriP;
	struct s_reperto* scorriR;
	char nomecercato [25];
	
	scorriP=p;
	scorriR=p->PAPR;

	while (scorriP==NULL){
		while(scorriR==NULL){ 
			if (scorriR->livello==r1->livello && scorriR->piano==r1->piano)     
			printf("%s\n", scorriR->NomeDelFile);
			scorriR=scorriR->next;}
		scorriP=scorriP->next;
	}

	printf("quale reperto si desidera analizzare?");
	scanf("%s", nomecercato);

	scorriP=p;
	while(!(scorriP->next==NULL)){
		if(trovato(scorriP->PAPR, nomecercato)){ 
			strcpy(Nome, nomecercato); 
			return 1;}
		scorriP=scorriP->next;}
	return 0;
}

//-----------------
/*
int LivelliGrigio(char NomeFile[]){

	BMP_Image im;
	int a,i,j,k,ok;
	int t=1;
	int livelli[256] = {-1};

	a=loadBMP(NomeFile, &im); 
	if (a) {printf("impossibile aprire l’immagine (vedi sopra)"); return 0;}

	for(i=0;i<DATA_DIM;i++){
		for(j=0;j<DATA_DIM;j++){
			ok=1;
			for(k=0;k<t;k++) {
				if(livelli[k]==im.data[i][j].grey){
					ok=0;
					break;}
			}
	if(ok){
		livelli[t-1]=im.data[i][j].grey;
		t++;}}}
	
	for(k=0;k<t;k++){
		printf("%d\n",livelli[k]);}

	return t-1;                    

    else{
        printf("L'immagine non è stata aperta correttamente\n");  
        return -1;}
}



void GreyDistribution (char NomeFile[], int* array, int NUMMAX, int count[]){

	BMP_Image im;
	int a,j,x,i;
	a = loadBMP(NomeFile, &im);

	if (a==0){
	for(i=0; i<=NUMMAX; i++)
	for (j=0; j<DATA_DIM; j++){
	for(x=0; x<DATA_DIM; x++)
	if(  array[i] == im.data[j][x].grey  )
	count[i]++;
	printf("la sfumatura di grigio %d ricorre %d volte nell’immagine", array[i], count[i]);
	}

	}

	else printf ("Immagine non caricata correttamente");
}
*/


void SchermataElaborazione(struct s_paziente* t){

	int OK,a,b;
	float area1, area2;
	struct s_reperto* reperto;                
	struct s_paziente * pazientedaesaminare;

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

	if(OK==7){
		a=SchermataConfronto(t);
	if(a)
		return;
	else {printf("schermata confronto chiusa senza successo"); return;}
	}
	
	CP(t,&pazientedaesaminare);
	b=CercaRepertoConStampa(pazientedaesaminare,&reperto);

	switch(OK){
		case 1:
			/*b= LivelliGrigio(reperto->NomeDelFile);*/
		break;
		case 2:
			/*GreyDistribution(reperto->NomeDelFile, array, NUMMAX, count[]);*/ 
		case 3:
			b=livelli(reperto->NomeDelFile);
		break;
		case 4:
			b=CreaContorno(reperto->NomeDelFile) ;
		break;
		case 5:
			b= Area(reperto->NomeDelFile);
		break;
		case 6:
			b=ChiaroScuro(reperto->NomeDelFile,&area1,&area2);
		break;
		default:
			printf("Si inserisca un numero valido\n");
		break;
	}
}

