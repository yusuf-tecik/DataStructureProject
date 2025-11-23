#include "Star.h"
#include "Screen.h"
#include <cmath>

Star::Star(int x, int y, int height, char symbol, int z)
    : Shape(x, y, height, symbol, z)
{
}

Star::~Star()
{
}

int Star::getWidth() const
{
    // Çift sayıysa: Üst yarının en geniş yeri
    // Tek sayıysa: Tam ortası
    int half = height / 2;
    if (height % 2 == 0)
    {
        // Çiftse: Yükseklik 6 ise, yarısı 3. En geniş yer 2*2+1 = 5
        return 2 * (half - 1) + 1;
    }
    else
    {
        // Tekse: Yükseklik 5 ise, yarısı 2. En geniş yer 2*2+1 = 5
        return 2 * half + 1;
    }
}

void Star::draw(Screen *screen)
{
    int half = height / 2;
    bool isEven = (height % 2 == 0);

    for (int i = 0; i < height; i++)
    {
        int dist = 0;

        if (isEven)
        {
            // Çift yükseklik mantığı (Örn: 6)
            // Satırlar: 0, 1, 2 (Üst) | 3, 4, 5 (Alt)
            // 2 ve 3. satırlar en geniş (dist = 0) olmalı
            if (i < half)
                dist = (half - 1) - i; // Üst yarı
            else
                dist = i - half; // Alt yarı
        }
        else
        {
            // Tek yükseklik mantığı (Eski mantık)
            dist = i - half;
            if (dist < 0)
                dist = -dist;
        }

        // Genişlik hesabı (Çift ve tek için ortak formüle indirgendi)
        // En geniş halden (merkez), uzaklık kadar daralt
        int maxHalfWidth = isEven ? (half - 1) : half;
        int starCount = (2 * maxHalfWidth + 1) - (2 * dist);

        int startOffset = dist;

        for (int j = 0; j < starCount; j++)
        {
            screen->place(x + startOffset + j, y + i, symbol, z);
        }
    }
}