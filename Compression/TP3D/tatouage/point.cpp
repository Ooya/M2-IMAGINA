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
    qDebug()<< "x: " << this->x << " y: " << this->y << " z: " << this->z;
}
