#include "Triangle.h"
#include "Screen.h"

Triangle::Triangle(int x, int y, int height, char symbol, int z)
    : Shape(x, y, height, symbol, z)
{
}

Triangle::~Triangle()
{
}

int Triangle::getWidth() const
{
    // Piramit taban genişliği formülü: (2 * yükseklik) - 1
    return 2 * height - 1;
}

void Triangle::draw(Screen *screen)
{
    // Eşkenar Üçgen (Piramit) Çizimi
    //      * (1. satır, 1 yıldız)
    //     *** (2. satır, 3 yıldız)
    //    ***** (3. satır, 5 yıldız)

    for (int i = 0; i < height; i++)
    {
        // Yıldız sayısı: 2*i + 1
        // Başlangıç ötelemesi (boşluk): height - 1 - i

        int startOffset = height - 1 - i;
        int starCount = 2 * i + 1;

        for (int j = 0; j < starCount; j++)
        {
            screen->place(x + startOffset + j, y + i, symbol, z);
        }
    }
}