#include "FileHandler.h"
#include <iostream>
#include <conio.h> // _getch() için
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include "DoubleList.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Star.h"
#include "Screen.h"

using namespace std;

// --- YARDIMCI FONKSİYONLAR ---

int randomInt(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

void initRandomData(DoubleList *mainList)
{
    int mainNodeCount = 10;

    for (int i = 0; i < mainNodeCount; i++)
    {
        mainList->addNode();
        int shapeCount = randomInt(2, 7);

        MainNode *currentMain = mainList->getHead();
        while (currentMain->next != nullptr)
            currentMain = currentMain->next;

        for (int j = 0; j < shapeCount; j++)
        {
            int x = randomInt(0, 70);
            int y = randomInt(0, 20);
            int w = randomInt(1, 5);
            int h = randomInt(3, 7); // Yıldız ve Üçgen için yükseklik biraz daha büyük olsun ki şekil belli olsun
            int z = randomInt(0, 15);

            char symbols[] = {'+', 'o', '#'};
            char symbol = symbols[randomInt(0, 2)];

            // Rastgele şekil seçimi (0: Dikdörtgen, 1: Üçgen, 2: Yıldız)
            int shapeType = randomInt(0, 2);

            if (shapeType == 0)
            {
                currentMain->shapeList->add(new Rectangle(x, y, w, h, symbol, z));
            }
            else if (shapeType == 1)
            {
                currentMain->shapeList->add(new Triangle(x, y, h, symbol, z));
            }
            else
            {
                // Yıldız (Star) ekle
                currentMain->shapeList->add(new Star(x, y, h, symbol, z));
            }
        }
    }
}

int main()
{
    srand(time(0));
    Screen screen;
    DoubleList *mainList = new DoubleList();

    cout << "Veri Yapilari Odev 1" << endl;
    cout << "1. Rastgele uret" << endl;
    cout << "2. Dosyadan oku" << endl;
    cout << "Seciminiz: ";

    char choice;
    cin >> choice;

    if (choice == '2')
    {
        // Dosyadan oku
        FileHandler::readFromFile(mainList, "data.txt");
        // Eğer dosya yoksa veya boşsa, listeye en az bir düğüm ekle ki patlamasın
        if (mainList->getHead() == nullptr)
        {
            cout << "Dosya bulunamadi veya bos! Rastgele uretiliyor..." << endl;
            initRandomData(mainList);
            // Bekleme yapıp yazıyı okutabilirsin ama gerek yok
        }
    }
    else
    {
        // Rastgele üret (Varsayılan)
        initRandomData(mainList);
    }

    int state = 0; // 0: Liste Gezinme, 1: Şekil Düzenleme
    MainNode *selectedMainNode = mainList->getHead();
    int mainNodeIndex = 0; // Görsel olarak kaçıncı satırdayız (ok çizimi için)

    // Şekil modu için değişkenler
    ShapeNode *selectedShapeNode = nullptr;

    while (true)
    {
        screen.clear();

        // 1. Tüm şekilleri çiz
        // 1. Sadece SEÇİLİ satırın şekillerini çiz
        if (selectedMainNode != nullptr && selectedMainNode->shapeList != nullptr)
        {
            selectedMainNode->shapeList->drawAll(&screen);
        }

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
        // --- BURADAN BAŞLA ---
        cout << "LISTE DURUMU:" << endl;
        MainNode *temp = mainList->getHead(); // temp burada tanımlanıyor
        int index = 0;                        // index burada tanımlanıyor

        while (temp != nullptr)
        {
            // Sadece yakın olanları yazdıralım
            if (index >= mainNodeIndex - 2 && index <= mainNodeIndex + 2)
            {
                cout << "Liste [" << index + 1 << "]";

                // --- İSTEDİĞİN GÜNCELLEME BURADA ---
                // "temp" değişkeni while döngüsü içinde olduğu için burada hata vermez
                if (temp->shapeList != nullptr)
                {
                    cout << " (" << temp->shapeList->getSize() << " sekil)";
                }

                if (temp == selectedMainNode)
                    cout << "  <-- SECILI";
                cout << endl;
            }
            temp = temp->next;
            index++;
        }
        // --- BURADA BİTİYOR ---
        cout << "=================================================================" << endl;

        // 3. Mod Bilgileri
        if (state == 0)
        {
            cout << "MOD: ANA LISTE GEZINME" << endl;
            cout << "[W/S] Yukari/Asagi | [F] Iceri Gir | [C] Dugumu Sil | [ESC] Cikis" << endl;
        }
        else if (state == 1)
        {
            cout << "MOD: SEKIL DUZENLEME (List " << mainNodeIndex + 1 << ")" << endl;
            cout << "Secili Sekil Adresi: " << selectedShapeNode << endl;
            cout << "[Q/E] Onceki/Sonraki Sekil | [W/A/S/D] Hareket Ettir | [C] Sekli Sil | [G] Geri Don" << endl;
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
            // ... (W ve S tuşlarından sonra) ...
            else if (key == 'c' || key == 'C')
            {
                if (selectedMainNode != nullptr)
                {
                    MainNode *toDelete = selectedMainNode;

                    // Seçimi kaydır (Önce aşağı, yoksa yukarı)
                    if (selectedMainNode->next != nullptr)
                    {
                        selectedMainNode = selectedMainNode->next;
                    }
                    else if (selectedMainNode->prev != nullptr)
                    {
                        selectedMainNode = selectedMainNode->prev;
                        mainNodeIndex--; // Yukarı kaydığı için indeksi azalt
                    }
                    else
                    {
                        // Listede tek eleman vardı ve onu siliyoruz
                        selectedMainNode = nullptr;
                    }

                    // Düğümü sil
                    mainList->removeNode(toDelete);

                    // Eğer liste tamamen boşaldıysa programı kapatabilir veya boş ekran gösterebiliriz
                    if (mainList->getHead() == nullptr)
                    {
                        // Basitlik olsun diye yeni boş bir liste oluşturabiliriz
                        // veya programın çökmemesi için kontrol ekleyebiliriz.
                        // Şimdilik boş kalsın, ekrana çizim yaparken hata vermez (head nullptr kontrolü var)
                    }
                }
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

            // ŞEKİL MODU (state == 1) İÇİNDEKİ C TUŞU BLOĞU:
            else if (key == 'c' || key == 'C') // Şekil Silme
            {
                // 1. Silinecek şekli belirle
                ShapeNode *toDelete = selectedShapeNode;

                // 2. Seçimi kaydır (Sonraki yoksa başa dön)
                if (selectedShapeNode->next != nullptr)
                    selectedShapeNode = selectedShapeNode->next;
                else
                    selectedShapeNode = selectedMainNode->shapeList->getHead();

                // Eğer tek eleman kaldıysa ve onu siliyorsak seçim nullptr olur
                if (toDelete == selectedShapeNode)
                    selectedShapeNode = nullptr;

                // 3. Şekli listeden sil
                selectedMainNode->shapeList->remove(toDelete);

                // 4. KONTROL: Eğer o satırda hiç şekil kalmadıysa SATIRI SİL ve ÇIK
                if (selectedMainNode->shapeList->getHead() == nullptr)
                {
                    state = 0; // Ana menüye dön
                    selectedShapeNode = nullptr;

                    // --- ANA DÜĞÜMÜ SİLME MANTIĞI ---
                    MainNode *nodeToDelete = selectedMainNode;

                    // Ana menüdeki seçimi de kaydır ki boşluğa düşmesin
                    if (selectedMainNode->next != nullptr)
                    {
                        selectedMainNode = selectedMainNode->next;
                    }
                    else if (selectedMainNode->prev != nullptr)
                    {
                        selectedMainNode = selectedMainNode->prev;
                        mainNodeIndex--;
                    }
                    else
                    {
                        selectedMainNode = nullptr; // Başka düğüm kalmadı
                    }

                    // Ana listeden kutuyu tamamen sil
                    mainList->removeNode(nodeToDelete);
                }
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
                s->move(dx, dy); // Doğru: Sadece değişim miktarını gönderiyoruz
            }
        }
    }

    delete mainList;
    return 0;
}