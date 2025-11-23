#include "Shape.h"
#include "Screen.h"

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
void Shape::move(int dx, int dy)
{
    // Ekran boyutlarını Screen.h'den alıyoruz (önceki adımda include etmiştik)
    // Eğer include "Screen.h" yoksa dosyanın başına ekle.

    int nextX = this->x + dx;
    int nextY = this->y + dy;

    int myWidth = this->getWidth(); // Artık genişliği biliyoruz!

    // KATI DUVAR KONTROLÜ:
    // Sol Duvar: nextX >= 0 olmalı
    // Sağ Duvar: nextX + genişlik <= SCREEN_WIDTH olmalı (Eşitlik sınıra değmeye izin verir)
    // Üst Duvar: nextY >= 0 olmalı
    // Alt Duvar: nextY + yükseklik <= SCREEN_HEIGHT olmalı

    bool xValid = (nextX >= 0) && (nextX + myWidth <= SCREEN_WIDTH);
    bool yValid = (nextY >= 0) && (nextY + height <= SCREEN_HEIGHT);

    if (xValid && yValid)
    {
        this->x = nextX;
        this->y = nextY;
    }
}