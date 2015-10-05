#include <stdio.h>
#include "bmp.h"
int CreaContorno(char[]);

int main() {

	char NomeDelFile[40];
	printf("N D F");
	printf("1");
	scanf("%s", NomeDelFile);
	printf("2");
	CreaContorno(NomeDelFile);
	return 0;
}
int CreaContorno(char NomeDelFile[]){
	printf("3");
	int a, i, j;
	BMP_Image im;
	printf("4");
	int soglia =3;
	printf("pre tutto");
	a = loadBMP(NomeDelFile, &im);
    if (a) {printf("impossibile aprire l’immagine (vedi sopra)"); return 0;}
printf("pre primo for");
	for(i=0;i<DATA_DIM;i++){
		j=0;
		while(im.data[i][j].grey<soglia && j<256){
			im.data[i][j].grey=0;
			j++;}
		im.data[i][j].grey=255;
	}
printf("pre secondo for");
	for(i=0;i<DATA_DIM;i++){
		j =255;
		while(im.data[i][j].grey<soglia && j>-1){
		   im.data[i][j].grey=0;
		    j--;}
		im.data[i][j].grey=255;
	}
printf("pre terzo for");
	for(j=0;j<DATA_DIM;j++){
		i=0;
		while(im.data[i][j].grey<soglia && j<256){
			im.data[i][j].grey=0;
			i++;}
		im.data[i][j].grey=255;
	}
printf("pre quarto for");
	for(j=0;j<DATA_DIM;j++){
		i=255;
		while(im.data[i][j].grey<soglia && j>-1){
		   im.data[i][j].grey=0;
		    i--;}
		im.data[i][j].grey=255;
	}
	printf("suka");
	saveBMP(im, "./modificate/contorno.bmp");
	printf("sukaprrr");
	return 1;	
}

