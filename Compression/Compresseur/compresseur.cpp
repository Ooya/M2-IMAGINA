#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <regex>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "image_ppm.h"
#include "huffman.h"
#include "huffman.c"

using namespace std;

/*
const int UniqueSymbols = 1 << CHAR_BIT;

typedef std::vector<bool> HuffCode;
typedef std::map<char, HuffCode> HuffCodeMap;

class INode
{
public:
	const int f;

	virtual ~INode() {}

protected:
	INode(int f) : f(f) {}
};

class InternalNode : public INode
{
public:
	INode *const left;
	INode *const right;

	InternalNode(INode* c0, INode* c1) : INode(c0->f + c1->f), left(c0), right(c1) {}
	~InternalNode()
	{
		delete left;
		delete right;
	}
};

class LeafNode : public INode
{
public:
	const char c;

	LeafNode(int f, char c) : INode(f), c(c) {}
};

struct NodeCmp
{
	bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};

INode* BuildTree(const int (&frequencies)[UniqueSymbols])
{
	std::priority_queue<INode*, std::vector<INode*>, NodeCmp> trees;

	for (int i = 0; i < UniqueSymbols; ++i)
	{
		if(frequencies[i] != 0)
			trees.push(new LeafNode(frequencies[i], (char)i));
	}
	while (trees.size() > 1)
	{
		INode* childR = trees.top();
		trees.pop();

		INode* childL = trees.top();
		trees.pop();

		INode* parent = new InternalNode(childR, childL);
		trees.push(parent);
	}
	return trees.top();
}

void GenerateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes)
{
	if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
	{
		outCodes[lf->c] = prefix;
	}
	else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
	{
		HuffCode leftPrefix = prefix;
		leftPrefix.push_back(false);
		GenerateCodes(in->left, leftPrefix, outCodes);

		HuffCode rightPrefix = prefix;
		rightPrefix.push_back(true);
		GenerateCodes(in->right, rightPrefix, outCodes);
	}
}
*/
long GetFileSize( FILE *f ){
	long pos, size;

	pos = ftell( f );
	fseek( f, 0, SEEK_END );
	size = ftell( f );
	fseek( f, pos, SEEK_SET );

	return size;
}

int ReadWord32( FILE *f )
{
	unsigned char buf[4];
	fread( buf, 4, 1, f );
	return (((unsigned int)buf[0])<<24) +
	(((unsigned int)buf[1])<<16) +
	(((unsigned int)buf[2])<<8)  +
	(unsigned int)buf[3];
}

void WriteWord32( int x, FILE *f )
{
	fputc( (x>>24)&255, f );
	fputc( (x>>16)&255, f );
	fputc( (x>>8)&255, f );
	fputc( x&255, f );
}

void drawCarre(OCTET *ImgOut, int xHG, int yHG, int taille, int couleur){
	for(int i=xHG; i< xHG+taille;i++){
		for(int j=yHG; j<yHG+taille;j++){
			ImgOut[i*512+j] = couleur;
		}
	}
}

void divRecursive(OCTET *ImgIn, OCTET *ImgOut,int x,int y, int nTaille, int nH, int nW, int seuil){
	int somme1=0;
	int somme2=0;
	int somme3=0;
	int somme4=0;

	for (int i=x; i < x+nH; i++){
		for (int j=y; j < y+nW; j++){
			if (j<y+(nW/2) && i<x+(nH/2)){
				somme1 += ImgIn[i*512+j];
			}
			else if (j>=y+(nW/2) && i<x+(nH/2)){
				somme2 += ImgIn[i*512+j];
			}
			else if (j<y+(nW/2) && i>=x+(nH/2)){
				somme3 += ImgIn[i*512+j];
			}
			else if (j>=y+(nW/2) && i>=x+(nH/2)){
				somme4 += ImgIn[i*512+j];
			}
		}
	}

	int moyenne1 = somme1/(nTaille/4);
	int moyenne2 = somme2/(nTaille/4);
	int moyenne3 = somme3/(nTaille/4);
	int moyenne4 = somme4/(nTaille/4);

	drawCarre(ImgOut, x,y,nH/2,moyenne1);
	drawCarre(ImgOut, x,y+(nH/2),nH/2,moyenne2);
	drawCarre(ImgOut, x+(nH/2),y,nH/2,moyenne3);
	drawCarre(ImgOut, x+(nH/2),y+(nW/2),nH/2,moyenne4);

	float variance1 = 0.0;
	float variance2 = 0.0;
	float variance3 = 0.0;
	float variance4 = 0.0;

	for (int i=x; i < x+nH; i++){
		for (int j=y; j < y+nW; j++){
			if (j<y+(nW/2) && i<x+(nH/2)){
				variance1 += pow(ImgIn[i*512+j] - moyenne1,2);
			}
			else if (j>=y+(nW/2) && i<x+(nH/2)){
				variance2 += pow(ImgIn[i*512+j] - moyenne2,2);
			}
			else if (j<y+(nW/2) && i>=x+(nH/2)){
				variance3 += pow(ImgIn[i*512+j] - moyenne3,2);
			}
			else if (j>=y+(nW/2) && i>=x+(nH/2)){
				variance4 += pow(ImgIn[i*512+j] - moyenne4,2);
			}
		}
	}
	variance1 /= (nTaille/4);
	variance2 /= (nTaille/4);
	variance3 /= (nTaille/4);
	variance4 /= (nTaille/4);
	//cout << "Variances : " << variance1 << " " << variance2 << " " << variance3 << " " << variance4 << endl;


	if(sqrt(variance1) > seuil){
		divRecursive(ImgIn, ImgOut,x,y,nTaille/4,nH/2,nW/2,seuil);
	}
	if(sqrt(variance2) > seuil){
		divRecursive(ImgIn, ImgOut,x,y+(nW/2),nTaille/4,nH/2,nW/2,seuil);
	}
	if(sqrt(variance3) > seuil){
		divRecursive(ImgIn, ImgOut,x+(nH/2),y,nTaille/4,nH/2,nW/2,seuil);
	}
	if(sqrt(variance4) > seuil){
		divRecursive(ImgIn, ImgOut,x+(nH/2),y+(nW/2),nTaille/4,nH/2,nW/2,seuil);
	}
}

void prediction(OCTET *ImgIn, OCTET *ImgOut, int lignes, int colonnes) {
	int i, j, index, indexmoinsun;
	int k = 0;
	for(i = 0; i < lignes; i++){
		for(j = 0; j < colonnes; j++){
			index = j * lignes + i;
			if(j > 0){
				indexmoinsun = j * lignes + (i-1);
				ImgOut[index] = ImgIn[index] - ImgIn[indexmoinsun] + 128;
			}else{
				ImgOut[index] = 128;//200 - 190 -> 10+128(138); 200 - 210 -> -10+128(118)
			}
		}
	}
}

void deprediction(OCTET *ImgIn, OCTET *ImgOut, int lignes, int colonnes){
	int i, j, index, indexmoinsun;
	int k = 0;
	for(i = 0; i < lignes; i++){
		for(j = 0; j < colonnes; j++){
			index = j * lignes + i;
			if(j > 0){
				indexmoinsun = j * lignes + (i-1);
				ImgOut[index] = ImgIn[indexmoinsun] + (ImgIn[index]);
			}else{
				ImgOut[index] = 128;
			}
		}
	}
}

void calcPSNR(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW){
	//calcul du PSNR
	float somme = 0.0f;
	for(int i = 0; i< nW; i++){
		for(int j = 0; j<nH;j++){
			somme += pow(ImgIn[(i*nW)+j] - ImgOut[(i*nW)+j],2);
		}
	}
	float EQM = somme/(nW*nH);
	float PSNR = 10*log10(pow(255,2)/EQM);
	cout << "PSNR: " << PSNR << endl;
}

void jeanExport(vector<char> jeanVector, ostream& stream){
	for(auto i : jeanVector){
		stream << i;
	}
}

void stringExport(vector<string> jeanVector, ostream& stream){
	for(auto i : jeanVector){
		stream << i;
	}
}

int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite1[250], cNomImgEcrite2[250], cNomImgComp[250], cNomImgDecomp[250];
	int nH, nW, nTaille;
	int seuil;
	regex regPGM ("(.*pgm)");
	regex regPPM ("(.*ppm)");
	
	if (argc != 7) {
		printf("Usage: tauxComp(5) Image.pgm QuadTree.pgm QTPred.pgm comp.ouf decomp.ouf\n"); 
		exit (1) ;
	}

	bool isGris;
	
	sscanf (argv[1],"%d",&seuil);
	sscanf (argv[2],"%s",cNomImgLue);
	sscanf (argv[3],"%s",cNomImgEcrite1);
	sscanf (argv[4],"%s",cNomImgEcrite2);
	sscanf (argv[5],"%s",cNomImgComp);
	sscanf (argv[6],"%s",cNomImgDecomp);

	if(regex_match(cNomImgLue,regPGM)){
		cout << "Image en niveau de gris detectee..." << endl << endl;
		isGris = true;
	} else if(regex_match(cNomImgLue,regPPM)){
		cout << "Image en couleur detectee..." << endl;
		isGris = false;
	}

	if(isGris){
		OCTET *ImgIn, *ImgOut, *ImgInt1, *ImgIn2;

		lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;

		allocation_tableau(ImgIn, OCTET, nTaille);
		lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
		allocation_tableau(ImgInt1, OCTET, nTaille);
		allocation_tableau(ImgOut, OCTET, nTaille);

		cout << "QuadTree...." << endl;
		divRecursive(ImgIn, ImgInt1,0,0, nTaille, nH, nW, seuil);
		ecrire_image_pgm(cNomImgEcrite1, ImgInt1,  nH, nW);

		cout << endl << "Prediction..." << endl;
		prediction(ImgInt1,ImgOut,nH,nW);
	//calcPSNR(ImgInt1, ImgOut, nH, nW);
		ecrire_image_pgm(cNomImgEcrite2, ImgOut,  nH, nW);

		cout << endl << "Compression..." << endl;
		FILE *f;
		unsigned char *in, *out, command, algo=0;
		unsigned int  insize, outsize=0, *work;
		char *inname, *outname;

    /* Open input file */
		f = fopen( cNomImgEcrite1, "rb" );
		if( !f )
		{
			printf( "Unable to open input file \"%s\".\n", cNomImgEcrite1 );
			return 0;
		}

    /* Get input file size */
		insize = GetFileSize( f );

	/* Read input file */
		printf( "Fichier entree : %d bits\n", insize );
		in = (unsigned char *) malloc( insize );
		if( !in ) {
			printf( "Not enough memory\n" );
			fclose( f );
			return 0;
		}
		fread( in, insize, 1, f );
		fclose( f );

	/* Open output file */
		f = fopen( cNomImgComp, "wb" );
		if( !f )
		{
			printf( "Unable to open output file \"%s\".\n", cNomImgComp );
			free( in );
			return 0;
		}

	/* Write header */
		WriteWord32( insize, f );

		outsize = (insize*104+50)/100 + 384;

		out = (unsigned char *) malloc( outsize );
		if( !out )
		{
			printf( "Not enough memory\n" );
			fclose( f );
			free( in );
			return 0;
		}

		outsize = Huffman_Compress( in, out, insize );
		printf( "Fichier compresse : %d bits (%.1f%%)\n", outsize,100*(float)outsize/(float)insize );
		fwrite( out, outsize, 1, f );
		fclose( f );
		cout << "=== Compression faite ===" << endl;

		cout << endl << "Décompression ..." << endl;

	//input file
		f = fopen( cNomImgComp, "rb" );
		if( !f )
		{
			printf( "Unable to open input file \"%s\".\n", cNomImgComp );
			return 0;
		}
	/* Get input file size */
		insize = GetFileSize( f );

		outsize = ReadWord32( f );
		insize -= 12;

	/* Read input file */
		printf( "Fichier entree compresse : %d bits\n", insize+8 );
		in = (unsigned char *) malloc( insize );
		if( !in )
		{
			printf( "Not enough memory\n" );
			fclose( f );
			return 0;
		}
		fread( in, insize, 1, f );
		fclose( f );
		printf( "Fichier decompressé : %d bits\n", outsize );

    /* Open output file */
		f = fopen( cNomImgDecomp, "wb" );
		if( !f )
		{
			printf( "Unable to open output file \"%s\".\n", cNomImgDecomp );
			free( in );
			return 0;
		}

    /* Allocate memory for output buffer */
		out = (unsigned char *) malloc( outsize );
		if( !out )
		{
			printf( "Not enough memory\n" );
			fclose( f );
			free( in );
			return 0;
		}

		Huffman_Uncompress( in, out, insize, outsize );
		fwrite( out, outsize, 1, f );
		fclose( f );
		cout << "=== Décompression faite ===" << endl << endl;
		free( in );
		free(out);


		calcPSNR(ImgIn, ImgInt1, nH, nW);



	// string all = ss.str();
	// vector<char> jeanVector;
	// for (int i = 0; i < all.size(); i+=8){
	// 	char c = strtol(all.substr(i,8).c_str(),0,2);
	// 	jeanVector.push_back(c);
	// }
	// ofstream jeanFile("med5p.ouf");
	// jeanExport(jeanVector, jeanFile);

	// ofstream rleFile("RLEfile.txt");
	// stringExport(vRLE, rleFile);


		free(ImgIn);

	}//end gris
	else if(!isGris){

		int nR, nG, nB, S;
		char imgR[] = "jackR";
		char imgG[] = "jackG";
		char imgB[] = "jackB";
		char imgQTR[] = "jackQTR";
		char imgQTG[] = "jackQTG";
		char imgQTB[] = "jackQTB";

		OCTET *ImgIn, *ImgOutR, *ImgOutG, *ImgOutB, *ImgOutQTR, *ImgOutQTG, *ImgOutQTB, *ImgOutQT;

		lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
		nTaille = nH * nW;

		int nTaille3 = nTaille * 3;
		allocation_tableau(ImgIn, OCTET, nTaille3);
		lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
		allocation_tableau(ImgOutR, OCTET, nTaille);
		allocation_tableau(ImgOutG, OCTET, nTaille);
		allocation_tableau(ImgOutB, OCTET, nTaille);
		allocation_tableau(ImgOutQTR, OCTET, nTaille);
		allocation_tableau(ImgOutQTG, OCTET, nTaille);
		allocation_tableau(ImgOutQTB, OCTET, nTaille);
		allocation_tableau(ImgOutQT, OCTET, nTaille3);

		cout << endl << "separation des images RGB.." << endl;

		for (int i=0; i < nTaille3; i+=3){
			nR = ImgIn[i];
			nG = ImgIn[i+1];
			nB = ImgIn[i+2];
			ImgOutR[i/3]=nR;
			ImgOutG[i/3]=nG;
			ImgOutB[i/3]=nB;
		}

		ecrire_image_pgm(imgR, ImgOutR,  nH, nW);
		ecrire_image_pgm(imgG, ImgOutG,  nH, nW);
		ecrire_image_pgm(imgB, ImgOutB,  nH, nW);

		cout << endl << "Quadtree sur chaque image R-G-B" << endl;

		divRecursive(ImgOutR, ImgOutQTR,0,0, nTaille, nH, nW, seuil);
		divRecursive(ImgOutG, ImgOutQTG,0,0, nTaille, nH, nW, seuil);
		divRecursive(ImgOutB, ImgOutQTB,0,0, nTaille, nH, nW, seuil);
		ecrire_image_pgm(imgQTR, ImgOutQTR,  nH, nW);
		ecrire_image_pgm(imgQTG, ImgOutQTG,  nH, nW);
		ecrire_image_pgm(imgQTB, ImgOutQTB,  nH, nW);

		cout << endl << "Fusion des trois images" << endl;

		//on fusionne les 3 canaux R, GA et BA
		for (int i = 0; i < nTaille3; i+=3){
			ImgOutQT[i] = ImgOutQTR[i/3];
			ImgOutQT[i+1] = ImgOutQTG[i/3];
			ImgOutQT[i+2] = ImgOutQTB[i/3];
		}

		ecrire_image_ppm(cNomImgEcrite1, ImgOutQT, nH, nW);

		remove(imgR);
		remove(imgG);
		remove(imgB);
		remove(imgQTR);
		remove(imgQTG);
		remove(imgQTB);

		cout << endl << "Compression Huffman ..." << endl;

		FILE *f;
		unsigned char *in, *out, command, algo=0;
		unsigned int  insize, outsize=0, *work;
		char *inname, *outname;

    /* Open input file */
		f = fopen( cNomImgEcrite1, "rb" );
		if( !f )
		{
			printf( "Unable to open input file \"%s\".\n", cNomImgEcrite1 );
			return 0;
		}

    /* Get input file size */
		insize = GetFileSize( f );

	/* Read input file */
		printf( "Fichier entree : %d bits\n", insize );
		in = (unsigned char *) malloc( insize );
		if( !in ) {
			printf( "Not enough memory\n" );
			fclose( f );
			return 0;
		}
		fread( in, insize, 1, f );
		fclose( f );

	/* Open output file */
		f = fopen( cNomImgComp, "wb" );
		if( !f )
		{
			printf( "Unable to open output file \"%s\".\n", cNomImgComp );
			free( in );
			return 0;
		}

	/* Write header */
		WriteWord32( insize, f );

		outsize = (insize*104+50)/100 + 384;

		out = (unsigned char *) malloc( outsize );
		if( !out )
		{
			printf( "Not enough memory\n" );
			fclose( f );
			free( in );
			return 0;
		}

		outsize = Huffman_Compress( in, out, insize );
		printf( "Fichier compresse : %d bits (%.1f%%)\n", outsize,100*(float)outsize/(float)insize );
		fwrite( out, outsize, 1, f );
		fclose( f );
		cout << "=== Compression faite ===" << endl;

		cout << endl << "Décompression ..." << endl;

	//input file
		f = fopen( cNomImgComp, "rb" );
		if( !f )
		{
			printf( "Unable to open input file \"%s\".\n", cNomImgComp );
			return 0;
		}
	/* Get input file size */
		insize = GetFileSize( f );

		outsize = ReadWord32( f );
		insize -= 12;

	/* Read input file */
		printf( "Fichier entree compresse : %d bits\n", insize+8 );
		in = (unsigned char *) malloc( insize );
		if( !in )
		{
			printf( "Not enough memory\n" );
			fclose( f );
			return 0;
		}
		fread( in, insize, 1, f );
		fclose( f );
		printf( "Fichier decompressé : %d bits\n", outsize );

    /* Open output file */
		f = fopen( cNomImgDecomp, "wb" );
		if( !f )
		{
			printf( "Unable to open output file \"%s\".\n", cNomImgDecomp );
			free( in );
			return 0;
		}

    /* Allocate memory for output buffer */
		out = (unsigned char *) malloc( outsize );
		if( !out )
		{
			printf( "Not enough memory\n" );
			fclose( f );
			free( in );
			return 0;
		}

		Huffman_Uncompress( in, out, insize, outsize );
		fwrite( out, outsize, 1, f );
		fclose( f );
		cout << "=== Décompression faite ===" << endl << endl;
		free( in );
		free(out);


		calcPSNR(ImgIn, ImgOutQT, nH*3, nW);

		free(ImgIn);
		
	}//end couleur


	return 1;
}