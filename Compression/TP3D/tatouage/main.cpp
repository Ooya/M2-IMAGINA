#include <QCoreApplication>
#include <QString>
#include "face.h"
#include "point.h"
#include "maillage.h"
#include "bin.h"

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "/home/thibaut/Dropbox/M2-IMAGINA/Compression/TP3D/";
    Maillage m;

    qDebug() << endl << "...lireMaillage()...";
    m.lireMaillage(path+"triceratops.off");

    qDebug() << endl << "...calculG()...";
    m.calculG();

    qDebug() << endl << "...convSpherique()...";
    m.convSpherique();

    qDebug() << endl << "...convCart()...";
    m.convCart();

    qDebug() << endl << "...ecrireMaillage()...";
    m.ecrireMaillage(path+"triceratopsTatoue.off");

    return a.exec();
}
