#ifndef SHAPE_H
#define SHAPE_H

// İleri bildirim: Screen sınıfı diye bir şey var, haberin olsun.
class Screen;

class Shape
{
protected:
    int x, y;
    int height;
    char symbol;
    int z;

public:
    Shape(int x, int y, int height, char symbol, int z);
    virtual ~Shape();

    // GÜNCELLEME: Artık çizim için Screen nesnesini alıyor
    virtual void draw(Screen *screen) = 0;

    int getZ() const;
    void move(int newX, int newY);
    int getX() const { return x; }
    int getY() const { return y; }
};

#endif