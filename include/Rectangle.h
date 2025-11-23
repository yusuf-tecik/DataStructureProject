#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
// Rectangle.cpp içinde Screen.h'yi include edeceğiz, burada gerek yok ama draw imzası değişmeli.

class Rectangle : public Shape
{
private:
    int width;

public:
    Rectangle(int x, int y, int width, int height, char symbol, int z);
    ~Rectangle();

    // GÜNCELLEME
    void draw(Screen *screen) override;
    int getWidth() const override { return width; }
    int getType() const override { return 0; }
};

#endif