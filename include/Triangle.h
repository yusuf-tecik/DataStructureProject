#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
public:
    // Üçgenin sadece yüksekliği olur (tabanı yüksekliğe göre hesaplanır), genişlik parametresine gerek yok
    Triangle(int x, int y, int height, char symbol, int z);
    ~Triangle();

    // Shape sınıfından gelen "çiz" emrini kendine göre uygulayacak
    void draw(Screen *screen) override;
    // draw fonksiyonunun altına:
    int getWidth() const override;
    int getType() const override { return 1; }
};

#endif