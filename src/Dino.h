#ifndef DINO_H
#define DINO_H

#include "C:\\raylib\\raylib\\src\\raylib.h"
#include "HP.h"
#include <vector> 
#include <cstddef>

class Dino : public HP {
public:
    Dino();
    ~Dino();
    void Draw();
    void Update();
    Rectangle GetRect();
    void DrawHitbox(bool isColliding);
    void TakeDamage(int damage);
    bool isDead();
    void ActivateInvincibility(float duration); // Activate invincibility for a certain duration
    bool IsInvincible() const; // Check if Dino is currently invincible
    Vector2 position;
private:
    std::vector<Texture2D> frames;
    int speed;

    size_t currentFrame;
    int frameCounter;
    int frameSpeed;

    bool isJumping;
    float jumpVelocity;
    float gravity;
    float initialY;

    bool isInvincible;  
    float invincibilityTime; 
    float invincibilityTimer; 
};

#endif // DINO_H
