#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

using namespace std;

int moyenne4(int a, int b, int c, int d){
	return((a+b+c+d)/4);
}

int main(int argc, char* argv[]){
	char cNomImgLue[250], cNomImgEcriteR[250], cNomImgEcriteG[250], cNomImgEcriteB[250], cNomImgEcriteGA[250], cNomImgEcriteBA[250], cNomImgFin[250];
	int nH, nW, nTaille, nR, nG, nB, S;

	if (argc != 8) {
		printf("Usage: ImageIn.ppm R.ppm G.ppm B.ppm GA.ppm BA.ppm madmaxCompRGB.ppm\n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcriteR);
	sscanf (argv[3],"%s",cNomImgEcriteG);
	sscanf (argv[4],"%s",cNomImgEcriteB);
	sscanf (argv[5],"%s",cNomImgEcriteGA);
	sscanf (argv[6],"%s",cNomImgEcriteBA);
	sscanf (argv[7],"%s",cNomImgFin);

	OCTET *ImgIn, *ImgOutR, *ImgOutG, *ImgOutB, *ImgOutGA, *ImgOutBA, *ImgOutFin;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOutR, OCTET, nTaille3);
	allocation_tableau(ImgOutG, OCTET, nTaille3/4);
	allocation_tableau(ImgOutB, OCTET, nTaille3/4);
	allocation_tableau(ImgOutGA, OCTET, nTaille3);
	allocation_tableau(ImgOutBA, OCTET, nTaille3);
	allocation_tableau(ImgOutFin, OCTET, nTaille3);


	int g=0;
	int b=0;
	//on conserve le canal Rouge
	for (int i=0; i < nTaille3; i+=3){
		nR = ImgIn[i];
		// nG = ImgIn[i+1];
		// nB = ImgIn[i+2];
		ImgOutR[i]=nR;
		ImgOutR[i+1]=0;
		ImgOutR[i+2]=0;
	}
	//on diminue la taille des canaux Vert et Bleu
	for (int i=0; i < nH; i+=2){
		for(int j = 0; j<nW*3; j+=6){
			nG = moyenne4(ImgIn[(i*nW*3)+j+1],ImgIn[(i*nW*3)+j+4],ImgIn[((i+1)*nW*3)+j+1],ImgIn[((i+1)*nW*3)+j+4]);
			nB = moyenne4(ImgIn[(i*nW*3)+j+2],ImgIn[(i*nW*3)+j+5],ImgIn[((i+1)*nW*3)+j+2],ImgIn[((i+1)*nW*3)+j+5]);
			ImgOutG[g++]=0;
			ImgOutG[g++]=nG;
			ImgOutG[g++]=0;
			ImgOutB[b++]=0;
			ImgOutB[b++]=0;
			ImgOutB[b++]=nB;
		}
	}
	//on agrandit de nouveau les canaux Vert et Bleu
	int ga = 0;
	int ba = 0;
	for (int i = 0; i < nW; i+=2){
		for (int j = 0; j < (nW)*3; j+=6){
			//cout << i << "|" << j << " ";
			ImgOutGA[(i*nW*3)+j+1] = ImgOutG[((i/2)*(nW/2)*3)+(j/2)+1];
			ImgOutGA[(i*nW*3)+j+4] = ImgOutG[((i/2)*(nW/2)*3)+(j/2)+1];
			ImgOutGA[((i+1)*nW*3)+j+1] = ImgOutG[((i/2)*(nW/2)*3)+(j/2)+1];
			ImgOutGA[((i+1)*nW*3)+j+4] = ImgOutG[((i/2)*(nW/2)*3)+(j/2)+1];
			ImgOutBA[(i*nW*3)+j+2] = ImgOutB[((i/2)*(nW/2)*3)+(j/2)+2];
			ImgOutBA[(i*nW*3)+j+5] = ImgOutB[((i/2)*(nW/2)*3)+(j/2)+2];
			ImgOutBA[((i+1)*nW*3)+j+2] = ImgOutB[((i/2)*(nW/2)*3)+(j/2)+2];
			ImgOutBA[((i+1)*nW*3)+j+5] = ImgOutB[((i/2)*(nW/2)*3)+(j/2)+2];
		}
	}

	//on fusionne les 3 canaux R, GA et BA
	for (int i = 0; i < nW; ++i){
		for (int j = 0; j < nW*3; j+=3){
			ImgOutFin[(i*nW*3)+j] = ImgOutR[(i*nW*3)+j];
			ImgOutFin[(i*nW*3)+j+1] = ImgOutGA[(i*nW*3)+j+1];
			ImgOutFin[(i*nW*3)+j+2] = ImgOutBA[(i*nW*3)+j+2];
		}
	}

	ecrire_image_ppm(cNomImgEcriteR, ImgOutR,  nH, nW);
	ecrire_image_ppm(cNomImgEcriteG, ImgOutG,  nH/2, nW/2);
	ecrire_image_ppm(cNomImgEcriteB, ImgOutB,  nH/2, nW/2);
	ecrire_image_ppm(cNomImgEcriteGA, ImgOutGA,  nH, nW);
	ecrire_image_ppm(cNomImgEcriteBA, ImgOutBA,  nH, nW);
	ecrire_image_ppm(cNomImgFin, ImgOutFin,  nH, nW);
	free(ImgIn);
	return 1;
}