#include "maillage.h"

Maillage::Maillage()
{
}

void Maillage::lireMaillage(QString chemin){
    int nbLigne=0;

    int nbS,nbF,nbA;

    QFile file(chemin);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        nbLigne++;
        QString line = in.readLine();
        if(nbLigne == 1 && line=="OFF"){
            qDebug() << "Fichier OFF detecte !!!!!!!!!";
        }
        if(nbLigne == 2){
            qDebug() << line;
           // qDebug() << nbS << nbF << nbA;
        }
    }
}

void Maillage::ecrireMaillage(QString chemin){

}
