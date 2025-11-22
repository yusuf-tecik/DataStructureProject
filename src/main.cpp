#include <iostream>
#include <conio.h> // _getch() için
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include "DoubleList.h"
#include "Rectangle.h"
#include "Screen.h"

using namespace std;

// --- YARDIMCI FONKSİYONLAR ---

int randomInt(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

void initRandomData(DoubleList *mainList)
{
    int mainNodeCount = 10; // 10 tane liste satırı olsun

    for (int i = 0; i < mainNodeCount; i++)
    {
        mainList->addNode();
        int shapeCount = randomInt(3, 6); // Her satırda 3-6 şekil

        MainNode *currentMain = mainList->getHead();
        while (currentMain->next != nullptr)
            currentMain = currentMain->next;

        for (int j = 0; j < shapeCount; j++)
        {
            int x = randomInt(5, 60);
            int y = randomInt(2, 20);
            int w = randomInt(3, 6);
            int h = randomInt(3, 5);
            int z = randomInt(0, 9);
            char symbol = (char)randomInt(65, 90); // A-Z arası harfler

            currentMain->shapeList->add(new Rectangle(x, y, w, h, symbol, z));
        }
    }
}

int main()
{
    srand(time(0));
    Screen screen;
    DoubleList *mainList = new DoubleList();

    initRandomData(mainList);

    int state = 0; // 0: Liste Gezinme, 1: Şekil Düzenleme
    MainNode *selectedMainNode = mainList->getHead();
    int mainNodeIndex = 0; // Görsel olarak kaçıncı satırdayız (ok çizimi için)

    // Şekil modu için değişkenler
    ShapeNode *selectedShapeNode = nullptr;

    while (true)
    {
        screen.clear();

        // 1. Tüm şekilleri çiz
        mainList->drawAll(&screen);

        // 2. Ok İşaretini Çiz (<--)
        // Bu biraz hileli: Ekranın sol tarafına dikey listenin temsili çizimini yapıyoruz.
        // Normalde bu Shape sınıfı içinde değil, arayüzün parçasıdır.

        // 2.1 Ekranı yazdır
        screen.print();

        // 2.2. Menü ve Okları Yazdır (Konsola direkt basıyoruz)
        // İmleci yukarı taşıyamadığımız için menüyü alta yazıyoruz ama
        // Hocanın istediği sol taraftaki gösterimi burada simüle edelim:

        cout << "=================================================================" << endl;

        // Liste Görünümü Simülasyonu (Basitçe hangi düğümdeyiz)
        cout << "LISTE DURUMU:" << endl;
        MainNode *temp = mainList->getHead();
        int index = 0;
        while (temp != nullptr)
        {
            // Sadece yakın olanları yazdıralım (List çok uzunsa ekran kaymasın)
            if (index >= mainNodeIndex - 2 && index <= mainNodeIndex + 2)
            {
                cout << "Liste [" << index + 1 << "]";
                if (temp == selectedMainNode)
                    cout << "  <-- SECILI";
                cout << endl;
            }
            temp = temp->next;
            index++;
        }
        cout << "=================================================================" << endl;

        // 3. Mod Bilgileri
        if (state == 0)
        {
            cout << "MOD: ANA LISTE GEZINME" << endl;
            cout << "[W/S] Yukari/Asagi | [F] Iceri Gir | [ESC] Cikis" << endl;
        }
        else if (state == 1)
        {
            cout << "MOD: SEKIL DUZENLEME (List " << mainNodeIndex + 1 << ")" << endl;
            cout << "Secili Sekil Adresi: " << selectedShapeNode << endl;
            cout << "[Q/E] Onceki/Sonraki Sekil | [W/A/S/D] Hareket Ettir | [G] Geri Don" << endl;
        }

        // 4. Klavye Kontrolü
        char key = _getch();
        if (key == 27)
            break; // ESC

        if (state == 0) // LİSTE MODU
        {
            if (key == 's' || key == 'S')
            {
                if (selectedMainNode->next != nullptr)
                {
                    selectedMainNode = selectedMainNode->next;
                    mainNodeIndex++;
                }
            }
            else if (key == 'w' || key == 'W')
            {
                if (selectedMainNode->prev != nullptr)
                {
                    selectedMainNode = selectedMainNode->prev;
                    mainNodeIndex--;
                }
            }
            else if (key == 'f' || key == 'F')
            {
                state = 1;
                // İçeri girince ilk şekli seç
                if (selectedMainNode->shapeList->getHead() != nullptr)
                    selectedShapeNode = selectedMainNode->shapeList->getHead();
                else
                    state = 0; // Liste boşsa girme
            }
        }
        else if (state == 1) // ŞEKİL MODU
        {
            if (key == 'g' || key == 'G')
            {
                state = 0; // Geri dön
            }
            else if (key == 'e' || key == 'E') // Sonraki şekil
            {
                if (selectedShapeNode && selectedShapeNode->next)
                    selectedShapeNode = selectedShapeNode->next;
            }
            else if (key == 'q' || key == 'Q') // Önceki şekil
            {
                // Tek yönlü liste olduğu için baştan gelip öncekini bulmalıyız
                ShapeNode *curr = selectedMainNode->shapeList->getHead();
                ShapeNode *prev = nullptr;
                while (curr != nullptr && curr != selectedShapeNode)
                {
                    prev = curr;
                    curr = curr->next;
                }
                if (prev != nullptr)
                    selectedShapeNode = prev;
            }

            // Hareket Ettirme (W, A, S, D)
            // Hareket Ettirme (W, A, S, D)
            int dx = 0, dy = 0;
            if (key == 'w' || key == 'W')
                dy = -1;
            if (key == 's' || key == 'S')
                dy = 1;
            if (key == 'a' || key == 'A')
                dx = -1;
            if (key == 'd' || key == 'D')
                dx = 1;

            if ((dx != 0 || dy != 0) && selectedShapeNode != nullptr)
            {
                Shape *s = selectedShapeNode->data;
                s->move(s->getX() + dx, s->getY() + dy);
            }
        }
    }

    delete mainList;
    return 0;
}