#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[])
{
	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille;
	
	if (argc != 3) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
		exit (1) ;
	}
	
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);

	OCTET *ImgIn, *ImgOut;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }

	//255 = blanc;0 = noir;



	int min = 255;
	int max = 0;
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgIn[i*nW+j] < min){
				min = ImgIn[i*nW+j];
			} else if (ImgIn[i*nW+j] > max){
				max = ImgIn[i*nW+j];
			}
		}
	}
	cout << "min: " << min << " max: " << max << endl;
	float th = (max - min)/2;
	cout << "th " << th << endl;


	int tailleModule = 4;
	int nb = 0;
	//TODO
	for (int i=0; i < nH; i+=tailleModule){
		for (int j=0; j < nW; j+=tailleModule){
			for (int k = 0; k < tailleModule; k++){
				nb = 0;
				if ( ImgIn[i*nW+j+k] < th) {
					nb++;
				}		
			}
		}
	}

	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;
     
 }