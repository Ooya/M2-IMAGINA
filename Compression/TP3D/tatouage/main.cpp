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
    m.lireMaillage(path+"triceratops.off");
    m.ecrireMaillage(path+"triceratopsTatoue.off");

    return a.exec();
}
