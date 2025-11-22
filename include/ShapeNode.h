#ifndef SHAPENODE_H
#define SHAPENODE_H

#include "Shape.h"

class ShapeNode
{
public:
    Shape *data;     // Vagonun taşıdığı yük (Şekil)
    ShapeNode *next; // Bir sonraki vagonun adresi

    // Kurucu
    ShapeNode(Shape *data);

    // Yıkıcı
    ~ShapeNode();
};

#endif