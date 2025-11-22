#ifndef SCREEN_H
#define SCREEN_H

// Sabit ekran boyutları
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

class Screen
{
private:
    char data[SCREEN_HEIGHT][SCREEN_WIDTH];   // Karakterlerin tutulduğu matris
    int zBuffer[SCREEN_HEIGHT][SCREEN_WIDTH]; // Derinlik bilgisinin tutulduğu matris

public:
    Screen();

    // Ekranı temizler (Her döngü başında çağrılır)
    void clear();

    // Bir noktaya karakter koyar (Ama sadece Z değeri daha yüksekse!)
    void place(int x, int y, char symbol, int z);

    // Matrisi ekrana basar
    void print();
};

#endif