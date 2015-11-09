#include "point.h"

#ifndef FACE_H
#define FACE_H

class Face
{
public:
    Point a, b, c;
    Face();
    Face(Point a, Point b, Point c);
};

#endif // FACE_H
