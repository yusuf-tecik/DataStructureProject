#ifndef MAINNODE_H
#define MAINNODE_H

#include "ShapeList.h"

class MainNode
{
public:
    ShapeList *shapeList; // Bu kutunun içindeki şekiller listesi
    MainNode *next;       // Sonraki düğüm (Aşağıdaki kutu)
    MainNode *prev;       // Önceki düğüm (Yukarıdaki kutu)

    MainNode();
    ~MainNode();
};

#endif