#ifndef HP_H
#define HP_H

#include "C:\\raylib\\raylib\\src\\raylib.h"

class HP {
public:
    HP(int initialHP, const char* heartImagePath);
    ~HP();
    void DrawHP();
    void Decrease(int amount);
    void Increase(int amount);
    int GetCurrentHP() const;
    bool IsEmpty() const;
    void resetHP();

private:
    int maxHP;
    int currentHP;
    Texture2D heartTexture;
    Vector2 position; 

};

#endif 
