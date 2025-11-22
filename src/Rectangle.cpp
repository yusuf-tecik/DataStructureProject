#include "Rectangle.h"
#include "Screen.h" // Screen metodlarını kullanacağımız için ekledik

Rectangle::Rectangle(int x, int y, int width, int height, char symbol, int z)
    : Shape(x, y, height, symbol, z)
{
    this->width = width;
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(Screen *screen)
{
    // Dikdörtgenin alanı kadar döngü kurup her noktayı ekrana gönderiyoruz
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // x+j : Sütun (Yatay), y+i : Satır (Dikey)
            screen->place(x + j, y + i, symbol, z);
        }
    }
}