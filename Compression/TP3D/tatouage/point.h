#include <QDebug>

#ifndef POINT_H
#define POINT_H

class Point
{
public:
    float x, y, z;
    Point();
    Point(float x, float y, float z);
    void afficheP();
};

#endif // POINT_H
