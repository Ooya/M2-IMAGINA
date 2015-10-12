#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

class matrice{
public:
	int larg;
	int haut;
	int** mat;
	matrice(int larg, int haut){
		mat = new int*[larg];
		for(int i=0;i<larg;i++){
			mat[i] = new int[haut];
		}
		this->larg = larg;
		this->haut = haut;
	}

	void printMatrice(){
		for(int i=0;i<this->larg;i++){
			for(int j=0;j<this->haut;j++){
				cout<<this->mat[i][j]<<" ";
			}
			cout<<endl;
		}
	}
};

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

	//255 = blanc;0 = noir;



	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;

}