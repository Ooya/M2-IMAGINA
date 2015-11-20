#include <QCoreApplication>
#include <QString>
#include "face.h"
#include "point.h"
#include "maillage.h"

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

    qDebug() << endl << "...ecrireMaillage()...";
    m.ecrireMaillage(path+"triceratopsTatoue.off");

    //qDebug() << endl << "...convSpherique()...";

    //qDebug() << endl << "...convCart()...";

    return a.exec();
}
