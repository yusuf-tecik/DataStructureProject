#ifndef SHAPE_H
#define SHAPE_H

// Ödev kuralı: Başlık dosyasında sadece tanımlar olur, kod gövdesi olmaz[cite: 21].

class Shape
{
protected:
    // protected: Miras alan sınıflar (Triangle vb.) bu değişkenleri görebilsin diye private yapmadık.
    int x, y;    // Koordinatlar [cite: 9]
    int height;  // Boyutlar [cite: 9]
    char symbol; // Çizim karakteri [cite: 9]
    int z;       // Çizim önceliği (derinlik) [cite: 9]

public:
    // Kurucu Fonksiyon (Constructor)
    Shape(int x, int y, int height, char symbol, int z);

    // Yıkıcı Fonksiyon (Destructor) - Virtual olmak zorunda!
    virtual ~Shape();

    // Saf Sanal Fonksiyon (Pure Virtual Function)
    // = 0 demek: "Bu metodun gövdesi yok, türeten sınıf (Triangle vb.) bunu KENDİSİ yazmak ZORUNDA" demektir.
    virtual void draw() = 0;

    // Yardımcı Fonksiyonlar
    int getZ() const;              // Z değerini okumak için (sıralamada lazım olacak)
    void move(int newX, int newY); // Şekli hareket ettirmek için [cite: 14]
};

#endif