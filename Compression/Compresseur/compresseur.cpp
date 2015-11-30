#include <stdio.h>
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
#include <sstream>
#include <fstream>
#include <vector>
#include "image_ppm.h"

using namespace std;

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
	int nb = 0;
	int k = 0;
	nb = 0;
	for(i = 0; i < lignes; i++){
		for(j = 0; j < colonnes; j++){
			index = j * lignes + i;
			if(j > 0){
				indexmoinsun = j * lignes + (i-1);
				ImgOut[index] = ImgIn[index] - ImgIn[indexmoinsun] + 128;
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

int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite1[250], cNomImgEcrite2[250];
	int nH, nW, nTaille;
	int seuil;
	regex e ("(.*pgm)");
	regex f ("(.*ppm)");
	
	if (argc != 5) {
		printf("Usage: tauxComp ImageIn.pgm ImageQuadTree.pgm ImageQTPred.pgm \n"); 
		exit (1) ;
	}

	
	sscanf (argv[1],"%d",&seuil);
	sscanf (argv[2],"%s",cNomImgLue);
	sscanf (argv[3],"%s",cNomImgEcrite1);
	sscanf (argv[4],"%s",cNomImgEcrite2);

	//cout << cNomImgLue << endl << argv[2] << endl;

	if(regex_match(cNomImgLue,e)){
		cout << "Image en niveau de gris detectee..." << endl;
	} else if(regex_match(cNomImgLue,f)){
		cout << "Image en couleur detectee..." << endl;
	}
	
	OCTET *ImgIn, *ImgOut, *ImgInt1;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgInt1, OCTET, nTaille);
	allocation_tableau(ImgOut, OCTET, nTaille);

	cout << "QuadTree...." << endl;
	divRecursive(ImgIn, ImgInt1,0,0, nTaille, nH, nW, seuil);
	ecrire_image_pgm(cNomImgEcrite1, ImgInt1,  nH, nW);
	calcPSNR(ImgIn, ImgInt1, nH, nW);

	cout << "Prediction..." << endl;
	prediction(ImgInt1,ImgOut,nH,nW);
	calcPSNR(ImgInt1, ImgOut, nH, nW);
	ecrire_image_pgm(cNomImgEcrite2, ImgOut,  nH, nW);

	cout << "Compression Huffman..." << endl;
    // Build frequency table
    int frequencies[UniqueSymbols] = {0};
        for (int i = 0; i < nW; i++){
        for (int j = 0; j < nH; j++){
            frequencies[ImgIn[i*nW+j]]++;
        }
    }
    INode* root = BuildTree(frequencies);
    HuffCodeMap codes;
    GenerateCodes(root, HuffCode(), codes);
    delete root;
    stringstream ss;
    int cpt = 0;
    for (int i = 0; i < nW; i++){
        for (int j = 0; j < nH; j++){
            for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it){
                if(it->first == ImgOut[i*nW+j]){
                    for(int k =0; k< it->second.size();k++){
                        ss << it->second[k];
                    }
                }
            }
        }
    }
    string all = ss.str();
    vector<char> jeanVector;
    for (int i = 0; i < all.size(); i+=8){
        char c = strtol(all.substr(i,8).c_str(),0,2);
        jeanVector.push_back(c);
    }
    ofstream jeanFile("med5p.ouf");
    jeanExport(jeanVector, jeanFile);

	free(ImgIn);
	return 1;
}