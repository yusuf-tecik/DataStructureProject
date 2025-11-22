#include "DoubleList.h"
#include <iostream>

using namespace std;

DoubleList::DoubleList()
{
    head = nullptr;
}

DoubleList::~DoubleList()
{
    MainNode *temp = head;
    while (temp != nullptr)
    {
        MainNode *nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
}

void DoubleList::addNode()
{
    MainNode *newNode = new MainNode();

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        MainNode *temp = head;
        // En sona kadar git
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        // Bağlantıları kur (Çift yönlü)
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void DoubleList::drawAll(Screen *screen)
{
    MainNode *temp = head;
    while (temp != nullptr)
    {
        temp->shapeList->drawAll(screen); // İç listeye "Çiz" emrini iletiyoruz
        temp = temp->next;
    }
}

MainNode *DoubleList::getHead() const
{
    return head;
}