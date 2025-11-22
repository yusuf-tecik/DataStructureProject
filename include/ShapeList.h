#ifndef SHAPELIST_H
#define SHAPELIST_H

#include "ShapeNode.h"

class ShapeList
{
private:
    ShapeNode *head; // Listenin ilk elemanı

public:
    ShapeList();
    ~ShapeList();

    void add(Shape *shape);       // Listeye yeni şekil ekler
    void drawAll(Screen *screen); // Test için: Listedeki şekilleri çizer
    ShapeNode *getHead() const;
};

#endif