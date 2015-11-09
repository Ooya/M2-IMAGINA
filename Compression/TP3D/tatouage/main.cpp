#include <QCoreApplication>
#include <QString>
#include "face.h"
#include "point.h"
#include "maillage.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "/auto_home/tcastanie/Dropbox/M2-IMAGINA/Compression/TP3D/triceratops.off";
    Maillage m;
    m.lireMaillage(path);

    return a.exec();
}
