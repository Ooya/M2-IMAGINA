#include <QString>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <sstream>
#include <QtMath>
#include "face.h"
#include "point.h"

#ifndef MAILLAGE_H
#define MAILLAGE_H

class Maillage
{
public:
    int nbS,nbF,nbA;
    double* tabSommets;
    int* tabFaces;

    QVector<Point> vPoints;
    QVector<Face> vFaces;

    Maillage();
    void lireMaillage(QString chemin);
    void ecrireMaillage(QString chemin);
    Point *calculG();
    void convSpherique();
    void convCart();
};

#endif // MAILLAGE_H
