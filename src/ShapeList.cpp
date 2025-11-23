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

void ShapeList::remove(ShapeNode *node)
{
    if (head == nullptr || node == nullptr)
        return;

    // Eğer silinecek düğüm baştaki düğümse
    if (head == node)
    {
        head = head->next;
        // Node'un destructor'ı içindeki shape'i de siler
        delete node;
        return;
    }

    // Değilse, silinecek düğümün bir öncesini bul
    ShapeNode *prev = head;
    while (prev->next != nullptr && prev->next != node)
    {
        prev = prev->next;
    }

    // Bulduysak silme işlemini yap (Bağlantıyı kopar ve sil)
    if (prev->next == node)
    {
        prev->next = node->next;
        delete node;
    }
}

int ShapeList::getSize() const
{
    int count = 0;
    ShapeNode *temp = head;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}