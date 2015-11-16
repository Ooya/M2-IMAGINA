#include "maillage.h"

Maillage::Maillage()
{
}

void Maillage::lireMaillage(QString chemin){
    int nbLigne=0;


    QFile file(chemin);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        nbLigne++;
        QString line = in.readLine();
        if(nbLigne == 1 && line=="OFF"){
            qDebug() << "Fichier OFF detecte";
        }
        if(nbLigne == 2){
            QStringList list = line.split(" ");
            nbS = list[0].toInt();
            nbF = list[1].toInt();
            nbA = list[2].toInt();
            qDebug() << "L objet possede " << nbS  << " sommets, " << nbF << " faces et " << nbA << " aretes.";
            tabSommets = new double[nbS*3];
            tabFaces = new int[nbF*4];
        }
        if (nbLigne>2 && nbLigne<=nbS+2){
            QStringList iss = line.split(" ");
            double pt1, pt2, pt3;
            pt1 = iss[0].toDouble();
            pt2 = iss[1].toDouble();
            pt3 = iss[2].toDouble();
            tabSommets[3*(nbLigne-3)]=pt1;
            tabSommets[3*(nbLigne-3)+1]=pt2;
            tabSommets[3*(nbLigne-3)+2]=pt3;
        }
        if (nbLigne>nbS+2){
            QStringList iss = line.split(" ");
            int p1, p2, p3, nb;
            nb = iss[0].toInt();
            p1 = iss[1].toInt();
            p2 = iss[2].toInt();
            p3 = iss[3].toInt();
            tabFaces[3*(nbLigne-(nbLigne+3))]=p1;
            tabFaces[3*(nbLigne-(nbLigne+3))+1]=p2;
            tabFaces[3*(nbLigne-(nbLigne+3))+2]=p3;
        }
    }
    qDebug() << "Fichier .off lu et stocké";
}

void Maillage::ecrireMaillage(QString chemin){
    QFile file( chemin );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << "OFF" << endl;
        stream << nbS << " " << nbF << " " << nbA << endl;
        for(int i = 0; i<nbS*3; i+=3){
            stream << tabSommets[i] << " " << tabSommets[i+1] << " " << tabSommets[i+2] << endl;
        }
        for(int i = 0; i<nbF*4; i+=4){
            stream << tabFaces[i] << " " << tabFaces[i+1] << " " << tabFaces[i+2] << endl;
        }
    }
    qDebug() << "Fichier .off écrit";
}
