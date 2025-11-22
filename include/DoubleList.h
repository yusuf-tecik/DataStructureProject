#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include "MainNode.h"

class DoubleList
{
private:
    MainNode *head; // Listenin başı (En üstteki kutu)

public:
    DoubleList();
    ~DoubleList();

    void addNode();               // Yeni bir ana düğüm (kutu) ekle
    void drawAll(Screen *screen); // Tüm kutuları ve içindekileri yazdır (Test için)

    // İleride buraya aşağı/yukarı gitme fonksiyonları da gelecek
    MainNode *getHead() const;
};

#endif