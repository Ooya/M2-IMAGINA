#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <cmath>

using namespace std;

int moyenne4(int a, int b, int c, int d){
	return((a+b+c+d)/4);
}

int main(int argc, char* argv[]){
	char cNomImgLue[250], cNomImgOut[250];
	int nH, nW, nTaille, nR, nG, nB, S;

	if (argc != 3) {
		printf("Usage: ImageInRGB.ppm ImageYCbCr.ppm\n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgOut);

	OCTET *ImgIn, *ImgOut;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille3);

	//on convertit ImgInRGB en YCbCr
	for (int i = 0; i < nW; ++i){
		for (int j = 0; j < nW*3; j+=3){
			ImgOut[(i*nW*3)+j] = 0.299*ImgIn[(i*nW*3)+j] + 0.587*ImgIn[(i*nW*3)+j+1] + 0.114*ImgIn[(i*nW*3)+j+2];
			ImgOut[(i*nW*3)+j+1] = -0.16874*ImgIn[(i*nW*3)+j] - 0.33126*ImgIn[(i*nW*3)+j+1] + 0.5*ImgIn[(i*nW*3)+j+2];
			ImgOut[(i*nW*3)+j+2] = 0.5*ImgIn[(i*nW*3)+j] - 0.41869*ImgIn[(i*nW*3)+j+1] + 0.08131*ImgIn[(i*nW*3)+j+2];
		}
	}

	//écriture de l'image
	ecrire_image_ppm(cNomImgOut, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;
}