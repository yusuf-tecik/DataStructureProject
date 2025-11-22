#include "Shape.h"

// Kurucu fonksiyonun gövdesi
Shape::Shape(int x, int y, int height, char symbol, int z)
{
    this->x = x;
    this->y = y;
    this->height = height;
    this->symbol = symbol;
    this->z = z;
}

// Yıkıcı fonksiyon (Boş olsa bile yazmalıyız)
Shape::~Shape()
{
    // Şimdilik yapılacak özel bir temizlik yok
}

// Z değerini döndüren fonksiyon
int Shape::getZ() const
{
    return this->z;
}

// Hareket ettirme fonksiyonu
void Shape::move(int newX, int newY)
{
    this->x = newX;
    this->y = newY;
}