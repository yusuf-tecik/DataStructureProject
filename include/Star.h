#ifndef STAR_H
#define STAR_H

#include "Shape.h"

class Star : public Shape
{
public:
    // Yıldız için de genişlik parametresine gerek yok, yüksekliğe göre hesaplayacağız.
    Star(int x, int y, int height, char symbol, int z);
    ~Star();

    void draw(Screen *screen) override;
    int getWidth() const override;
    int getType() const override { return 2; }
};

#endif