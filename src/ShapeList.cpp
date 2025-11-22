#include "ShapeList.h"
#include <iostream>

ShapeList::ShapeList()
{
    head = nullptr; // Liste başta boş
}

ShapeList::~ShapeList()
{
    // Listeyi temizlerken tüm düğümleri tek tek gezip siliyoruz
    ShapeNode *temp = head;
    while (temp != nullptr)
    {
        ShapeNode *nextNode = temp->next;
        delete temp; // Bu işlem Node'un içindeki Shape'i de siler (Node yıkıcısı sayesinde)
        temp = nextNode;
    }
}

void ShapeList::add(Shape *shape)
{
    ShapeNode *newNode = new ShapeNode(shape);

    if (head == nullptr) // Liste boşsa, ilk eleman bu olur
    {
        head = newNode;
    }
    else // Değilse, en sona kadar gidip oraya ekleriz
    {
        ShapeNode *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void ShapeList::drawAll(Screen *screen)
{
    ShapeNode *temp = head;
    while (temp != nullptr)
    {
        temp->data->draw(screen); // Şekle "Kendini bu ekrana çiz" diyoruz
        temp = temp->next;
    }
}

ShapeNode *ShapeList::getHead() const
{
    return head;
}