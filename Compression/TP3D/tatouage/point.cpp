#include "point.h"

Point::Point()
{

}

Point::Point(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Point::afficheP(){
    qDebug()<< "\t(" << this->x << ";" << this->y << ";" << this->z << ")";
}
