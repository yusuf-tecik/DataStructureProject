#include "FileHandler.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Star.h"
#include <fstream>
#include <iostream>

using namespace std;

void FileHandler::saveToFile(DoubleList *list, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
        return;

    MainNode *tempMain = list->getHead();
    while (tempMain != nullptr)
    {
        file << "NODE" << endl; // Yeni bir ana düğüm başlangıcı

        ShapeNode *tempShape = tempMain->shapeList->getHead();
        while (tempShape != nullptr)
        {
            Shape *s = tempShape->data;
            // Format: SHAPE <type> <x> <y> <height> <symbol> <z> <width(sadece rect için)>
            // Biz basitlik için width'i de height ile aynı yerde tutabiliriz veya
            // Rectangle ise width'i ayrıca yazabiliriz ama okurken kolay olsun diye standart yapalım.
            // Rectangle'da width farklı olabiliyor, o yüzden onu özel alalım.

            int w = 0;
            if (s->getType() == 0) // Rectangle ise gerçek genişliğini alalım
                w = s->getWidth();
            else
                w = 0; // Diğerlerinde parametre olarak width yoktu, 0 geçelim.

            file << "SHAPE "
                 << s->getType() << " "
                 << s->getX() << " "
                 << s->getY() << " "
                 << s->getHeight() << " "      // Star ve Triangle için height yeterli
                 << (int)s->getSymbol() << " " // Char'ı int olarak yazalım güvenli olsun
                 << s->getZ() << " "
                 << w << endl; // Rectangle için width

            tempShape = tempShape->next;
        }
        tempMain = tempMain->next;
    }
    file.close();
}

void FileHandler::readFromFile(DoubleList *list, const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
        return;

    string line;
    MainNode *currentMain = nullptr;

    while (file >> line)
    {
        if (line == "NODE")
        {
            list->addNode();
            // Son eklenen düğümü bul (En sona eklediği için)
            currentMain = list->getHead();
            while (currentMain->next != nullptr)
                currentMain = currentMain->next;
        }
        else if (line == "SHAPE")
        {
            int type, x, y, h, z, w, symInt;
            file >> type >> x >> y >> h >> symInt >> z >> w;

            char symbol = (char)symInt;

            if (currentMain != nullptr)
            {
                if (type == 0) // Rectangle
                    currentMain->shapeList->add(new Rectangle(x, y, w, h, symbol, z));
                else if (type == 1)                                                // Triangle
                    currentMain->shapeList->add(new Triangle(x, y, h, symbol, z)); // Triangle'da w yok
                else if (type == 2)                                                // Star
                    currentMain->shapeList->add(new Star(x, y, h, symbol, z));     // Star'da w yok
            }
        }
    }
    file.close();
}