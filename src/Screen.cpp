#include "Screen.h"
#include <iostream>
#include <cstdlib> // system("cls") için

using namespace std;

Screen::Screen()
{
    clear();
}

void Screen::clear()
{
    // Tüm ekranı boşlukla, Z değerlerini de en küçük sayıyla (-1) doldur
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            data[i][j] = ' ';   // Boşluk
            zBuffer[i][j] = -1; // En arkadaki değer
        }
    }
}

void Screen::place(int x, int y, char symbol, int z)
{
    // Sınır kontrolü: Ekran dışına taşarsa çizme
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;

    // Z-Buffer Kontrolü:
    // Eğer yeni gelen şeklin Z değeri (z), oradaki mevcut Z değerinden (zBuffer[y][x])
    // büyük veya eşitse, o karakterin üzerine yaz.
    if (z >= zBuffer[y][x])
    {
        data[y][x] = symbol;
        zBuffer[y][x] = z; // Yeni Z değerini kaydet
    }
}

void Screen::print()
{
    // İmleci başa al (Ekranı temizlemeden üzerine yazmak titremeyi azaltır)
    // Ancak ödevde system("cls") genelde istenir, basitlik için onu kullanıyoruz.
    system("cls");

    // Üst çerçeve (Opsiyonel ama şık durur)
    for (int k = 0; k < SCREEN_WIDTH + 2; k++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        cout << "|"; // Sol kenar
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            cout << data[i][j];
        }
        cout << "|" << endl; // Sağ kenar
    }

    // Alt çerçeve
    for (int k = 0; k < SCREEN_WIDTH + 2; k++)
        cout << "-";
    cout << endl;
}