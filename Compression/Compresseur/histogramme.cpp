#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

//Ressort l'histogramme d'une image pgm
int main(int argc, char* argv[]){

	char cNomImgLue[250];
	int nH, nW, nTaille, cPixel, nb;
	
	if (argc != 2) {
		printf("Usage: ImageIn.pgm \n"); 
		exit (1) ;
	}
	
	sscanf (argv[1],"%s",cNomImgLue);
	
	OCTET *ImgIn;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	
	for(int i = 0; i< 256; i++){
		nb=0;
		for(int j = 0;j<nH;j++){
			for(int k = 0;k<nW;k++){
				cPixel = ImgIn[j*nW+k];
				if(cPixel==i){
					nb++;
				}
			}	
		}		
		cout << i << " " << nb << "\n";
	}
		
	//plot 'histoBaboon.dat' using 2 with lines lt 1, 'histoBaboon.dat' using 3 with lines lt 2, 'histoBaboon.dat' using 4 with lines lt 3
		
	
	free(ImgIn);
	return 1;

}