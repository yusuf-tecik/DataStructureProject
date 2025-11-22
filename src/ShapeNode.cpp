#include "ShapeNode.h"

ShapeNode::ShapeNode(Shape *data)
{
    this->data = data;
    this->next = nullptr; // İlk başta bir sonrakine bağlı değil
}

ShapeNode::~ShapeNode()
{
    // Düğüm silinince içindeki şekli de hafızadan siliyoruz
    if (data != nullptr)
    {
        delete data;
    }
}