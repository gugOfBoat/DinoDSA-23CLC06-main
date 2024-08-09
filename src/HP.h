#ifndef HP_H
#define HP_H

#include "C:\\raylib\\raylib\\src\\raylib.h"

class HP {
public:
    HP(int initialHP, const char* heartImagePath);
    ~HP();
    void Draw();
    void Decrease(int amount);
    int GetCurrentHP() const;
    bool IsEmpty() const;

private:
    int maxHP;
    int currentHP;
    Texture2D heartTexture;
    Vector2 position; 
};

#endif 
