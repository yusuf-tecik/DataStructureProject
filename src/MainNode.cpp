#include "MainNode.h"

MainNode::MainNode()
{
    this->shapeList = new ShapeList(); // Her ana düğümün kendi şekil listesi olur
    this->next = nullptr;
    this->prev = nullptr;
}

MainNode::~MainNode()
{
    // Ana düğüm silinirse, içindeki şekil listesi de silinmeli
    if (this->shapeList != nullptr)
    {
        delete this->shapeList;
    }
}